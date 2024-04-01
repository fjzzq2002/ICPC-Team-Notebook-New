typedef long long ll;
inline ll cf(ll a,ll b,ll c) {return (__int128)a*b%c;}
ll qp_64(ll x,ll y,ll m) {
	ll a=1; x%=m;
	while(y) {
		if(y&1) a=cf(a,x,m);
		x=cf(x,x,m); y>>=1;
	}
	return a;
}
bool isprime(ll p) {
	if(p<=1) return 0;
	int b=0; ll a=p-1;
	while(!(a&1)) ++b, a>>=1;
	const int xx[]={2,3,5,7,11,13,17,19,23};
	for(auto x:xx) {
		if(x%p==0) continue;
		ll u=qp_64(x,a,p);
		if(u==1) goto ct;
		for(int j=0;j<b;j++) {
			if(j) u=cf(u,u,p);
			if(u==p-1) goto ct;
		}
		return 0; ct:;
	}
	return 1;
}
