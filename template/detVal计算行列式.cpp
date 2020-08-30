#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int MOD=998244353,N=1e2+5;

LL a[N][N],ans;

int T,n,m,sign;

int M[N][N],M2[N][N];

struct Edge{
    int u,v,w;
}e[10005];

LL detVal(int n){
    sign=0;LL ans=1;
    for(int i=1;i<=n;i++){
        for(int j=i+1; j<=n; j++){//��ǰ֮���ÿһ�е�һ����Ҫת����0
            int x=i,y=j;
            while(a[y][i]){//����gcd�ķ�������ͣ�ؽ���շת���
                LL t=a[x][i]/a[y][i];
                for(int k=i; k<n; k++)
                    a[x][k]=(a[x][k]-a[y][k]*t)%MOD;
                swap(x, y);
            }
            if(x!=i){//�����ν�������D=-D'���н���
                for(int k=1;k<n;k++)
                    swap(a[i][k],a[x][k]);
                sign^= 1;//����ʽ*-1
            }
        }
        if(!a[i][i]){//б�Խ�����һ��0������Ϊ0
            return 0;
        }
        else ans=ans*a[i][i]%MOD;
    }
    if(sign!=0) ans*=-1;
    if(ans<0) ans+=MOD;
    return ans;
}

int main(){
    cin>>T;
    while(T--) {
        scanf("%d%d",&n,&m);
        memset(M,0,sizeof(M));
        for (int i=1;i<=m;i++) {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            e[i].u=u;e[i].v=v;e[i].w=w;
        }
        memset(a,0,sizeof(a));
        for (int k=1;k<=m;k++) {
            int i=e[k].u,j=e[k].v;
            a[i][i]++;a[j][j]++;
            a[i][j]--;a[j][i]--;
        }
        LL tot=detVal(n);
        tot=bin(tot,MOD-2);
        ans=0;
        for (int i=0;i<=30;i++)
        {
            memset(M2,0,sizeof(M2));
            memset(a,0,sizeof(a));
            for (int p=1;p<=m;p++) {
                if (e[p].w&(1<<i)) {
                    int j=e[p].u,k=e[p].v;
                    a[j][j]++;a[k][k]++;
                    a[j][k]--;a[k][j]--;
                }
            }
            LL cur=detVal(n-1);
            ans=(ans+(1ll*cur*tot)%MOD*(1<<i))%MOD;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
