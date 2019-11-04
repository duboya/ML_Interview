不少网络笔试不像 LeetCode 帮你完成 I/O，需要手动完成；个人深受其痛，现将常用的 IO 模板总结与此，分别总结了 C/C++ 和 Python 代码


### 1. 输入不说明有多少个 Input，以 EOF 为结束标志

**C**

```c
    int a, b;
    // scanf 返回值为变量的个数，如果没有返回 -1，EOF 是一个预定义的常量 -1
    while (scanf("%d %d", &a, &b) != EOF) {  
        // ...
    }
```
**C++**

```cpp
    int a, b;
    while (cin >> a >> b) {
        // ...
    }
```
### 2. 输入不说明有多少个 Input，以某个特殊输入为结束标志

**C**
```c
    // 示例 1
    int a, b;
    while (scanf("%d %d", &a, &b) != EOF && (a != 0 && b != 0)) {
        // ...
    }
    
    // 或者
    while (scanf("%d %d", &a, &b) != EOF && (a || b)) {
        // ...
    }
    
    // 示例 2
    int n;
    while (scanf("%d", &n) != EOF && n != 0) {
        // ...
    }
```
**C++**
```cpp
    // 示例 1
    int a, b;
    while (cin >> a >> b) {
        if (a == 0 && b == 0)
            break;
        // ...
    }
    
    // 示例 2
    int n;
    while (cin >> n && n != 0) {
        // ...
    }
```
### 3. 指示有 N 个 Input

**C**
```c
    int n;
    scanf("%d", &n);
    
    int a, b;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a, &b);
        // ...
    }
```

**C++**
```cpp
    int n;
    cin >> n;
    
    int a, b;
    while(n--) {
        cin >> a >> b;
    }
```

**Python3**
```py
n = int(input())
for _ in range(n):
    # ...
```




### 4. 指示有 N 组输入，并以某个特殊输入退出

**C/C++**
```cpp
    int n;
    while (cin >> n && n != 0) {
        int a, b;
        for (int i = 0; i < n; i++) {
            cin >> a >> b;
            // ...
        }
    }
```
### 5. 输入是一整行（包括空格）

**用 char[] 接收（C/C++）**
```cpp
    const int MAXN = 1000;
    char buff[MAXN];
    
    // C
    gets(buff);
    puts(buff); // 输出
    
    // C++
    cin.getline(buff, MAXN);  // 第三个参数默认是 '\n'
    cin.getline(buff, MAXN, '\n');
```
**用 string 接收（C++）**
```cpp
    string s;
    getline(cin, s);          // 第三个参数默认是 '\n'
    getline(cin, s, '\n');
```
### 6. 输入是多行（包括空格）

**C++**
```cpp
    int n;
    cin >> n;
    cin.get();  // 否则，n 也会计入下面的 getline()，导致少一组数据
    
    while (n--) {
        string s;
        getline(cin, s);
    }
```
### 7. 从文件读取

**C**
```c
    FILE *cfin = fopen("in.txt", "r");
    FILE *cfout = fopen("out.txt", "w");
    
    int a, b;
    // 注意要传入文件指针
    while (fscanf(cfin, "%d %d", &a, &b) != EOF) { // 类似的，把 scanf 替换成 fscanf
        fprintf(cfout, "%d\n", a + b);             // 把 printf 替换为 fprintf
    }
    
    fclose(cfin);
    fclose(cfout);
```
**C++**
```cpp
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    
    int a, b;
    while (fin >> a >> b) {
        fout << a + b << endl;
    }
    
    fin.close();
    fout.close();

```
### 8. **Python IO 模板**

在笔试时，有时候用 Python 进行数据处理比 C++ 要方便很多，但是如何能够顺利地读入数据呢？如果使用input()，那么输入时不能有空格分割，这不是我们想要的。 比如我们需要一次读取一行，可以使用sys.stdin.
```py
    for line in sys.stdin
        #operate(line)
        #print(line)
```
这样可以一次读取一整行。 也可以这样做：
```py
    while True:
        line = sys.stdin.readline()
        #operate(line)
        #print(line)
        if line == ''
            break
```
还有，如果在输出时，print 的换行很不好用的话，可以使用sys.stdout.write()，这样容易控制整个输出。

```py
    def test():
        N = int(input())
        inputlist = []
        area = 0
        for i in range(N):
            line = input()
            line_res = rule(line)
            print(line_res)
```


## 参考文献
[1] [Python IO 模板](https://github.com/duboya/ML_Interview/blob/master/ML%E4%BB%A3%E7%A0%81%E5%9D%97/Python%20IO%20%E6%A8%A1%E6%9D%BF.md)
[2] [备忘-IO 模板](https://github.com/linxid/Interview_Notes-Chinese/blob/master/%E7%AE%97%E6%B3%95/%E5%A4%87%E5%BF%98-IO%E6%A8%A1%E6%9D%BF.md)