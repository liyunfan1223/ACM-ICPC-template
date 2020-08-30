#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int N=1e7+5;

int vis[N],prime[N],countPrime;
void getPrime() {
	for (int i=2;i<N;i++) {
		if (!vis[i]) prime[++countPrime]=i;
		for (int j=1;j<=countPrime;j++) {
			if (i*prime[j]>=N) break;
			vis[i*prime[j]]=1;
			if (i%prime[j]==0) break;
		}
	}
}

int main() {
	getPrime();
	printf("%d",countPrime);
	return 0;
}

