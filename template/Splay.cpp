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
