#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<fstream>

using namespace std;

int job_number;
int machine_number;
vector<double> time1;
double best_time = INT_MAX;
int k = 0;
std::vector<std::vector<int>> machine;
std::vector<std::vector<int>> result2 = machine;

std::vector<string> split(const std::string& str, const std::string& delim) //将输入字符串str按delim标志进行分割
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
void Read(){ //读取txt文件，处理成一个vector<vector<int>>--二维整型数组
    ifstream Infile("data.txt");
    vector<string> vec_str;
    vector<vector<string>> vec_substr;

    string s; //字符串s用于存储从.txt文件中读取的每行内容
    while(getline(Infile,s)) 
    {
        vec_str.push_back(s);
    }
    
    for(int i=0; i<vec_str.size(); i++) //对读取进来的每行原始字符串进行分割
    {
        string s;
        vec_substr.push_back({});
        vec_substr[vec_substr.size()-1] = split(vec_str[i], " "); //对vec数组的每一行按空格进行分割,原vec中每行字符串会被分割为多个字符串
    }

    
        char * strs = new char[vec_substr[0][0].length()+1];
        strcpy(strs, vec_substr[0][0].c_str());
        job_number = atoi(strs);
        char * strs1 = new char[vec_substr[0][1].length()+1];
        strcpy(strs1, vec_substr[0][1].c_str());
        machine_number = atoi(strs1);

        for(int i=0; i<job_number; i++)
        {
            char * strs = new char[vec_substr[1][i].length()+1];
            strcpy(strs, vec_substr[1][i].c_str());
            time1.push_back(atof(strs));
        }
   
}

void BackTrack(int k, vector<double>& temp_time, int n, const vector<double>& time1)
{
    if(k>=n)
    {
        double total_time = 0;
        for(int i=0; i<machine.size(); i++)
        {
            double temp_time1 = 0;
            for(int j=0; j<machine[i].size(); j++)
            {
                temp_time1 +=time1[machine[i][j]];
            }
            total_time = (total_time>temp_time1?total_time:temp_time1);
        }
        if(total_time<best_time)
        {
            best_time = total_time;
            // std::cout<<"best_time:"<<best_time<<std::endl;
            
            for(int m=0; m<machine.size(); m++)
            {
                if(result2.size()!=machine.size())
                    result2.push_back(machine[m]);
                else
                    result2[m] = machine[m];
            }
        }
    }
    
    else{
            for(int j=0;  j<machine.size(); j++)
            {
                machine[j].push_back(k);
                if(temp_time[j] + time1[machine[j][machine[j].size()-1]]<=best_time)
                {
                    
                    temp_time[j] += time1[machine[j][machine[j].size()-1]];
                    BackTrack(k+1, temp_time, n, time1);
                    temp_time[j] -= time1[machine[j][machine[j].size()-1]];
                }
                machine[j].pop_back();

            }
        }
}
int main()
{
    
    Read();
    int n = job_number;
    std::vector<double> temp_time (machine_number,0);

    for(int j=0; j<machine_number; j++)
    {
        machine.push_back({});
    }
    BackTrack(k,temp_time, n, time1);
    double best_time2 = best_time;
    std::vector<std::vector<int>> result = result2;
    std::cout<<"耗费总时间为   "<<best_time<<std::endl;
    std::cout<<"最佳调度方案为："<<std::endl;
    for(int i=0; i<result.size(); i++)
    {
        std::cout<<"机器 "<<i+1<<":    ";
        for(int j=0; j<result[i].size(); j++)
        {
            std::cout<<"任务"<<result[i][j]+1<<"  ";
            if(j==result[i].size()-1)
                std::cout<<std::endl;
        }
    }
    return 0;
}