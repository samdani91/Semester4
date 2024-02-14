#include<bits/stdc++.h>
using namespace std;


string encrypt(string line,int n)
{   
    string output;
    for(int i=0;i<line.size();i++){
        if(line[i]>='A' and line[i]<='Z') output+= (line[i]+n-'A')%26+'A';
        else if(line[i]>='a' and line[i]<='z') output+= (line[i]+n-'a')%26+'a';
        else output+=line[i];
    }
    return output;
}

string decrypt(string line,int n)
{   
    return encrypt(line,26-n);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);

    
    string line;
    int n;
    getline(cin,line);
    cin>>n;

    string encrypted=encrypt(line,n);

    cout<<"Encrypted: ";
    cout<<encrypted<<endl;

    cout<<"Decrypted: ";
    cout<<decrypt(encrypted,n)<<endl;

    return 0;
}