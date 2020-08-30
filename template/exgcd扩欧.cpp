#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=3e6+5;

void Exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) x = 1, y = 0;
    else Exgcd(b, a % b, y, x), y -= a / b * x;
}
int n,p;

int main()
{
    cin>>n>>p;
    for (int i=1;i<=n;i++)
    {
        ll x, y;
        Exgcd (i, p, x, y);
        x = (x % p + p) % p;
        printf ("%d\n", x); //x是a在mod p下的逆元
    }
}
