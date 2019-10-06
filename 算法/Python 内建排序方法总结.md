## Python 内建排序方法总结
### 1. 排序方法介绍
Python中有 2 个排序函数，一个是 list 内置的 `sort()` 方法，另一个是全局的 `sorted()` 方法

```python
sorted(iterable,key=None,reverse=False) 
#返回排好序的新列表,不改变对象本身,默认升序;reverse:-True降序 -False 正序对所有可迭代的对象均有效 
list.sort(key=None,reverse=False) 
#将list自身进行排序,不返回新的list对象,默认升序;reverse:-True降序 -False 正序
```

### 2 基本的列表排序

1）`list.sort()` 排序

```python
data = [5, 7, 9, 3, -6, -7, -8, -9, 3, -8]
result = data.sort()
print(data) #结果为 [-9, -8, -8, -7, -6, 3, 3, 5, 7, 9]
print(result) #结果为None
```

2）`sorted()` 排序

```python
data = [5, 7, 9, 3, -6, -7, -8, -9, 3, -8]
result = sorted(data)
print(data) #结果为 [5, 7, 9, 3, -6, -7, -8, -9, 3, -8]
print(result) #结果为 [-9, -8, -8, -7, -6, 3, 3, 5, 7, 9]
```



### 3 以 tuple 作为 list 的元素

在默认情况下 `sort` 和 `sorted` 函数接收的参数是元组时，它将会先按元组的第一个元素进行排序再按第二个元素进行排序，再按第三个、第四个…依次排序。
我们通过一个简单的例子来了解它，以下面这个list为例：

```python
data = [(1, 'B'), (1, 'A'), (2, 'A'), (0, 'B'), (0, 'a')]
```

我们通过 `sorted()` 对它进行排序

```python
data = [(1, 'B'), (1, 'A'), (2, 'A'), (0, 'B'), (0, 'a')]
result = sorted(data)
print(data) #结果为 [(1, 'B'), (1, 'A'), (2, 'A'), (0, 'B'), (0, 'a')]
print(result) #结果为 [(0, 'B'), (0, 'a'), (1, 'A'), (1, 'B'), (2, 'A')]
```

会发现排序后的结果中 `(0, 'B')` 在 `(0, 'a')` 的前面。这是因为在按元组第一个元素排好之后，将 `(0, 'B')` , `(0, 'a')`  按第二个元素进行排序了，而 `'B'` 的 ASCII 编码比 `'a'`小，所以 `(0, 'B')` 就排在 `(0, 'a')` 的前面了。

那如何想要让它排序时不分大小写呢？

这就要用到 `sort` 方法和 `sorted` 方法里的 `key` 参数了。
我们来看一下具体的实现：

```python
data = [(1, 'B'), (1, 'A'), (2, 'A'), (0, 'B'), (0, 'a')]
#利用参数key来规定排序的规则
result = sorted(data,key=lambda x:(x[0],x[1].lower()))

print(data) #结果为 [(1, 'B'), (1, 'A'), (2, 'A'), (0, 'B'), (0, 'a')]
print(result) #结果为 [(0, 'a'), (0, 'B'), (1, 'A'), (1, 'B'), (2, 'A')]
```

其中的`lambda x:(x[0],x[1].lower()`可以理解为一个匿名函数；
其功能类似于:

```python
def fun(x)
    return(x[0],x[1].lower())
```

**如果想要以字母作为第一排序规则,并且字母大小写不敏感，该怎么实现？**
这就能要运用到之前所讲到的

> 在默认情况下sort和sorted函数接收的参数是元组时，它将会先按元组的第一个元素进行排序再按第二个元素进行排序，再按第三个、第四个…依次排序。

再配合lambda返回一个自定义tuple；代码如下：

```python
data = [(1, 'B'), (1, 'A'), (2, 'A'), (0, 'B'), (0, 'a')]
#将x[1].lower()作为返回元组里的第一个元素,按照sorted的排序规律,就会先按字母排序,再按数字排序了
result = sorted(data,key=lambda x:(x[1].lower(),x[0]))

print(data) #结果为 [(1, 'B'), (1, 'A'), (2, 'A'), (0, 'B'), (0, 'a')] 
print(result) #结果为 [(0, 'a'), (1, 'A'), (2, 'A'), (0, 'B'), (1, 'B')]
```

### 4. 以 dict 作为 list 的元素

这个 `list` 里的元素是`dict` 形式,每个 `dict` 都存有`姓名`和`升高`现在想要以升高进行升序排列：

```python
data = [{'name': '张三', 'height': 175}, {'name': '李四', 'height': 165}, {'name': '王五', 'height': 185}]
#将x['height']最为返回tuple的第个一元素
result = sorted(data,key=lambda x:(x['height'],x['name']))
print(data) #结果为 
print(result)
#data   结果:[{'name': '张三', 'height': 175}, {'name': '李四', 'height': 165}, {'name': '王五', 'height': 185}]
#result 结果:[{'name': '李四', 'height': 165}, {'name': '张三', 'height': 175}, {'name': '王五', 'height': 185}]
```

### 5. 字典排序

按照 `key` 进行排序

```python
dict1 = {1:0, 2:3, 4:1}
res = sorted(dict1.items(), key=lambda d: d[0])
```

按照 `value` 进行排序

```python
dict1 = {1:0, 2:3, 4:1}
res = sorted(dict1.items(), key=lambda d: d[1])
```



## 参考文献：

[1] https://blog.csdn.net/qq_24076135/article/details/78550898

[2] https://segmentfault.com/a/1190000004959880