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
