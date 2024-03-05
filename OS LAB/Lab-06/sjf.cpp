#include<bits/stdc++.h>
using namespace std;

const int N=6;

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

bool createReadyQ(vector<Process>&ready,vector<Process>p,int currT)
{
    ready.clear();
    for(auto process:p){
        if(process.at<=currT) ready.push_back(process);
    }
    sort(ready.begin(),ready.end(),sortReadyQ);
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
        }
    }
}