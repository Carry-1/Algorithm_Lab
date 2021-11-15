#include <iostream>
#include <vector>
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
            nil = CreatNode(0);
            root = nil;
        }
        friend RBTree& RB_Insert(RBTree& , TNode* );
        friend RBTree& RB_Insert_Fixup(RBTree& , TNode* );
    private:
        TNode* nil; //nil结点的key为0
        TNode* root;
};

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

RBTree& RB_Insert_Fixup(RBTree& T, TNode* z)
{
    while(z->p->color==red)
    {
        if(z->p==z->p->p->left)
        {
            TNode* y = z->p->p->right;
            if(y->color==red)              //case 1
            {
                z->p->color = black;
                y->color = black;
                z->p->p->color = red;
                z = z->p->p;
            }
            else if(z == z->p->right)    //case 2
            {
                z = z->p;
                left_Rotate(T, z);
            }
            
        }

    }
}
int main()
{
    return 0;
}