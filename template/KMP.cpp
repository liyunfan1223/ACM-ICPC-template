#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;

struct KMP{
    int nxt[N];
    void getNext(string &t) {
        nxt[0]=-1;
        for (int i=1,j=-1;i<=t.length();i++) {
            while(j!=-1 && t[i-1]!=t[j]) j=nxt[j];
            nxt[i]=++j;
        }
    }
    void getAns(string &s,string &t) {
        int len=t.length();
        for (int i=0,j=0;i<s.length();) {
            if (j==-1 || s[i]==t[j]) i++,j++;
            else j=nxt[j];
            if (j==len) printf("%d\n",i-j+1),j=nxt[j];
        }
    }
}kmp;

string s,t;

int main() {
    cin>>s;
    cin>>t;
    kmp.getNext(t);
    kmp.getAns(s,t);
    for (int i=1;i<=t.length();i++) printf("%d ",kmp.nxt[i]);
}
