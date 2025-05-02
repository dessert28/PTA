import pandas as pd
import numpy as np
from datetime import datetime, timedelta
from utils import DataProcessor
import tensorflow as tf
from sklearn.preprocessing import MinMaxScaler, StandardScaler
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import LSTM, Dense, Dropout, Bidirectional
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.callbacks import EarlyStopping, ReduceLROnPlateau
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score
import os
import matplotlib.pyplot as plt

def predict_new_follows():
    # 检查数据文件是否存在
    if not os.path.exists('附件1 (Attachment 1).csv') or not os.path.exists('附件2 (Attachment 2).csv'):
        print("错误：找不到数据文件，请确保数据文件在正确的目录中")
        return
    
    print("开始加载数据...")
    # 初始化数据处理器
    dp = DataProcessor()
    
    # 设置目标日期
    target_date = pd.to_datetime('2024-07-21')
    
    print("开始处理创作者数据...")
    # 获取所有创作者的列表
    all_creators = dp.df1['creator_id'].unique()
    
    # 准备结果存储
    results = []
    evaluation_metrics = []
    
    # 超参数设置（调整以获得最佳性能）
    sequence_length = 5
    lstm_units1 = 128
    lstm_units2 = 64
    dense_units1 = 64
    dense_units2 = 32
    dropout_rate = 0.3
    learning_rate = 0.001
    batch_size = 16
    epochs = 150
    early_stopping_patience = 15
    
    # 对每个创作者进行预测
    total_creators = len(all_creators)
    successful_models = 0
    
    for idx, creator_id in enumerate(all_creators, 1):
        if idx % 10 == 0 or idx == total_creators:
            print(f"正在处理第 {idx}/{total_creators} 个创作者... (成功率: {successful_models}/{idx})")
            
        try:
            # 获取创作者特征
            creator_features = dp.get_creator_features(target_date)
            creator_row = creator_features[creator_features['creator_id'] == creator_id]
            
            if creator_row.empty:
                print(f"创作者 {creator_id} 没有足够的特征数据")
                continue
                
            # 准备LSTM序列数据
            sequences, targets = dp.prepare_lstm_sequences(creator_id, sequence_length=sequence_length)
            
            if len(sequences) == 0:
                print(f"创作者 {creator_id} 没有足够的历史数据")
                
                # 使用特征值直接预测
                view_to_follow_rate = creator_row['view_to_follow_rate'].values[0]
                total_interactions = creator_row['action'].values[0]
                
                # 简单模型：基于历史转化率预测
                prediction = view_to_follow_rate * (total_interactions / 10)  # 假设10%的互动会在下一天发生
                
                results.append({
                    'creator_id': creator_id,
                    'predicted_follows': prediction,
                    'model_type': 'simple',
                    'trend_factor': 1.0,
                    'view_to_follow_rate': view_to_follow_rate
                })
                continue
            
            if len(sequences) < 5:  # 如果数据太少，使用简化模型
                view_to_follow_rate = creator_row['view_to_follow_rate'].values[0]
                recent_follows = np.mean(targets)
                prediction = max(recent_follows, view_to_follow_rate * 2)
                
                results.append({
                    'creator_id': creator_id,
                    'predicted_follows': prediction,
                    'model_type': 'average',
                    'trend_factor': 1.0,
                    'view_to_follow_rate': view_to_follow_rate
                })
                continue
                
            # 数据标准化
            scaler_x = StandardScaler()
            scaler_y = StandardScaler()
            
            # 重塑数据以适应标准化
            sequences_reshaped = sequences.reshape(-1, sequences.shape[-1])
            sequences_scaled = scaler_x.fit_transform(sequences_reshaped)
            sequences_scaled = sequences_scaled.reshape(sequences.shape)
            
            # 标准化目标值
            targets_reshaped = targets.reshape(-1, 1)
            targets_scaled = scaler_y.fit_transform(targets_reshaped)
            
            # 创建3折交叉验证
            k_fold = 3
            fold_size = len(sequences) // k_fold
            fold_metrics = []
            
            # 进行k折交叉验证
            for fold in range(k_fold):
                # 分割训练集和验证集
                val_start = fold * fold_size
                val_end = (fold + 1) * fold_size
                
                val_indices = list(range(val_start, min(val_end, len(sequences))))
                train_indices = list(range(0, val_start)) + list(range(val_end, len(sequences)))
                
                x_train = sequences_scaled[train_indices]
                y_train = targets_scaled[train_indices]
                x_val = sequences_scaled[val_indices]
                y_val = targets_scaled[val_indices]
                
                # 构建双向LSTM模型
                model = Sequential([
                    # 第一层双向LSTM
                    Bidirectional(LSTM(lstm_units1, return_sequences=True), 
                                input_shape=(sequences.shape[1], sequences.shape[-1])),
                    Dropout(dropout_rate),
                    # 第二层双向LSTM
                    Bidirectional(LSTM(lstm_units2)),
                    Dropout(dropout_rate),
                    Dense(dense_units1, activation='relu'),
                    Dropout(dropout_rate/2),
                    Dense(dense_units2, activation='relu'),
                    Dense(1)
                ])
                
                # 编译模型
                optimizer = Adam(learning_rate=learning_rate)
                model.compile(optimizer=optimizer, loss='mse', metrics=['mae'])
                
                # 早停和学习率调整
                callbacks = [
                    EarlyStopping(patience=early_stopping_patience, restore_best_weights=True, verbose=0),
                    ReduceLROnPlateau(factor=0.5, patience=10, min_lr=0.00001, verbose=0)
                ]
                
                # 训练模型
                history = model.fit(
                    x_train, y_train,
                    epochs=epochs, 
                    batch_size=batch_size, 
                    validation_data=(x_val, y_val),
                    callbacks=callbacks,
                    verbose=0
                )
                
                # 评估模型
                val_loss = model.evaluate(x_val, y_val, verbose=0)[0]
                
                # 预测验证集
                y_val_pred = model.predict(x_val, verbose=0)
                y_val_true = scaler_y.inverse_transform(y_val)
                y_val_pred = scaler_y.inverse_transform(y_val_pred)
                
                # 计算评估指标
                mse = mean_squared_error(y_val_true, y_val_pred)
                rmse = np.sqrt(mse)
                mae = mean_absolute_error(y_val_true, y_val_pred)
                
                # 计算R²（如果可能的话）
                try:
                    r2 = r2_score(y_val_true, y_val_pred)
                except:
                    r2 = 0
                
                # 保存评估指标
                fold_metrics.append({
                    'fold': fold,
                    'mse': mse,
                    'rmse': rmse,
                    'mae': mae,
                    'r2': r2,
                    'val_loss': val_loss
                })
            
            # 计算平均评估指标
            avg_metrics = {
                'mse': np.mean([m['mse'] for m in fold_metrics]),
                'rmse': np.mean([m['rmse'] for m in fold_metrics]),
                'mae': np.mean([m['mae'] for m in fold_metrics]),
                'r2': np.mean([m['r2'] for m in fold_metrics]),
                'val_loss': np.mean([m['val_loss'] for m in fold_metrics])
            }
            
            # 保存评估指标
            evaluation_metrics.append({
                'creator_id': creator_id,
                'mse': avg_metrics['mse'],
                'rmse': avg_metrics['rmse'],
                'mae': avg_metrics['mae'],
                'r2': avg_metrics['r2'],
                'val_loss': avg_metrics['val_loss'],
                'num_samples': len(sequences)
            })
            
            # 使用全部数据训练最终模型
            model = Sequential([
                Bidirectional(LSTM(lstm_units1, return_sequences=True), 
                            input_shape=(sequences.shape[1], sequences.shape[-1])),
                Dropout(dropout_rate),
                Bidirectional(LSTM(lstm_units2)),
                Dropout(dropout_rate),
                Dense(dense_units1, activation='relu'),
                Dropout(dropout_rate/2),
                Dense(dense_units2, activation='relu'),
                Dense(1)
            ])
            
            optimizer = Adam(learning_rate=learning_rate)
            model.compile(optimizer=optimizer, loss='mse', metrics=['mae'])
            
            history = model.fit(
                sequences_scaled, targets_scaled,
                epochs=epochs,
                batch_size=batch_size,
                validation_split=0.2,
                callbacks=callbacks,
                verbose=0
            )
            
            # 准备预测数据
            last_sequence = sequences[-1:]
            last_sequence_reshaped = last_sequence.reshape(-1, sequences.shape[-1])
            last_sequence_scaled = scaler_x.transform(last_sequence_reshaped)
            last_sequence_scaled = last_sequence_scaled.reshape(1, sequences.shape[1], sequences.shape[-1])
            
            # 预测
            prediction_scaled = model.predict(last_sequence_scaled, verbose=0)
            prediction = scaler_y.inverse_transform(prediction_scaled)[0][0]
            
            if not creator_row.empty:
                # 获取额外特征
                view_to_follow_rate = creator_row['view_to_follow_rate'].values[0]
                total_interactions = creator_row['action'].values[0]
                
                # 计算趋势因子
                recent_trend = np.mean(targets[-3:]) - np.mean(targets[-7:-3]) if len(targets) >= 7 else 0
                trend_factor = 1.2 if recent_trend > 0 else (0.8 if recent_trend < 0 else 1.0)
                
                # 平均R²作为模型权重的依据
                r2 = avg_metrics['r2']
                model_weight = 0.4
                if r2 > 0.7:  # 模型性能很好
                    model_weight = 0.7
                elif r2 < 0.3:  # 模型性能较差
                    model_weight = 0.2
                
                # 计算加权预测
                final_prediction = max(0, (
                    prediction * model_weight * trend_factor +
                    view_to_follow_rate * total_interactions * (0.6 - model_weight) +
                    np.log1p(total_interactions) * 0.2
                ))
                
                results.append({
                    'creator_id': creator_id,
                    'predicted_follows': final_prediction,
                    'model_type': 'lstm',
                    'model_loss': avg_metrics['val_loss'],
                    'trend_factor': trend_factor,
                    'view_to_follow_rate': view_to_follow_rate,
                    'model_r2': r2
                })
                
                successful_models += 1
                
        except Exception as e:
            print(f"处理创作者 {creator_id} 时出错: {str(e)}")
            continue
    
    print("\n开始生成最终预测结果...")
    
    # 保存评估指标
    eval_df = pd.DataFrame(evaluation_metrics)
    if not eval_df.empty:
        eval_df.to_csv('model_evaluation.csv', index=False)
        
        # 打印平均评估指标
        print("\n模型评估指标平均值:")
        print(f"MSE: {eval_df['mse'].mean():.4f}")
        print(f"RMSE: {eval_df['rmse'].mean():.4f}")
        print(f"MAE: {eval_df['mae'].mean():.4f}")
        print(f"R²: {eval_df['r2'].mean():.4f}")
    
    # 转换为DataFrame并排序
    results_df = pd.DataFrame(results)
    if not results_df.empty:
        # 按模型类型统计
        model_counts = results_df['model_type'].value_counts()
        print(f"\n模型类型统计:")
        for model_type, count in model_counts.items():
            print(f"{model_type}: {count}")
        
        # 根据不同模型类型应用不同权重
        results_df['weight'] = 1.0
        if 'model_loss' in results_df.columns:
            results_df.loc[results_df['model_type'] == 'lstm', 'weight'] = 1 / (1 + results_df['model_loss'])
        
        if 'model_r2' in results_df.columns:
            results_df.loc[results_df['model_type'] == 'lstm', 'weight'] *= (results_df['model_r2'] + 1) / 2
        
        results_df['weighted_prediction'] = (
            results_df['predicted_follows'] * 
            results_df['weight'] *
            results_df['trend_factor']
        )
        
        # 获取top 5
        top_5 = results_df.nlargest(5, 'weighted_prediction')
        
        # 打印结果
        print("\n问题1结果：")
        print("排名\t博主ID\t预计新增关注数")
        for i, (_, row) in enumerate(top_5.iterrows(), 1):
            print(f"{i}\t{row['creator_id']}\t{int(round(row['predicted_follows']))}")
            
        # 保存详细结果
        result_columns = ['creator_id', 'predicted_follows', 'trend_factor', 'view_to_follow_rate', 'model_type']
        if 'model_r2' in top_5.columns:
            result_columns.append('model_r2')
            
        top_5[result_columns].to_csv('problem1_results.csv', index=False)
        
        # 返回结果供后续分析
        return top_5
    else:
        print("没有足够的数据进行预测")
        return None

def plot_evaluation_metrics():
    """绘制模型评估指标分布"""
    try:
        eval_df = pd.read_csv('model_evaluation.csv')
        
        # 创建图表
        fig, axes = plt.subplots(2, 2, figsize=(12, 10))
        
        # MSE分布
        axes[0, 0].hist(eval_df['mse'], bins=20)
        axes[0, 0].set_title('MSE分布')
        axes[0, 0].set_xlabel('MSE')
        axes[0, 0].set_ylabel('频率')
        
        # RMSE分布
        axes[0, 1].hist(eval_df['rmse'], bins=20)
        axes[0, 1].set_title('RMSE分布')
        axes[0, 1].set_xlabel('RMSE')
        axes[0, 1].set_ylabel('频率')
        
        # MAE分布
        axes[1, 0].hist(eval_df['mae'], bins=20)
        axes[1, 0].set_title('MAE分布')
        axes[1, 0].set_xlabel('MAE')
        axes[1, 0].set_ylabel('频率')
        
        # R²分布
        axes[1, 1].hist(eval_df['r2'], bins=20)
        axes[1, 1].set_title('R²分布')
        axes[1, 1].set_xlabel('R²')
        axes[1, 1].set_ylabel('频率')
        
        plt.tight_layout()
        plt.savefig('model_evaluation_metrics.png')
        plt.close()
        
        print("评估指标分布图已保存为 'model_evaluation_metrics.png'")
    except Exception as e:
        print(f"绘制评估指标图表时出错: {str(e)}")

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
    
    # 运行预测
    top_5_results = predict_new_follows()
    
    # 绘制评估指标分布
    plot_evaluation_metrics() 