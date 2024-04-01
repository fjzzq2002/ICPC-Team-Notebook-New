/**
 * Author: Ziqian Zhong
 * Description: Palindromic tree. Odd and even roots etc.
 */
struct PTree {
int ch[SZ][26],len[SZ],fail[SZ],cnt[SZ],s[SZ],cl,an,lst;
int addn(int l) {len[an]=l; return an++;}
PTree() {
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
	s[++cl]=c;
	int cp=gfail(lst,cl);
	if(!ch[cp][c]) {
		int nn=addn(len[cp]+2);
		fail[nn]=ch[gfail(fail[cp],cl)][c];
		ch[cp][c]=nn;
	}
	cnt[lst=ch[cp][c]]++;
}
void getcnt() {
	for(int i=an-1;i>=2;i--) cnt[fail[i]]+=cnt[i];
}
}pt;
