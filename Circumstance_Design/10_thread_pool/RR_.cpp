#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <queue>

using namespace std;

typedef struct{
    char name;//进程名字
    int ArrivalTime;//到达时间
    int ServiceTime;//服务时间
    int FinishedTime;//完成时间
    int WholeTime;//周转时间
    double WeightWholeTime;//带权周转时间
}RR;


static queue<RR>RRqueue;  //用来模拟进程执行RR调度算法的队列
static double SumWT=0,SumWWT=0,AverageWT =0,AverageWWT=0;//平均周转时间、平均带权周转时间
static int q;  //时间片数
static int n;  //进程个数
static RR RRarray[100];  //进程结构体
static RR temp;  //进程结构
 

void Enter(); //输入时间片、到达时间、服务时间等
void RRfunction();//执行RR调度算法
void display();//显示各时间执行情况，以及各个时间值


//执行RR调度算法
void Enter()
{
    int i;
    cout << "输入进程数目:" ;
    cin >> n;
    cout << "输入时间片数:" ;
    cin >> q;
    for (i=0; i<n; i++)
    {
        cout << "输入进程名:";
        cin >> RRarray[i].name;
        cout << "输入到达时间: ";
        cin >> RRarray[i].ArrivalTime;
        cout << "输入服务时间: ";
        cin >> RRarray[i].ServiceTime;
    }
}


void RRfunction(){
    char Moment[100];   //存储每个时间片p对应的进程名称
    RRqueue.push(RRarray[0]);   //第一个进程进队列
    int MomentPoint = 0;
    int CurrentTime=0;
    int tempTime;   //控制CurrentTime的累加时间，当前进程的服务时间小于时间片q的时候，起到重要作用
    int i=1,j,k,p;  //指向还未处理的进程的下标
    int finalNumber = 0;   //执行RR算法后，进程的个数
    int Time[50];
    bool canAdd=false;//用于解决CurrentTime在第一个进程完成计算时多加了一次服务时间的问题
     //判断第一个进程的服务时间是否大于时间片，如果大于CurrentTime=q，如果小于CurrentTime=服务时间
    if (RRarray[0].ServiceTime>=q)
        CurrentTime = q;
    else
        CurrentTime = RRarray[0].ServiceTime;
    while(!RRqueue.empty()){
        for (j=i;j<n;j++){   //使得满足进程的到达时间小于当前时间的进程都进入队列
            if (RRarray[j].name!=NULL && CurrentTime >= RRarray[j].ArrivalTime){
                RRqueue.push(RRarray[j]);
                i++;
            }
        }
        if (RRqueue.front().ServiceTime<q)
            tempTime = RRqueue.front().ServiceTime;
        else
            tempTime = q; 
        RRqueue.front().ServiceTime -= q;   //进程每执行一次，就将其服务时间 -q 
        //将队首进程的名称放入数组中
        Moment[MomentPoint] = RRqueue.front().name;
        MomentPoint++;
        Time[finalNumber] = tempTime;
        finalNumber++; 
        if (RRqueue.front().ServiceTime <= 0)  //把执行完的进程退出队列
            RRqueue.pop();   //如果进程的服务时间小于等于，即该进程已经服务完了，将其退栈
        else{
            //将队首移到队尾
            RRqueue.push(RRqueue.front());
            RRqueue.pop();
        }
       if(canAdd){
         CurrentTime += tempTime;
        }
       canAdd=true;  
    }
     //进程输出处理   每个时间段对应的执行的进程
	cout<<"各进程的执行时刻信息："<<endl;
 
	Time[finalNumber]=0;
	int time = Time[0];
 
	int count = 0;
	int countTime=0;
 
	for (int i=0;i<finalNumber;i++)//计算完成时间
	{
 
		count = 0;
 
 
		while(RRarray[count].name!=Moment[i] && count<n)
		{
 
			count++;
		}
		RRarray[count].FinishedTime = time;
 
		if (i<finalNumber - 1)
		{
 			time += Time[i+1];
		}
 	}
 	for(int i=0;i<finalNumber;i++){//输出
            	 for(int j=0;j<Time[i];j++){
            cout<<setw(3)<<countTime<<" --"<<setw(3)<<countTime+1<<setw(6)<<"时刻     "<<"进程"<<Moment[i]<<"执行";
           for(int k=0;k<n;k++){
            if(RRarray[k].ArrivalTime==countTime){
                cout<<"   进程"<<RRarray[k].name<<"到达";
            }
            else if(RRarray[k].FinishedTime==countTime+1&&countTime!=0){
                cout<<"   进程"<<RRarray[k].name<<"完成";
            }
           }
            countTime+=1;
           cout<<endl; 
 	    } 
	}
	cout<<endl; 
    //周转时间、带权周转时间、平均周转时间、带权平均周转时间的计算
    for (i=0;i<n;i++){
        RRarray[i].WholeTime = RRarray[i].FinishedTime - RRarray[i].ArrivalTime;
        RRarray[i].WeightWholeTime = (double)RRarray[i].WholeTime/RRarray[i].ServiceTime;
    }
     for (i=0;i<n;i++){
        SumWT += RRarray[i].WholeTime;
        SumWWT += RRarray[i].WeightWholeTime;
    }
    AverageWT = SumWT/n;
    AverageWWT = SumWWT/n;
 
}

void display()//显示各时间执行情况，以及各个时间值
{

}


int main(int argc, char const *argv[])
{
    Enter();
    RRfunction();    
    return 0;
}
