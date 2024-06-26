/**
 * Author: Ziqian Zhong
 * Description: Linear recurrence toolkit.
 */
typedef long long ll;
using namespace std;
const int MOD=1e9+7; ll qp(ll a,ll b) {a%=MOD;/*...*/}
namespace linear_seq {
inline vector<int> BM(vector<int> x) {
	vector<int> ls,cur;
	int pn=0,lf,ld;
	for(int i=0;i<int(x.size());++i) {
		ll t=-x[i]%MOD;
		for(int j=0;j<int(cur.size());++j)
			t=(t+x[i-j-1]*(ll)cur[j])%MOD;
		if(!t) continue;
		if(!cur.size())
		{cur.resize(i+1); lf=i; ld=t; continue;}
		ll k=-t*qp(ld,MOD-2)%MOD;
		vector<int> c(i-lf-1); c.pb(-k);
		for(int j=0;j<int(ls.size());++j) c.pb(ls[j]*k%MOD);
		if(c.size()<cur.size()) c.resize(cur.size());
		for(int j=0;j<int(cur.size());++j)
			c[j]=(c[j]+cur[j])%MOD;
		if(i-lf+(int)ls.size()>=(int)cur.size())
			ls=cur,lf=i,ld=t;
		cur=c;
	}
	vector<int>&o=cur;
	for(int i=0;i<int(o.size());++i)
		o[i]=(o[i]%MOD+MOD)%MOD;
	return o;
}
int N; ll a[SZ],h[SZ],t_[SZ],s[SZ],t[SZ];
inline void mull(ll*p,ll*q) {
	for(int i=0;i<N+N;++i) t_[i]=0;
	for(int i=0;i<N;++i) if(p[i])
		for(int j=0;j<N;++j)
			t_[i+j]=(t_[i+j]+p[i]*q[j])%MOD;
	for(int i=N+N-1;i>=N;--i) if(t_[i])
		for(int j=N-1;~j;--j)
			t_[i-j-1]=(t_[i-j-1]+t_[i]*h[j])%MOD;
	for(int i=0;i<N;++i) p[i]=t_[i];
}
inline ll calc(ll K) {
	for(int i=N;~i;--i) s[i]=t[i]=0;
	s[0]=1; if(N!=1) t[1]=1; else t[0]=h[0];
	for(;K;mull(t,t),K>>=1) if(K&1) mull(s,t); ll su=0;
	for(int i=0;i<N;++i) su=(su+s[i]*a[i])%MOD;
	return (su%MOD+MOD)%MOD;
}
inline int gao(vector<int> x,ll n) {
	if(n<int(x.size())) return x[n];
	vector<int> v=BM(x); N=v.size(); if(!N) return 0;
	for(int i=0;i<N;++i) h[i]=v[i],a[i]=x[i];
	return calc(n);
}
}
