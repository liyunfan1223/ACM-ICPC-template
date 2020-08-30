#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5+5;
int ans = N,head[N],nxt[N*2],e[N*2],tot,n;//����ͼ�������ռ�
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
            cnt = max(cnt,s);//ÿ��ͳ����uΪ���������е�ĸ��������ֵ
            sum += s;
        }
    }
    cnt = max(cnt,n - sum - 1);//��ʣ��ĵ�ĸ����Ƚ�
    ans = min(ans,cnt);//�Ƚϸ������ֵ�е���Сֵ
    return sum + 1;//������uΪ���������еĵ�ĸ��������ϱ���
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
