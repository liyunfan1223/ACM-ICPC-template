int bin(int x,int p) {
	int res=1;
	for (;p;p>>=1,x=(1ll*x*x)%MOD)
		if (p&1) res=(1ll*res*x)%MOD;
	return res;
}
