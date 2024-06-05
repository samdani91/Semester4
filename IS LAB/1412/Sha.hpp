#include <bits/stdc++.h>
using namespace std;

string SHA512(string myString)
{

    stringstream fixedstream;

    for (int i = 0; i < myString.size(); ++i) {
        fixedstream << bitset<8>(myString[i]);
    }


    string s1024;


    s1024 = fixedstream.str();

    cout<<"Before Padding:\n\n";
    cout<<s1024<<endl<<endl;
    cout<<"Length:"<<s1024.size()<<endl;
    cout<<endl<<endl;


    int orilen = s1024.length();
    int tobeadded;


    int modded = s1024.length() % 1024;

    if (1024 - modded >= 128) {
        tobeadded = 1024 - modded;
    }
    else if (1024 - modded < 128) {
        tobeadded = 2048 - modded;
    }

    s1024 += "1";

    for (int y = 0; y < tobeadded - 129; y++) {
        s1024 += "0";
    }


    string lengthbits
        = std::bitset<128>(orilen).to_string();

    s1024 += lengthbits;

    

    return s1024;

}