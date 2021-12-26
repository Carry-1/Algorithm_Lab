#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
#include<map>
#include<unordered_map>

#include<queue>
#include<cmath>

using namespace std;

struct HuffmanNode{
    int weight;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode* parent;
    char character; 
    
};

class ComparePointer
{
public:
 
    // 重载括号操作符，自定义实现比较操作，示例如下：
    bool operator () (const HuffmanNode* left, const HuffmanNode* right) const
    {
        if (nullptr == left)
            return true;
        else
            return (left->weight > right->weight);
    }
};

typedef priority_queue<HuffmanNode*, vector<HuffmanNode*>, ComparePointer> Priority_Queue;

HuffmanNode* CreateHuffmanNode(int weight)
{
        HuffmanNode* p = new HuffmanNode;
        p->left = nullptr;
        p->right = nullptr;
        p->weight = weight;
        p->parent = nullptr;
        return p;
}
HuffmanNode* BuildHuffmanTree(Priority_Queue& pq)
{
    HuffmanNode* p;
    HuffmanNode* root;
    int n = pq.size();
    for(int i=0; i<n-1; i++)
    {
        HuffmanNode* x = pq.top();
        pq.pop();
        HuffmanNode* y = pq.top();
        pq.pop();
        p = CreateHuffmanNode(x->weight+y->weight);
        p->character = '0';
        p->left = x;
        p->right = y;
        x->parent = p;
        y->parent = p;
        pq.push(p); 
    }
    root = p;
    return root;
}

map<char, string> GenerateCoding(HuffmanNode*root, vector<HuffmanNode*>& Leaves)
{
    map<char, string> table;
    for(int i=0; i<Leaves.size(); i++)
    {
        HuffmanNode* p = Leaves[i];
        string code;
        while(p->parent)
        {
            if(p == p->parent->left)
                code.insert(0,"0");
            else
                code.insert(0,"1");
            p = p->parent;
        }
        table.insert({Leaves[i]->character, code});
    }
    return table;
}

double CompressionRate(const string& Input, const unordered_map<char, int>& Frequency,  map<char, string> table)
{
    int FixedLen = 0;
    int VariableLen = 0;
    int n = 0;
    while(pow(2,n)<Frequency.size())
        n++;
    FixedLen = n*Input.size();
    for(auto ite=Frequency.begin(); ite!= Frequency.end(); ite++)
    {
        char c = ite->first;
        int freq = ite->second;
        int len = table[c].size();
        VariableLen += len*freq;
    }
    double compression_rate = (double)VariableLen/FixedLen;
    return compression_rate;

}

string Read(){ //读取txt文件，处理成一个vector<vector<int>>--二维整型数组，
    ifstream Infile("data.txt");
    string Input;
    string s;
    while(getline(Infile, s)) //按行读取txt文件的内容--读取后的每行内容是字符串，存于vec_str中，
    {
        Input = s;
    }
    return Input;
}
void Output(const map<char, string>& table)
{
        ofstream outfile("encode.txt");
        for(auto ite = table.begin(); ite!=table.end(); ite++)
        {
            outfile<<ite->first<<": "<<ite->second<<endl; 
        }
}
int main()
{
    // string Input = "AABBBEEEEGZ";
    string Input = Read();
    unordered_multiset<char> multiset;    
    unordered_set<char> set;
    map<char, string> table;
    unordered_map<char, int> Frequency;

    Priority_Queue pq;
    vector<HuffmanNode*> Leaves;
    for(int i=0;i<Input.size();i++)
    {
        multiset.insert(Input[i]);
        set.insert(Input[i]);
    }

    for(auto ite=set.begin(); ite!=set.end(); ite++)
    {
        int weight = multiset.count(*ite);
        Frequency.insert({*ite, weight});
        HuffmanNode* p = CreateHuffmanNode(weight);
        Leaves.push_back(p);
        p->character = *ite;
        pq.push(p);
    }
    HuffmanNode* root = BuildHuffmanTree(pq);
    table = GenerateCoding(root, Leaves);
    double Compression_Rate = CompressionRate(Input, Frequency, table);
    cout<<"Compression_Rate="<<Compression_Rate<<endl;
    Output(table);
    return 0;
}