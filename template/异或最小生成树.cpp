#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
const int INF=0x3f3f3f3f;

int l[N<<5],r[N<<5];

struct Edge{
    int t,w;
};

int root,num;

vector<Edge>G[N];

vector<int>P;

int u,v,w,n;

ll tot;

void dfs(int x,int fa,int now) {
    P.push_back(now);
    for (auto to:G[x]) {
        if (to.t!=fa)
            dfs(to.t,x,now^to.w);
    }
}
void MakeTrie(int subroot,int check,int x) {
    if (check==0) return;
    if ((x&check)==0) {
        if (l[subroot]==0) l[subroot]=++num;
        MakeTrie(l[subroot],check>>1,x);
    }
    else {
        if (r[subroot]==0) r[subroot]=++num;
        MakeTrie(r[subroot],check>>1,x);
    }
}
ll dfs3(int a,int b,int check) {
	if (!a || !b) return INF;
    if (check==0) return 0;
    ll t1,t2;
    t1=min(dfs3(l[a],l[b],check>>1),dfs3(r[a],r[b],check>>1));
    if (t1==INF)
		t2=check+min(dfs3(l[a],r[b],check>>1),dfs3(r[a],l[b],check>>1));
	else t2=INF;
    return min(t1,t2);
}
ll dfs2(int subroot,int check) {
    ll ret=0;
    if (l[subroot]) ret+=dfs2(l[subroot],check>>1);
    if (r[subroot]) ret+=dfs2(r[subroot],check>>1);
    if (l[subroot] && r[subroot]) {
        int t1=l[subroot],t2=r[subroot];
        ret+=check+dfs3(t1,t2,check>>1);
    }
    return ret;
}

int main() {
    cin>>n;
    for (int i=1;i<=n-1;i++) {
        scanf("%d%d%d",&u,&v,&w);
        G[u].push_back({v,w});
        G[v].push_back({u,w});
    }
    dfs(0,-1,0);
    sort(P.begin(),P.end());
    P.erase(unique(P.begin(),P.end()),P.end());
    for (auto x:P) {
        MakeTrie(0,1<<30,x);
    }
    printf("%lld\n",dfs2(0,1<<30));
    return 0;
}

