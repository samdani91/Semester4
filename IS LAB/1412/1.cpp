#include "aesCounter.hpp"
#include<bits/stdc++.h>
using namespace std;

int main()
{

    ifstream file("input.txt");

    string inpt, encr,line;

    while(getline(file,line)){
        inpt+=line;
        inpt+='\n';
    }
    inpt.pop_back();

    encr = ctr_encryption(inpt);
    write_file(encr);
    string decr;
    decr = getDecryptedText(encr);
    write_dec_file(decr, inpt.size());

}