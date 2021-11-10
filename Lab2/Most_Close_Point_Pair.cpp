#include <iostream>
#include <vector>
#include <algorithm>
#include<cmath>
using namespace std;

typedef pair< pair<double, double>, pair<double, double> > Point_Pair;
typedef pair<Point_Pair, double> Result;
Result Find_Most_Close_Point_Pair(const vector<pair<double, double> >& P, const vector<double>& X, const vector<double>& Y)
{
    Result result;
    if(P.size()<=3)
    {

        Point_Pair pp;
        pair<double, double> p1 = P[0], p2 = P[1], p3 = P[2]; 
        double dist1 = sqrt(pow(p1.first-p2.first,2) + pow(p1.second-p2.second,2));
        double dist2 = sqrt(pow(p1.first-p3.first,2) + pow(p1.second-p3.second,2));
        double dist3 = sqrt(pow(p2.first-p3.first,2) + pow(p2.second-p3.second,2));
        double min_dist;
        min_dist = (dist1<dist2) ? dist1 : dist2;
        min_dist = (min_dist<dist3) ? min_dist : dist3;
        if(min_dist==dist1)
        {
            pp.first = p1;
            pp.second = p2;
        }
        else if(min_dist==dist2)
        {
            pp.first = p1;
            pp.second = p3;
        }
        else{
            pp.first = p2;
            pp.second = p3;
        }  
        
        result.first = pp;
        result.second = min_dist;      
    }

    else{
        //将输入点集P划分为两个子点集P_L和P_R
        vector<pair<double, double> > P_L;
        vector<pair<double, double> > P_R;
        int middle = X.size()/2;
        if(X.size()%2==1)
            middle += 1;
        for(int i=0; i<middle; i++)  //生成P_L
        {
            P_L.push_back(P[i]);
        }
        for(int i=middle; i<P.size(); i++)  //生成P_R
        {
            P_R.push_back(P[i]);
        }
        vector<double> X_L;
        vector<double> X_R;
        vector<double> Y_L;
        vector<double> Y_R;

        for(int i=0; i<P_L.size(); i++)  //生成X_L和Y_L
        {
            X_L.push_back(P_L[i].first);
            Y_L.push_back(P_L[i].second);
        }
        for(int i=0; i<P_R.size(); i++)  //生成X_R和Y_R
        {
            X_R.push_back(P_R[i].first);
            Y_R.push_back(P_R[i].second);
        }

        Result result_L = Find_Most_Close_Point_Pair(P_L, X_L, Y_L);
        Result result_R = Find_Most_Close_Point_Pair(P_R, X_R, Y_R);
        double sigma1 = result_L.second;
        double sigma2 = result_R.second;
        double sigma = min(sigma1, sigma2);
        result = (sigma==sigma1) ? result_L : result_R;

        
        double left_end, right_end;  //设置跨区域的左右端点
        if(middle%2==1)  //如middle = 3  -> 0 1 2 3 4 
        {
            left_end = X[middle-1] - 2*sigma; 
            right_end = X[middle-1] + 2*sigma;
        }
        else
        {
            left_end = (X[middle-1]+X[middle])/2 - 2*sigma;
            right_end = (X[middle-1]+X[middle])/2 + 2*sigma;
        }

        for(int i=0; )


    }
    
    return result;
}

vector<pair<double, double> > Point_Sorting(vector<pair<double, double>>& P)
{
    //利用插入排序对输入点集按X坐标递增进行排序
    for(int i=1; i<P.size(); i++)
    {
        if(P[i].first<P[i-1].first)
        {
            pair<double, double> p = P[i];
            int j;
            for(j=i-1; P[j].first > p.first&& j>=0; j--)
            {
                P[j+1] = P[j];
            }
            P[j+1] = p;
        }
    }
    return P;
}

int main()
{
    vector<pair<double, double> > P(5, pair<double,double>(0,0));
    P[0] = make_pair(1.1, 2.0);
    P[1] = make_pair(3.1, 1.0);
    P[2] = make_pair(4.4, 5.3);
    P[3] = make_pair(2.6, 3.2);
    P[4] = make_pair(2.6, 4.6);
    // P[5] = make_pair(5.3, 5.2);
    // P[6] = make_pair(3.2, 4.5);
    // P[7] = make_pair(5.3, 4.7);

    vector<double> X;
    vector<double> Y;
    for(int i=0; i<P.size(); i++)
    {
        X.push_back(P[i].first);
        Y.push_back(P[i].second);
    }
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    Point_Sorting(P);    //对输入点对排序
    Result result = Find_Most_Close_Point_Pair(P, X, Y);
    return 0;
}