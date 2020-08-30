#include<bits/stdc++.h>
using namespace std;

const int MAXN=5e2+5;

vector<int>G[MAXN];

int n,m,e,ans,u,v;

int vistime[MAXN],mch[MAXN];

bool dfs(int u,int tag) {
    if (vistime[u]==tag) return 0;
    vistime[u]=tag;
    for (auto v:G[u])
        if (mch[v]==0 || dfs(mch[v],tag)) {
            mch[v]=u;
            return 1;
        }
    return 0;
}

int main() {
    cin>>n>>m>>e;
    for (int i=1;i<=e;i++) {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
    }
    for (int i=1;i<=n;i++)
        if (dfs(i,i)) ans++;
    printf("%d\n",ans);
    return 0;
}
