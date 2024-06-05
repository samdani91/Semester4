#include "Sha.hpp"
#include<bits/stdc++.h>
using namespace std;

int main()
{

    ifstream file("input.txt");

    string inpt,line;

    while(getline(file,line)){
        inpt+=line;
        inpt+='\n';
    }
    inpt.pop_back();

    string ans=SHA512(inpt);
    cout<<"After Padding:\n\n";
    cout<<ans<<endl<<endl;
    cout<<"Lenght:"<<ans.size();

    cout<<endl<<endl;
    

}