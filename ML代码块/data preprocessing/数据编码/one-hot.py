# 数据分列（对列进行one-hot）

train_test = pd.get_dummies(train_test,columns=["Embarked"])
train_test = pd.get_dummies(train_test,columns = ['SibSp','Parch','SibSp_Parch']) 