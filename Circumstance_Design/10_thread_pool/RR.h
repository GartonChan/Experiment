typedef struct 
{
    char name;
    int ArrivalTime;  // 到达时间
    int ServiceTime;  // 服务时间
    int FinishedTime;  // 完成时间
    int WholeTime;  // 周转时间
    double WeightWholeTime;  // 带权周转时间
}RR;

void Enter();
void RRfunction();
void Display();

