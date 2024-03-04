#include<bits/stdc++.h>
using namespace std;

const int N=5;

vector<int>burstTime={2,1,8,4,5};
vector<int>prefix(N,0),arrivalTime(N,0);

void ganttCharts()
{   
    prefix[0]=burstTime[0];
    for(int i=0;i<burstTime.size();i++){
        prefix[i]=prefix[i-1]+burstTime[i];
    }
    printf("\nGantt Charts:\n\n|");
    for(int i=0;i<N;i++){
        printf(" P%d  |",i+1);
    }
    printf("\n");
    printf("%d",0);
    for(int i=0;i<prefix.size();i++){
        printf("     %d",prefix[i]);
    }
    printf("\n\n\n");
}

void turnAround()
{
    printf("Turn Around Time for each process:\n\n");
    int sum=0;
    for(int i=0;i<prefix.size();i++){
        int temp=prefix[i]-arrivalTime[i];
        sum+=temp;
        printf("P%d:%d\n",i+1,temp);
    }
    printf("\n");

    printf("Average Turn Around Time:%.2lf\n\n",sum/(double)N);
}

void waitingTime()
{
    printf("Waiting Time for each process:\n\n");
    int sum=0;
    for(int i=0;i<prefix.size();i++){
        int temp=prefix[i]-burstTime[i];
        sum+=temp;
        printf("P%d:%d\n",i+1,temp);
    }
    printf("\n");

    printf("Average Waiting Time:%.2lf\n\n",sum/(double)N);
}

int main()
{   
    printf("\n\t\t-----------------FCFS---------------\n\n");
    ganttCharts();
    turnAround();
    waitingTime();
}