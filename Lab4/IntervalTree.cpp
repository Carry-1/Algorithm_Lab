#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

typedef bool colortype;
const colortype black = false;
const colortype red = true;
struct Interval{
    int low;
    int high;
};
typedef pair<int,vector<int> > Input;
struct Interval_TNode{   //区间树节点结构
    int key;
    Interval_TNode* left;
    Interval_TNode* right;
    Interval_TNode* p;
    colortype color; 
    Interval interval;  //区间
    int max;   //子树中区间的端点的最大值
};

Interval_TNode* CreatNode(Interval interval1)
{//新生成一个结点
    Interval_TNode* pointer = new Interval_TNode;
    pointer->key = interval1.low;
    pointer->left = nullptr;
    pointer->right = nullptr;
    pointer->p = nullptr;
    pointer->color = red;
    pointer->interval = interval1;
    pointer->max  = interval1.high;
    return pointer;
}

class IntervalTree{
    public:
        IntervalTree()
        {
            
            nil = CreatNode({INT_MIN,INT_MIN+1});    //nil节点的key为INT_MIN
            nil->color = black;
            root = nil;
        }
        friend IntervalTree& RB_Insert(IntervalTree& , Interval_TNode* );
        friend IntervalTree& RB_Insert_Fixup(IntervalTree& , Interval_TNode* );
        friend IntervalTree& left_rotate(IntervalTree&, Interval_TNode*);
        friend IntervalTree& right_rotate(IntervalTree&, Interval_TNode*);
        Interval_TNode* Nil();
        Interval_TNode* Root();
    private:
        Interval_TNode* nil; //nil结点的key为INTMIN
        Interval_TNode* root;
};