def remove_col_str(df):
    # remove a portion of string in a dataframe column - col_1
    df['col_1'].replace('\n', '', regex=True, inplace=True)

    # remove all the characters after &# (including &#) for column - col_1
    df['col_1'].replace(' &#.*', '', regex=True, inplace=True)



```
删除列中的字符串:

有时你可能会看到一行新的字符，或在字符串列中看到一些奇怪的符号。你可以很容易地使用 df['col_1'].replace 来处理该问题，其中「col_1」是数据帧 df 中的一列。
```
	