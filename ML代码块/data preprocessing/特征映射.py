```
1. 顺序特征映射

```



	age_map = {val: ii for ii, val in enumerate(set(users['Age']))}
	users['Age'] = users['Age'].map(age_map)


```
2. 基于正则表达的特征映射


```


    # 读取Movie数据集
    movies_title = ['MovieID', 'Title', 'Genres']
    movies = pd.read_csv('./ml-1m/movies.dat', sep='::', header=None, names=movies_title, engine='python')
    movies_orig = movies.values
    # 将Title中的年份去掉
    pattern = re.compile(r'^(.*)\((\d+)\)$')

    title_map = {val: pattern.match(val).group(1) for ii, val in enumerate(set(movies['Title']))}
    movies['Title'] = movies['Title'].map(title_map)