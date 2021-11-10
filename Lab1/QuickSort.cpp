# include<iostream>
# include<vector>
# include<cstdlib>
# include<windows.h>
# include<algorithm>
# include<cmath>
using namespace std;

enum {VectorSize = 1000000};

void InsertSort(vector<int>& Input) //插入排序
{
    for(int i=1; i<Input.size(); i++)
    {
        if(Input[i]<Input[i-1])
        {
            int temp = Input[i];
            int j;
            for( j = i-1; j>=0&&Input[j]>temp; j--)
                Input[j+1] = Input[j];
            Input[j+1] = temp;
        }
    }
}

void Exchange(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}
int Partition(vector<int>& Input, int low, int high) //划分
{
    int x = Input[high];
    int i = low-1;
    int j = low;
    while(j<high)
    {
        if(Input[j] < x)
        {
            i++;
            Exchange(Input[i], Input[j]);
        }
        j++;
    }
    Exchange(Input[i+1], Input[j]);
    return i+1;   
}


void QuickSort(vector<int>& Input, int low, int high, int k)  //快排
{
    if(high-low+1 >= k) //判断输入数组的长度是否小于k
    {   
        int pivot = 0;
        pivot = Partition(Input, low, high);
        QuickSort(Input, low, pivot-1, k);
        QuickSort(Input, pivot+1, high, k);
    }
}

void display(const vector<int>& Input)
{
    for(int i=0; i<Input.size(); i++)
        cout<<Input[i]<<" ";
    cout<<endl;
}
int main()
{
    //输入数组
    vector<int> Input;
    for(int i=0; i<VectorSize; i++)
    {
        Input.push_back(rand()%VectorSize);
    }
    cout<<"Before sorting:"<<endl;
    // display(Input);
    cout<<"After sorting:"<<endl;
    /***********************************************************************************************************/
    vector<int> Input1 = Input;
    double time1;
    LARGE_INTEGER t1,t2,tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    /*************排序*********/
    QuickSort(Input1, 0, Input1.size()-1, 2);
    InsertSort(Input1);
    // display(Input1);
    /**************************/
    QueryPerformanceCounter(&t2);
    time1=(double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart; 
    cout<<"My sorting algorithm:"<<endl;
    cout<<"time = "<<time1<<"s"<<endl;  //输出时间（单位：ｓ）
    /********************************************************************************************************/
    vector<int> Input2 = Input;
    auto ite1 = Input2.begin(); 
    auto ite2 = Input2.end();
    double time2;
    LARGE_INTEGER t11,t22,tcc;
    QueryPerformanceFrequency(&tcc);
    QueryPerformanceCounter(&t11);
    /*************排序*********/
    sort(ite1, ite2);
    /**************************/
    QueryPerformanceCounter(&t22);
    time2=(double)(t22.QuadPart-t11.QuadPart)/(double)tc.QuadPart; 
    cout<<"library sorting-algorithm:"<<endl;
    cout<<"time = "<<time2<<"s"<<endl;  //输出时间（单位：ｓ）

    return 0;


}