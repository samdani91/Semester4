#include<bits/stdc++.h>
using namespace std;

const int N=6;

vector<int>burstTime={20,25,25,15,10,10};
vector<int>arrivalTime={0,25,30,60,100,105};
vector<int>ct(N),tat(N),wt(N);

void ganttCharts()
{   
    ct[0]=burstTime[0];
    vector<pair<int,int>>chart;
    chart.push_back({0,ct[0]});
    for(int i=1;i<burstTime.size();i++){
        if(arrivalTime[i]>ct[i-1]){
            chart.push_back({-1,arrivalTime[i]});
            ct[i]=arrivalTime[i]+burstTime[i];
        }else{
            ct[i]=ct[i-1]+burstTime[i];
        }
            chart.push_back({i,ct[i]});
    }

    printf("\nGantt Charts:\n\n|");

    for(auto it:chart){
        if(it.first==-1){
            printf("   -   |");
        }else{
            printf("   P%d%4c",it.first+1,'|');
        }
    }

    printf("\n");
    printf("%d",0);
    for(auto it:chart){
        printf("%9d",it.second);
    }
    printf("\n\n\n");
}

void turnAround()
{
    printf("Turn Around Time for each process:\n\n");
    int sum=0;
    for(int i=0;i<N;i++){
        tat[i]=ct[i]-arrivalTime[i];
        sum+=tat[i];
        printf("P%d:%d\n",i+1,tat[i]);
    }
    printf("\n");

    printf("Average Turn Around Time:%.2lf\n\n",sum/(double)N);
}

void waitingTime()
{
    printf("Waiting Time for each process:\n\n");
    int sum=0;
    for(int i=0;i<N;i++){
        wt[i]=tat[i]-burstTime[i];
        sum+=wt[i];
        printf("P%d:%d\n",i+1,wt[i]);
    }
    printf("\n");

    printf("Average Waiting Time:%.2lf\n\n",sum/(double)N);
}

int main()
{
    ganttCharts();
    turnAround();
    waitingTime();
}