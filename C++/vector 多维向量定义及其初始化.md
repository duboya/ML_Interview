# vector 多维向量定义及其初始化

## 1. 一维 vector

```cpp
vector<int> vector_1D_1;//只定义向量
vector<int> vector_1D_2(n);//定义的同时初始化大小
vector<int> vector_1D_3(n,m);//定义的同时初始化大小为n,元素初始值为m
vector<int> vector_1D_4;
vector_1D_4=vector<int>(n,m);//先定义变量，再初始化大小和初值
```

由此看出，关键看有没有使用“（）”，从而使用构造函数。

## 2. 二维 vector

```cpp
vector<vector<int> > vector_2D_1;
vector<vector<int> > vector_2D_2(n);//仅指定第一维大小
vector<vector<int> > vector_2D_3(n,vector<int>(m));//指定维度为n*m
vector<vector<int> > vector_2D_4(n,vector<int>(m,x));//指定维度为n*m并初始化初值为x
vector<vector<int> > vector_2D_5(n,vector_1D_3);//使用已知向量来初始化，第二维大小和vector_1D_3一样
```

## 3. 三维 vector

```cpp
vector< vector< vector<int> > > vector_3D_1;
vector< vector< vector<int> > > vector_3D_2(n);//仅指定第一维大小
vector< vector< vector<int> > > vector_3D_3(n,vector<vector<int>>(m,vector<int>(y)));//初始化维度大小为n*m*y.
vector< vector< vector<int> > > vector_3D_4(n,vector<vector<int>>(m,vector<int>(y，x)));//初始化维度大小为n*m*y,全部初始值为x。
vector< vector< vector<int> > > vector_3D_5(n，vector_2D_4）//使用已知向量来初始化，除了第一维是n，其他维度和已知向量相同，所以已知向量维度应该是比当前向量维度少一。
```

## 4. 四维 vector

```cpp
vector<vector<vector<vector<int>>>>  vector_4D_1;
vector<vector<vector<vector<int>>>>  vector_4D_2(n,vector<vector<vector<int>>>(m,vector< vector<int>>(x,vector<int>(y))));//初始化维度大小为n*m*x*y
vector<vector<vector<vector<int>>>>  vector_4D_3(n,vector<vector<vector<int>>>(m,vector< vector<int>>(x,vector<int>(y，z))));//初始化维度大小为n*m*x*y，初值为z。
vector<vector<vector<vector<int>>>>  vector_4D_4(n，vector_3D_4）;//使用已知向量来初始化
```

