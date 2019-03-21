def remove_col_white_space(df):
    # remove white space at the beginning of string 
    df[col] = df[col].str.lstrip()
	
```
删除列中的空格:

当数据十分混乱时，很多意想不到的情况都会发生。在字符串的开头有一些空格是很常见的。因此，当你想要删除列中字符串开头的空格时，这种方法很实用。
```