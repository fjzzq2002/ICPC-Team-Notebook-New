/**
 * Author: Ziqian Zhong?
 * Description: Min25 sieve with DFS.
 */
#include <bits/stdc++.h>
using namespace std;
typedef unsigned us;
typedef unsigned long long ull;
typedef long long ll;
const us MOD=1e9+7;
#define SS 2333333
ll n,c0[SS],c1[SS],b0[SS],b1[SS];
#define MU 6000000
int S,ps[MU/10],pn=0;
int U=MU;
#define V 40
unsigned fc[V][MU];
inline ull F(ull x,us g) {
	if(g<V&&x<U) return fc[g][x];
    if(x<=1||ps[g]>x) return 0;
    ull ans=((x>S)?b1[n/x]:c1[x])-c1[ps[g-1]]+MOD;
    for(us j=g;j<=pn&&ps[j]*(ll)ps[j]<=x;++j) {
        ull cn=x/ps[j],ce=ps[j]*(ll)ps[j];
        for(us e=1;cn>=ps[j];++e,cn/=ps[j],ce*=ps[j])
            ans+=F(cn,j+1)*(ps[j]^e)+(ps[j]^(e+1)),ans%=MOD;
    }
    return ans%MOD;
}
int mf[MU];
unsigned f[MU];
int main() {
//	n=1e11;
    cin>>n;
	S=sqrtl(n);
	U=min(U,int(S*30));
	for(int i=1;i<U;++i) f[i]=1;
	for(int i=2;i<U;++i) {
		if(!mf[i]) {
			f[i]=i^1; ps[++pn]=i; mf[i]=pn;
		}
		for(int j=1;j<=pn&&i*ps[j]<U;++j) {
			int w=i*ps[j]; mf[w]=j;
			if(i%ps[j]==0) {
				int p=ps[j];
				int o=w,c=0;
				while(o%p==0) o/=p,++c;
				f[w]=f[o]*(p^c);
				break;
			}
			else f[w]=f[i]*(ps[j]^1);
		}
	}
	for(int j=0;j<V;++j) {
		unsigned*fcj=fc[j];
		for(int i=2;i<U;++i) {
			if(mf[i]>=j) {
				fcj[i]=fcj[i-1]+f[i];
				(fcj[i]>=MOD)?(fcj[i]-=MOD):0;
			}
			else fcj[i]=fcj[i-1];
		}
	}
	pn=0;
    for(int i=1;i<=S;++i) {
        ll t=(n/i)%MOD; b0[i]=t;
        b1[i]=t*(t+1)/2%MOD; c0[i]=i;
        c1[i]=i*(ll)(i+1)/2%MOD;
    }
    for(int i=2;i<=S;++i)
    {
        if(c0[i]==c0[i-1]) continue; //not a prime
        ll x0=c0[i-1],x1=c1[i-1]%MOD,r=(ll)i*i; ps[++pn]=i;
        int u=min((ll)S,n/(i*(ll)i)),uu=min(u,S/i);
        for(int j=1;j<=uu;++j)
            (b1[j]-=(b1[j*i]-x1)*i)%=MOD,
            b0[j]-=b0[j*i]-x0;
        ll t=n/i;
        if(t<=2147483647) {
        int tt=t;
        for(int j=uu+1;j<=u;++j)
            b1[j]-=(c1[tt/j]-x1)*i,
            b0[j]-=c0[tt/j]-x0;
        }
        else {
        for(int j=uu+1;j<=u;++j)
            (b1[j]-=(c1[t/j]-x1)*i)%=MOD,
            b0[j]-=c0[t/j]-x0;
        }
        for(int j=S;j>=r;--j)
            c1[j]-=(c1[j/i]-x1)*i,
            c0[j]-=c0[j/i]-x0;
    }
    for(int i=1;i<=S;++i) {
        c1[i]%=MOD;
        b1[i]%=MOD;
        c1[i]-=c0[i];
        b1[i]-=b0[i];
        if(i>=2) c1[i]+=2;
        if(n>=2LL*i) b1[i]+=2;
        c1[i]=(c1[i]%MOD+MOD)%MOD;
        b1[i]=(b1[i]%MOD+MOD)%MOD;
    }
    ps[pn+1]=S+1;
    vector<ll> u;
    for(ll i=1;i<=n;) {
    	ll d=n/i,r=n/d; i=r+1;
    	u.pb(((1+F(d,1))%MOD+MOD)%MOD);
	}
	sort(u.begin(),u.end());
	u.erase(unique(u.begin(),u.end()),u.end());
	ll ans=0;
	for(auto c:u) ans^=c;
	cout<<ans<<"\n";
}
