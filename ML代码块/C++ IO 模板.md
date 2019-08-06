[TOC]

### 一、不需要数据行数
#### 1.1 一行，以逗号分隔
输入：

```cpp
1,2,3,4,5,66,77,88
```

想得到：
```
1 2 3 4 5 66 77 88
```
那么使用下面的代码，可以根据需要去掉不想要的代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
//#include <bits/stdc++.h>
using namespace std;

int main() {
	vector<string> stringdata;	// 如果想获得以逗号分隔的字符串
	vector<int> intdata;             // 如果想获得以逗号分隔的整数
	string oneline;
	string tmp;
	while (cin >> oneline) {
		stringstream input(oneline);
		while (getline(input, tmp, ',')) {
			stringdata.push_back(tmp);
			intdata.push_back(stoi(tmp));
		}
	}
#ifdef DEBUG	
	for (auto i : stringdata)
		cout << i << " ";
	
	cout << "\n=====\n";
	
	for (auto i : intdata)
		cout << i << " ";
#endif
	return 0;
```
可以得到下面的结果，该方法同样适用于空格分隔的情况：


但是，如果多加一行输入，会把它们全都加入到最后的结果中，所以请酌情使用

#### 1.2 一行，以空格分隔
输入：

```
11 2222 33 4 5 6
```

请使用下面的方案：
```
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
//#include <bits/stdc++.h>
using namespace std;

int main() {
	vector<string> stringdata;	// 如果想获得以逗号分隔的字符串
	vector<int> intdata;             // 如果想获得以逗号分隔的整数
	string oneline;
	string tmp;
	while (cin >> oneline) {
		stringstream input(oneline);
		while (getline(input, tmp, ' ')) {
			stringdata.push_back(tmp);
			intdata.push_back(stoi(tmp));
		}
	}
#ifdef DEBUG	
	for (auto i : stringdata)
		cout << i << " ";
	
	cout << "\n=====\n";
	
	for (auto i : intdata)
		cout << i << " ";
#endif
	return 0;
}
```
#### 1.3 多行，以逗号分隔（万能，也适用于空格分隔）
输入：

```
3,2,3,555
1,2,3,4,5
2,3,4,5,6
1,2,3
```

请使用下面的方案：
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
//#include <bits/stdc++.h>
using namespace std;

vector<int> split(const string &s, const char flag) {
	vector<int> res;
	istringstream iss(s);
	string tmp;
	while (getline(iss, tmp, flag))
		res.push_back(stoi(tmp));
	return res;
}

int main() {

	string oneline;
	vector<vector<int>> arr;
	while (getline(cin, oneline)) {
		vector<int> tmp = split(oneline, ',');
		arr.push_back(tmp);
	}
	
	cout << "===" << endl;
	
	for (auto i : arr) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
	
	return 0;
}
```
#### 1.4 多行，以空格分隔（万能，也适用于逗号分隔）
输入：

```
3 2 3 555
1 2 3 4 5
2 34 5 6
1 23
```

请使用下面的方案：

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
//#include <bits/stdc++.h>
using namespace std;

vector<int> split(const string &s, const char flag) {
	vector<int> res;
	istringstream iss(s);
	string tmp;
	while (getline(iss, tmp, flag))
		res.push_back(stoi(tmp));
	return res;
}

int main() {

	string oneline;
	vector<vector<int>> arr;
	while (getline(cin, oneline)) {
		vector<int> tmp = split(oneline, ' ');
		arr.push_back(tmp);
	}
	
	cout << "===" << endl;
	
	for (auto i : arr) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
	
	return 0;
}
```

### 二、需要数据行数
#### 2.1 行数、多行，以逗号分隔
输入：

```
3
1,2,3,4,5
2,3,4,5,6
1,2,3
```

想得到：
```
1 2 3 4 5
2 3 4 5 6
1 2 3
```

那么使用下面的方案

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
//#include <bits/stdc++.h>
using namespace std;

vector<int> split(const string &s, const char flag) {
	vector<int> res;
	istringstream iss(s);
	string tmp;
	while (getline(iss, tmp, flag))
		res.push_back(stoi(tmp));
	return res;
}

int main() {

	int n;
	cin >> n;
	vector<vector<int>> arr;
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		vector<int> res = split(s, ',');
		arr.push_back(res);
		cin.get();
	}
#ifdef DEBUG
	cout << "===" << endl;
	
	for (auto i : arr) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
#endif
	return 0;
}
```
可以得到正确的结果

在这种方法中，如果字符串之间以空格分隔，是不能得到正确结果的，如下图所示

#### 2.2 行数、多行，以空格分隔
输入：

```
5
1 2 3 4 5 6
222 333
11 22 333
34 54 76 00 99
12 21
```
请使用下面的方案：
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
//#include <bits/stdc++.h>
using namespace std;

vector<int> split(const string &s, const char flag) {
	vector<int> res;
	istringstream iss(s);
	string tmp;
	while (getline(iss, tmp, flag))
		res.push_back(stoi(tmp));
	return res;
}

int main() {

	string oneline;
	vector<vector<int>> arr;
	int n;
	cin >> n;
	cin.get();
	for (int i = 0; i < n; ++i) {
		getline(cin, oneline);
		vector<int> tmp = split(oneline, ' ');
		arr.push_back(tmp);
	}
	
	cout << "===" << endl;
	
	for (auto i : arr) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
	
	return 0;
}
```
### 三、要得到不同的数组输入
#### 3.1 输入多行，以逗号分隔，作为多个数组
输入：

```
1,2,3,4,5,6
222,333
```
请使用下面的方案：
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
//#include <bits/stdc++.h>
using namespace std;

vector<int> split(const string &s, const char flag) {
	vector<int> res;
	istringstream iss(s);
	string tmp;
	while (getline(iss, tmp, flag))
		res.push_back(stoi(tmp));
	return res;
}

int main() {

	string oneline;
	cin >> oneline;
	vector<int> A = split(oneline, ',');
	cin >> oneline;
	vector<int> B = split(oneline, ',');


	cout << "===" << endl;
	cout << "vector A : ";
	for (auto i : A)
		cout << i << " ";
	
	cout << endl;
	
	cout << "vector B : ";
	for (auto i : B)
		cout << i << " ";
	return 0;
}
```
#### 3.2 输入多行，以空格分隔，作为多个数组
输入：

```
1 2 3 4 5 6
222 333
1
2
```
请使用下面的方案：

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
//#include <bits/stdc++.h>
using namespace std;

vector<int> split(const string &s, const char flag) {
	vector<int> res;
	istringstream iss(s);
	string tmp;
	while (getline(iss, tmp, flag))
		res.push_back(stoi(tmp));
	return res;
}

int main() {

	string oneline;
	getline(cin, oneline);
	vector<int> A = split(oneline, ' ');
	getline(cin, oneline);
	vector<int> B = split(oneline, ' ');


	cout << "===" << endl;
	cout << "vector A : ";
	for (auto i : A)
		cout << i << " ";
	
	cout << endl;
	
	cout << "vector B : ";
	for (auto i : B)
		cout << i << " ";
	return 0;
}
```