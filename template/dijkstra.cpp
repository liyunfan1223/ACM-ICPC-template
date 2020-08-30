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
