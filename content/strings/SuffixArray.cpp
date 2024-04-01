/**
 * Author: Ziqian Zhong
 * Description: Suffix array, 0-indexed. lcp(a,b) equals minimum h between rk[a] and rk[b].
 */
int sa[SZ],rk[SZ],su[SZ],ork[SZ];
char s[SZ]; int n,h[SZ];
bool diff(int a,int b,int g)
{return ork[a]!=ork[b]||ork[a+g]!=ork[b+g];}
void build_sa() {
	int G=max(n,200);
	for(int i=0;i<=G;++i) su[i]=0;
	for(int i=0;i<n;++i) ++su[rk[i]=s[i]];
	for(int i=1;i<=G;++i) su[i]+=su[i-1];
	for(int i=0;i<n;++i) sa[--su[rk[i]]]=i;
	for(int g=1;g<=n;g<<=1) {
		for(int i=0;i<=G;++i) su[i]=0;
		static int ts[SZ]; int tn=0;
		for(int i=n-1;i>=0;--i) {
			if(sa[i]>=g) ts[++tn]=sa[i]-g;
			ork[i]=rk[i];
		}
		for(int i=n-g;i<n;++i) ts[++tn]=i;
		for(int i=1;i<=tn;++i) ++su[rk[ts[i]]];
		for(int i=1;i<=G;++i) su[i]+=su[i-1];
		for(int i=1;i<=tn;++i)
			sa[--su[rk[ts[i]]]]=ts[i];
		int t=0;
		for(int i=0;i<n;++i) {
			if(i&&diff(sa[i-1],sa[i],g)) ++t;
			rk[sa[i]]=t;
		}
	}
	for(int i=0;i<n;++i) rk[sa[i]]=i;
	int g=0;
	for(int i=0;i<n;++i) {
		g=max(g-1,0);
		if(rk[i]==n-1) {
			h[rk[i]]=0;
			continue;
		}
		int A=i,B=sa[rk[i]+1];
		while(s[A+g]==s[B+g]) ++g;
		h[rk[i]]=g;
	}
}
