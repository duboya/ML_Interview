```
按区间分割-数据离散化
返回x所属区间的索引值，半开区间

```
#将年龄划分四个阶段10以下,10-18,18-30,30-50,50以上
train_test['Age'] = pd.cut(train_test['Age'], bins=[0,10,18,30,50,100],labels=[1,2,3,4,5])