```
1. 转换时间戳（从字符串类型转换为日期「DateTime」格式）：

在处理时间序列数据时，你可能会遇到字符串格式的时间戳列。这意味着我们可能不得不将字符串格式的数据转换为根据我们的需求指定的日期「datetime」格式，以便使用这些数据进行有意义的分析和展示。
```


def convert_str_datetime(df): 
    '''
    AIM    -> Convert datetime(String) to datetime(format we want)

    INPUT  -> df

    OUTPUT -> updated df with new datetime format 
    ------
    '''
    df.insert(loc=2, column='timestamp', value=pd.to_datetime(df.transdate, format='%Y-%m-%d %H:%M:%S.%f'))


```
2. 将 object 类型时间戳转换成日期「DateTime」格式：

```


def convert_obj_datetime(X_df): 
    '''
    AIM    -> Convert datetime(object) to datetime(format we want)

    INPUT  -> df

    OUTPUT -> updated df with new datetime format 
    ------
    '''

	#So date doesn't get dropped in next step
	X_df['date_recorded'] = pd.to_datetime(X_df['date_recorded'])
	X_df['YearMonth'] = X_df['date_recorded'].map(lambda x: 100*x.year + x.month)
	X_df['Year'] = X_df['date_recorded'].map(lambda x: x.year)
	X_df['Month'] = X_df['date_recorded'].map(lambda x: x.month)