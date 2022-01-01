#include<vector>
#include<string>
#include<cstring>
#include<fstream>

using namespace std;
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

vector<vector<double> > Read(){ //读取txt文件，处理成一个vector<vector<int>>--二维整型数组
    ifstream Infile("data.txt");
    vector<string> vec_str; //vec_str数组用于存储从data.txt文件中读取的每一行的内容--每一行的内容都是字符串
    vector<vector<string> > vec_substr; //vec_substr数组用于存储对vec数组中每一行分割过后的内容
    vector<vector<double> > vec_result;  //vec2用于存储将vec_substr中每个字符串转换为对应整数的形式
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