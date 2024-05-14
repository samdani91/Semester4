#include<bits/stdc++.h>
using namespace std;
#define ROTR(x, n) ((x>>n) | (x<<(64-n)))
#define SHR(x, n) (x>>n)
#define Ch(x, y, z) ((x&y)^((~x)&z)) 
#define Maj(x, y, z) ((x&y)^(x&z)^(y&z))

uint64_t H[8] = {0x6a09e667f3bcc908,
                 0xbb67ae8584caa73b,
                 0x3c6ef372fe94f82b,
                 0xa54ff53a5f1d36f1,
                 0x510e527fade682d1,
                 0x9b05688c2b3e6c1f,
                 0x1f83d9abfb41bd6b,
                 0x5be0cd19137e2179};

uint64_t K[80]
    = { 0x428a2f98d728ae22, 0x7137449123ef65cd,
        0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
        0x3956c25bf348b538, 0x59f111f1b605d019,
        0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
        0xd807aa98a3030242, 0x12835b0145706fbe,
        0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
        0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
        0x9bdc06a725c71235, 0xc19bf174cf692694,
        0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
        0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
        0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
        0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
        0x983e5152ee66dfab, 0xa831c66d2db43210,
        0xb00327c898fb213f, 0xbf597fc7beef0ee4,
        0xc6e00bf33da88fc2, 0xd5a79147930aa725,
        0x06ca6351e003826f, 0x142929670a0e6e70,
        0x27b70a8546d22ffc, 0x2e1b21385c26c926,
        0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
        0x650a73548baf63de, 0x766a0abb3c77b2a8,
        0x81c2c92e47edaee6, 0x92722c851482353b,
        0xa2bfe8a14cf10364, 0xa81a664bbc423001,
        0xc24b8b70d0f89791, 0xc76c51a30654be30,
        0xd192e819d6ef5218, 0xd69906245565a910,
        0xf40e35855771202a, 0x106aa07032bbd1b8,
        0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
        0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
        0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
        0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
        0x748f82ee5defb2fc, 0x78a5636f43172f60,
        0x84c87814a1f0ab72, 0x8cc702081a6439ec,
        0x90befffa23631e28, 0xa4506cebde82bde9,
        0xbef9a3f7b2c67915, 0xc67178f2e372532b,
        0xca273eceea26619c, 0xd186b8c721c0c207,
        0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
        0x06f067aa72176fba, 0x0a637dc5a2c898a6,
        0x113f9804bef90dae, 0x1b710b35131c471b,
        0x28db77f523047d84, 0x32caab7b40c72493,
        0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
        0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
        0x5fcb6fab3ad6faec, 0x6c44198c4a475817 };

string padding(string s)
{
    stringstream ss;
    for(int i=0; i<s.size(); i++)
    ss<<bitset<8>(s[i]);
    string padded = ss.str();
    int len = padded.size();
    int add;
    int mod = padded.length()%1024;

    if((1024-mod)>=128)
    add = 1024-mod;
    else if((1024-mod)<128)
    add = 2048 - mod;

    padded+="1";
    for(int i=0; i<add-129; i++)
    padded+="0";

    string L = std::bitset<128>(len).to_string();
    padded+=L;

    return padded;
}

string getHex(string bin)
{
    if (bin == "0000")
        return "0";
    if (bin == "0001")
        return "1";
    if (bin == "0010")
        return "2";
    if (bin == "0011")
        return "3";
    if (bin == "0100")
        return "4";
    if (bin == "0101")
        return "5";
    if (bin == "0110")
        return "6";
    if (bin == "0111")
        return "7";
    if (bin == "1000")
        return "8";
    if (bin == "1001")
        return "9";
    if (bin == "1010")
        return "a";
    if (bin == "1011")
        return "b";
    if (bin == "1100")
        return "c";
    if (bin == "1101")
        return "d";
    if (bin == "1110")
        return "e";
    if (bin == "1111")
        return "f";
}

uint64_t toDec(string str)
{
    uint64_t val = bitset<64>(str).to_ullong();
    return val;
}

string toHex(uint64_t val)
{
    string temp = bitset<64>(val).to_string();

    string res, temp2;

    for(int i=0; i<temp.size(); i+=4)
    {
        temp2 = temp.substr(i, 4);
        res += getHex(temp2);
    }
    return res;
}

uint64_t sigma1(uint64_t word)
{
    return ROTR(word, 19) ^ ROTR(word, 61) ^ SHR(word, 6);
}

uint64_t sigma0(uint64_t word)
{
    return ROTR(word, 1) ^ ROTR(word, 8) ^ SHR(word, 7);
}

uint64_t sumA(uint64_t word)
{
    return ROTR(word, 28) ^ ROTR(word, 34) ^ ROTR(word, 39);
}

uint64_t sumE(uint64_t word)
{
    return ROTR(word, 14) ^ ROTR(word, 18) ^ ROTR(word, 41);
}

vector<uint64_t> getWord(string block)
{
    vector<uint64_t>Words(80);
    for(int i=0,k=0; i<block.length(); i+=64)
    Words[k++] = toDec(block.substr(i,64));

    for(int i=16; i<80; i++)
    {
        Words[i] = sigma1(Words[i-2])+Words[i-7]+sigma0(Words[i-15])+Words[i-16];
    }
    return Words;
}

string getHash(string message)
{
    string padded = padding(message);
    int rounds = padded.size()/1024;
    vector<string>blocks(rounds);

    for(int i=0,k=0; i<padded.size(); i+=1024)
    {
        blocks[k++] = padded.substr(i, 1024);
    }

    for(int i=0; i<rounds; i++)
    {
        vector<uint64_t>Words(getWord(blocks[i]));
        uint64_t a,b,c,d,e,f,g,h;
        a = H[0];
        b = H[1];
        c = H[2];
        d = H[3];
        e = H[4];
        f = H[5];
        g = H[6];
        h = H[7];
        for(int i=0; i<80; i++)
        {
            uint64_t T1 = h + Ch(e,f,g) + sumE(e) + Words[i] + K[i];
            uint64_t T2 = sumA(a) + Maj(a,b,c);
            h = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
        }
        H[0] += a;
        H[1] += b;
        H[2] += c;
        H[3] += d;
        H[4] += e;
        H[5] += f;
        H[6] += g;
        H[7] += h;
    }
    stringstream hashVal;

    for(int i=0; i<8; i++)
    {
        hashVal<<toHex(H[i]);
    }
    return hashVal.str();
}

int main()
{
    string message;
    getline(cin, message);
    cout<<getHash(message)<<endl;
    return 0;
}