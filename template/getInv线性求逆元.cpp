#include<bits/stdc++.h>
using namespace std;

const int N=3e6+5;

int inv[N],n,p;

void getInv(int n) {
    inv[1] = 1;
    for(int i=2 i<=n;i++)
        inv[i]=1ll*(p-p/i)*inv[p%i]%p;
}

int main() {
    cin>>n>>p;
    getInv(n);
    for (int i=1;i<=n;i++)
        printf("%d\n",inv[i]);
}
