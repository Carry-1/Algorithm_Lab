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
{
    //新生成一个结点
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
        friend IntervalTree& Interval_Insert(IntervalTree& , Interval_TNode* );
        friend IntervalTree& Interval_Insert_Fixup(IntervalTree& , Interval_TNode* );
        friend IntervalTree& left_rotate(IntervalTree&, Interval_TNode*);
        friend IntervalTree& right_rotate(IntervalTree&, Interval_TNode*);
        friend Interval_TNode* Interval_Search(IntervalTree&, Interval& );
        Interval_TNode* Nil();
        Interval_TNode* Root();
    private:
        Interval_TNode* nil; //nil结点的key为INTMIN
        Interval_TNode* root;
};

Interval_TNode* IntervalTree::Nil()
{
    return nil;
}

Interval_TNode* IntervalTree::Root()
{
    return root;
}

int max(int a, int b, int c)
{
    int result=0;
    result = max(a,b);
    return result = max(result,c);
}
IntervalTree& left_rotate(IntervalTree& T, Interval_TNode* x)
{
    Interval_TNode* y = x->right;
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
    
    //区间树与红黑树相比，节点增加了区间信息和最大端点信息max，旋转操作只需要维护max即可
    x->max = max(x->left->max, x->interval.high, x->right->max);
    y->max = max(x->max,y->interval.high, y->right->max);
    return T;
}

IntervalTree& right_rotate(IntervalTree& T, Interval_TNode* x)
{
    Interval_TNode* y = x->left;
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
        
    x->max = max(x->left->max, x->interval.high, x->right->max);
    y->max = max(x->max,y->interval.high, y->left->max);
    return T;
}

IntervalTree& Interval_Insert_Fixup(IntervalTree& T, Interval_TNode* z)
{
    while(z->p->color==red)
    {
        if(z->p==z->p->p->left)
        {
            Interval_TNode* y = z->p->p->right;
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
                Interval_TNode* y = z->p->p->left;
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

IntervalTree& Interval_Insert(IntervalTree& T, Interval_TNode* z)
{
    Interval_TNode* y = T.nil;
    Interval_TNode* x = T.root;
    while(x!=T.nil)
    {
        if(x->max<z->max)
            x->max = z->max;
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

    Interval_Insert_Fixup(T, z);
    return T;
}

bool Overlap(const Interval& interval1, const Interval& interval2)
{
    if(interval1.low>interval2.high||interval2.low>interval1.high)
        return false;
    else    
        return true;
}

Interval_TNode* Interval_Search(IntervalTree& T, Interval& i)
{
    Interval_TNode* x = T.Root();
    while(x!=T.Nil()&&!Overlap(i,x->interval))
    {
        if(x->left!=T.Nil()&&x->left->max>=i.low)
            x = x->left;
        else x= x->right;
    }
    return x;


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
 
	char *p = strtok(strs, d); //调用C库函数strtok()进行字符串分割
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
    vector<vector<int> > Input = Read();
    vector<Interval> inter;
    for(int i=1; i<=Input[0][0]; i++)
    {
        inter.push_back({Input[i][0],Input[i][1]});
    }

    IntervalTree T;
    for(int i=0; i<inter.size();i++)
    {
        Interval_TNode* p = CreatNode(inter[i]);
        Interval_Insert(T, p);
    }
    cout<<endl;
    cout<<endl;
    cout<<"please input a interval that you want to search: ";
    Interval interval1;
    cin>>interval1.low>>interval1.high;
    cout<<"the interval you just input is ["<<interval1.low<<","<<interval1.high<<"]"<<endl;
    Interval_TNode* result = Interval_Search(T, interval1);
    Interval interval2 = result->interval;
    cout<<"the interval that overlaps with  ["<<interval1.low<<","<<interval1.high<<"] is:"<<endl;
    cout<<"["<<interval2.low<<","<<interval2.high<<"]"<<endl;
     return 0;
}