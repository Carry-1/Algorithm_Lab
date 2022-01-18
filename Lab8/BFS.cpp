#include<vector>
#include<string>
#include<map>
#include<iostream>
#include<queue>
#include "IO.cpp"

using namespace std;

void Read(vector<string>& Vex,  vector<vector<string>>& Edge);

struct EdgeNode
{
    bool visited;
    int ivex;
    int jvex;
    EdgeNode* iLink;
    EdgeNode* jLink;

};

struct VexNode
{
    bool visited;
    string vex;
    EdgeNode* firstEdge;
};


vector<VexNode*> StoreGraph(const vector<string>& Vex, const vector<vector<string>>& Edge)
{
    map<string, int> table;
    vector<VexNode*> VexPointer;
    vector<EdgeNode*> EdgePointer;

    for(int i=0; i<Vex.size(); i++)
    {
        VexNode * v = new VexNode;
        v->vex = Vex[i];
        v->firstEdge = nullptr;
        v->visited = false;
        VexPointer.push_back(v);
        table[Vex[i]] = i;
    }
    for(int i=0; i<Edge.size(); i++)
    {
        EdgeNode * e = new EdgeNode;
        e->visited = false;
        e->ivex = table[Edge[i][0]];
        e->iLink = nullptr;
        e->jvex = table[Edge[i][1]];
        e->jLink = nullptr;
        EdgePointer.push_back(e);
    }

    for(int i=0; i<EdgePointer.size(); i++)
    {
        int ivex = EdgePointer[i]->ivex;
        if(VexPointer[ivex]->firstEdge==nullptr)
            VexPointer[ivex]->firstEdge = EdgePointer[i];
        else{
            EdgeNode * rear = VexPointer[ivex]->firstEdge;
            while(rear->iLink!=nullptr)
            {
                rear = rear->iLink;
            }
            rear->iLink = EdgePointer[i];
        }
    }
    for(int i=0; i<VexPointer.size(); i++)
    {
        if(VexPointer[i]->firstEdge==nullptr)
        {
            for(int j=0; j<EdgePointer.size(); j++)
            {
                int jvex = EdgePointer[j]->jvex;
                if(jvex==i)
                {
                    VexPointer[i]->firstEdge = EdgePointer[j];
                    break;
                }
            }
        }
    }

    for(int i=0; i<VexPointer.size(); i++)
    {
        bool first = true;
        EdgeNode* p = nullptr;
        for(int j=0; j<EdgePointer.size(); j++)
        {
            if(EdgePointer[j]->jvex==i)
            {
                if(first)
                {
                    p = EdgePointer[j];
                    first = !first;
                }
                else{
                    p->jLink = EdgePointer[j];
                    p = EdgePointer[j];
                }
            }
        }
    }  
    return VexPointer;
}
vector<string> BFS(const vector<VexNode*>& VexPointer)
{
    vector<string> result;
    for(int i=0; i<VexPointer.size(); i++)
    {
            queue<VexNode*> q;
            q.push(VexPointer[i]);

            while(!q.empty())
            {
                VexNode* p = q.front();
                q.pop();
                if(p->visited)
                    continue;
                p->visited = true;
                result.push_back(p->vex);
                if(p->firstEdge==nullptr)   //此节点不和任何边相连
                    break;
                EdgeNode* pointer = p->firstEdge;
                while(pointer&&pointer->visited==false)
                {
                    pointer->visited = true;
                    if(VexPointer[pointer->jvex]->visited==false)
                        q.push(VexPointer[pointer->jvex]);   
                    pointer = pointer->iLink;
                }
                p->firstEdge->visited = true;
            }
        
    }
    return result;

}

int main()
{
     
    // vector<string> Vex = {"A","B","C","D","E","F","G","H"};
    // vector<vector<string>> Edge = {{"A","B"},{"A","C"},{"C","D"},{"C","E"},{"D","E"},{"F","G"}};
    vector<string> Vex;
    vector<vector<string>> Edge;
    Read(Vex,Edge);
    vector<VexNode*> VexPointer = StoreGraph(Vex, Edge);
    vector<string> result = BFS(VexPointer);
    cout<<"========================================"<<endl;
    for(int i=0; i<result.size(); i++)
        cout<<result[i]<<" ";
    return 0;
}