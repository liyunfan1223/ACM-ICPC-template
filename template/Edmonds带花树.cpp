#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAX_N=1000+20;
const int INF=0x3f3f3f3f;

int N,M;
int n,m;
int d[MAX_N];

bool Graph[MAX_N][MAX_N];
int Match[MAX_N];
bool InQueue[MAX_N],InPath[MAX_N],InBlossom[MAX_N];
int Head,Tail;
int Queue[MAX_N];
int Start,Finish;
int NewBase;
int Father[MAX_N],Base[MAX_N];
int Count;

void CreatGraph(){//O(n^3)
    int u,v;
    vector<int>V[MAX_N];
    memset(Graph,false,sizeof(Graph));
    int tot=1;
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&d[i]);
        for (int j=1;j<=d[i];j++) V[i].push_back(tot++);
    }
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        int x=tot++,y=tot++;
        for (int j=0;j<d[u];j++) Graph[V[u][j]][x]=Graph[x][V[u][j]]=1;
        for (int j=0;j<d[v];j++) Graph[V[v][j]][y]=Graph[y][V[v][j]]=1;
        Graph[x][y]=Graph[y][x]=1;
    }
    N=tot-1;
}
void Push(int u){
    Queue[Tail]=u;
    Tail++;
    InQueue[u]=true;
}
int Pop(){
    int res=Queue[Head];
    Head++;
    return res;
}
int FindCommonAncestor(int u,int v){
    memset(InPath,false,sizeof(InPath));
    while(1){
        u=Base[u];
        InPath[u]=1;
        if(u==Start)break;
        u=Father[Match[u]];
    }
    while(1){
        v=Base[v];
        if(InPath[v])break;
        v=Father[Match[v]];
    }
    return v;
}
void ResetTrace(int u){
    int v;
    while(Base[u]!=NewBase){
        v=Match[u];
        InBlossom[Base[u]]=InBlossom[Base[v]]=1;
        u=Father[v];
        if(Base[u]!=NewBase)Father[u]=v;
    }
}
void BloosomContract(int u,int v){
    NewBase=FindCommonAncestor(u,v);
    memset(InBlossom,false,sizeof(InBlossom));
    ResetTrace(u);
    ResetTrace(v);
    if(Base[u]!=NewBase)Father[u]=v;
    if(Base[v]!=NewBase)Father[v]=u;
    for(int tu=1;tu<=N;tu++){
        if(InBlossom[Base[tu]]){
            Base[tu]=NewBase;
            if(!InQueue[tu])Push(tu);
        }
    }
}
void FindAugmentingPath(){
    memset(InQueue,false,sizeof(InQueue));
    memset(Father,0,sizeof(Father));
    for(int i=1;i<=N;i++){
        Base[i]=i;
    }
    Head=Tail=1;
    Push(Start);
    Finish=0;
    while(Head<Tail){
        int u=Pop();
        for(int v=1;v<=N;v++){
            if(Graph[u][v]&&(Base[u]!=Base[v])&&(Match[u]!=v)){
                if((v==Start)||((Match[v]>0)&&Father[Match[v]]>0))BloosomContract(u,v);
                else if(Father[v]==0){
                    Father[v]=u;
                    if(Match[v]>0)Push(Match[v]);
                    else{
                        Finish=v;
                        return;
                    }
                }
            }
        }
    }
}
void AugmentPath(){
    int u,v,w;
    u=Finish;
    while(u>0){
        v=Father[u];
        w=Match[v];
        Match[v]=u;
        Match[u]=v;
        u=w;
    }
}
void Edmonds(){
    memset(Match,0,sizeof(Match));
    for(int u=1;u<=N;u++){
        if(Match[u]==0){
            Start=u;
            FindAugmentingPath();
            if(Finish>0)AugmentPath();
        }
    }
}
void PrintMatch(){
    Count=0;
    for(int u=1;u<=N;u++){
        if(Match[u]>0)Count++;
    }
    if(Count==N)printf("Yes\n");
    else printf("No\n");
}
int main(){
    while(scanf("%d%d",&n,&m)==2){
        CreatGraph();
        Edmonds();
        PrintMatch();
    }
}
