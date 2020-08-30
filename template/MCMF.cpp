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
