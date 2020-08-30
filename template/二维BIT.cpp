struct BIT{
    int C[N][N];
    int lowbit(int x) {return x&(-x);}
    void Modify(int i,int j,int delta){
        for(int x=i;x<=a;x+=lowbit(x))
            for(int y=j;y<=b;y+=lowbit(y)) {
                C[x][y]+=delta;
            }
    }
    int Sum(int i,int j)
    {
        int result=0;
        for(int x=i;x>0;x-=lowbit(x)) {
            for(int y=j;y>0;y-=lowbit(y)) {
                result+=C[x][y];
            }
        }
        return result;
    }
}bit;
