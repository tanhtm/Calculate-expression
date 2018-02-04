#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include "AlgorithmBigInt.h"
using namespace std;
void balance (string &a, string &b){ // làm cho 2 số thành cùng size bằng cách thêm những số 0 đàng trc số bé hơn
    int sz_a = a.size(), sz_b= b.size();
    if(sz_a > sz_b) b= string(sz_a- sz_b,'0') +b;
    else a= string(sz_b- sz_a,'0') +a;
}
//So sánh
int cmp (string a, string b){ // so sánh 2 số
    // O(n)
    int szA= a.size(), szB= b.size();
    if(szA> szB) return 1;
    if(szA< szB) return -1;
    for( int i=0;i< szA;i++){
        if(a[i]> b[i]) return 1;
        if(a[i]< b[i]) return -1;
    }
    return 0;
}
//Tổng
string add (string a, string b){ // tổng 2 số
    // O(n)
    balance(a,b);
    int sz= a.size(), flag=0;
    for(int i=sz-1; i>=0;i--){
        a[i]= a[i] + b[i] + flag - '0';
        flag =0;
        if(a[i]>'9'){
            flag= 1;
            a[i]-= 10;
        }
    }
    if(flag==1) a = "1" + a;
    return a;
}
string sub(string a, string b){ // trừ , mặc định trả về kết quả dương
    // O(n)
    balance(a,b);
    if(a < b) swap(a,b);
    int sz= a.size(), flag=0;
    for(int i=sz-1; i>=0;i--){
        a[i]= a[i] - b[i] - flag + '0';
        flag =0;
        if(a[i]<'0'){
            flag= 1;
            a[i]+= 10;
        }
    }
    int i;
    for(i=0; i< sz; i++) if(a[i]!= '0') break;
    if(i!= 0) return string(a.begin()+i, a.end());
    return a;
}
string mulChar(string a, char c){ // nhân 1 big number với số có 1 chữ số
    // O(n)
    if(c=='0') return "0";
    if(c=='1') return a;
    int flag= 0;
    for(int i=a.size()-1;i>=0;i--){
        a[i]= (a[i]-'0') * (c - '0') + flag;
        flag =0;
        if(a[i]>= 10){
            flag= a[i]/10;
            a[i]= a[i]%10 + '0';
        }else a[i]+= '0';
    }
    if( flag !=0) a= char(flag + '0') + a;
    return a;
}

string divideBy10 (string a){
    if(a.size() == 1) return string("0");
    return string(a.begin(), a.end()-1);
}
string mulBy10(string a){
    a+='0';
    return a;
}
/// Phép nhân
string mul(string a, string b){ // thuật toán nhân
    // O(n*m)
    string kq;
    if(a.size()< b.size()) swap(a,b);
    if(b.size()== 1 ) return mulChar(a,b[0]);
    kq= mul(a, divideBy10(b));
    kq= mulBy10(kq); // nhân 10
    kq= add(kq,mulChar(a,b[b.size()-1]));
    //cout<<"mul "<<a<<" "<<b<<" "<<kq<<endl;
    return kq;
}
/// Phép chia
QR preDivide(string a, string b) // phép chia nhanh 2 số gần bằng nhau ( a > b và a.size == b.size hoặc a.size == b.size + 1)
{
    // O(n)
    char c='0';
    while ( cmp(a,b) != -1 ){ // chạy ko quá 9 vòng lặp
        c++;
        a= sub(a,b);
    }
    if(a == string()) a+= '0';
    return QR(string()+c,a);
}
void addChar(string &a, char c){
    if(a != "0") a.push_back(c);
    else a= string() + c;
}
QR divide(string a, string b){
    // n phép trừ
    if(b=="1") return QR(a,"0");
    if(cmp(a,b)== -1) return QR("0",a);
    QR qr= divide(divideBy10(a),b);
    string q = qr.first, r= qr.second;
    addChar(r,a[a.size() -1]);
    qr = preDivide(r,b);
    r= qr.second;
    addChar(q, qr.first[0]);
    return QR(q,r);
}
/// Phép lũy thừa
bool isEven(string a){ // kiểm tra số chẵn
    char c= a[a.size()-1];
    if(c%2 == 0) return true;
    return false;
}
string divideBy2( string s){ // chia đôi
    // O(n)
    if(s.size()==1 && s[0]<='1') return "0";
    int flag= 0,c,i=0;
    if(s[0] < '2'){
        i++;
        flag = s[0] - 48;
    }
    string res;
    for(i; i<s.size();i++){
        c= s[i] -48 + flag*10;
        flag= c%2;
        c= c/2;
        res += c+ 48;
    }
    if(res == string()) res= "0";
    return res;
}
string pow(string a,string b){
    // a^b ý tưởng giảm giần mũ đi 2 lần
    //O(n*m*log b) // log b phep nhan
    if(b=="2") return mul(a,a);
    if(b=="1") return a;
    string x= pow(a,divideBy2(b));
    x= mul(x,x);
    if(!isEven(b)) x= mul(x,a);
    return x;
}
string randomChar( int length){
    /* initialize random seed: */
    srand (time(NULL));
    string s;
    while(s.size() != length){
        int x= rand() % 10;
        s+= char(x+ 48);
    }
    if(s[0]=='0'){
        while(s[0] == '0'){
            int x= rand() % 10;
            s[0]= x+ 48;
        }
    }
    return s;
}
