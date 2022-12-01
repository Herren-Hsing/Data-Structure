#include <iostream>
using namespace std;
class ListNode
{
public:
    int data;
    ListNode *link;
    ListNode() : data(0), link(0) {}
    ListNode(int x) : data(x), link(0) {}
};
class LinkedList
{
private:
    ListNode *first;
    int num;

public:
    LinkedList()
    {
        num = 0;
        first = new ListNode(0);
    }
    ~LinkedList() //从第一个节点遍历析构
    {
        ListNode *next;
        while (first)
        {
            next = first->link;
            delete first;
            first = next;
        }
        delete first;
    }
    void Create() //尾插
    {
        ListNode *p = first;
        int x;
        while (cin >> x)
        {
            ListNode *newNode = new ListNode(x);
            p->link = newNode;
            p = newNode;
            num++;
            if (cin.get() == '\n')
            {
                break;
            }
        }
    }
    void Output()
    {
        ListNode *p = first;
        while (p)
        {
            p = p->link;
            if (p)
                cout << p->data << ' ';
        }
        cout << endl;
    }
    void Reverse() //将头节点指向nullptr，后面的节点依次插入头节点之后
    {
        ListNode *p, *q, *r;
        p = first;
        q = first->link;
        p->link = nullptr;
        while (q)
        {
            r = q->link;
            q->link = p->link;
            p->link = q;
            q = r;
        }
    }
    void DeleteDuplicates(ListNode *yFirst)
    {
        ListNode *y = yFirst->link;
        while (y && y != yFirst)
        { //遍历B的节点，比较
            ListNode *p = first, *q = first->link;
            while (q)
            {
                if (q->data == y->data) //数据相同，删除节点，继续遍历A
                {
                    p->link = q->link;
                    delete q;
                    q = p->link;
                }
                else //不相同继续遍历A
                {
                    p = q;
                    q = q->link;
                }
            }
            y = y->link;
        }
    }
    void SearchNthFromtheEnd(int n)
    {
        if (n < 1 || n > num)
        {
            cout << "ERROR" << endl;
            return;
        }
        ListNode *p = first, *q = first;
        while (n--)
        { //快指针先走n步
            p = p->link;
        }
        while (p)
        { //快指针到最后一个节点时，慢指针到达目标节点
            p = p->link;
            q = q->link;
        }
        cout << q->data;
        return;
    }
};
class CircleList // 循环链表类
{
private:
    ListNode *first;
    int num;

public:
    CircleList()
    {
        num = 0;
        first = new ListNode(0);
        first->link = first;
    }
    ~CircleList()
    {
        ListNode *p, *q;
        p = first->link;
        while (p != first)
        {
            q = p->link;
            delete p;
            p = q;
        }
        if (p == first)
            p->link = first;
        //成为只有头节点的空表
        delete first;
        //删除头节点
    }
    ListNode *getFirst()
    {
        return first;
    }
    void Create()
    {
        ListNode *p = first;
        int x;
        while (cin >> x)
        {
            ListNode *newNode = new ListNode(x);
            p->link = newNode;
            p = newNode;
            num++;
            if (cin.get() == '\n')
            {
                break;
            }
        }
        p->link = first; //尾指针指向头节点
    }
    void Output()
    {
        ListNode *p = first;
        while (p->link != first)
        {
            p = p->link;
            cout << p->data << ' ';
        }
        cout << endl;
    }
    void Reverse()
    {
        ListNode *p, *q, *r;
        p = first;
        q = first->link;
        p->link = p;
        while (q != first)
        {
            r = q->link;
            q->link = p->link;
            p->link = q;
            q = r;
        }
    }
};
int main()
{
    LinkedList x;
    CircleList y;
    cout << "Enter list A:" << endl;
    x.Create();
    cout << "Enter list B:" << endl;
    y.Create();
    cout << "Reverse the lists:" << endl;
    x.Reverse();
    y.Reverse();
    x.Output();
    y.Output();
    cout << "Delete the node with the same data as list B in list A:" << endl;
    x.DeleteDuplicates(y.getFirst());
    x.Output();
    cout << "Enter the Nth node from the end to be searched:";
    int n;
    cin >> n;
    cout << "The data of the node is:";
    x.SearchNthFromtheEnd(n);
    system("pause");
    return 0;
}