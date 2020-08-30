# 图论

单源最短路径（dijkstra）

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=2e5+5;
const LL INF=0x3f3f3f3f3f3f3f3f;

struct Dijkstra {
	struct Edge {
		int to;LL val;
	};
	struct Node {
		LL dis;int key;
		friend bool operator < (const Node &x,const Node &y) {
			return x.dis>y.dis;
		}
	};
	bool vis[N];
	int n,m,s;
	LL dis[N];
	vector<Edge>G[N];
	priority_queue<Node>Q;
	void init(int _n,int _s) {
		n=_n,s=_s;
		for (int i=0;i<=n;i++) G[i].clear();
		for (int i=1;i<=n;i++) dis[i]=INF;
	}
	void addEdge(int from,int to,LL val) {
		G[from].push_back({to,val});
	}
	void go() {
		dis[s]=0;
		Q.push({0,s});
		while(!Q.empty()) {
			Node top=Q.top(); Q.pop();
			int now=top.key;
			if (vis[now]) continue;
			vis[now]=1;
			for (int i=0;i<G[now].size();i++) {
				int to=G[now][i].to;
				if (dis[to]>dis[now]+G[now][i].val) {
					dis[to]=dis[now]+G[now][i].val;
					if (!vis[to]) Q.push({dis[to],to});
				}
			}
		}
	}
}dijkstra;

int n,m,s;

int main() {
	cin>>n>>m>>s;
	dijkstra.init(n,s);
	for (int i=1;i<=m;i++) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		dijkstra.addEdge(u,v,w);
	}
	dijkstra.go();
	for (int i=1;i<=n;i++) printf("%lld ",dijkstra.dis[i]);
	return 0;
}
```

树的重心

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5+5;
int ans = N,head[N],nxt[N*2],e[N*2],tot,n;//无向图开两倍空间
bool st[N];
void add(int u,int v) {
    e[tot] = v;
    nxt[tot] = head[u];
    head[u] = tot++;
}
int dfs(int u) {
    st[u] = true;
    int cnt = 0,sum = 0;
    for(int i=head[u];i != -1;i = nxt[i]) {
        int j = e[i];
        if(!st[j]) {
            int s = dfs(j);
            cnt = max(cnt,s);//每次统计以u为根的子树中点的个数的最大值
            sum += s;
        }
    }
    cnt = max(cnt,n - sum - 1);//与剩余的点的个数比较
    ans = min(ans,cnt);//比较各个最大值中的最小值
    return sum + 1;//返回以u为根的子树中的点的个数（加上本身）
}
int main() {
    cin >> n;
    int l,r;
    memset(head,-1,sizeof(head));
    for(int i=0;i<n;i++) {
        cin >> l >> r;
        add(l,r);
        add(r,l);
    }
    dfs(1);
    cout << ans;
    return 0;
}
```

虚树

```cpp
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
```

最大流Dinic

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int N=5e3+5;

//理论上界O(N^2*M)
//二分图最大匹配时间复杂度O(sqrt(N)*M)
struct Dinic{
	struct Edge{
		int to;LL v;int rev;
	};
	int n,s,t,dep[N],_cur[N];
	bool used[N];
	vector<Edge>G[N];
	queue<int>L;
	void init(int n_,int s_,int t_) {
		n=n_,s=s_,t=t_;
		for (int i=0;i<=n;i++) G[i].clear();
	}
	void addEdge(int x,int y,LL v) {
		G[x].push_back({y,v,G[y].size()});
		G[y].push_back({x,0,G[x].size()-1});
	}
	bool bfs() {
		memset(used,0,sizeof(used));
		dep[s]=1,used[s]=1;
		L.push(s);
		while(!L.empty()) {
			int cur=L.front();
			L.pop();
			for (int i=0;i<G[cur].size();i++) {
				Edge &e=G[cur][i];
				if (!used[e.to] && e.v>0) {
					dep[e.to]=dep[cur]+1;
					used[e.to]=1;
					L.push(e.to);
				}
			}
		}
		return used[t];
	}
	LL dfs(int c,LL flow) {
		if (c==t ||flow==0) return flow;
		LL ret=0,f;
		for (int &i=_cur[c];i<G[c].size();i++) {
			Edge &e=G[c][i];
			if (dep[e.to]==dep[c]+1 && (f=dfs(e.to,min(flow,e.v)))>0) {
				ret+=f,flow-=f,e.v-=f;
				G[e.to][e.rev].v+=f;
				if (!flow) break;
			}
		}
		return ret;
	}
	LL go() {
		LL ans=0;
		while(bfs()) {
			memset(_cur,0,sizeof(_cur));
			ans+=dfs(s,1LL*100*INT_MAX);
		}
		return ans;
	}
}dinic;

int n,m,e,s,t;
int main() {
	cin>>n>>m>>s>>t;
	dinic.init(n,s,t);
	for (int i=1;i<=m;i++) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		dinic.addEdge(u,v,w);
	}
	printf("%lld\n",dinic.go());
	return 0;
}
```

最小费用最大流（MCMF）

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=1e5+5;
const int INF=0x3f3f3f3f3f3f3f3f;

struct MCMF {
	struct E{
		int from,to;
		LL flow,dis;
	};
	queue<int>Q;
	vector<E>edge;
	vector<int>G[N];
	bool vis[N];
	int n,m,s,t,pre[N],last[N];
	LL dis[N],flow[N],maxflow,mincost;
	void init(int _n,int _s,int _t) {
		n=_n,s=_s,t=_t;
		for (int i=0;i<=n;i++) G[i].clear();
		edge.clear();m=0;
		maxflow=mincost=0;
	}
	void addEdge(int from,int to,int flow,int cost) {
		edge.push_back({from,to,flow,cost});
		edge.push_back({to,from,0,-cost});
		G[from].push_back(m++);
		G[to].push_back(m++);
	}
	bool spfa(int s,int t) {
		for (int i=0;i<=n;i++) {
			dis[i]=INF;flow[i]=INF;vis[i]=0;
		}
		Q.push(s);dis[s]=0;vis[s]=1;pre[t]=-1;
		while(!Q.empty()) {
			int now=Q.front();
			Q.pop();
			vis[now]=0;
			for (int i:G[now]) {
				if (edge[i].flow && dis[edge[i].to]>dis[now]+edge[i].dis) {
					dis[edge[i].to]=dis[now]+edge[i].dis;
					pre[edge[i].to]=now;
					last[edge[i].to]=i;
					flow[edge[i].to]=min(flow[now],edge[i].flow);
					if (!vis[edge[i].to]) {
						vis[edge[i].to]=1;
						Q.push(edge[i].to);
					}
				}
			}
		}
		return pre[t]!=-1;
	}
	LL go() {
		while(spfa(s,t)) {
			int now=t;
			maxflow+=flow[t];
			mincost+=flow[t]*dis[t];
			while(now!=s) {
				edge[last[now]].flow-=flow[t];
				edge[last[now]^1].flow+=flow[t];
				now=pre[now];
			}
		}
		return mincost;
	}
}mcmf;

int n,m,s,t;

int main() {
	cin>>n>>m>>s>>t;
	mcmf.init(n,s,t);
	for (int i=1;i<=m;i++) {
		int u,v;LL w,f;
		scanf("%d%d%lld%lld",&u,&v,&w,&f);
		mcmf.addEdge(u,v,w,f);
	}
	mcmf.go();
	printf("%lld %lld\n",mcmf.maxflow,mcmf.mincost);
	return 0;
}
```

二分图最大匹配（匈牙利算法）

```cpp
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
```

一般图最大匹配（Edmonds带花树）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAX_N=1000+20;
const int INF=0x3f3f3f3f;

int N,M;
int n,m;
int d[MAX_N];

bool Graph[MAX_N][MAX_N];
int Match[MAX_N];
bool InQueue[MAX_N],InPath[MAX_N],InBlossom[MAX_N];
int Head,Tail;
int Queue[MAX_N];
int Start,Finish;
int NewBase;
int Father[MAX_N],Base[MAX_N];
int Count;

void CreatGraph(){//O(n^3)
    int u,v;
    vector<int>V[MAX_N];
    memset(Graph,false,sizeof(Graph));
    int tot=1;
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&d[i]);
        for (int j=1;j<=d[i];j++) V[i].push_back(tot++);
    }
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        int x=tot++,y=tot++;
        for (int j=0;j<d[u];j++) Graph[V[u][j]][x]=Graph[x][V[u][j]]=1;
        for (int j=0;j<d[v];j++) Graph[V[v][j]][y]=Graph[y][V[v][j]]=1;
        Graph[x][y]=Graph[y][x]=1;
    }
    N=tot-1;
}
void Push(int u){
    Queue[Tail]=u;
    Tail++;
    InQueue[u]=true;
}
int Pop(){
    int res=Queue[Head];
    Head++;
    return res;
}
int FindCommonAncestor(int u,int v){
    memset(InPath,false,sizeof(InPath));
    while(1){
        u=Base[u];
        InPath[u]=1;
        if(u==Start)break;
        u=Father[Match[u]];
    }
    while(1){
        v=Base[v];
        if(InPath[v])break;
        v=Father[Match[v]];
    }
    return v;
}
void ResetTrace(int u){
    int v;
    while(Base[u]!=NewBase){
        v=Match[u];
        InBlossom[Base[u]]=InBlossom[Base[v]]=1;
        u=Father[v];
        if(Base[u]!=NewBase)Father[u]=v;
    }
}
void BloosomContract(int u,int v){
    NewBase=FindCommonAncestor(u,v);
    memset(InBlossom,false,sizeof(InBlossom));
    ResetTrace(u);
    ResetTrace(v);
    if(Base[u]!=NewBase)Father[u]=v;
    if(Base[v]!=NewBase)Father[v]=u;
    for(int tu=1;tu<=N;tu++){
        if(InBlossom[Base[tu]]){
            Base[tu]=NewBase;
            if(!InQueue[tu])Push(tu);
        }
    }
}
void FindAugmentingPath(){
    memset(InQueue,false,sizeof(InQueue));
    memset(Father,0,sizeof(Father));
    for(int i=1;i<=N;i++){
        Base[i]=i;
    }
    Head=Tail=1;
    Push(Start);
    Finish=0;
    while(Head<Tail){
        int u=Pop();
        for(int v=1;v<=N;v++){
            if(Graph[u][v]&&(Base[u]!=Base[v])&&(Match[u]!=v)){
                if((v==Start)||((Match[v]>0)&&Father[Match[v]]>0))BloosomContract(u,v);
                else if(Father[v]==0){
                    Father[v]=u;
                    if(Match[v]>0)Push(Match[v]);
                    else{
                        Finish=v;
                        return;
                    }
                }
            }
        }
    }
}
void AugmentPath(){
    int u,v,w;
    u=Finish;
    while(u>0){
        v=Father[u];
        w=Match[v];
        Match[v]=u;
        Match[u]=v;
        u=w;
    }
}
void Edmonds(){
    memset(Match,0,sizeof(Match));
    for(int u=1;u<=N;u++){
        if(Match[u]==0){
            Start=u;
            FindAugmentingPath();
            if(Finish>0)AugmentPath();
        }
    }
}
void PrintMatch(){
    Count=0;
    for(int u=1;u<=N;u++){
        if(Match[u]>0)Count++;
    }
    if(Count==N)printf("Yes\n");
    else printf("No\n");
}
int main(){
    while(scanf("%d%d",&n,&m)==2){
        CreatGraph();
        Edmonds();
        PrintMatch();
    }
}
```

# 数据结构

树状数组

```cpp
//第一个位置从1开始(0不可用)
struct BIT{
    LL tr[N];
    int lowbit(int x){ return x&(-x); }
    void clr(int x){
        while(x<SZ)
        {
            tr[x]=0;
            x+=lowbit(x);
        }
    }
    void add(int v,int x){
        while(x<N)
        {
            tr[x]+=v;
            x+=lowbit(x);
        }
    }
    LL sum(int x){
        LL sum=0;
        while(x>0)
        {
            sum+=tr[x];
            x-=lowbit(x);
        }
        return sum;
    }
}bit;
//BIT求MEX
struct BIT {
	int bucket[N],tr[N];
	int lowbit(int x){
    	return x&(-x);
	}
    void add(int x,int v) {
    	if (x<SZ) {
			bucket[x]+=v;
			if (bucket[x]==1 && v==1|| bucket[x]==0 && v==-1)
				while(x<SZ)	{
					tr[x]+=v;
					x+=lowbit(x);
				}
		}
    }
    int sum(int x) {
        int sum=0;
        while(x>0) {
            sum+=tr[x];
            x-=lowbit(x);
        }
        return sum;
    }
    int MEX() {
		int l=1,r=SZ-1;
		while(l<r) {
			int mid=(l+r)>>1;
			if (sum(mid)<mid)
				r=mid;
			else l=mid+1;
		}
		return l;
    }
}bit;
```

二维树状数组

```cpp
struct BIT{
    int C[N][N];
    int lowbit(int x) {return x&(-x);}
    void Modify(int i,int j,int delta){
        for(int x=i;x<=a;x+=lowbit(x))
            for(int y=j;y<=b;y+=lowbit(y)) {
                C[x][y]+=delta;
            }
    }
    int Sum(int i,int j)
    {
        int result=0;
        for(int x=i;x>0;x-=lowbit(x)) {
            for(int y=j;y>0;y-=lowbit(y)) {
                result+=C[x][y];
            }
        }
        return result;
    }
}bit;
```

线段树

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int N=1e5+5;

struct Segtree {
	LL t[N<<4],lz[N<<4];
	void push_down(int o,int l,int r) {
		if (lz[o]) {
			int mid=(l+r)>>1;
			t[o*2]+=lz[o]*(mid-l+1);
			t[o*2+1]+=lz[o]*(r-mid);
			lz[o*2]+=lz[o];
			lz[o*2+1]+=lz[o];
			lz[o]=0;
		}
	}
	void push_up(int o,int l,int r) {
		t[o]=t[o*2]+t[o*2+1];
	}
	void update(int o,int l,int r,LL v) {
		t[o]+=v*(r-l+1);
		lz[o]+=v;
	}
	void build(int o,int l,int r) {
		lz[o]=0;
		if (l==r) {
			scanf("%lld",&t[o]);
			return;
		}
		int mid=(l+r)>>1;
		build(o*2,l,mid);
		build(o*2+1,mid+1,r);
		push_up(o,l,r);
	}
	void modify(int o,int l,int r,int tl,int tr,LL v) {
		if (tl<=l && tr>=r) {
			update(o,l,r,v);
			return;
		}
		push_down(o,l,r);
		int mid=(l+r)>>1;
		if (tl<=mid) modify(o*2,l,mid,tl,tr,v);
		if (tr>mid) modify(o*2+1,mid+1,r,tl,tr,v);
		push_up(o,l,r);
	}
	LL query(int o,int l,int r,int tl,int tr) {
		if (tl<=l && r<=tr) return t[o];
		push_down(o,l,r);
		int mid=(l+r)>>1;
		if (tr<=mid) return query(o*2,l,mid,tl,tr);
		if (tl>mid) return query(o*2+1,mid+1,r,tl,tr);
		return query(o*2,l,mid,tl,tr)+query(o*2+1,mid+1,r,tl,tr);
	}
}segtree;

int n,m,x,y,k,op;

int main() {
	cin>>n>>m;
	segtree.build(1,1,n);
	for (int i=1;i<=m;i++) {
		scanf("%d",&op);
		switch (op){
			case 1:
				scanf("%d%d%d",&x,&y,&k);
				segtree.modify(1,1,n,x,y,k);
				break;
			case 2:
				scanf("%d%d",&x,&y);
				printf("%lld\n",segtree.query(1,1,n,x,y));
		}
	}
	return 0;
}
```

Splay

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5,INF=0x3f3f3f3f;

struct Splay_tree{
    int root=0,ch[N][2],ff[N],sz[N],cnt[N],val[N],points;
    void push_up(int x) {
        sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+cnt[x];
    }
    void Rotate(int x) {
        int y=ff[x],z=ff[y],k=ch[y][1]==x;
        ch[z][ch[z][1]==y]=x,ff[x]=z;
        ch[y][k]=ch[x][k^1],ff[ch[y][k]]=y;
        ch[x][k^1]=y,ff[y]=x;
        push_up(y);push_up(x);
    }
    void Splay(int x,int goal) {
        while(ff[x]!=goal) {
            int y=ff[x],z=ff[y];
            if (z!=goal) {
                if ((ch[z][1]==y) ^ (ch[y][1]==x)) Rotate(x);
                else Rotate(y);
            }
            Rotate(x);
        }
        if (goal==0) root=x;
    }
    void Insert(int x) {
        int u=root,f=0;
        while(u && val[u]!=x) {
            f=u;
            u=ch[u][val[u]<x];
        }
        if (u) cnt[u]++;
        else {
            u=++points;
            if (f) ch[f][x>val[f]]=u;
            ch[u][0]=ch[u][1]=0;
            ff[u]=f; val[u]=x;
            sz[u]=1; cnt[u]=1;
        }
        Splay(u,0);
    }
    void Find(int x) {
        int u=root;
        if (!u) return;
        while(ch[u][x>val[u]] && x!=val[u]) u=ch[u][x>val[u]];
        Splay(u,0);
    }
    int Next(int x,int f) {
        Find(x);
        int u=root;
        if ((val[u]>x && f) || (val[u]<x && !f)) return u;
        u=ch[u][f];
        while(ch[u][f^1]) u=ch[u][f^1];
        return u;
    }
    void Delete(int x) {
        int pre=Next(x,0),nxt=Next(x,1);
        Splay(pre,0);Splay(nxt,pre);
        int del=ch[nxt][0];
        if (cnt[del]>1) {
            cnt[del]--;
            Splay(del,0);
        }
        else {
            ch[nxt][0]=0;
            //Splay(nxt,0);
        }
    }
    int Rank(int x) {
        Find(x);
        return sz[ch[root][0]];
    }
    int K_th(int x) {
        int u=root;
        if (sz[u]<x) return -1;
        while(true) {
            if (sz[ch[u][0]]+cnt[u]<x) {
                x-=sz[ch[u][0]]+cnt[u];
                u=ch[u][1];
            }
            else if (sz[ch[u][0]]>=x) {
                u=ch[u][0];
            }
            else return u;
        }
    }
}splay;

int n,opt,x;

int main() {
    cin>>n;
    splay.Insert(-INF);splay.Insert(INF);
    while(n--) {
        scanf("%d%d",&opt,&x);
        switch(opt) {
            case 1:splay.Insert(x);break;
            case 2:splay.Delete(x);break;
            case 3:printf("%d\n",splay.Rank(x));break;
            case 4:printf("%d\n",splay.val[splay.K_th(x+1)]);break;
            case 5:printf("%d\n",splay.val[splay.Next(x,0)]);break;
            case 6:printf("%d\n",splay.val[splay.Next(x,1)]);break;
        }
    }
    return 0;
}
```

树链剖分

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int N=1e5+5;

LL q[N];

int n,m,r,p,ord[N];

struct segTree {
	LL t[N<<4];
	LL lztag[N<<4];
	void init() {
		memset(t,0,sizeof(t));
		memset(lztag,0,sizeof(lztag));
	}
	void pushdown(int o,int l,int r) {
		if (lztag[o]) {
			int mid=(l+r)>>1;
			t[o*2]+=lztag[o]*(mid-l+1);
			t[o*2]%=p;
			t[o*2+1]+=lztag[o]*(r-mid);
			t[o*2+1]%=p;
			lztag[o*2]+=lztag[o];
			lztag[o*2]%=p;
			lztag[o*2+1]+=lztag[o];
			lztag[o*2+1]%=p;
			lztag[o]=0;
		}
	}
	void pushup(int o,int l,int r) {
		t[o]=(t[o*2]+t[o*2+1])%p;
	}
	void build(int o,int l,int r) {
		if (l==r) {
			t[o]=ord[l]%p;
			return;
		}
		int mid=(l+r)>>1;
		build(o*2,l,mid);
		build(o*2+1,mid+1,r);
		pushup(o,l,r);
	}
	void modify(int o,int l,int r,int tl,int tr,int v) {
		if (tl<=l && r<=tr) {
			t[o]+=1LL*v*(r-l+1);
			t[o]%=p;
			lztag[o]+=v;
			lztag[o]%=p;
			return;
		}
		int mid=(l+r)>>1;
		pushdown(o,l,r);
		if (tl<=mid) modify(o*2,l,mid,tl,tr,v);
		if (tr>mid) modify(o*2+1,mid+1,r,tl,tr,v);
		pushup(o,l,r);
	}
	LL query(int o,int l,int r,int tl,int tr) {
		if (tl<=l && tr>=r) return t[o];
		int mid=(l+r)>>1;
		pushdown(o,l,r);
		if (tr<=mid) return query(o*2,l,mid,tl,tr)%p;
		if (tl>mid) return query(o*2+1,mid+1,r,tl,tr)%p;
		return (query(o*2,l,mid,tl,tr)+query(o*2+1,mid+1,r,tl,tr))%p;
	}
}ST;

int sz[N],dep[N],son[N],fa[N],top[N],num[N],cnt;

vector<int>G[N];

void init() {
	memset(sz,0,sizeof(sz));
	cnt=0;
	fa[r]=-1;
	dep[r]=1;
	top[r]=r;
}

void dfs1(int x) {
	int mxson=-1;
	son[x]=-1;
	for (auto to:G[x]) {
		if (to==fa[x]) continue;
		dep[to]=dep[x]+1;
		fa[to]=x;
		dfs1(to);
		if (sz[to]>mxson) mxson=sz[to], son[x]=to;
		sz[x]+=sz[to];
	}
	sz[x]++;
}
void dfs2(int x,int tp) {
	num[x]=++cnt;
	ord[cnt]=q[x];
	top[x]=tp;
	if (~son[x]) dfs2(son[x],tp);
	for (auto to:G[x]) {
		if (to==fa[x] || to==son[x]) continue;
		dfs2(to,to);
	}
}
void chainModify(int x,int y,int z) {
	while(top[x]!=top[y]) {
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		ST.modify(1,1,n,num[top[x]],num[x],z);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	ST.modify(1,1,n,num[x],num[y],z);
}
LL chainQuery(int x,int y) {
	LL res=0;
	while(top[x]!=top[y]) {
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		res+=ST.query(1,1,n,num[top[x]],num[x]);
		res%=p;
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	res+=ST.query(1,1,n,num[x],num[y]);
	res%=p;
	return res;
}
void subtreeModify(int x,int z) {
    ST.modify(1,1,n,num[x],num[x]+sz[x]-1,z);
}
LL subtreeQuery(int x) {
    return ST.query(1,1,n,num[x],num[x]+sz[x]-1);
}

int main() {
	cin>>n>>m>>r>>p;
	for (int i=1;i<=n;i++) {
		scanf("%lld",&q[i]);
		q[i]%=p;
	}
	for (int i=1;i<=n-1;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	init();
	dfs1(r);
	dfs2(r,r);
	ST.build(1,1,n);
	for (int i=1;i<=m;i++) {
		int opt,x,y;
		LL z;
		scanf("%d",&opt);
		if (opt==1) {
			scanf("%d%d%lld",&x,&y,&z);
			z%=p;
			chainModify(x,y,z);
		}
		if (opt==2) {
			scanf("%d%d",&x,&y);
			printf("%lld\n",chainQuery(x,y));
		}
		if (opt==3) {
			scanf("%d%lld",&x,&z);
			z%=p;
			subtreeModify(x,z);
		}
		if (opt==4) {
			scanf("%d",&x);
			printf("%lld\n",subtreeQuery(x));
		}
	}
	return 0;
}
```

# 数学

快速幂

```cpp
int bin(int x,int p) {
	int res=1;
	for (;p;p>>=1,x=(1ll*x*x)%MOD)
		if (p&1) res=(1ll*res*x)%MOD;
	return res;
}
```

exgcd扩展欧几里得（求ax+by=0整数解）

```cpp
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
```

欧拉筛

```cpp
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
```

线性求逆元

```cpp
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
```

行列式计算/生成树计数

```cpp
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
        for(int j=i+1; j<=n; j++){//当前之后的每一行第一个数要转化成0
            int x=i,y=j;
            while(a[y][i]){//利用gcd的方法，不停地进行辗转相除
                LL t=a[x][i]/a[y][i];
                for(int k=i; k<n; k++)
                    a[x][k]=(a[x][k]-a[y][k]*t)%MOD;
                swap(x, y);
            }
            if(x!=i){//奇数次交换，则D=-D'整行交换
                for(int k=1;k<n;k++)
                    swap(a[i][k],a[x][k]);
                sign^= 1;//行列式*-1
            }
        }
        if(!a[i][i]){//斜对角中有一个0，则结果为0
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
            ans=(ans+(1ll*cur*tot)%M(1<<i))%MOD;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

点和向量旋转

```cpp
//任意点(x,y)，绕一个坐标点(rx0,ry0)逆时针旋转a角度后的新的坐标设为(x0, y0)，有公式：
// x0= (x-rx0)*cos(a)-(y-ry0)*sin(a)+rx0 ;
// y0= (x-rx0)*sin(a)+(y-ry0)*cos(a)+ry0 ;

//任意向量(x,y)，绕一个坐标点(rx0,ry0)逆时针旋转a角度后的新的向量设为(x0, y0)，有公式：
// x0= x*cos(a)-y*sin(a);
// y0= x*sin(a)+y*cos(a);
void Rotate(double &x,double &y,double &vx,double &vy,double x0,double y0,double a)
{
	double x_,vx_,y_,vy_;
	x_=(x-x0)*cos(a)-(y-y0)*sin(a)+x0;
	vx_=vx*cos(a)-vy*sin(a);
	y_=(x-x0)*sin(a)+(y-y0)*cos(a)+y0;
	vy_=vx*sin(a)+vy*cos(a);
	x=x_,y=y_,vx=vx_,vy=vy_;
}
```

# 算法

CDQ分治

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int N=1e5+5;

struct BIT{
    int tr[N];
    int lowbit(int x){ return x&(-x); }
    void clr(int x){
        while(x<N)
        {
            tr[x]=0;
            x+=lowbit(x);
        }
    }
    void add(int v,int x){
        while(x<N)
        {
            tr[x]+=v;
            x+=lowbit(x);
        }
    }
    int sum(int x){
        int sum=0;
        while(x>0)
        {
            sum+=tr[x];
            x-=lowbit(x);
        }
        return sum;
    }
}bit;

struct node{
    int id,x,y,z;
    bool operator==(node &t){
        return x==t.x && y==t.y && z==t.z;
    }
}A[N],tmp[N];

int n,k,ans[N],cnt[N];

void CDQ(int l,int r)
{
    if (l==r) return;
    int mid=(l+r)>>1;
    CDQ(l,mid);
    CDQ(mid+1,r);
    int p1=l,p2=mid+1,pt=l;
    while(p1!=mid+1 || p2!=r+1)
    {
        if (p1==mid+1 || A[p2].y<A[p1].y && p2!=r+1)
        {
            ans[A[p2].id]+=bit.sum(A[p2].z);
            tmp[pt++]=A[p2];
            p2++;
        }
        else
        {
            bit.add(1,A[p1].z);
            tmp[pt++]=A[p1];
            p1++;
        }
    }
    for (int i=l;i<=mid;i++) bit.clr(A[i].z);
    for (int i=l;i<=r;i++) A[i]=tmp[i];
}

bool cmp(node &a,node &b){
    if (a.x==b.x && a.y==b.y)
        return a.z<b.z;
    else if(a.x==b.x) return a.y<b.y;
    else return a.x<b.x;
}

int main()
{
    cin>>n>>k;
    for (int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&A[i].x,&A[i].y,&A[i].z);
        A[i].id=i;
    }
    sort(A+1,A+1+n,cmp);
    int same=0;
    for (int i=n;i>=2;i--)
    {
        if (A[i]==A[i-1]) ans[A[i-1].id]+=++same;
        else same=0;
    }
    CDQ(1,n);
    for (int i=1;i<=n;i++) cnt[ans[i]]++;
    for (int i=0;i<n;i++) printf("%d\n",cnt[i]);
    return 0;
}

```

数位DP

```cpp
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
```

异或最小生成树

```cpp
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
```

# 字符串

KMP

```cpp
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
```

后缀数组SA

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
int n;
char S[MAXN];
int s[MAXN];
int last[2];
//char s[MAXN];
struct SA {
    int sa[MAXN], ra[MAXN], height[MAXN];
    int t1[MAXN], t2[MAXN], c[MAXN];
    void build(int *str, int n, int m) {
        str[n] = 0;
        n++;
        int i, j, p, *x = t1, *y = t2;
        for (i = 0; i < m; i++) c[i] = 0;
        for (i = 0; i < n; i++) c[x[i] = str[i]]++;
        for (i = 1; i < m; i++) c[i] += c[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
        for (j = 1; j <= n; j <<= 1) {
            p = 0;
            for (i = n - j; i < n; i++) y[p++] = i;
            for (i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
            for (i = 0; i < m; i++) c[i] = 0;
            for (i = 0; i < n; i++) c[x[y[i]]]++;
            for (i = 1; i < m; i++) c[i] += c[i - 1];
            for (i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for (i = 1; i < n; i++)
                x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + j] == y[sa[i] + j]) ? p - 1 : p++;
            if (p >= n) break;
            m = p;
        }
        n--;
        for (int i = 0; i <= n; i++) ra[sa[i]] = i;
        for (int i = 0, j = 0, k = 0; i <= n; i++) {
            if (k) k--;
            j = sa[ra[i] - 1];
            while (str[i + k] == str[j + k]) k++;
            height[ra[i]] = k;
        }
        st_init(height, n);
    }
    int lg[MAXN], table[23][MAXN];
    void st_init(int *arr, int n) {
        if (!lg[0]) {
            lg[0] = -1;
            for (int i = 1; i < MAXN; i++)
                lg[i] = lg[i / 2] + 1;
        }
        for (int i = 1; i <= n; ++i)
            table[0][i] = arr[i];
        for (int i = 1; i <= lg[n]; ++i)
            for (int j = 1; j <= n; ++j)
                if (j + (1 << i) - 1 <= n)
                    table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
    }
    int lcp(int l, int r) {
        l = ra[l], r = ra[r];
        if (l > r) swap(l, r);
        ++l;
        int t = lg[r - l + 1];
        return min(table[t][l], table[t][r - (1 << t) + 1]);
    }
} sa;

/*bool cmp(int i, int j) {
    if (dis[i] != dis[j]) return dis[i] < dis[j];
    if (i + dis[i] > n) return true;
    if (j + dis[j] > n) return false;
    int lcp = sa.lcp(i + dis[i], j + dis[j]);
    return a[i + lcp + dis[i]] < a[j + lcp + dis[j]];
}*/

int main(){
    while(scanf("%d",&n)!=-1)
    {
        scanf("%s",S);
        last[0]=last[1]=0;
        s[n]=n+1;
        for (int i=n-1;i>=0;i--)
        {
            int now= S[i]=='a' ? 0 : 1;
            if (last[now]==0) s[i]=n;
            else s[i]=(last[now]-i);
            last[now]=i;
        }
        n++;
        sa.build(s,n,n+2);
        for(int i = n-1;i >=1 ;i--)
            printf("%d ",sa.sa[i]+1);
        printf("\n");
    }
    return 0;
}
```
