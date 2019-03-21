```
1. Replace the missing data of column by mean

```


# Importing the datasets
dataset = pd.read_csv('Data.csv')

# Creating the matrix of features. In the imported dataset Country, Age, Salary are independent variables
X = dataset.iloc[:, :-1].values

# Creating the dependent variable
y = dataset.iloc[:, 3].values
...
# Taking care of missing data
from sklearn.preprocessing import Imputer

# Creating the object of Imputer class
imputer = Imputer(missing_values = 'NaN', strategy = 'mean', axis = 0)

# fit imputer object to data X (Matrix of feature X)
imputer = imputer.fit(X[:, 1:3]) 

# Replace the missing data of column by mean
X[:, 1:3] = imputer.transform(X[:, 1:3])



```
2. drop nan

```


# eliminating rows with missing data
print(df.dropna())

# eliminating columns with missing data
to_drop_col = ['Edition Statement',
            'Corporate Author',
            'Corporate Contributors',
            'Former owner',
            'Engraver',
            'Contributors',
            'Issuance type',
            'Shelfmarks']

df.drop(to_drop_col, inplace=True, axis=1)

# Alternatively, we could also remove the columns by passing them to the columns parameter 
# directly instead of separately specifying the labels to be removed and the axis where Pandas should look for the labels:

df.drop(columns=to_drop, inplace=True)



# eliminating columns where all values as NaN
print(df.dropna(how='all'))

# eliminating rows that have atleast 4 non-NaN values
print(df.dropna(thresh=4))


```
3. convert special character to nan.

```

# dataset has '?' in it, convert these into NaN
df = df.replace('?', np.nan)


```
4. 根据数据是否缺失进行处理

```

train_test.loc[train_test["Age"].isnull() ,"age_nan"] = 1
train_test.loc[train_test["Age"].notnull() ,"age_nan"] = 0