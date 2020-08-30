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
