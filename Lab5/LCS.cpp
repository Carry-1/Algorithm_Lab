# include<string>
# include<vector>
# include<iostream>
using namespace std;
class Solution {
public:
    string GenerateLCS(string text1, vector<vector<char>> b, int i, int j, string& LCS)
    {
        if(i==0||j==0)
            return LCS;
        if(b[i][j]=='1')
        {
            GenerateLCS(text1, b, i-1, j-1, LCS); 
            return  LCS += text1[i-1];
        }
        else if(b[i][j]=='0')
            return GenerateLCS(text1, b, i-1, j, LCS); 
        else
            return GenerateLCS(text1, b, i, j-1, LCS); 
        return 0;
    }
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size();
        int n = text2.size();
        vector<vector<char>> b(m+1,vector<char>(n+1, '3'));
        vector<vector<int>> c(m+1,vector<int>(n+1, 0));
        for(int i = 0; i<=m; i++)
            c[i][0] = 0;
        for(int j = 1; j<=n; j++)
            c[0][j] = 0;
        for(int i=1; i<=m; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(text1[i-1]==text2[j-1])
                {
                    c[i][j] = c[i-1][j-1]+1;
                    b[i][j] = '1';

                }
                else if(c[i-1][j]>=c[i][j-1])
                {
                    c[i][j] = c[i-1][j];
                    b[i][j] = '0';
                }
                else{
                    c[i][j] = c[i][j-1];
                    b[i][j] = '2';
                }
            }
        }
        string LCS;
        // 生成并打印LCS
        // GenerateLCS(text1, b, m, n, LCS);
        // cout<<"text1:"<<text1<<endl;
        // cout<<"text2:"<<text1<<endl;
        // cout<<"LCS:"<<LCS;
        return c[m][n];

    }
};