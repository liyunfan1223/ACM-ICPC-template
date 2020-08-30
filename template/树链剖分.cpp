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
