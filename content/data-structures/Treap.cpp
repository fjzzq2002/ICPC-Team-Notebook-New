/**
 * Author: Ziqian Zhong
 * Description: Treap.
 */
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define SZ 233333
mt19937 mt1(time(0));
int ch[SZ][2],sz[SZ],an=0,root;
ll tag[SZ],val[SZ],sum[SZ];
void addnode(int& ad,int x) {
	ad=++an; sz[ad]=1; sum[ad]=val[ad]=x;
}
void pd(int x) {
	if(!x||!tag[x]) return;
	val[x]+=tag[x];
	if(ch[x][0]) tag[ch[x][0]]+=tag[x], sum[ch[x][0]]+=tag[x]*sz[ch[x][0]];
	if(ch[x][1]) tag[ch[x][1]]+=tag[x], sum[ch[x][1]]+=tag[x]*sz[ch[x][1]];
	tag[x]=0;
}
void upd(int x) {
	if(!x) return;
	sz[x]=1+sz[ch[x][0]]+sz[ch[x][1]];
	sum[x]=val[x]+sum[ch[x][0]]+sum[ch[x][1]];
}
void split(int x,int& a,int& b,int s) {
	if(sz[x]<=s) a=x, b=0;
	else if(s==0) a=0, b=x;
	else {
		pd(x);
		if(sz[ch[x][0]]>=s)
			b=x, split(ch[x][0],a,ch[x][0],s), upd(x);
		else
			a=x, split(ch[x][1],ch[x][1],b,s-sz[ch[x][0]]-1), upd(x);
	}
}
void merge(int& ad,int a,int b) {
	if(a&&b) {
		if((int)mt1()%(sz[a]+sz[b])<sz[a])
			pd(ad=a), merge(ch[a][1],ch[a][1],b);
		else
			pd(ad=b), merge(ch[b][0],a,ch[b][0]);
		upd(ad);
	}
	else ad=a|b;
}
void edit(int l,int r,ll v) {
	int a,b,c;
	split(root,a,b,l-1);
	split(b,b,c,r-l+1);
	tag[b]+=v;
	sum[b]+=v*sz[b];
	merge(a,a,b);
	merge(root,a,c);
}
ll query(int l,int r) {
	int a,b,c;
	split(root,a,b,l-1);
	split(b,b,c,r-l+1);
	ll ans=sum[b];
	merge(a,a,b);
	merge(root,a,c);
	return ans;
}
int n,ns[SZ];
int ins(int l,int r) {
	if(l>r) return 0;
	if(l==r) {
		int ad; addnode(ad,ns[l]); return ad;
	}
	int mid=(l+r)>>1,lc=ins(l,mid),rc=ins(mid+1,r);
	merge(lc,lc,rc); return lc;
}
void init() {
	addnode(root,0);
	merge(root,ins(1,n),root);
}