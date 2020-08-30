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
