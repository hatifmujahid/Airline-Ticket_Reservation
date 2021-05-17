#include<iostream>
using namespace std;
string pass_encrypt(string password, const string pass)
{
    if(password.empty())
        return password;

    for (int j = 0; j < password.size(); j++)
        password[j] ^= pass[j%pass.size()];
    return password;
}

string pass_decrypt(string password, const string pass)
{
    if(password.empty()){
        return password;
    }
    for (int j = 0; j < password.size(); j++){
        password[j] ^= pass[j%pass.size()];
    }
    return password;
}

int main(){
    string pass="Hatif";
    string key="monkey";
    string k;
    k=pass_encrypt(pass, key);
    string password="Hatif";
    string key1="money";
    string l;
    l=pass_encrypt(password, key1);
    if(k==l){
        cout<<"sad";
    }
    else{
        cout<<"das";
    }
}