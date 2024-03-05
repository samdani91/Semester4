#include<bits/stdc++.h>
using namespace std;

struct Process{
    string name;
    int burstTime;
    int priority;
    int arrivalTime;
    int startTime;
    int endTime;
};

struct Result{
    string name;
    int start;
    int end;
    int taTime;
    int waitTime;
};

void takeInput(int size, vector<Process> &processes){
    Process process;
    for(int i=0; i<size; i++){
        process.name = "P" + to_string(i+1);
        cin >> process.burstTime >> process.priority >> process.arrivalTime;
        process.startTime = -1;
        process.endTime = -1;
        processes.push_back(process);
    }
}

bool compareTwoProcess(Process a, Process b){
    if(a.arrivalTime == b.arrivalTime) return a.burstTime < b.burstTime;
    return a.arrivalTime < b.arrivalTime;
}

bool compareTwoResult(Result a, Result b){
    return a.name < b.name;
}

bool sortReady(Process a, Process b){
    return a.burstTime < b.burstTime;
}

void makeReadyQueue(vector<Process> &ready, int currTime, vector<Process> processes){
    ready.clear();
    for(auto p: processes){
        if(p.arrivalTime <= currTime){
            ready.push_back(p);
        }
    }
    sort(ready.begin(), ready.end(), sortReady);
}

void print(vector<Process> a){
    for(auto ab: a){
        cout << ab.name << "  " << ab.burstTime << "  " << ab.arrivalTime << endl;
    }
}

void printR(vector<Result> a){
    for(auto ab: a){
        cout << ab.name << "  " << ab.start << "  " << ab.end << endl;
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    vector<Process> processes;
    vector<Process> temp;
    takeInput(6, processes);
    temp = processes;
    sort(temp.begin(), temp.end(), compareTwoProcess);
    vector<Process> ready;
    vector<Result> results;

    
    // while(true){
    //     makeReadyQueue(ready, currTime, temp);
    //     if(ready.size() == 0){
    //         continue;
    //     }
    //     sort(ready.begin(), ready.end(), sortReady);
    //     Process currP = ready[0];
        
    // }


    int currTime = 0;
    int w = 0;
    int s = -1;

    while(!temp.empty()){
        makeReadyQueue(ready, currTime, temp);
        if(ready.empty()){
            if(s == -1){
                s = currTime;
            }
            currTime++;
            w++;
            continue;
        }
        if(w > 0){
            Result r;
        r.name = "Dl";
        r.start = s;
        r.end = s+w;
        w = 0;
        s = -1;
        results.push_back(r);
        }
        Process currP = ready[0];
        if(currP.startTime == -1){
            currP.startTime = currTime;
            for(auto &p: processes){
                if(p.name == currP.name){
                    p.startTime = currTime;
                    break;
                }
            }
            for(auto &p: temp){
                if(p.name == currP.name){
                    p.startTime = currTime;
                    break;
                }
            }
        }
        // cout << currP.startTime << endl;
        while(currP.burstTime != 0){
            currTime++;
            currP.burstTime--;
            for(auto &t: temp){
                if(t.name == currP.name){
                    t.burstTime--;
                    break;
                }
            }
            makeReadyQueue(ready, currTime, temp);
            if(ready.empty()){
                continue;
            }
            if(currP.burstTime <= ready[0].burstTime){
                continue;
            }
            break;
        }
        Result res;
        res.name = currP.name;
        res.start = currP.startTime;
        res.end = currTime;
        results.push_back(res);
        if(currP.burstTime == 0){
            currP.endTime = currTime;
            for(auto &p: processes){
                if(p.name == currP.name){
                    p.endTime = currTime;
                    break;
                }
            }
            // cout << currP.name << "  " << currP.startTime << " " << currP.endTime << endl;
            auto it = temp.begin();
            while(it != temp.end()){
                if((*it).name == currP.name){
                    temp.erase(it);
                    break;
                }
                it++;
            }
        }
        // else{
        //     Result res;
        //     res.name = currP.name;
        //     res.start = currP.startTime;
        //     res.end = currTime;
        //     results.push_back(res);
        // }
    }

    printf("|");

    for(auto r: results){
        printf("---%s---|", r.name.c_str());
    }

    cout << endl;
    
    printf("%-9d", 0);

    for(auto r: results){
        printf("%-9d", r.end);
    }

    cout << endl << endl;



    cout << processes[2].startTime << endl;



    sort(results.begin(), results.end(), compareTwoResult);

    printf("%10s %10s %10s\n", "Process ID", "Turn Time", "Wait Time");
    int totalTurnTime = 0, totalWaitTime = 0;
    for(auto p: processes){
        int tTime = p.endTime - p.startTime;
        int wTime = (p.startTime - p.arrivalTime) + (p.endTime-p.startTime-p.burstTime);
        printf("%-10s %10d %10d\n", p.name.c_str(), tTime, wTime);
        totalTurnTime += tTime;
        totalWaitTime += wTime;
    }

    printf("Average Turn Around Time: %.2lf\n", totalTurnTime/double(processes.size()));
    printf("Average Waiting Time: %.2lf\n", totalWaitTime/double(processes.size()));
}