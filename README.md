# Calculator
Qt exercise
参考了一些utube上的Qt Tutorial.
实现的运算符有 + - * / && || !(Not） C（Clear），其中还解决了-为单目运算符负号的情况，同时拥有报错功能。
关于计算器逻辑运算的代码实现。首先判断字符数据类型是运算符还是数字，再分别压入相应的栈里，进行对应的计算，并在有逻辑错误的地方进行报错。如果是操作符（Stack<char>op)，首先判断优先级，优先级高的入栈，优先级低于栈顶操作符，则栈顶操作符出栈并进行运算；如果是操作数(Stack<int>num)，则在循环中将QString中的数值转为int型。
关于报错：
1.	除数为0时：增添if语句，判断除数是否为0，如果是，就返回-1；
2.	有多个连续的操作符时（不包括！、（、））：增添isoperator2函数，在计算压栈时，判断当前字符与下一个字符在isoperator2函数中的值是否都为真，如果是，就返回-1。其中，由于逻辑与或运算是两个字符，为了使其顺利运算，当前字符与下一个字符都为&或|的情况跳过。
3.	缺少成对的括号：设置一个全局变量qnum，每当有‘（’入栈时，num++；每当一个‘）’与‘（’相抵消时，num--；直到判断s[i]是否为等于号时判断pnum是否等于0，如果不是，则返回-1。
4.	表达式第一个字符是双目操作符：在计算压栈时，判断操作符栈是否为空，当它为空时，如果操作数栈为空并且当前字符为*/&|时返回-1，否则将当前字符入栈。
