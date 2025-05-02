import pandas as pd
import numpy as np
from datetime import datetime, timedelta

class DataProcessor:
    def __init__(self):
        # 读取数据
        self.df1 = pd.read_csv('附件1 (Attachment 1).csv')
        self.df2 = pd.read_csv('附件2 (Attachment 2).csv')
        
        # 数据预处理
        self.preprocess_data()
    
    def preprocess_data(self):
        # 重命名列
        self.df1.columns = ['user_id', 'action', 'creator_id', 'timestamp']
        self.df2.columns = ['user_id', 'action', 'creator_id', 'timestamp']
        
        # 转换时间戳
        self.df1['timestamp'] = pd.to_datetime(self.df1['timestamp'])
        self.df2['timestamp'] = pd.to_datetime(self.df2['timestamp'])
        
        # 添加日期和小时列
        self.df1['date'] = self.df1['timestamp'].dt.date
        self.df1['hour'] = self.df1['timestamp'].dt.hour
        self.df2['date'] = self.df2['timestamp'].dt.date
        self.df2['hour'] = self.df2['timestamp'].dt.hour
        
        # 确认数据日期范围
        min_date = self.df1['date'].min()
        max_date = self.df1['date'].max()
        print(f"附件1数据日期范围: {min_date} 至 {max_date}")
        
        min_date2 = self.df2['date'].min()
        max_date2 = self.df2['date'].max()
        print(f"附件2数据日期范围: {min_date2} 至 {max_date2}")
        
        # 数据统计
        print(f"附件1数据量: {len(self.df1)} 条记录")
        print(f"附件2数据量: {len(self.df2)} 条记录")
        print(f"用户数量: {self.df1['user_id'].nunique()}")
        print(f"博主数量: {self.df1['creator_id'].nunique()}")
        
        # 处理隐含的观看行为
        # 如果用户对某博主有点赞、评论或关注行为，说明已经观看了内容
        self.add_implicit_views()
    
    def get_user_creator_interactions(self, start_date=None, end_date=None):
        """获取用户和创作者之间的互动数据"""
        df = self.df1.copy()
        if start_date:
            df = df[df['date'] >= start_date]
        if end_date:
            df = df[df['date'] <= end_date]
            
        interactions = df.groupby(['user_id', 'creator_id']).agg({
            'action': ['count', lambda x: (x == 1).sum(),  # 观看数
                                lambda x: (x == 2).sum(),  # 点赞数
                                lambda x: (x == 3).sum(),  # 评论数
                                lambda x: (x == 4).sum()]  # 关注数
        })
        interactions.columns = ['total_interactions', 'views', 'likes', 'comments', 'follows']
        return interactions.reset_index()
    
    def get_user_daily_activity(self, user_id):
        """获取用户的每日活动数据"""
        user_data = self.df1[self.df1['user_id'] == user_id]
        daily_activity = user_data.groupby('date').size().reset_index()
        daily_activity.columns = ['date', 'activity_count']
        return daily_activity
    
    def get_user_hourly_pattern(self, user_id):
        """获取用户的小时活动模式"""
        user_data = self.df1[self.df1['user_id'] == user_id]
        hourly_pattern = user_data.groupby('hour').size().reset_index()
        hourly_pattern.columns = ['hour', 'activity_count']
        return hourly_pattern
    
    def get_creator_popularity(self, date=None):
        """获取创作者的受欢迎程度指标"""
        df = self.df1.copy()
        if date:
            df = df[df['date'] < date.date()]
            
        creator_stats = df.groupby('creator_id').agg({
            'user_id': 'nunique',  # 独立用户数
            'action': lambda x: ((x == 2) | (x == 3)).sum()  # 互动数（点赞+评论）
        }).reset_index()
        creator_stats.columns = ['creator_id', 'unique_users', 'engagement']
        return creator_stats

    def get_recent_user_activity(self, user_id, date, days_lookback=7):
        """获取用户最近的活动数据"""
        end_date = pd.to_datetime(date)
        start_date = end_date - timedelta(days=days_lookback)
        
        user_data = self.df1[
            (self.df1['user_id'] == user_id) & 
            (self.df1['date'] >= start_date.date()) &
            (self.df1['date'] < end_date.date())
        ]
        return user_data
    
    def get_creator_growth_rate(self, days_lookback=7):
        """计算创作者的粉丝增长率"""
        end_date = self.df1['timestamp'].max()
        start_date = end_date - timedelta(days=days_lookback)
        
        recent_follows = self.df1[
            (self.df1['action'] == 4) & 
            (self.df1['timestamp'] >= start_date)
        ]
        
        growth_rate = recent_follows.groupby('creator_id').size().reset_index()
        growth_rate.columns = ['creator_id', 'new_follows']
        growth_rate['daily_growth_rate'] = growth_rate['new_follows'] / days_lookback
        return growth_rate
        
    def prepare_lstm_sequences(self, creator_id, sequence_length=7):
        """准备LSTM模型的序列数据"""
        # 获取创作者的每日数据
        creator_data = self.df1[self.df1['creator_id'] == creator_id].copy()
        
        # 计算每日的各种指标 - 分开聚合以避免嵌套索引问题
        follows = creator_data[creator_data['action'] == 4].groupby('date').size().to_frame('follows')
        views = creator_data[creator_data['action'] == 1].groupby('date').size().to_frame('views')
        likes = creator_data[creator_data['action'] == 2].groupby('date').size().to_frame('likes')
        comments = creator_data[creator_data['action'] == 3].groupby('date').size().to_frame('comments')
        total = creator_data.groupby('date').size().to_frame('total_interactions')
        unique_users = creator_data.groupby('date')['user_id'].nunique().to_frame('unique_users')
        
        # 合并所有指标
        daily_stats = pd.concat([follows, views, likes, comments, total, unique_users], axis=1)
        daily_stats = daily_stats.fillna(0)
        
        # 计算转化率特征
        daily_stats['like_rate'] = daily_stats['likes'] / daily_stats['views'].replace(0, 1)
        daily_stats['comment_rate'] = daily_stats['comments'] / daily_stats['views'].replace(0, 1)
        daily_stats['follow_rate'] = daily_stats['follows'] / daily_stats['views'].replace(0, 1)
        
        # 确保日期连续
        try:
            date_range = pd.date_range(daily_stats.index.min(), daily_stats.index.max())
            daily_stats = daily_stats.reindex(date_range).fillna(0)
        except Exception as e:
            print(f"创建日期范围时出错: {str(e)}")
            return np.array([]), np.array([])
        
        # 准备序列数据
        sequences = []
        targets = []
        
        if len(daily_stats) <= sequence_length:
            return np.array([]), np.array([])
        
        for i in range(len(daily_stats) - sequence_length):
            sequence = daily_stats.iloc[i:i+sequence_length].values
            target = daily_stats.iloc[i+sequence_length]['follows']
            sequences.append(sequence)
            targets.append(target)
        
        if len(sequences) == 0:
            return np.array([]), np.array([])
        
        return np.array(sequences), np.array(targets)

    def get_creator_features(self, date):
        """提取创作者的特征工程，使用更全面的指标"""
        df = self.df1[self.df1['date'] < date.date()].copy()
        
        # 基础特征: 计算创作者的各项指标
        creator_features = df.groupby('creator_id').agg({
            'user_id': 'nunique',  # 独立用户数
            'action': 'count',     # 总互动数
        }).reset_index()
        
        # 添加动作类型统计
        for action_type in [1, 2, 3, 4]:
            action_counts = df[df['action'] == action_type].groupby('creator_id').size()
            creator_features[f'action_{action_type}_count'] = creator_features['creator_id'].map(action_counts).fillna(0)
        
        # 计算转化率指标
        creator_features['view_to_like_rate'] = creator_features['action_2_count'] / creator_features['action_1_count'].replace(0, 1)
        creator_features['view_to_comment_rate'] = creator_features['action_3_count'] / creator_features['action_1_count'].replace(0, 1)
        creator_features['view_to_follow_rate'] = creator_features['action_4_count'] / creator_features['action_1_count'].replace(0, 1)
        creator_features['engagement_rate'] = (creator_features['action_2_count'] + creator_features['action_3_count']) / creator_features['action_1_count'].replace(0, 1)
        
        # 时间序列特征: 计算最近一段时间的增长率
        recent_period = 5  # 最近5天
        end_date = date.date() - timedelta(days=1)
        start_date = end_date - timedelta(days=recent_period)
        
        recent_df = df[(df['date'] >= start_date) & (df['date'] <= end_date)]
        
        # 计算最近一段时间的动作统计
        recent_stats = recent_df.groupby('creator_id').agg({
            'user_id': 'nunique',  # 最近的独立用户数
            'action': 'count'      # 最近的总互动数
        })
        recent_stats.columns = ['recent_unique_users', 'recent_interactions']
        
        # 合并到特征中
        creator_features = pd.merge(creator_features, recent_stats, on='creator_id', how='left')
        creator_features = creator_features.fillna(0)
        
        # 计算增长率特征
        creator_features['user_growth_rate'] = creator_features['recent_unique_users'] / creator_features['user_id'].replace(0, 1)
        creator_features['interaction_growth_rate'] = creator_features['recent_interactions'] / creator_features['action'].replace(0, 1)
        
        # 动力指标: 最近一天的活跃度相对历史平均的比率
        last_day = end_date
        last_day_df = df[df['date'] == last_day]
        
        last_day_stats = last_day_df.groupby('creator_id').agg({
            'action': 'count'  # 最后一天的互动数
        })
        last_day_stats.columns = ['last_day_interactions']
        
        # 合并到特征中
        creator_features = pd.merge(creator_features, last_day_stats, on='creator_id', how='left')
        creator_features = creator_features.fillna(0)
        
        # 计算平均每日互动数
        total_days = (df['date'].max() - df['date'].min()).days + 1
        creator_features['avg_daily_interactions'] = creator_features['action'] / total_days
        
        # 计算动力指标
        creator_features['momentum'] = creator_features['last_day_interactions'] / creator_features['avg_daily_interactions'].replace(0, 1)
        
        # 添加时段分布特征
        hour_counts = df.groupby(['creator_id', 'hour']).size().unstack(fill_value=0)
        hour_distribution = hour_counts.div(hour_counts.sum(axis=1), axis=0)
        hour_distribution.columns = [f'hour_{i}_ratio' for i in hour_distribution.columns]
        
        # 合并时段分布特征
        creator_features = pd.merge(creator_features, hour_distribution.reset_index(), on='creator_id', how='left')
        creator_features = creator_features.fillna(0)
        
        # 添加关注增长特征
        follows_df = df[df['action'] == 4]
        follows_by_day = follows_df.groupby(['creator_id', 'date']).size().unstack(fill_value=0)
        
        if not follows_by_day.empty:
            # 计算最近3天的关注增长率
            recent_follows_dates = sorted(follows_by_day.columns)[-3:]
            if len(recent_follows_dates) >= 2:
                # 计算斜率
                first_day = recent_follows_dates[0]
                last_day = recent_follows_dates[-1]
                days_diff = (last_day - first_day).days
                
                if days_diff > 0:
                    follows_first = follows_by_day[first_day]
                    follows_last = follows_by_day[last_day]
                    follows_slope = (follows_last - follows_first) / days_diff
                    
                    creator_features['follows_trend'] = creator_features['creator_id'].map(follows_slope).fillna(0)
                else:
                    creator_features['follows_trend'] = 0
            else:
                creator_features['follows_trend'] = 0
        else:
            creator_features['follows_trend'] = 0
        
        return creator_features 