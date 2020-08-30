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
