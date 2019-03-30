# Python IO 模板

在笔试时，有时候用Python进行数据处理比C++要方便很多，但是如何能够顺利地读入数据呢？如果使用input()，那么输入时不能有空格分割，这不是我们想要的。 
比如我们需要一次读取一行，可以使用sys.stdin.

```
for line in sys.stdin
    #operate(line)
    #print(line)
```
这样可以一次读取一整行。 
也可以这样做：
```
while True:
    line = sys.stdin.readline()
    #operate(line)
    #print(line)
    if line == ''
        break
```
还有，如果在输出时，print 的换行很不好用的话，可以使用sys.stdout.write()，这样容易控制整个输出。





```python
def test():
    N = int(input())
    inputlist = []
    area = 0
    for i in range(N):
        line = input()
        line_res = rule(line)
        print(line_res)
```

