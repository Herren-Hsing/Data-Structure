#include <iostream>
using namespace std;
class NoMem
{
public:
    NoMem() {}
};
class OutOfBounds
{
public:
    OutOfBounds() {}
};
template <class T>
class Stack
{
    T *stack;
    int top;
    int maxsize;

public:
    Stack()
    {
        maxsize = 99;
        top = -1;
        stack = new T[100];
    }
    Stack(int max)
    {
        maxsize = max - 1;
        top = -1;
        stack = new T[max];
    }
    bool isEmpty() { return top == -1; }
    bool isFull() { return top == maxsize; }
    void Push(T x)
    {
        if (isFull())
        {
            throw NoMem();
        }
        top++;
        stack[top] = x;
    }
    T Pop()
    {
        if (isEmpty())
        {
            throw OutOfBounds();
        }
        T x = stack[top];
        top--;
        return x;
    }
    T Top()
    {
        if (isEmpty())
            throw OutOfBounds();
        return stack[top];
    }
};
int isPrior(Stack<char> s, char x) //优先级是否高于栈顶元素
{
    if (s.isEmpty())
        return 1;
    int t = s.Top();
    if (t == '+' || t == '-')
    {
        if (x == '*' || x == '/' || x == '(')
            return 1;
        else
            return 0;
    }
    else if (t == '*' || t == '/')
    {
        if (x == '(')
            return 1; //'('高于左边任何运算符
        else
            return 0;
    }
    else if (t == '(')
    {
        if (x == ')')
        {
            return -1;
        }
        //括号匹配消除括号，单列
        return 1; //'('低于右边任何运算符
    }
    else
        return 0;
    //')'高于右边任何运算符
}
double caculate(char x, double m, double n)
{
    if (x == '+')
        return m + n;
    else if (x == '-')
        return n - m;
    else if (x == '*')
        return m * n;
    else
    {
        if (m == 0)
            throw n;
        return n / m;
    }
}
int judgeChar(char x)
{
    if (x >= '0' && x <= '9')
        return 0;
    else if (x == '+' || x == '*' || x == '/' || x == '-' || x == '(' || x == ')')
        return 1;
    else if (x == '.')
        return 2;
    else
        return 3;
}
int main()
{
    try
    {
        Stack<double> Operand; //操作数栈
        Stack<char> Operator;  //操作符栈
        char x;
        char PopOperator;
        double Operand1, Operand2, res;
        bool isNegative = 0;
        char tmp;
        cin >> x;
        while (judgeChar(x) != 3)
        //输入其他字符结束输入
        {
            if (!judgeChar(x)) //数字
            {
                double i = 10, num = 0;
                while (!judgeChar(x)) //处理多位数
                {
                    num = num * i + x - '0';
                    cin >> x;
                }
                if (x == '.') //处理小数
                {
                    cin >> x;
                    double s = 0.1;
                    while (!judgeChar(x))
                    {
                        num += s * (x - '0');
                        s *= 0.1;
                        cin >> x;
                    }
                }
                Operand.Push(num);
                if (isNegative) //如果是负数，读完操作数后，后面再赋值加一个`)`，把读到的后面的运算符先存到tmp中
                {
                    tmp = x;
                    x = ')';
                }
            }
            if (judgeChar(x) == 1) //输入运算符
            {
                if (x == '-' && Operator.isEmpty() && Operand.isEmpty())
                //如输入的表达式形如-3*4，如果读到的第一个字符是`-`，这个`-`一定是负号
                {
                    Operand.Push(0);
                    Operator.Push('(');
                    Operator.Push('-');
                    cin >> x;
                    isNegative = 1;
                }
                else
                {
                    int priority = isPrior(Operator, x);
                    if (priority == 1) //比栈顶元素优先级高，压入栈
                    {
                        Operator.Push(x);
                        cin >> x;
                        if (x == '-')
                        { //负号：紧跟在运算符（除`)`外）后的`-`符号
                            Operand.Push(0);
                            Operator.Push('(');
                            Operator.Push('-');
                            cin >> x;
                            isNegative = 1;
                        }
                    }
                    else if (!priority) //比栈顶元素优先级低：取出栈顶运算符和两个操作数，计算结果进数字栈，再与新的栈顶比较...
                    {
                        PopOperator = Operator.Pop();
                        Operand1 = Operand.Pop(), Operand2 = Operand.Pop();
                        res = caculate(PopOperator, Operand1, Operand2);
                        Operand.Push(res);
                        priority = isPrior(Operator, x);
                    }
                    else //如果输入的是右括号，如果左右括号相遇，左括号出来，右括号就不用进了
                    {
                        Operator.Pop();
                        if (isNegative) //如果这个右括号是因为负数自己赋值的
                        {
                            x = tmp; //将存的tmp赋回x，继续读入表达式
                            isNegative = 0;
                        }
                        else
                        {
                            cin >> x;
                            if (x == '-') //特殊情况：右括号后的`-`是减号
                            {
                                Operator.Push(x);
                                cin >> x;
                            }
                        }
                        if (x == '-')
                        { //负号：紧跟在运算符（除`)`外）后的`-`符号
                            Operand.Push(0);
                            Operator.Push('(');
                            Operator.Push('-');
                            cin >> x;
                            isNegative = 1;
                        }
                    }
                }
            }
        }
        while (!Operator.isEmpty()) //对两个栈剩余元素处理
        {
            PopOperator = Operator.Pop();
            Operand1 = Operand.Pop(), Operand2 = Operand.Pop();
            res = caculate(PopOperator, Operand1, Operand2);
            Operand.Push(res);
        }
        cout << Operand.Top(); //最终运算符栈空，操作数栈仅剩最终结果
    }
    catch (NoMem)
    {
        cerr << "Stack is full" << endl;
    }
    catch (OutOfBounds)
    {
        cerr << "Stack is empty" << endl;
    }
    catch (double)
    {
        cerr << "Error of dividing zero" << endl;
    }
    system("pause");
    return 0;
}