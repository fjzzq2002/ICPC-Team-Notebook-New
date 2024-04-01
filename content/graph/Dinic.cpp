/**
 * Author: Ziqian Zhong
 * Description: Dinic.
 */
int N,S,T,M=1; //M=1 is important!!
int fst[SZ],vb[SZ],nxt[SZ],vc[SZ];
void ad_de_(int a,int b,int c)
{++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;vc[M]=c;}
void ad_de(int a,int b,int c){ad_de_(a,b,c);ad_de_(b,a,0);}
int d[SZ],ff[SZ];
bool bfs() {
	static int qs[SZ]; int h=0,t=0;
	memset(d,-1,sizeof(int)*(N+1));
	qs[t++]=S; d[S]=0;
	while(h^t) {
		int x=qs[h++];
		for esb(x,e,b) {
			if((~d[b])||!vc[e]) continue;
			d[b]=d[x]+1; qs[t++]=b;
		}
	}
	return d[T]!=-1;
}
ll dfs(int x,ll u) {
	if(x==T||!u) return u;
	ll f=0;
	for(int&e=fst[x];e;e=nxt[e]) {
		int b=vb[e];
		if(d[b]!=d[x]+1) continue;
		ll s=dfs(vb[e],min(u-f,(ll)vc[e]));
		f+=s; vc[e]-=s; vc[e^1]+=s;
		if(f==u) break;
	}
	if(!f) d[x]=-1;
	return f;
}
ll dinic() {
	ll ans=0;
	memcpy(ff,fst,sizeof(int)*(N+1));
	while(bfs())
		ans+=dfs(S,1e18),
		memcpy(fst,ff,sizeof(int)*(N+1));
	return ans;
}
