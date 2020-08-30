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
