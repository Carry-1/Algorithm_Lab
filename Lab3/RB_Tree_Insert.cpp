#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef bool colortype;
const colortype black = false;
const colortype red = true;
struct TNode{
    int key;
    TNode* left;
    TNode* right;
    TNode* p;
    colortype color; 
};

TNode* CreatNode(int k)
{//新生成一个结点
    TNode* pointer = new TNode;
    pointer->key = k;
    pointer->left = nullptr;
    pointer->right = nullptr;
    pointer->p = nullptr;
    pointer->color = red;
    return pointer;
}
class RBTree{
    public:
        RBTree()
        {
            nil = CreatNode(-1);    //nil节点的key为-1
            nil->color = black;
            root = nil;
        }
        friend RBTree& RB_Insert(RBTree& , TNode* );
        friend RBTree& RB_Insert_Fixup(RBTree& , TNode* );
        friend RBTree& left_rotate(RBTree&, TNode*);
        friend RBTree& right_rotate(RBTree&, TNode*);
        TNode* Nil();
        TNode* Root();
    private:
        TNode* nil; //nil结点的key为0
        TNode* root;
};

TNode* RBTree::Nil()
{
    return nil;
}

TNode* RBTree::Root()
{
    return root;
}

RBTree& left_rotate(RBTree& T, TNode* x)
{
    TNode* y = x->right;
    x->right = y->left;
    if(y->left != T.nil)
        y->left->p = x;
    y->p = x->p;
    if(x->p==T.nil)
        T.root = y;
    else if(x==x->p->left)
        x->p->left = y;
    else 
        x->p->right = y;
    y->left = x;
    x->p = y;

    return T;
}

RBTree& right_rotate(RBTree& T, TNode* x)
{
    TNode* y = x->left;
    x->left = y->right;
    if(y->right != T.nil)
        y->right->p = x;
    y->p = x->p;
    if(x->p==T.nil)
        T.root = y;
    else if(x==x->p->left)
        x->p->left = y;
    else 
        x->p->right = y;
    y->right = x;
    x->p = y;

    return T;
}

RBTree& RB_Insert_Fixup(RBTree& T, TNode* z)
{
    while(z->p->color==red)
    {
        if(z->p==z->p->p->left)
        {
            TNode* y = z->p->p->right;
            if(y->color==red)              //case 1
            {
                z->p->color = black;  //case 1
                y->color = black;  //case 1
                z->p->p->color = red;  //case 1
                z = z->p->p;   //case 1
            }
            else
            {
                    if(z==z->p->right) //case 2
                    {
                        z = z->p;  //case 2
                        left_rotate(T, z);   //case 2
                    }
                    z->p->color = black;    //case 3
                    z->p->p->color = red;  //case 3
                    right_rotate(T, z->p->p);   //case 3  
            }
            
        }
        else{
                TNode* y = z->p->p->left;
            if(y->color==red)              //case 4
            {
                z->p->color = black;//case 4
                y->color = black;//case 4
                z->p->p->color = red;//case 4
                z = z->p->p;//case 4
            }
            else
            {
                    if(z==z->p->left) //case 5
                    {
                        z = z->p; //case 5
                        right_rotate(T, z); //case 5
                    }
                    z->p->color = black;    //case 6
                    z->p->p->color = red;  //case 6
                    left_rotate(T, z->p->p);    //case 6  
            }
        }

    }
    T.root->color = black;
    return T;
}

RBTree& RB_Insert(RBTree& T, TNode* z)
{
    TNode* y = T.nil;
    TNode* x = T.root;
    while(x!=T.nil)
    {
        y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if(y==T.nil)
        T.root = z;
    else if(z->key < y->key)
        y->left = z;
    else 
        y->right = z;
    z->left = T.nil;
    z->right =T.nil;
    z->color = red;

    RB_Insert_Fixup(T, z);

    return T;
}
void LevelOrderTraverse(RBTree& T)
{
    queue<TNode*> q;
    TNode* p;
    if(T.Root() != T.Nil())
        q.push(T.Root());
    while(q.size())
    {
        p = q.front();
        cout<<p->key<<" ";
        q.pop();
        if(p->left&&p->left!=T.Nil())
            q.push(p->left);
        if(p->right&&p->right!=T.Nil())
            q.push(p->right);
    }
}
int main()
{
    RBTree T;
    vector<int> Input = {12, 1, 9, 2, 0, 11, 7};
    // vector<int> Input = {12, 1, 9, 2, 0, 11, 7, 19, 4, 15, 18, 5, 14, 13, 10, 16, 6, 3, 8, 17};
    for(int i=0; i<Input.size(); i++)
    {
        TNode* p = CreatNode(Input[i]);
        RB_Insert(T, p);
    }
    LevelOrderTraverse(T);
    return 0;
}