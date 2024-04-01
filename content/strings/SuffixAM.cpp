/**
 * Author: Ziqian Zhong
 * Description: Suffix automaton. To build upon a Trie use BFS.
 */
int N,ch[SZ][26],fa[SZ],ml[SZ];
void init() {N=0; fa[0]=-1; ml[0]=0;}
int ins(int p,int c) {
	int x=ch[p][c],y=0;
	if(!x) {
		x=++N;ml[x]=ml[p]+1;y=1;
		for(;p!=-1&&!ch[p][c];p=fa[p]) ch[p][c]=x;
	}
	if(p==-1) fa[x]=0;
	else if(ml[ch[p][c]]==ml[p]+1) y?(fa[x]=ch[p][c]):0;
	else {
		int q=++N,cc=ch[p][c];ml[q]=ml[p]+1;
		for(int i=0;i<26;i++) ch[q][i]=ch[cc][i];
		fa[q]=fa[cc],fa[cc]=fa[x]=q;
		for(;p!=-1&&ch[p][c]==cc;p=fa[p]) ch[p][c]=q;
		if(!y) return q;
	}
	return x;
}
int qs[SZ],od[SZ]; //od[0]..od[N]
void topo() {
	for(int i=0;i<=N;i++) qs[i]=0;
	for(int i=0;i<=N;i++) qs[ml[i]]++;
	for(int i=1;i<=N;++i) qs[i]+=qs[i-1];
	for(int i=N;i>=0;i--) od[--qs[ml[i]]]=i;
}
char s[SZ]; int ri[SZ];
int main(){
	init(); scanf("%s",s+1); int w=0;
	for(int j=1;s[j];j++) ++ri[w=ins(w,s[j]-'a')];
	topo(); ll ans=0;
	for(int i=N;i;--i) {
		int x=od[i]; ri[fa[x]]+=ri[x];
		if(ri[x]!=1) ans=max(ans,(ll)ri[x]*ml[x]);
	}
	printf("%lld\n",ans);
}
