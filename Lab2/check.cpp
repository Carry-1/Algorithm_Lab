#include <iostream>
#include <vector>
#include <algorithm>
#include<cmath>
using namespace std;
typedef pair< pair<double, double>, pair<double, double> > Point_Pair;
typedef pair<Point_Pair, double> Result;


int main()
{
    vector<pair<double, double> > P(12, pair<double,double>(0,0));
    P[0] = make_pair(1.1, 2.0);
    P[1] = make_pair(3.1, 1.0);
    P[2] = make_pair(4.4, 5.3);
    P[3] = make_pair(2.6, 3.2);
    P[4] = make_pair(2.6, 4.6);
    P[5] = make_pair(5.3, 5.2);
    P[6] = make_pair(3.2, 4.5);
    P[7] = make_pair(5.3, 4.7);
    P[8] = make_pair(4, 6.6);
    P[9] = make_pair(8, 7.9);
    P[10] = make_pair(6, 3.8);
    P[11] = make_pair(4, 6.9);
    Result result;
    result.first.first = P[0];
    result.first.second = P[1];
    result.second = 100;
    for(int i=0; i<P.size(); i++)
    {
        for(int j=i+1; j<P.size(); j++)
        {
            double dist = sqrt(pow(P[i].first-P[j].first,2) + pow(P[i].second-P[j].second,2));
            if(dist<result.second)
            {
                result.first.first = P[i];
                result.first.second = P[j];
                result.second = dist;
            }
        }
    }
    cout<<endl;
    cout<<endl;
    cout<<"brutal search:"<<endl;
    cout<<"The shortest-distance Point-Pair is:"<<endl;
    cout<<"("<<result.first.first.first<<","<<result.first.first.second<<")"<<" and ";
    cout<<"("<<result.first.second.first<<","<<result.first.second.second<<")"<<endl;
    cout<<"The shortest dist is:"<<result.second<<endl;
    return 0;
}