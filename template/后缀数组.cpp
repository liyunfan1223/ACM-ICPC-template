#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
int n;
char S[MAXN];
int s[MAXN];
int last[2];
//char s[MAXN];
struct SA {
    int sa[MAXN], ra[MAXN], height[MAXN];
    int t1[MAXN], t2[MAXN], c[MAXN];
    void build(int *str, int n, int m) {
        str[n] = 0;
        n++;
        int i, j, p, *x = t1, *y = t2;
        for (i = 0; i < m; i++) c[i] = 0;
        for (i = 0; i < n; i++) c[x[i] = str[i]]++;
        for (i = 1; i < m; i++) c[i] += c[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
        for (j = 1; j <= n; j <<= 1) {
            p = 0;
            for (i = n - j; i < n; i++) y[p++] = i;
            for (i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
            for (i = 0; i < m; i++) c[i] = 0;
            for (i = 0; i < n; i++) c[x[y[i]]]++;
            for (i = 1; i < m; i++) c[i] += c[i - 1];
            for (i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for (i = 1; i < n; i++)
                x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + j] == y[sa[i] + j]) ? p - 1 : p++;
            if (p >= n) break;
            m = p;
        }
        n--;
        for (int i = 0; i <= n; i++) ra[sa[i]] = i;
        for (int i = 0, j = 0, k = 0; i <= n; i++) {
            if (k) k--;
            j = sa[ra[i] - 1];
            while (str[i + k] == str[j + k]) k++;
            height[ra[i]] = k;
        }
        st_init(height, n);
    }
    int lg[MAXN], table[23][MAXN];
    void st_init(int *arr, int n) {
        if (!lg[0]) {
            lg[0] = -1;
            for (int i = 1; i < MAXN; i++)
                lg[i] = lg[i / 2] + 1;
        }
        for (int i = 1; i <= n; ++i)
            table[0][i] = arr[i];
        for (int i = 1; i <= lg[n]; ++i)
            for (int j = 1; j <= n; ++j)
                if (j + (1 << i) - 1 <= n)
                    table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
    }
    int lcp(int l, int r) {
        l = ra[l], r = ra[r];
        if (l > r) swap(l, r);
        ++l;
        int t = lg[r - l + 1];
        return min(table[t][l], table[t][r - (1 << t) + 1]);
    }
} sa;

/*bool cmp(int i, int j) {
    if (dis[i] != dis[j]) return dis[i] < dis[j];
    if (i + dis[i] > n) return true;
    if (j + dis[j] > n) return false;
    int lcp = sa.lcp(i + dis[i], j + dis[j]);
    return a[i + lcp + dis[i]] < a[j + lcp + dis[j]];
}*/

int main(){
    while(scanf("%d",&n)!=-1)
    {
        scanf("%s",S);
        last[0]=last[1]=0;
        s[n]=n+1;
        for (int i=n-1;i>=0;i--)
        {
            int now= S[i]=='a' ? 0 : 1;
            if (last[now]==0) s[i]=n;
            else s[i]=(last[now]-i);
            last[now]=i;
        }
        n++;
        sa.build(s,n,n+2);
        for(int i = n-1;i >=1 ;i--)
            printf("%d ",sa.sa[i]+1);
        printf("\n");
    }
    return 0;
}
