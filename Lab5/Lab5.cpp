#include <iostream>
#include <queue>
#include <stack>
using namespace std;
class SortBinaryTree;
class BinaryTreeNode
{
    int data;
    int bf;
    BinaryTreeNode *left, *right;
    friend class SortBinaryTree;

public:
    BinaryTreeNode()
    {
        data = 0;
        bf = 0;
        left = nullptr;
        right = nullptr;
    }
    BinaryTreeNode(int x)
    {
        data = x;
        bf = 0;
        left = nullptr;
        right = nullptr;
    }
    BinaryTreeNode(int x, BinaryTreeNode *l, BinaryTreeNode *r)
    {
        data = x;
        bf = 0;
        left = l;
        right = r;
    }
};
class SortBinaryTree
{
private:
    BinaryTreeNode *root;
    int getHeight(BinaryTreeNode *tmp);

public:
    SortBinaryTree() { root = nullptr; }
    void createSortBinaryTree();
    void OutPut();
    void OutPutData();
    void toAVL();
    bool isAVL();
};
// 逐点插入法构建二叉搜索树
void SortBinaryTree::createSortBinaryTree()
{
    int val;
    while (cin >> val)
    {
        if (!root)
        {
            root = new BinaryTreeNode(val);
        }
        else
        {
            BinaryTreeNode *tmp = root;
            while (tmp)
            {
                if (val == tmp->data)
                {
                    break;
                }
                else if (val > tmp->data)
                {
                    if (tmp->right)
                    {
                        tmp = tmp->right;
                    }
                    else
                    {
                        tmp->right = new BinaryTreeNode(val);
                        break;
                    }
                }
                else if (val < tmp->data)
                {
                    if (tmp->left)
                    {
                        tmp = tmp->left;
                    }
                    else
                    {
                        tmp->left = new BinaryTreeNode(val);
                        break;
                    }
                }
            }
        }
        if (cin.get() == '\n')
            break;
    }
}
//输出二叉搜索树
void SortBinaryTree::OutPut()
{
    int curNum = 1, nextNum = 0;
    if (root)
    {
        queue<BinaryTreeNode *> s;
        s.push(root);
        while (!s.empty())
        {
            BinaryTreeNode *head = s.front();
            s.pop();
            cout << head->data << '(';
            curNum--;
            if (head->left)
            {
                cout << head->left->data << ',';
                s.push(head->left);
                nextNum++;
            }
            else
            {
                cout << "#,";
            }
            if (head->right)
            {
                cout << head->right->data << ") ";
                s.push(head->right);
                nextNum++;
            }
            else
            {
                cout << "#) ";
            }
            if (!curNum)
            {
                cout << endl;
                curNum = nextNum;
                nextNum = 0;
            }
        }
    }
}
//中序输出
void SortBinaryTree::OutPutData()
{
    stack<BinaryTreeNode *> s;
    BinaryTreeNode *tmp = root;
    while (tmp || (!s.empty()))
    {
        if (tmp)
        {
            s.push(tmp);
            tmp = tmp->left;
        }
        else
        {
            tmp = s.top();
            s.pop();
            cout << tmp->data << ' ';
            tmp = tmp->right;
        }
    }
    cout << endl;
}
int SortBinaryTree::getHeight(BinaryTreeNode *tmp)
{
    int h = 0, hl = 0, hr = 0;
    if (!tmp)
        return 0;
    hl = getHeight(tmp->left);
    hr = getHeight(tmp->right);
    h = (hr > hl) ? hr : hl;
    return h + 1;
}
//判断是否为二叉平衡树
bool SortBinaryTree::isAVL()
{
    bool rightBF = 1;
    queue<BinaryTreeNode *> s;
    s.push(root);
    while (!s.empty())
    {
        BinaryTreeNode *head = s.front();
        s.pop();
        head->bf = getHeight(head->left) - getHeight(head->right);
        if (head->bf != 1 && head->bf != 0 && head->bf != -1)
            rightBF = 0;
        if (head->left)
        {
            s.push(head->left);
        }
        if (head->right)
        {
            s.push(head->right);
        }
    }
    return rightBF;
}
//转化为二叉平衡树
void SortBinaryTree::toAVL()
{
    while (!isAVL())
    {
        queue<BinaryTreeNode *> s;
        stack<BinaryTreeNode *> BadNode;
        stack<BinaryTreeNode *> BadParent;
        //建立两个栈，一个存放平衡因子异常的结点，一个存放平衡因子异常结点的父母。
        s.push(root);
        if (root->bf != 1 && root->bf != 0 && root->bf != -1)
        {
            BadNode.push(root);
            BadParent.push(nullptr);
        }
        while (!s.empty())
        {
            BinaryTreeNode *head = s.front();
            s.pop();
            if (head->left)
            {
                if (head->left->bf != 1 && head->left->bf != 0 && head->left->bf != -1)
                {
                    BadNode.push(head->left);
                    BadParent.push(head);
                }
                s.push(head->left);
            }
            if (head->right)
            {
                if (head->right->bf != 1 && head->right->bf != 0 && head->right->bf != -1)
                {
                    BadNode.push(head->right);
                    BadParent.push(head);
                }
                s.push(head->right);
            }
        }
        BinaryTreeNode *badnode = BadNode.top();
        BinaryTreeNode *badparent = BadParent.top();
        //获取两个栈栈顶元素，得到最后一个异常结点和其父母。
        if (badnode->bf > 0) //如果其平衡因子大于0，需要处理其左子树使之平衡
        {
            if (badnode->left->bf > 0) // LL
            {
                BinaryTreeNode *tmp = badnode->left->right;
                BinaryTreeNode *tmp2 = badnode->left;
                badnode->left->right = badnode;
                badnode->left = tmp;
                if (badparent)
                {
                    if (badparent->left == badnode)
                    {
                        badparent->left = tmp2;
                    }
                    else
                    {
                        badparent->right = tmp2;
                    }
                }
                else
                {
                    root = tmp2;
                }
            }
            else // LR
            {
                BinaryTreeNode *tmp = badnode->left->right->left;
                BinaryTreeNode *tmp2 = badnode->left->right->right;
                BinaryTreeNode *newRoot = badnode->left->right;
                badnode->left->right->left = badnode->left;
                badnode->left->right->right = badnode;
                badnode->left->right = tmp;
                badnode->left = tmp2;
                if (badparent)
                {
                    if (badparent->left == badnode)
                    {
                        badparent->left = newRoot;
                    }
                    else
                    {
                        badparent->right = newRoot;
                    }
                }
                else
                {
                    root = newRoot;
                }
            }
        }
        else if (badnode->bf < 0) //如果其平衡因子小于0，需要处理其右子树使之平衡
        {
            if (badnode->right->bf < 0) // RR
            {
                BinaryTreeNode *tmp = badnode->right->left;
                BinaryTreeNode *tmp2 = badnode->right;
                badnode->right->left = badnode;
                badnode->right = tmp;
                if (badparent)
                {
                    if (badparent->left == badnode)
                    {
                        badparent->left = tmp2;
                    }
                    else
                    {
                        badparent->right = tmp2;
                    }
                }
                else
                {
                    root = tmp2;
                }
            }
            else // RL
            {
                BinaryTreeNode *tmp = badnode->right->left->left;
                BinaryTreeNode *tmp2 = badnode->right->left->right;
                BinaryTreeNode *newRoot = badnode->right->left;
                badnode->right->left->left = badnode;
                badnode->right->left->right = badnode->right;
                badnode->right->left = tmp2;
                badnode->right = tmp;
                if (badparent)
                {
                    if (badparent->left == badnode)
                    {
                        badparent->left = newRoot;
                    }
                    else
                    {
                        badparent->right = newRoot;
                    }
                }
                else
                {
                    root = newRoot;
                }
            }
        }
    }
}
int main()
{
    SortBinaryTree a;
    a.createSortBinaryTree();
    cout << "BST:" << endl;
    a.OutPut();
    cout << "Data: ";
    a.OutPutData();
    cout << "Whether it is an AVL: " << (a.isAVL() ? "True" : "False") << endl;
    if (!a.isAVL())
    {
        cout << "AVL:" << endl;
        a.toAVL();
        a.OutPut();
        cout << "Whether it is an AVL: " << (a.isAVL() ? "True" : "False") << endl;
    }
    system("pause");
}