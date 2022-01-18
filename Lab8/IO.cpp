#include<vector>
#include<string>
#include<map>
#include<fstream>
#include<iostream>

#include<queue>
using namespace std;

void Read(vector<string>& Vex,  vector<vector<string>>& Edge)
{
    ifstream infile("data.txt");
    string s;
    getline(infile,s);
    for(int i=0; i<s.size(); i++)
    {
        if(s[i]!=',')
        {
            Vex.push_back(s.substr(i,1));
        }
    }
    while(getline(infile,s))
    {
        Edge.push_back({});
        for(int i=0; i<s.size(); i++)
        {
            if(s[i]!='-')
            {
            Edge[Edge.size()-1].push_back(s.substr(i,1));
            }
        }
    }

}
