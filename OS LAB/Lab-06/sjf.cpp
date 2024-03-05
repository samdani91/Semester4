#include<bits/stdc++.h>
using namespace std;

const int N=5;

struct Process{
    string name;
    int bt,at;
    int st,et;
};

struct Res{
    string name;
    int st,et,tat,wt;
};

void readInput(vector<Process>&p)
{
    Process process;
    for(int i=1;i<=N;i++){
        process.name = "P"+to_string(i);
        cin>>process.bt>>process.at;
        process.st=-1;
        process.et=-1;
        p.push_back(process);
    }
}

bool cmpProcess(Process one,Process two)
{
    if(one.at==two.at) return one.bt < two.bt;
    return one.at < two.at;
}

bool cmpRes(Res one,Res two)
{
    return one.name < two.name;
}

bool sortReadyQ(Process one,Process two)
{
    return one.bt < two.bt;
}

void createReadyQ(vector<Process>&ready,vector<Process>p,int currT)
{
    ready.clear();
    for(auto process:p){
        if(process.at<=currT) ready.push_back(process);
    }
    sort(ready.begin(),ready.end(),sortReadyQ);
}

void ganttChart(vector<Res>results)
{
    printf("Gantt Chart\n\n|");

    for(auto r:results) printf("   %s   |",r.name.c_str());

    printf("\n");

    printf("%-9d",0);

    for(auto r:results) printf("%-9d",r.et);

    printf("\n\n");
}

void turnAround(vector<Process>p)
{
    printf("Turn Around Time for each process:\n\n");
    int sum=0;
    for(auto process:p){
        int tat=process.et-process.at;
        sum+=tat;
        printf("%s:%d\n", process.name.c_str(), tat);
    }
    printf("\n");
    printf("Average Turn Around Time:%.2lf\n\n",sum/(double)N);
}

void waitingTime(vector<Process>p)
{
    printf("Waiting Time for each process:\n\n");
    int sum=0;
    for(auto process:p){
        int wt=(process.et-process.at-process.bt);
        sum+=wt;
        printf("%s:%d\n", process.name.c_str(), wt);
    }
    printf("\n");
    printf("Average Waiting Time:%.2lf\n\n",sum/(double)N);
}

int main()
{
    freopen("input.txt","r",stdin);
    vector<Process>p,temp,ready;
    vector<Res>results;
    readInput(p);
    temp=p;

    sort(temp.begin(),temp.end(),cmpProcess);

    int currT=0,waitT=0,s=-1;

    while(!temp.empty()){
        createReadyQ(ready,temp,currT);
        if(ready.empty()){
            if(s==-1){
                s=currT;
            }
            currT++;
            waitT++;
            continue;
        }
        if(waitT>0){
            Res res;
            res.name="--";
            res.st=s;
            res.et=s+waitT;
            waitT=0;
            s=-1;
            results.push_back(res);
        }
        Process currP=ready[0];
        if(currP.st==-1){
            currP.st=currT;
            for(auto &process:p){
                if(process.name==currP.name){
                    process.st=currT;
                    break;
                }
            }
            for(auto &process:temp){
                if(process.name==currP.name){
                    process.st=currT;
                    break;
                }
            }
        }
        while(currP.bt!=0){
            currT++;
            currP.bt--;
            for(auto &t:temp){
                if(t.name==currP.name){
                    t.bt--;
                    break;
                }
            }
            createReadyQ(ready,temp,currT);
            if(ready.empty()){
                continue;
            }
            if(currP.bt<=ready[0].bt){
                continue;
            }
            break;
        }
        Res res2;
        res2.name=currP.name;
        res2.st=currP.st;
        res2.et=currT;

        results.push_back(res2);

        if(currP.bt==0){
            currP.et=currT;
            for(auto &process:p){
                if(process.name==currP.name){
                    process.et=currT;
                    break;
                }
            }

            auto it=temp.begin();
            while(it!=temp.end()){
                if((*it).name==currP.name){
                    temp.erase(it);
                    break;
                }
                it++;
            }
        }
    }

    ganttChart(results);

    turnAround(p);

    waitingTime(p);

    return 0;
}