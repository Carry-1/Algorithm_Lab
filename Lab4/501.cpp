#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include <queue>
using namespace std;

enum Color{
    red,
    black
};

struct RBNode{
    int key, max;
    pair<int,int> interval;
    Color color;
    RBNode *parent, *lchild, *rchild;
};

class RBTree{
private:
    RBNode *nil, *root;
    void insertFixup(RBNode* z){
        while(z->parent->color == red){
            // 插入结点父亲是一个左孩子，对应情况1，2，3
            if(z->parent == z->parent->parent->lchild){
                RBNode* y = z->parent->parent->rchild;
                // 情况1：叔叔是红色
                if(y->color == red){
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                }
                else{
                    // 情况2：叔叔是黑色且z是一个右孩子
                    if (z == z->parent->rchild){
                        z = z->parent;
                        leftRotate(z);
                    }
                    // 情况3：叔叔是黑色且z是一个左孩子
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    rightRotate(z->parent->parent);
                }
            }
            else{
                RBNode* y = z->parent->parent->lchild;
                // 情况4：叔叔是红色
                if(y->color == red){
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                }
                else{
                    // 情况5：叔叔是黑色且z是一个左孩子
                    if (z == z->parent->lchild){
                        z = z->parent;
                        rightRotate(z);
                    }
                    // 情况6：叔叔是黑色且z是一个右孩子
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = black;
    }
    void leftRotate(RBNode* x){
        RBNode* y = x->rchild;
        x->rchild = y->lchild;
        if(y->lchild != nil){
            y->lchild->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == nil){
            root = y;
        }
        else if(x == x->parent->lchild){
            x->parent->lchild = y;
        }
        else x->parent->rchild = y;
        y->lchild = x;
        x->parent = y;
        x->max = max(max(x->interval.second, x->lchild->max) , x->rchild->max);
        y->max = max(y->max, x->max);
    }
    void rightRotate(RBNode* x){
        RBNode* y = x->lchild;
        x->lchild = y->rchild;
        if(y->rchild != nil){
            y->rchild->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == nil){
            root = y;
        }
        else if(x == x->parent->rchild){
            x->parent->rchild = y;
        }
        else x->parent->lchild = y;
        y->rchild = x;
        x->parent = y;
        x->max = max(max(x->interval.second, x->rchild->max) , x->lchild->max);
        y->max = max(y->max, x->max);
    }
    bool isOverlap(RBNode* p, pair<int,int> x){
        return x.second >= p->interval.first && x.first <= p->interval.second;
    }
    pair<int, int> search(RBNode* p, pair<int,int> x){
        // cout << p->key << ' ' << p->max << endl;
        if(p == nil || p->max < x.first){
            return {};
        }
        if(isOverlap(p, x)){
            return p->interval;
        }
        if(p->key > x.first){
            return search(p->lchild, x);
        }
        else{
            return search(p->rchild, x);
        }
    }
public:
    RBTree(){
        nil = new RBNode{0, 0, {}, black, nullptr, nullptr, nullptr};
        root = nil;
    }
    void insert(RBNode* z){
        z->lchild = nil;
        z->rchild = nil;
        z->color = red;
        RBNode *y = nil, *x = root;
        while(x != nil){
            y->max = max(y->max, z->max);
            y = x;
            x = z->key < x->key ? x->lchild : x = x->rchild;
        }
        z->parent = y;
        if(y == nil) root = z;
        else (z->key < y->key ? y->lchild : y->rchild) = z;
        insertFixup(z);
    }
    void print(string filename){
        ofstream outFile(filename, ios::out);
        queue<RBNode*> Q;
        Q.push(root);
        while(!Q.empty()){
            RBNode* p = Q.front();
            Q.pop();
            if(p != nil){
                outFile << p->key << ", " << (p->color == black ? "black" : "red") << endl;
                Q.push(p->lchild);
                Q.push(p->rchild);
            }
            else outFile << "nil" << endl;
        }
        outFile.close();
    }
    pair<int, int> search(pair<int, int> x){
        return search(root, x);
    }
    
};

// 读取文件内容，输出数据数组
vector<pair<int, int>> readFile(string filename){
    ifstream inFile(filename, ios::in);
    int num, num1, num2;
    inFile >> num;
    vector<pair<int, int>> data;
    while(inFile >> num1 >> num2){
        data.push_back({num1, num2});
    }
    inFile.close();
    return data;
}

int main(){
    vector<pair<int, int>> data = readFile("insert.txt");
    RBTree T;
    for(auto d: data){
        T.insert(new RBNode{d.first, d.second, {d.first, d.second}});
    }
    pair<int, int> ans = T.search({40, 60});
    if(ans == pair<int,int>{}){
        cout << "不存在区间与之重叠" << endl;
    }
    else cout << "存在重叠区间: [" << ans.first << ", " << ans.second << "]" << endl;
}