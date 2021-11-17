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

typedef pair<int,vector<int> > Input;
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
    ofstream outfile("LOT.txt");
    queue<TNode*> q;
    TNode* p;
    if(T.Root() != T.Nil())
        q.push(T.Root());
    while(q.size())
    {
        p = q.front();
        if(p==T.Nil())
            outfile<<"nil"<<endl;
        else if(p->color==red)
        {
            outfile<<p->key<<", "<<"red"<<endl;
        }
        else if(p->color==black)
        {
            outfile<<p->key<<", "<<"black"<<endl;
        }
        q.pop();
        if(p->left)
            q.push(p->left);
        if(p->right)
            q.push(p->right);
    }
}

vector<string> split(const string& str, const string& delim) //将输入字符串str按delim标志进行分割
{
    vector<string> vec_result;
	if("" == str) return vec_result; //如果要分割的串为空串，那么不进行分割

	//先将要切割的字符串从string类型转换为char*类型，之所以要这样做，是因为下面要调用的C库函数strtok的接口是这样要求的
	char * strs = new char[str.length() + 1] ; 
	strcpy(strs, str.c_str()); 
    
    //同上
	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());
 
	char *p = strtok(strs, d); //调用C库函数strok()进行字符串分割
	while(p) { 
		string s = p; //分割得到的字符串转换为string类型
		vec_result.push_back(s); //存入结果数组
		p = strtok(NULL, d); //这里之所以要这样写是因为strtok函数是多次调用的，详情见CSDN
	}
 
	return vec_result;
}

vector<vector<int> > Read(){ //读取txt文件，处理成一个vector<vector<int>>--二维整型数组
    ifstream Infile("insert.txt");
    vector<string> vec_str; //vec_str数组用于存储从data.txt文件中读取的每一行的内容--每一行的内容都是字符串
    vector<vector<string> > vec_substr; //vec_substr数组用于存储对vec数组中每一行分割过后的内容
    vector<vector<int> > vec_result;  //vec2用于存储将vec_substr中每个字符串转换为对应整数的形式
    string s; //字符串s用于存储从.txt文件中读取的每行内容
    while(getline(Infile,s)) //按行读取txt文件的内容--读取后的每行内容是字符串，存于vec_str中，
    {
        vec_str.push_back(s);
    }
    
    for(int i=0; i<vec_str.size(); i++) //对读取进来的每行原始字符串进行分割
    {
        string s;
        vec_substr.push_back({});
        vec_substr[vec_substr.size()-1] = split(vec_str[i], " "); //对vec数组的每一行按空格进行分割,原vec中每行字符串会被分割为多个字符串

    }

    for(int i=0; i<vec_substr.size(); i++) //将vec_substr中每个字符串转换为对应的整数
    {
        vec_result.push_back({});
        for(int j=0; j<vec_substr[i].size(); j++)
        {
            char * strs = new char[vec_substr[i][j].length() + 1] ;//vec1中每个元素都是string类型的，下面要调用的库函数atoi的接口要求其传入参数是C类型的字符串  
            strcpy(strs, vec_substr[i][j].c_str());
            vec_result[vec_result.size()-1].push_back(atoi(strs)); //调用库函数atoi
        }
    }
    return vec_result;
}

int main()
{


    RBTree T;
    //  vector<int> Input = {12, 1, 9, 2, 0, 11, 7};
    // // vector<int> Input = {12, 1, 9, 2, 0, 11, 7, 19, 4, 15, 18, 5, 14, 13, 10, 16, 6, 3, 8, 17};
    vector<vector<int> > In = Read();

    vector<int> Input;
    int size = In[0][0];
    for(int i=0; i<size; i++)
    {
        Input.push_back(In[1][i]);
    }

    for(int i=0; i<Input.size(); i++)
    {
        TNode* p = CreatNode(Input[i]);
        RB_Insert(T, p);
    }
    LevelOrderTraverse(T);
    return 0;
}