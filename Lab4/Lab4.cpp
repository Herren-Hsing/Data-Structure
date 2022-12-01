#include <iostream>
using namespace std;
class OutOfBounds
{
public:
    OutOfBounds() {}
};
template <class T>
class QNode
{
public:
    T data;
    QNode<T> *next;
};
template <class T>
class Queue
{
    QNode<T> *front;
    QNode<T> *rear;

public:
    Queue()
    {
        front = rear = nullptr;
    }
    ~Queue()
    {
        QNode<T> *n;
        while (front)
        {
            n = front->next;
            delete front;
            front = n;
        }
    }
    bool empty()
    {
        return (!front);
    }
    void push(T x)
    {
        QNode<T> *s = new QNode<T>();
        s->data = x;
        s->next = nullptr;
        if (front)
        {
            rear->next = s;
        }
        else
        {
            front = s;
        }
        rear = s;
    }
    T poll()
    //从队列头部获取元素
    {
        if (empty())
            throw OutOfBounds();
        T tmp = front->data;
        QNode<T> *p = front;
        front = front->next;
        delete p;
        return tmp;
    }
    void pop()
    {
        if (empty())
            throw OutOfBounds();
        QNode<T> *p = front;
        front = front->next;
        delete p;
    }
    T getFront()
    {
        if (empty())
            throw OutOfBounds();
        T tmp = front->data;
        return tmp;
    }
    T popRear()
    //从队列尾部获取元素
    {
        if (empty())
            throw OutOfBounds();
        T tmp = rear->data;
        if (rear == front)
        {
            return poll();
        }
        QNode<T> *p = front;
        while (p->next != rear && p->next)
        {
            p = p->next;
        }
        p->next = nullptr;
        rear = p;
        return tmp;
    }
};
class BinaryTree;
class BinaryTreeNode
{
    int data;
    BinaryTreeNode *left, *right;
    friend class BinaryTree;

public:
    BinaryTreeNode()
    {
        data = 0;
        left = nullptr;
        right = nullptr;
    }
    BinaryTreeNode(int x)
    {
        data = x;
        left = nullptr;
        right = nullptr;
    }
    BinaryTreeNode(int x, BinaryTreeNode *l, BinaryTreeNode *r)
    {
        data = x;
        left = l;
        right = r;
    }
};

class BinaryTree
{
private:
    BinaryTreeNode *root;
    void Remove(BinaryTreeNode *p);
    void Add(BinaryTreeNode *p, BinaryTreeNode *q);

public:
    BinaryTree() { root = new BinaryTreeNode; }
    void CreateBinaryTree(int *num, bool *b, int len);
    bool isComplete();
    int getHeight(int x);
    void OutPut();
    void toComplete();
};

void BinaryTree::CreateBinaryTree(int *num, bool *b, int len)
{
    if (b[0])
        return;
    root->data = num[0];
    Queue<BinaryTreeNode *> s;
    s.push(root);
    int i = 1;
    while (i < len && (!s.empty()))
    //层序创建
    {
        BinaryTreeNode *head = s.poll();
        if (!head)
        {
            s.push(nullptr);
            s.push(nullptr);
            i += 2;
            continue;
        }
        if (b[i]) //空节点
        {
            head->left = nullptr;
        }
        else //非空节点
        {
            head->left = new BinaryTreeNode;
            head->left->data = num[i];
        }
        s.push(head->left);
        if (++i >= len)
            break;
        if (b[i])
        {
            head->right = nullptr;
        }
        else
        {
            head->right = new BinaryTreeNode;
            head->right->data = num[i];
        }
        s.push(head->right);
        if (++i >= len)
            break;
    }
}
bool BinaryTree::isComplete() //由上到下，由左到右层序遍历，如果前面有过叶子节点，那么后面遍历到的就不能有孩子
{
    if (!root)
    {
        return true;
    }
    Queue<BinaryTreeNode *> s;
    s.push(root);
    bool preLeaf = 0; //未遇到过叶子节点
    while (!s.empty())
    {
        BinaryTreeNode *head = s.poll();
        if (head->left)
        {
            if (preLeaf)
            {
                return false;
            }
            s.push(head->left);
        }
        else
        {
            preLeaf = 1; //遇到了 叶子节点，那后面遍历到的就不能有孩子了
        }
        if (head->right)
        {
            if (preLeaf)
            {
                return false;
            }
            s.push(head->right);
        }
        else
        {
            preLeaf = 1;
        }
    }
    return true;
}
int BinaryTree::getHeight(int x)
{
    int height = 1, curNum = 1, nextNum = 0;
    // curnum是本层节点数，nextnum是下层节点数
    if (root)
    {
        Queue<BinaryTreeNode *> s;
        s.push(root);
        while (!s.empty())
        {
            BinaryTreeNode *head = s.poll();
            curNum--;
            if (head->data == x)
                break;
            //遍历到目标时，目标上面的层肯定都遍历完了
            if (head->left)
            {
                s.push(head->left);
                nextNum++;
            }
            if (head->right)
            {
                s.push(head->right);
                nextNum++;
            }
            if (!curNum)
            { //遍历完一层
                height++;
                curNum = nextNum;
                nextNum = 0;
                //变下层
            }
        }
    }
    return height;
}
void BinaryTree::OutPut()
{
    int curNum = 1, nextNum = 0;
    if (root)
    {
        Queue<BinaryTreeNode *> s;
        s.push(root);
        while (!s.empty())
        {
            BinaryTreeNode *head = s.poll();
            cout << head->data << ' ';
            curNum--;
            if (head->left)
            {
                s.push(head->left);
                nextNum++;
            }
            if (head->right)
            {
                s.push(head->right);
                nextNum++;
            }
            if (!curNum)
            { //本层的所有节点输出完毕
                cout << endl;
                curNum = nextNum;
                nextNum = 0;
            }
        }
    }
}
void BinaryTree::toComplete()
{
    Queue<BinaryTreeNode *> s;
    Queue<BinaryTreeNode *> tree;
    //先把所有节点存到队列tree中
    s.push(root);
    while (!s.empty())
    {
        BinaryTreeNode *head = s.poll();
        tree.push(head);
        if (head->left)
        {
            s.push(head->left);
        }
        if (head->right)
        {
            s.push(head->right);
        }
    }
    //接下来，按层遍历二叉树，遇到非空节点，tree队列出一个元素；遇到空节点，tree队列从尾部出一个元素，把这个节点从树中取下来，加在该位置。直到tree队列空。
    //这样二叉树前面的空缺被后面的节点补全。
    s.push(root);
    tree.poll();
    while (!tree.empty())
    {
        BinaryTreeNode *head = s.poll();
        if (!head->left) //如果该节点无左孩子
        {
            BinaryTreeNode *toDelete = tree.popRear();
            Remove(toDelete);
            Add(head, toDelete);
            //把最后的节点取下来，补过来
        }
        else
        {
            tree.poll();
        }
        s.push(head->left);
        if (tree.empty())
            break;
        if (!head->right)
        {
            BinaryTreeNode *toDelete = tree.popRear();
            Remove(toDelete);
            Add(head, toDelete);
        }
        else
        {
            tree.poll();
        }
        s.push(head->right);
    }
}
void BinaryTree::Remove(BinaryTreeNode *p)
{ //在转换的条件下，删除的节点一定没孩子
    Queue<BinaryTreeNode *> s;
    s.push(root);
    //找到删除节点的上一个节点
    BinaryTreeNode *head = new BinaryTreeNode;
    while (!s.empty())
    {
        head = s.poll();
        if (head->left == p || head->right == p)
        {
            break;
        }
        if (head->left)
        {
            s.push(head->left);
        }
        if (head->right)
        {
            s.push(head->right);
        }
    }
    if (head->left == p)
    {
        head->left = nullptr;
    }
    else
    {
        head->right = nullptr;
    }
}
void BinaryTree::Add(BinaryTreeNode *p, BinaryTreeNode *q)
{
    if (!p->left)
    {
        p->left = q;
    }
    else
    {
        p->right = q;
    }
}
int main()
{
    try
    {
        BinaryTree a;
        int num[100];
        bool symbol[100] = {0};
        int i = 0;
        char k;
        while (1)
        {
            if (!(cin >> num[i]))
            {
                cin.clear();
                cin >> k;
                symbol[i] = 1;
            }
            i++;
            if (cin.get() == '\n')
                break;
        }
        a.CreateBinaryTree(num, symbol, i);
        cout << "Whether it is a complete binary tree: ";
        cout << (a.isComplete() ? "True" : "False") << endl;
        cout << "Enter the node you want to search: ";
        int x;
        cin >> x;
        cout << "The height of the node is ";
        cout << a.getHeight(x) << endl;
        if (!a.isComplete())
        {
            cout << "Turn the binary tree to a complete one: " << endl;
            a.toComplete();
            a.OutPut();
            cout << "Whether you've successfully turned the binary tree to a complete one: ";
            cout << (a.isComplete() ? "True" : "False") << endl;
        }
    }
    catch (OutOfBounds)
    {
        cerr << "Queue is empty" << endl;
    }
    system("pause");
}