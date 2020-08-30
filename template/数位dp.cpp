#include<bits/stdc++.h>
using namespace std;
const int MOD=1e9+7;

const int N=200,M=5000;

int digit[20];
int dp[N][M][2][2];
char n[200];

int dfs(int pos,int del,int eqb,int eqa) {
	if (pos==-1) {
		if (del>2500)
			return 1;
		else return 0;
	}
	if (dp[pos][del][eqb][eqa]!=-1) return dp[pos][del][eqb][eqa];
	int upb=eqb?n[pos]:9;
	int sum=0;
	for (int b=0;b<=upb;b++) {
		for (int a=0;a<=(eqa?b:9);a++) {
			sum=(sum+dfs(pos-1,del+a-b,eqb&&(b==n[pos]),eqa&&(a==b)))%MOD;
		}
	}
	dp[pos][del][eqb][eqa]=sum;
	return sum;
}

int main() {
	scanf("%s",n);
	int len=strlen(n);
	reverse(n,n+len);
	for (int i=0;i<len;i++) n[i]-='0';
	memset(dp,-1,sizeof(dp));
	printf("%d",dfs(len-1,2500,1,1));
	return 0;
}

