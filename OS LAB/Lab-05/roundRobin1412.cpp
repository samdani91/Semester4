#include<bits/stdc++.h>
using namespace std;

const int N=5;

queue<string>rr_queue;
queue<string>line;
queue<int>rr_time;

void ganttCharts(int &index,int *new_time,string *new_process)
{
    printf("\nGantt Charts:\n\n|");
    int sum=0;
    while(line.size()!=0){
        new_process[index]=line.front();
        cout<<"   "<<line.front()<<"    |";
        line.pop();
        index++;
    }
    printf("\n");
    printf("%d",0);
    index=0;
    while(rr_time.size()!=0){
        sum+=rr_time.front();
        new_time[index]=sum;
        cout<<"         "<<sum;
        rr_time.pop();
        index++;
    }
    printf("\n\n");
}

void turnAround(int *completion_time,string *process)
{
    printf("Turn Around Time for each process:\n\n");
    int sum=0;
    for(int i=0;i<5;i++){
        cout<<process[i]<<":"<<completion_time[i]<<endl;
        sum+=completion_time[i];
    }
    printf("\n");

    printf("Average Turn Around Time:%.2lf\n\n",sum/(double)N);
}

void waitingTime(int *completion_time,int *burstTime2,string *process)
{
    printf("Waiting Time for each process:\n\n");
    int sum=0;
    for(int i=0;i<5;i++){
        cout<<process[i]<<":"<<completion_time[i]-burstTime2[i]<<endl;
        sum+=completion_time[i]-burstTime2[i];
    }
    printf("\n");

    printf("Average Waiting Time:%.2lf\n\n",sum/(double)N);
}
int main()
{   
    printf("\n\t\t\t-----------------Round Robin---------------\n\n");
    int quantam;
    printf("Enter Quantam:");
    scanf("%d",&quantam);

    string process[5]={"P1","P2","P3","P4","P5"};
    int burstTime[5]={2,1,8,4,5};
    int burstTime2[5]={2,1,8,4,5};
    int i,j;

    for(i=0;i<5;i++){
        rr_queue.push(process[i]);
    }

    for(i=1;i;i++){
        string popped=rr_queue.front();
        rr_queue.pop();
        line.push(popped);
        if(burstTime[popped[1]-'0'-1]>=quantam){
            rr_time.push(quantam);
            burstTime[popped[1]-'0'-1]=burstTime[popped[1]-'0'-1]-quantam;
        }
        else{
            rr_time.push(burstTime[popped[1]-'0'-1]);
            burstTime[popped[1]-'0'-1]=0;
        }
        if(burstTime[popped[1]-'0'-1]>0){
            rr_queue.push(popped);
        }
        if(rr_queue.size()==0){
            break;
        }
    }
    
    int index=0;
    string new_process[line.size()];
    int new_time[rr_time.size()];

    ganttCharts(index,new_time,new_process);

    int completion_time[5]={0};
    for(i=index-1;i>=0;i--){
        int idx=new_process[i][1]-'0'-1;
        if(completion_time[idx]==0){
            completion_time[idx]=new_time[i];
        }
    }

    turnAround(completion_time,process);
    
    waitingTime(completion_time,burstTime2,process);
    

    return 0;
}