#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=2e5+5;

int pre[N][25],dfn[N],deep[N],sta[N],TOP,lg[N];

int A[N],n,s,NODE,x,y;

ll ans=0;

vector<int>G[N];
vector<int>E[N];
vector<int>D[N];

void DFS(int x,int fa) {
    int to;
    dfn[x]=++NODE;
    deep[x]=deep[fa]+1;
    D[deep[x]].push_back(x);
    pre[x][0]=fa;
    for (int i=1;(1<<i)<=deep[x];i++) pre[x][i]=pre[pre[x][i-1]][i-1];
    for (int i=0;i<G[x].size();i++) {
        to=G[x][i];
        if (to!=fa)
            DFS(to,x);
    }
}

int LCA(int x,int y) {
    if (deep[x]<deep[y]) swap(x,y);
    while(deep[x]>deep[y]) x=pre[x][lg[deep[x]-deep[y]]-1];
    if (x==y) return x;
    for (int i=lg[deep[x]]-1;i>=0;i--)
        if (pre[x][i]!=pre[y][i])
            x=pre[x][i],y=pre[y][i];
    return pre[x][0];
}

void Insert(int x) {
    if (TOP==1) {
        if (sta[TOP]!=x) sta[++TOP]=x;
        return;
    }
    int lca=LCA(x,sta[TOP]);
    while(TOP>=2 && dfn[sta[TOP-1]]>=dfn[lca]) {
        E[sta[TOP-1]].push_back(sta[TOP]);
        TOP--;
    }
    if (sta[TOP]!=lca) E[lca].push_back(sta[TOP]),sta[TOP]=lca;
    sta[++TOP]=x;
}

ll solve(int x) {
    if (E[x].empty())
        return 1LL*A[x];
    ll ret=0;
    for (int i=0;i<E[x].size();i++) {
        int to=E[x][i];
        ll sol=solve(to);
        if (sol!=0)
            ret+=max(1LL,sol-(deep[to]-deep[x]));
    }
    E[x].clear();
    return ret;
}

int main() {
    cin>>n>>s;
    for (int i=1;i<=n;i++) lg[i]=lg[i-1]+(1<<(lg[i-1])==i);
    for (int i=1;i<=n;i++) scanf("%d",&A[i]);
    for (int i=1;i<=n-1;i++) {
        scanf("%d%d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFS(s,0);
    for (int i=1;!D[i].empty();i++) {
        sort(D[i].begin(),D[i].end(),[&](int u,int v){return dfn[u]<dfn[v];});
        TOP=0;
        sta[++TOP]=s;
        for (int j=0;j<D[i].size();j++) {
            Insert(D[i][j]);
        }
        while(TOP>1) {
            E[sta[TOP-1]].push_back(sta[TOP]);
            TOP--;
        }
        ll sol=solve(s);
        if (sol) ans+=max(1LL,sol-1);
    }
    printf("%lld",ans);
    return 0;
}
