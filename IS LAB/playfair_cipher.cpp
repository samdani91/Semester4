#include<bits/stdc++.h>
using namespace std;

vector<vector<char>>table(5,vector<char>(5));
map<char,pair<int,int>>mp;

string encryption(string diag);
string diagram(string keyword);
void preprocess(string Keyword);

int main()
{
    string keyword,text;

    cout<<"Enter Keyword: ";
    getline(cin,keyword);

    cout<<"Enter Text: ";
    getline(cin,text);

    cout<<endl;

    preprocess(keyword);

    cout<<endl;

    string diag=diagram(text);
    cout<<"Diagram String: "<<diag<<endl<<endl;
    string encryptedString=encryption(diag);
    cout<<"Encrypted String: "<<encryptedString<<endl;

}

void preprocess(string keyword)
{   
    int k=0;
    char ch='a';
    vector<bool>chars(27,false);
    chars[106-96]=true;//j

    int row=0,col;
    for(int i=0;i<keyword.size();i++){
        if(i%5==0 and i!=0) row++;
        table[row][(i%5)]=keyword[i];
        mp.insert({table[row][i%5],{row,i%5}});
        chars[keyword[i]-96]=true;
        col=i%5;
    }
    col++;

    for(int i=1;i<chars.size();i++){
        if(!chars[i] and row<5){
            table[row][col]=(char)96+i;
            mp.insert({table[row][col],{row,col}});
            col= (col+1)%5;
            if(col==0) row++;
        }
    }

    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cout<<table[i][j]<<" ";
        }
        cout<<endl;
    }
}

string diagram(string text)
{
    string diag;
    for(int i=0;i<text.size();){
        string subString=text.substr(i,2);
        
        if(subString.size()==1){
            diag+= subString+'x';
            break;
        }
        if(subString[0]==subString[1]){
            subString[1]='x';
            diag+=subString;
            i++;
        }else{
            diag+=subString;
            i+=2;
        }
    }
    return diag;
}

string encryption(string diag)
{   
    string encrypted;
    int r1,c1,r2,c2;

    for(int i=0;i<diag.size();i+=2){
        string subString=diag.substr(i,2);
        
        r1=mp[subString[0]].first;
        c1=mp[subString[0]].second;
        r2=mp[subString[1]].first;
        c2=mp[subString[1]].second;

        if(r1==r2){
            encrypted+= table[r1][(c1+1)%5];
            encrypted+= table[r1][(c2+1)%5];
        }else if(c1==c2){
            encrypted+= table[(r1+1)%5][c1];
            encrypted+= table[(r2+1)%5][c1];
        }else{
            encrypted+= table[r1][c2];
            encrypted+= table[r2][c1];
        }

    }

    return encrypted;
}