/**
 * Author: ?
 * Description: Magic euclid. Calculate $\sum_{x=1}^L A^x B^{\lfloor (Px+R)/Q\rfloor}$.
 */
#include<bits/stdc++.h>
using namespace std;
typedef __int128 ll;
const int mod=998244353;
long long p,q,r,l; int n;
inline int add(int x,int y){return x+y<mod?x+y:x+y-mod;}
struct matrix{
	int a[21][21];
	matrix(){memset(a,0,sizeof(a));}
	matrix operator +(const matrix &b){
		matrix c;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				c.a[i][j]=add(a[i][j],b.a[i][j]);
		return c;
	}
	matrix operator *(const matrix &b){
		matrix (c);
		for(int i=1;i<=n;i++){
			for(int k=1;k<=n;k++){
				if(!a[i][k]) continue;
				for(int j=1;j<=n;j++)
				c.a[i][j]=add(c.a[i][j],1ll*a[i][k]*b.a[k][j]%mod);
			}
		}
		return c;
	}
}a,b,I,ey;
struct node{
	matrix u,r,s;
	node operator +(const node &k){
		return node{u*k.u,r*k.r,s+r*k.s*u};
	}
	node operator *(ll n){
		node x=node{I,I,ey},y=node{u,r,s};
		while(n){
			if(n&1) x=x+y;
			y=y+y,n>>=1;
		}
		return x;
	}
}ans;
inline node solve(ll p,ll q,ll b,ll l,node u,node r){
	if(!l) return node{I,I,ey};
	if(p>=q) return solve(p%q,q,b,l,u,u*(p/q)+r);
	ll cnt=(l*p+b)/q; if(!cnt) return r*l;
	return r*((q-b-1)/p)+u+solve(q,p,(q-b-1)%p,cnt-1,r,u)+r*(l-(cnt*q-b-1)/p);
}
int main(){
	cin>>p>>q>>r>>l>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) cin>>a.a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) cin>>b.a[i][j];
	for(int i=1;i<=n;i++) I.a[i][i]=1;
	ans=node{b,I,ey}*(r/q)+solve(p,q,r%q,l,node{b,I,ey},node{I,a,a});
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) cout<<ans.s.a[i][j]<<' ';
		cout<<endl;
	}
}
