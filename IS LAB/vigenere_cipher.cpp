#include<bits/stdc++.h>
using namespace std;

string preprocess(string keyword,string text);
string encryption(string keyword,string text);
string decryption(string keyword,string encryptedString);

int main()
{
 	//Vigenere Cipher
	string keyword,text;

	cout<<"Enter Keyword: ";
	getline(cin,keyword);

	cout<<"Enter Text: ";
	getline(cin,text);

	if(keyword.size()<text.size()) keyword=preprocess(keyword,text);

    
	string encryptedString=encryption(keyword,text);
	cout<<"Encrypted Text: "<<encryptedString<<endl;

	string decryptedString=decryption(keyword,encryptedString);
	cout<<"Decrypted Text: "<<decryptedString<<endl;
 
    return 0;
}

string preprocess(string keyword,string text)
{
	int i=0;
	while(keyword.size()!=text.size() and i<text.size()){
		keyword+=text[i++];
	}
	return keyword;
}

string encryption(string keyword,string text)
{
	string encrypted;
	for(int i=0;i<keyword.size();i++){
		int temp = text[i]-97;
		int temp2 = keyword[i]-97;
		char ch = 'a'+(temp+temp2)%26;
		encrypted+=ch;
	}

	return encrypted;
}

string decryption(string keyword,string encryptedString)
{
	string decrypted;
	for(int i=0;i<keyword.size();i++){
		int temp = encryptedString[i]-97;
		int temp2 = keyword[i]-97;
		char ch = 'a'+((temp-temp2)+26)%26;
		decrypted+=ch;
	}

	return decrypted;
}