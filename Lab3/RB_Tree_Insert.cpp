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

TNode* CreatNode(int key)
{
    
}
class RBTree{
    public:
        RBTree()
        {

        }
        
    private:
        TNode nil;
        TNode root;
};
int main()
{
    return 0;
}