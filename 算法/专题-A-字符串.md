# 专题-字符串

## Index

- [模式匹配 TODO](https://github.com/imhuay/Algorithm_Interview_Notes-Chinese/blob/master/C-%E7%AE%97%E6%B3%95/%E4%B8%93%E9%A2%98-A-%E5%AD%97%E7%AC%A6%E4%B8%B2.md#%E6%A8%A1%E5%BC%8F%E5%8C%B9%E9%85%8D-todo)
- 进制转换
  - [10进制转任意进制](https://github.com/imhuay/Algorithm_Interview_Notes-Chinese/blob/master/C-%E7%AE%97%E6%B3%95/%E4%B8%93%E9%A2%98-A-%E5%AD%97%E7%AC%A6%E4%B8%B2.md#10%E8%BF%9B%E5%88%B6%E8%BD%AC%E4%BB%BB%E6%84%8F%E8%BF%9B%E5%88%B6)
  - [任意进制转10进制](https://github.com/imhuay/Algorithm_Interview_Notes-Chinese/blob/master/C-%E7%AE%97%E6%B3%95/%E4%B8%93%E9%A2%98-A-%E5%AD%97%E7%AC%A6%E4%B8%B2.md#%E4%BB%BB%E6%84%8F%E8%BF%9B%E5%88%B6%E8%BD%AC10%E8%BF%9B%E5%88%B6)
  - [长地址转短地址](https://github.com/imhuay/Algorithm_Interview_Notes-Chinese/blob/master/C-%E7%AE%97%E6%B3%95/%E4%B8%93%E9%A2%98-A-%E5%AD%97%E7%AC%A6%E4%B8%B2.md#%E9%95%BF%E5%9C%B0%E5%9D%80%E8%BD%AC%E7%9F%AD%E5%9C%B0%E5%9D%80)
- 功能函数
  - [`atoi()`](https://github.com/imhuay/Algorithm_Interview_Notes-Chinese/blob/master/C-%E7%AE%97%E6%B3%95/%E4%B8%93%E9%A2%98-A-%E5%AD%97%E7%AC%A6%E4%B8%B2.md#atoi)
- 表达式转化（中缀，后缀，前缀）
  - [中缀转后缀](https://github.com/imhuay/Algorithm_Interview_Notes-Chinese/blob/master/C-%E7%AE%97%E6%B3%95/%E4%B8%93%E9%A2%98-A-%E5%AD%97%E7%AC%A6%E4%B8%B2.md#%E4%B8%AD%E7%BC%80%E8%BD%AC%E5%90%8E%E7%BC%80)

## 模式匹配 TODO

**模式匹配基本方法**

> [字符串模式匹配算法——BM、Horspool、Sunday、KMP、KR、AC算法 - 单车博客园](https://www.cnblogs.com/dancheblog/p/3517338.html) - 博客园

- 双指针
- KMP
- ...

## 进制转换

### 10进制转任意进制

```
from string import digits, ascii_uppercase, ascii_lowercase

Alphabet = digits + ascii_lowercase + ascii_uppercase
print(Alphabet)  # "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
```

**递归方法**

```
def ten2any(n, b=62):
    """"""
    assert b <= 62

    n, index = divmod(n, b)  # n = n // b, index = n % b
    if n > 0:
        return ten2any(n, b) + Alphabet[index]
    else:
        return Alphabet[index]
```

**迭代方法**

```
def ten2any_2(n, b=62):
    """"""
    ret = ""
    while n > 0:
        n, index = divmod(n, b)
        ret = Alphabet[index] + ret

    return ret
```

### 任意进制转10进制

**迭代方法**

```
from string import digits, ascii_uppercase, ascii_lowercase

Alphabet = digits + ascii_lowercase + ascii_uppercase
print(Alphabet)  # "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

def any2ten(s, base=62):
    """"""
    n = 0
    for i, c in enumerate(reversed(s)):  # reversed(s)
        index = Alphabet.index(c)
        n += index * pow(base, i)

    return n
```

### 长地址转短地址

> [短 URL 系统是怎么设计的？](https://www.zhihu.com/question/29270034/answer/46446911) - 知乎

**基本思路**

- 发号策略：给每一个收录的长地址，分配一个自增索引
- 将分配的索引转换为一个 62 进制数（10数字+26大写字母+26小写字母）
- **注意**，发号机制不会判断是否重复

**重复长地址怎么处理？**

- 如果要求相同的长地址要对应唯一的短地址，那么唯一的方法就是维护一个映射表

- 但是维护一个映射表可能比忽略重复需要更多的空间

- 一个

  折衷

  的方法是——维护一个“最近”的长对短映射，比如采用一小时过期的机制来实现 LRU 淘汰

  - 当一个地址被频繁使用，那么它始终在这个 key-value 表中，总能返回当初生成那个短地址
  - 如果它使用并不频繁，那么长对短的 key 会过期，LRU 机制就会自动淘汰掉它

**如何保证发号器的大并发高可用？**

- 如果做成分布式的，那么多节点要保持同步加 1，多点同时写入，以 CAP 理论看，很难做到

- 一个简单的处理方式是，使用多个发号器，以

  奇偶

  /

  尾数

  区分

  - 比如一个发单号，一个发双号；
  - 或者实现 1000 个发号器，分别发尾号为 0 到 999 的号；每发一个号，每个发号器加 1000，而不是加 1

## 功能函数

### `atoi()`

**功能简述**

- 将字符串（C风格）转换成整型；
- 会跳过前面的空格字符，直到遇上数字或正负号才开始转换；
- 如果遇到的第一个字符不是数字，则返回 0，并结束转化；
- 当遇到**非数字**或**结束符**('\0') 时结束转化，并将结果返回（整型）
- 如果发生溢出，则输出 INT_MAX 或 INT_MIN;
- 内置 atoi 不会处理 NULL 指针

**合法样例**：

```
"123"           -> 123
"+123"          -> 123
"-123"          -> -123
"123abc"        -> 123
"   123abc"     -> 123
"a123"          -> 0
```

**核心代码（C++）**

```cpp
while (*p >= '0' && *p <= '9') {
    ret = ret * 10 + (*p - '0');
    p++;
}
```

- 除了核心代码，更重要的是**异常处理**和**溢出判断**

**完整代码**

```cpp
int atoi_my(const char* const cs) {
    if (cs == nullptr) return 0;

    int ret = 0;
    auto *p = cs;  // cs 为常指针

    // 跳过前面的空格
    while (isspace(*p)) p++;

    // 判断正负
    int sign = 1;   // 默认正数
    if (*p == '-') sign = -1;
    if (*p == '-' || *p == '+') p++;

    // 核心代码：循环转换整数（加入溢出判断）
    int tmp;  // 保存临时结果，用于溢出判断
    while (*p >= '0' && *p <= '9') {
        tmp = ret * 10 + (*p - '0');
        if (tmp / 10 != ret) {  // 溢出判断
            return sign > 0 ? INT_MAX : INT_MIN;
        }
        ret = tmp;
        p++;
    }
    // 核心代码（无溢出判断）
    //while (*p >= '0' && *p <= '9') {
    //    ret = ret * 10 + (*p - '0');
    //    p++;
    //}

    return sign * ret;
}
```

## 表达式转化（中缀，后缀，前缀）

> [前缀、中缀、后缀表达式](https://blog.csdn.net/antineutrino/article/details/6763722) - CSDN博客

**为什么要把中缀表达式转化为后缀，前缀？**

- 计算机无法直接计算带有括号，以及区分优先级的表达式，或者说很难计算。
- 使用后缀，前缀，消除了括号和优先级。

**如何计算后缀，前缀表达式？**

- 手工求法：

  > [中缀表达式与前、后缀表达式转化简单的技巧[转\] - Hslim](https://www.cnblogs.com/Hslim/p/5008460.html) - 博客园

  - 示例：`a+b*c-(d+e)`

  - 第一步：按照运算符的优先级对所有的运算单位加括号

    ```
    ((a+(b*c))-(d+e))
    ```

  - 第二步：转换前缀与后缀表达式

    ```
    后缀：把运算符号移动到对应的括号后面
          ((a(bc)* )+ (de)+ )-
      把括号去掉：
          abc*+de+- 
    前缀：把运算符号移动到对应的括号前面
          -( +(a *(bc)) +(de))
      把括号去掉：
          -+a*bc+de
    ```

- 计算机方法

  ：

  - [中缀转后缀](https://github.com/imhuay/Algorithm_Interview_Notes-Chinese/blob/master/C-%E7%AE%97%E6%B3%95/%E4%B8%93%E9%A2%98-A-%E5%AD%97%E7%AC%A6%E4%B8%B2.md#%E4%B8%AD%E7%BC%80%E8%BD%AC%E5%90%8E%E7%BC%80)

### 中缀转后缀

**思路**

- 从左到右遍历中缀表达式，遇到操作数则输出；遇到操作符，若当前操作符的优先级大于

  栈顶操作符优先级，进栈；否则，弹出栈顶操作符，当前操作符进栈。（这只是一段比较

  粗糙的描述，更多细节请参考链接或下面的源码）

  > [中、前、后缀表达式](https://blog.csdn.net/lin74love/article/details/65631935) - CSDN博客

**C++**（未测试）

```cpp
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <set>
using namespace std;

//set<char> l1{ '+', '-' };
//set<char> l2{ '*', '/' };
//
//vector<set<char>> l{ l1, l2 };

int get_level(char c) {
    switch (c) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    //case '(':
    //    return 3;
    default:
        return -1;
    }
}

string infix2suffix(const string& s) {
    stack<char> tmp;        // 符号栈
    queue<string> ans;      // 必须使用 string 队列，因为可能存在多位数字
    //stringstream ret;       // 用字符流模拟队列

    bool num_flag = false;      // 用于判断数字的末尾 
                                //初始设为 false 是为了避免第一个字符是括号
    //int v = 0;            // 保存数值
    string v{ "" };         // 用字符串保存更好，这样还能支持字母形式的表达式
    for (auto c : s) {
        // 处理数字
        if (isalnum(c)) {           // 处理多位数字
            v.append(string(1, c)); // 注意，char 字符不能直接转 string
            num_flag = true;
        }
        else {
            if (num_flag) {     // 因为可能存在多位数字，所以数字需要等遇到第一个非数字字符才入队
                ans.push(v);
                //ret << v << ' ';
                v.clear();
                num_flag = false;
            }

            // 处理运算符的过程
            if (c == ')') {  // 如果遇到右括号，则依次弹出栈顶符号，直到遇到**第一个**左括号并弹出（坑点 1：可能存在连续的左括号）
                while (!tmp.empty()) {
                    if (tmp.top() == '(') {
                        tmp.pop();
                        break;
                    }
                    ans.push(string(1, tmp.top()));
                    //ret << tmp.top() << ' ';
                    tmp.pop();
                }
            } // 注意这两个判断的顺序（坑点 2：右括号是始终不用入栈的，所以应该先处理右括号）
            else if (tmp.empty() || tmp.top() == '(' || c == '(') {  // 如果符号栈为空，或栈顶为 ')'，或遇到左括号
                tmp.push(c);                                         // 则将该运算符入栈
            }
            else {
                while (!tmp.empty() && get_level(tmp.top()) >= get_level(c)) {  // 如果栈顶元素的优先级大于等于当前运算符，则弹出
                    if (tmp.top() == '(')  // （坑点 3：左括号的优先级是大于普通运算符的，但它不应该在这里弹出）
                        break;
                    ans.push(string(1, tmp.top()));
                    //ret << tmp.top() << ' ';
                    tmp.pop();
                }
                tmp.push(c);
            }
        }
    }

    if (num_flag) {             // 表达式的最后一个数字入栈
        ans.push(v);
        //ret << v << ' ';
    }

    while (!tmp.empty()) {      // 字符串处理完后，依次弹出栈中的运算符
        if (tmp.top() == '(')   // 这个判断好像是多余的
            tmp.pop();
        ans.push(string(1, tmp.top()));
        //ret << tmp.top() << ' ';
        tmp.pop();
    }

    //return ret.str();

    stringstream ret;
    while (!ans.empty()) {
        ret << ans.front() << ' ';
        ans.pop();
    }
    return ret.str();
}

void solve() {
    // 只测试了以下样例，如果有反例请告诉我

    cout << infix2suffix("12+(((23)+3)*4)-5") << endl;  // 12 23 3 + 4 * + 5 -
    cout << infix2suffix("1+1+1") << endl;              // 1 1 + 1 +
    cout << infix2suffix("(1+1+1)") << endl;            // 1 1 + 1 +
    cout << infix2suffix("1+(2-3)*4+10/5") << endl;     // 1 2 3 - 4 * + 10 5 / +
    cout << infix2suffix("az-(b+c/d)*e") << endl;       // az b c d / + e * -
}
```



补一个 C++ 版本代码：

```cpp
#include <iostream>
#include <stack>
#include <string>
using namespace std;

/**
 *判断当前字符是否为数字
 */
bool isNumber(char s) {
    string opers = "+-*/()";
    for (int i = 0; i < opers.length(); i++) {
        if (s == opers.at(i)) {
            return false;
        }
    }
    return true;
}

/**
 * 判断当前运算符与栈顶运算符的优先级大小
 */
bool isPriorityLow(char currOper, char topOper) {
    if (currOper == '+' || currOper == '-') {
        if (topOper == '*' || topOper == '/' || topOper == '+' || topOper == '-') {
            return true;
        }
    }

    if (currOper == '*' || currOper == '/') {
        if (topOper == '*' || topOper == '/') {
            return true;
        }
    }

    return false;
}

/**
 * 如果当前运算符优先级小于或等于栈顶运算符, 将栈顶运算符弹出加到后缀表达式尾,
 * 并继续进行比较, 直到当前运算符优先级大于栈顶运算符优先级
 */
void loopPushOperator(string& s, char oper, stack<char>& operators) {
    if (operators.size() > 0 && isPriorityLow(oper, operators.top())) {
        s += operators.top();
        operators.pop();
        loopPushOperator(s, oper, operators);
    }
}

/**
 * 判断运算符是压入运算符栈还是加到后缀表达式尾
 */
void handleOperator(string& s, char oper,  stack<char>& operators) {
    switch (oper) {
    case '+':
    case '-':
    case '*':
    case '/':
        //如果运算符栈为空, 直接将当前运算符压栈
        if (operators.size() <= 0) {
            operators.push(oper);
        //如果当前运算符优先级小于等于栈顶运算符优先级, 将栈顶运算符加到后缀表达式尾
        } else if (isPriorityLow(oper, operators.top())) {
            loopPushOperator(s, oper, operators);
            operators.push(oper);
        ///如果当前运算符优先级大于栈顶运算符优先级, 将当前运算符压栈
        } else {
            operators.push(oper);
        }
        break;
    case '(':
        operators.push(oper);  //当前运算符为'('直接压栈
        break;
    case ')':
        //将栈中元素弹出加到后缀表达式尾,直到遇到运算符"("
        while (operators.top() != '(') {
            s += operators.top();
            operators.pop();
        }
        operators.pop();
        break;
    default:
        break;
    }
}

/**
 * 中缀表达式转后缀表达式
 */
string infixToSuffix(string& s) {
    stack<char> operators;     //运算符栈
    string suffix;                        //后缀表达式

    for (int i = 0; i < s.length(); i++) {
        if (isNumber(s.at(i))) {   //如果是数字直接加到后缀表达式尾
            suffix += s.at(i);
        } else {
            handleOperator(suffix, s.at(i), operators);  //处理运算符
        }
    }

    if (suffix.length() > 0) {
        while (operators.size() > 0) {  //将运算符栈中留有的运算符全部出栈加到后缀表达式尾
            suffix += operators.top();
            operators.pop();
        }
        return suffix;
    } else {
        return "";
    }
}

/**
 * 根据运算符,计算栈顶两个数的值,并将计算的值压栈
 */
void CalculateResult( char oper, stack<int>& tmpStack) {
    if (tmpStack.size() < 2) {
        return;
    }
    //栈是先进后出,所以先弹出的是第二个值
    int secondVal = tmpStack.top();
    tmpStack.pop();
    int firstVal = tmpStack.top();
    tmpStack.pop();

    int result = 0;
    switch (oper) {
    case '+':
        result = firstVal + secondVal;
        break;
    case '-':
        result = firstVal - secondVal;
        break;
    case '*':
        result = firstVal * secondVal;
        break;
    case '/':
        result = firstVal / secondVal;
        break;
    default:
        break;
    }

    tmpStack.push(result);
}

/**
 * 通过后缀表达式计算结果
 * 将后缀表达式依次入栈, 如果为操作符, 弹出栈中两个元素计算结果再压入栈中
 */
float getResultUseSuffix(string& s) {
    if (s.length() <= 0) {
        return 0;
    }

    stack<int> tmpStack;
    for (int i = 0; i < s.length(); i++) {
        if (isNumber(s.at(i))) {
            tmpStack.push(s.at(i) - '0');
        } else {
            CalculateResult(s.at(i), tmpStack);
        }
    }
    return tmpStack.top();
}

int main() {
    string infix;
    //输入的字符串不能有空格
    cin>>infix;
    string suffix = infixToSuffix(infix);
    float result = getResultUseSuffix(suffix);
    cout<<"计算结果为: "<<result<<endl;
    return 0;
}

```

最后补一个 Python 版本代码：



如何来具体计算一个后缀表达式：首先我们先建立一个栈，从左到右读这个表达式，如果读到操作数就将它压入栈中，如果读到N元操作符，则从栈顶自上而下的取出N元操作数来进行运算，然后再将运算结构代替原栈顶的N项中，压入栈顶。如果后缀表达式没有读完则重复上面的操作。

在计算机中如何实现中缀表达式转换为后缀表达式的算法思想: 
1.建立一个堆栈开始扫描。 
2.当读取到是操作数的时候，加入后缀表达式。 
3.当读取到一个操作符的时候: 
    a.如果是”(“，则入栈； 
    b.如果是一个”)”,则依次把栈中的运算符加入到后缀表达式中，直到出现”(“,从栈中删除“（”。 
    c.若为除开括号之外的其他操作符，首先我们要考虑算符优先级，当其优先级高于除“(”意外的栈顶运算符时，直接入栈。否则从栈顶开始，依次弹出比当前处理的算符优先级高和优先级相等的操作符，知道一个比他优先级低或者遇到了一个左括号为止。 
下面附上如何使用Python来实现简单的中缀表达式转后缀表达式的方法。我们这里定义了一个栈（将列表作为基础数据结构），同时给这个栈实现了push,peek,pop,empty的方法。 
push方法用于讲操作数，操作符压入堆栈。 
peek方法查看当前的栈顶元素。 
pop方法弹出栈顶元素，并且放回当前值。 
empty方法判断栈是否为空。





```python
class Stack(object):
    '''
    stack
            这里是基于列表的栈（将列表作为基础数据结构）
    push 往里面放
    peek 查看栈顶元素
    pop 弹出栈顶元素，并返回这个方法的返回值
    empty 判断栈是否为空
    ***效率优化 栈长度保留
    '''
    def __init__(self):
        self.datas = []
        self.length = 0
        print '初始化完成'

    #===========================================================================
    # put向栈顶插入一个元素
    #@param data: 要插入的元素没有返回值
    #===========================================================================
    def push(self,data):
        self.datas.append(data)
        self.length += 1

    #===========================================================================
    # peek查看栈顶元素
    #@return 栈顶元素
    #===========================================================================
    def peek(self):
        return None if self.empty() else self.datas[len(self.datas) - 1]

    #===========================================================================
    # pop 弹出栈顶元素
    #===========================================================================
    def pop(self):
        try:
            return self.peek()
        finally:
            self.length -= 1
            del self.datas[len(self.datas) - 1]

    def empty(self):
        #return not bool(self.datas)
        return not bool(self.length)

    def __str__(self):
        print '-----------------------str called----------------------'
        return ','.join([str(data) for data in self.datas])


if __name__ == '__main__':
    stack = Stack()
    stack.push('(')
    stack.push('abc')
    stack.push(1 + 2J)
    stack.push(1.2)
    print '%s' % stack
    print str(stack.peek())

    print '%s' % stack
    print str(stack.pop())

    print '%s' % stack
    print str(stack.pop())

    print '%s' % stack
    print stack.empty()
    print str(stack.pop())

    print '%s' % stack
    print stack.empty()
    print str(stack.pop())

    print '%s' % stack
    print stack.empty()
```



相关的注释我觉得在代码里面写的够详细了，在这里我们做了一个优化。在初始化的时候我们设置了一个栈长度self.length = 0，在我们插入栈顶元素的时候就为其自加，这样的话当我们判断栈是否为空的时候就非常好判断了。有一点不好的地方就是当反复的对栈进行插入和弹出操作的时候其实这样是相当消耗时间的。当然对于我们这个算法暂时可以不用去考虑这些。定义好栈了之后我们想着要如何来实现算法操作了。




```python

import re,stack

SUPPORT_SIGN = {'(': 99, '*': 3, '/': 3, '-': 1, '+': 1}
NUMBER_PATTERN = re.compile('\d') #\d匹配数字

sign_stack = None
number_stack = None

#===============================================================================
# init 初始化符号栈和数字栈
#在局部名称空间中，要使用全局名称空间中定义的变量，首先要使用关键字global 声明一下
#===============================================================================
def init():
    global sign_stack
    global number_stack
    sign_stack = stack.Stack()
    number_stack = stack.Stack()
#===============================================================================
# to_suffix 将中缀表达式转换成后缀表达式的形式
#@return: 方便操作返回一个列表，列表里面的元素要么是个操作数要么是个操作符
#===============================================================================
def to_suffix(expression):
    #check type
    result = []
    pre_char = None #定义之前接收的一个字符
    if not isinstance(expression, str):
        raise TypeError, '表达式类型错误'
    for char in expression:
        if char in SUPPORT_SIGN:
            pre_sign = sign_stack.peek()
            while pre_sign and SUPPORT_SIGN[char] <= SUPPORT_SIGN[pre_sign]:
                if pre_sign == '(':
                    break
                result.append(sign_stack.pop())
                pre_sign = sign_stack.peek()
            sign_stack.push(char)
        elif char == ')':
            pre_sign = sign_stack.peek()
            while pre_sign != '(':
                pre_sign = sign_stack.pop()
                result.append(pre_sign)#追加到result里面
                pre_sign = sign_stack.peek()
            sign_stack.pop()#左括号直接弹掉
        elif NUMBER_PATTERN.match(char):
            if pre_char and NUMBER_PATTERN.match(pre_char): #判断pre_char是否存在，同时上一个字符也是数字
                result[len(result - 1)] += char #拿到最后一个元素
            else:
                result.append(char)
        else:
            raise TypeError, '不支持的符号'
        pre_char = char
    while not sign_stack.empty():
        result.append(sign_stack.pop())
    return result 
#===============================================================================
# count 接口独立 调用后缀表达式
#在前面方法当中转换使用的是符号栈，现在计算的时候使用数字栈
#当前涉及的符号只有双目运算符
#===============================================================================
def count(suffix):
    #check type
    if not isinstance(suffix,list):
        raise TypeError, '表达式类型错误'
    for element in suffix:#eval得到的是int类型的值所以不能做字符串链接
        if element in SUPPORT_SIGN:
            number1 = number_stack.pop()
            number2 = number_stack.pop()
            eval_str = number2 + element + number1
            number_stack.push(str(eval(eval_str)))  #eval动态求值，用工厂函数转换
        else:
            try:
                number_stack.push(element)
            except TypeError, e:
                print '后缀表达式中有不支持的字符'
                exit()
    return number_stack
def parse(expression):
    return count(to_suffix(expression))

if __name__ == '__main__':
    init()
    print to_suffix('3+2*5*(1+2*3-4/(5-6))')
    print count(to_suffix('3+2*5*(1+2*3-4/(5-6))'))

```

