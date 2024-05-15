#include "aesCbc.hpp"
#include<bits/stdc++.h>
using namespace std;


int main()
{

    string inpt, encr;
    freopen("input.txt","r",stdin);
    getline(cin, inpt);
    encr = cbc_encryption(inpt);
    write_file(encr);
    string decr;
    decr = getDecryptedText(encr);
    write_dec_file(decr, inpt.size());
    

    return 0;
}