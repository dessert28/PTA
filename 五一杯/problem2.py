import pandas as pd
import numpy as np
from datetime import datetime, timedelta
from utils import DataProcessor
import tensorflow as tf
from sklearn.preprocessing import MinMaxScaler, StandardScaler
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import LSTM, Dense, Dropout, Bidirectional
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.callbacks import EarlyStopping
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score
from sklearn.ensemble import RandomForestClassifier, GradientBoostingClassifier
from sklearn.model_selection import cross_val_score
import os

def predict_new_follows():
    # 检查数据文件是否存在
    if not os.path.exists('附件1 (Attachment 1).csv') or not os.path.exists('附件2 (Attachment 2).csv'):
        print("错误：找不到数据文件，请确保数据文件在正确的目录中")
        return
    
    print("开始加载数据...")
    # 初始化数据处理器
    dp = DataProcessor()
    
    # 目标用户列表
    target_users = ['U7', 'U6749', 'U5769', 'U14990', 'U52010']
    
    # 目标日期
    target_date = pd.to_datetime('2024-07-22')
    
    # 获取7月22日的行为数据
    july_22_data = dp.df2.copy()
    
    print("开始预测用户关注行为...")
    # 记录结果
    results = {}
    model_performance = {}
    
    # 创建训练数据集
    # 查找用户之前的关注模式
    print("准备训练数据...")
    train_features = []
    train_labels = []
    
    # 获取附件1中的所有用户和博主对
    all_user_creator_pairs = []
    for _, row in dp.df1.iterrows():
        user_id = row['user_id']
        creator_id = row['creator_id']
        action = row['action']
        date = row['date']
        
        all_user_creator_pairs.append((user_id, creator_id, action, date))
    
    # 为每个用户-博主对创建特征
    for user_id, creator_id, action, date in all_user_creator_pairs:
        # 只关注用户关注博主的情况
        if action == 4:
            # 获取该用户在此日期前的所有行为
            past_actions = dp.df1[
                (dp.df1['user_id'] == user_id) & 
                (dp.df1['creator_id'] == creator_id) & 
                (dp.df1['date'] < date)
            ]
            
            if len(past_actions) > 0:
                # 计算特征
                views = len(past_actions[past_actions['action'] == 1])
                likes = len(past_actions[past_actions['action'] == 2])
                comments = len(past_actions[past_actions['action'] == 3])
                
                # 获取创作者特征
                creator_stats = dp.get_creator_features(pd.to_datetime(date))
                creator_row = creator_stats[creator_stats['creator_id'] == creator_id]
                
                if not creator_row.empty:
                    # 创作者特征
                    view_to_follow_rate = creator_row['view_to_follow_rate'].values[0]
                    view_to_like_rate = creator_row['view_to_like_rate'].values[0]
                    view_to_comment_rate = creator_row['view_to_comment_rate'].values[0]
                    total_interactions = creator_row['action'].values[0]
                    unique_users = creator_row['user_id'].values[0]
                    
                    # 添加用户-创作者交互特征
                    feature_vector = [
                        views, likes, comments,
                        view_to_follow_rate, view_to_like_rate, view_to_comment_rate,
                        total_interactions, unique_users
                    ]
                    
                    train_features.append(feature_vector)
                    train_labels.append(1)  # 用户关注了
                    
                    # 为模型添加一些负例（用户没有关注的博主）
                    # 获取用户互动过但没有关注的博主
                    not_followed = dp.df1[
                        (dp.df1['user_id'] == user_id) & 
                        (dp.df1['action'] != 4) & 
                        (dp.df1['date'] < date)
                    ]['creator_id'].unique()
                    
                    not_followed = set(not_followed) - {creator_id}
                    
                    # 最多添加5个负例
                    for neg_creator in list(not_followed)[:5]:
                        neg_past_actions = dp.df1[
                            (dp.df1['user_id'] == user_id) & 
                            (dp.df1['creator_id'] == neg_creator) & 
                            (dp.df1['date'] < date)
                        ]
                        
                        neg_views = len(neg_past_actions[neg_past_actions['action'] == 1])
                        neg_likes = len(neg_past_actions[neg_past_actions['action'] == 2])
                        neg_comments = len(neg_past_actions[neg_past_actions['action'] == 3])
                        
                        # 获取创作者特征
                        neg_creator_row = creator_stats[creator_stats['creator_id'] == neg_creator]
                        
                        if not neg_creator_row.empty:
                            # 创作者特征
                            neg_view_to_follow_rate = neg_creator_row['view_to_follow_rate'].values[0]
                            neg_view_to_like_rate = neg_creator_row['view_to_like_rate'].values[0]
                            neg_view_to_comment_rate = neg_creator_row['view_to_comment_rate'].values[0]
                            neg_total_interactions = neg_creator_row['action'].values[0]
                            neg_unique_users = neg_creator_row['user_id'].values[0]
                            
                            neg_feature_vector = [
                                neg_views, neg_likes, neg_comments,
                                neg_view_to_follow_rate, neg_view_to_like_rate, neg_view_to_comment_rate,
                                neg_total_interactions, neg_unique_users
                            ]
                            
                            train_features.append(neg_feature_vector)
                            train_labels.append(0)  # 用户没有关注
    
    # 检查是否有足够的训练数据
    if len(train_features) < 10:
        print("警告：训练数据不足，将使用基于规则的方法")
        has_training_data = False
    else:
        print(f"训练数据集大小: {len(train_features)} 样本，正例比例: {sum(train_labels)/len(train_labels):.2f}")
        has_training_data = True
        
        # 训练随机森林分类器
        X = np.array(train_features)
        y = np.array(train_labels)
        
        # 标准化特征
        scaler = StandardScaler()
        X_scaled = scaler.fit_transform(X)
        
        # 训练多个模型并选择最佳模型
        models = {
            'RandomForest': RandomForestClassifier(n_estimators=100, random_state=42),
            'GradientBoosting': GradientBoostingClassifier(n_estimators=100, random_state=42)
        }
        
        best_model_name = None
        best_f1 = 0
        
        for name, model in models.items():
            # 交叉验证
            f1_scores = cross_val_score(model, X_scaled, y, cv=5, scoring='f1')
            avg_f1 = np.mean(f1_scores)
            
            print(f"模型 {name} 交叉验证 F1分数: {avg_f1:.4f}")
            
            if avg_f1 > best_f1:
                best_f1 = avg_f1
                best_model_name = name
        
        print(f"选择最佳模型: {best_model_name} (F1: {best_f1:.4f})")
        
        # 使用最佳模型训练
        best_model = models[best_model_name]
        best_model.fit(X_scaled, y)
    
    # 对每个目标用户进行预测
    for user_id in target_users:
        print(f"处理用户 {user_id}...")
        try:
            # 获取用户的历史互动数据
            historical_interactions = dp.get_user_creator_interactions(
                end_date=pd.to_datetime('2024-07-21').date()
            )
            historical_interactions = historical_interactions[historical_interactions['user_id'] == user_id]
            
            # 获取用户在7月22日的行为数据
            user_july_22 = july_22_data[july_22_data['user_id'] == user_id]
            
            if user_july_22.empty:
                print(f"用户 {user_id} 在7月22日没有行为数据")
                continue
            
            # 获取用户已经关注的博主列表
            already_followed = set(historical_interactions[historical_interactions['follows'] > 0]['creator_id'])
            
            # 获取用户在7月22日与之互动的博主
            july_22_creators = set(user_july_22['creator_id'])
            
            # 找出未关注但有互动的博主
            potential_follows = july_22_creators - already_followed
            
            if not potential_follows:
                print(f"用户 {user_id} 在7月22日没有潜在的新关注博主")
                continue
            
            # 为每个潜在的博主创建特征
            follow_predictions = []
            
            for creator_id in potential_follows:
                try:
                    # 获取用户对该博主的互动数据
                    creator_interactions = user_july_22[user_july_22['creator_id'] == creator_id]
                    
                    # 计算互动特征
                    views = creator_interactions[creator_interactions['action'] == 1].shape[0]
                    likes = creator_interactions[creator_interactions['action'] == 2].shape[0]
                    comments = creator_interactions[creator_interactions['action'] == 3].shape[0]
                    
                    # 如果有训练数据，使用模型预测
                    if has_training_data:
                        # 获取创作者特征
                        creator_stats = dp.get_creator_features(target_date)
                        creator_row = creator_stats[creator_stats['creator_id'] == creator_id]
                        
                        if not creator_row.empty:
                            # 创作者特征
                            view_to_follow_rate = creator_row['view_to_follow_rate'].values[0]
                            view_to_like_rate = creator_row['view_to_like_rate'].values[0]
                            view_to_comment_rate = creator_row['view_to_comment_rate'].values[0]
                            total_interactions = creator_row['action'].values[0]
                            unique_users = creator_row['user_id'].values[0]
                            
                            # 构建特征向量
                            feature_vector = np.array([
                                views, likes, comments,
                                view_to_follow_rate, view_to_like_rate, view_to_comment_rate,
                                total_interactions, unique_users
                            ]).reshape(1, -1)
                            
                            # 标准化特征
                            feature_vector_scaled = scaler.transform(feature_vector)
                            
                            # 预测关注概率
                            follow_prob = best_model.predict_proba(feature_vector_scaled)[0][1]
                            
                            if follow_prob > 0.6:  # 阈值可调整
                                follow_predictions.append((creator_id, follow_prob))
                                print(f"预测用户 {user_id} 会关注博主 {creator_id}，关注概率: {follow_prob:.2f}")
                    else:
                        # 使用规则模型，基于经验阈值
                        follow_prob = 0
                        if comments > 0:
                            follow_prob += 0.5
                        if likes > 0:
                            follow_prob += 0.3
                        if views > 1:  # 多次观看
                            follow_prob += 0.2
                            
                        # 获取博主的整体特征
                        creator_features = dp.get_creator_features(target_date)
                        creator_row = creator_features[creator_features['creator_id'] == creator_id]
                        
                        if not creator_row.empty:
                            # 获取博主的受欢迎度特征
                            view_to_follow_rate = creator_row['view_to_follow_rate'].values[0]
                            unique_users = creator_row['user_id'].values[0]
                            
                            # 增加流行度特征权重
                            follow_prob += min(0.3, view_to_follow_rate) + min(0.2, np.log1p(unique_users) / 10)
                        
                        # 查看用户的历史关注行为模式
                        user_follow_pattern = historical_interactions[historical_interactions['follows'] > 0]
                        
                        # 如果用户历史上经常关注他互动过的博主
                        if len(user_follow_pattern) > 0:
                            follow_rate = len(user_follow_pattern) / len(historical_interactions)
                            follow_prob += min(0.3, follow_rate)
                        
                        # 如果概率大于阈值，预测关注
                        if follow_prob > 0.7:  # 调整阈值
                            follow_predictions.append((creator_id, follow_prob))
                            print(f"预测用户 {user_id} 会关注博主 {creator_id}，关注概率: {follow_prob:.2f}")
                
                except Exception as e:
                    print(f"预测用户 {user_id} 对博主 {creator_id} 的关注概率时出错: {str(e)}")
                    continue
            
            if follow_predictions:
                # 按概率排序
                follow_predictions.sort(key=lambda x: x[1], reverse=True)
                results[user_id] = [pred[0] for pred in follow_predictions]
        
        except Exception as e:
            print(f"处理用户 {user_id} 时出错: {str(e)}")
            continue
    
    # 打印结果
    print("\n问题2结果：")
    print("用户ID\t新关注博主ID")
    for user_id in target_users:
        if user_id in results and results[user_id]:
            print(f"{user_id}\t{', '.join(map(str, results[user_id]))}")
        else:
            print(f"{user_id}\t-")
    
    # 保存结果到CSV
    result_rows = []
    for user_id in target_users:
        if user_id in results and results[user_id]:
            for creator_id in results[user_id]:
                result_rows.append({'user_id': user_id, 'creator_id': creator_id})
    
    result_df = pd.DataFrame(result_rows)
    if not result_df.empty:
        result_df.to_csv('problem2_results.csv', index=False)
    
    return results

# 模型评估函数
def evaluate_model(y_true, y_pred):
    """计算模型评估指标"""
    accuracy = accuracy_score(y_true, y_pred)
    precision = precision_score(y_true, y_pred, zero_division=0)
    recall = recall_score(y_true, y_pred, zero_division=0)
    f1 = f1_score(y_true, y_pred, zero_division=0)
    
    print(f"准确率 (Accuracy): {accuracy:.4f}")
    print(f"精确率 (Precision): {precision:.4f}")
    print(f"召回率 (Recall): {recall:.4f}")
    print(f"F1值 (F1-score): {f1:.4f}")
    
    return {
        'accuracy': accuracy,
        'precision': precision,
        'recall': recall,
        'f1': f1
    }

if __name__ == "__main__":
    # 设置随机种子以确保结果可重现
    np.random.seed(42)
    tf.random.set_seed(42)
    
    # 设置GPU内存增长
    gpus = tf.config.experimental.list_physical_devices('GPU')
    if gpus:
        try:
            for gpu in gpus:
                tf.config.experimental.set_memory_growth(gpu, True)
        except RuntimeError as e:
            print(e)
    
    # 预测结果
    results = predict_new_follows()
    
    # 这里可以添加验证集的评估（如果有真实标签）
    # evaluate_model(y_true, y_pred) 