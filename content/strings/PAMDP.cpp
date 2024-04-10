/**
 * Author: Ziqian Zhong
 * Description: Palindrome tree and DP.
 */
#include <bits/stdc++.h>
using namespace std;
#define SZ 1234567
int ch[SZ][26],len[SZ],fail[SZ],s[SZ],cl,an,lst,sf[SZ],df[SZ],cnt[SZ];
int addn(int l) {len[an]=l; return an++;}
void init() {
	cl=an=lst=0;
	memset(ch,0,sizeof(ch));
	addn(0); addn(-1);
	fail[0]=1; s[0]=-233;
}
int gfail(int x,int l) {
	while(s[l-len[x]-1]!=s[l]) x=fail[x];
	return x;
}
void add(int c) {
	c-='a'; s[++cl]=c;
	int cp=gfail(lst,cl);
	if(!ch[cp][c]) {
		int nn=addn(len[cp]+2);
		fail[nn]=ch[gfail(fail[cp],cl)][c];
		ch[cp][c]=nn;
	}
	lst=ch[cp][c]; cnt[lst]++;
    df[lst]=len[lst]-len[fail[lst]];
	sf[lst]=(df[lst]==df[fail[lst]])?sf[fail[lst]]:fail[lst];
}
void getcnt() {
	for(int i=an-1;i>=2;i--) cnt[fail[i]]+=cnt[i];
}
const int MOD=1e9+7;
int ans[SZ],la[SZ];
char str[SZ],sc[SZ];
int main() {
	scanf("%s",str+1); init();
	int n=strlen(str+1),g=0;
	for(int i=1;i<=n+1-i;i++)
		sc[++g]=str[i],sc[++g]=str[n+1-i];
	ans[0]=1;
	for(int i=1;i<=n;++i) {
		add(sc[i]);
		for(int j=lst;len[j]>0;j=sf[j]) {
			la[j]=ans[i-(len[sf[j]]+df[j])];
			if(sf[j]!=fail[j]) (la[j]+=la[fail[j]])%=MOD;
			if(i%2==0) (ans[i]+=la[j])%=MOD;
		}
	}
	printf("%d\n",ans[n]);
}