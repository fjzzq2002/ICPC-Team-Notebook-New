char ch[N<<1];
int f[N<<1];
//f[i*2]: i centered; f[i*2+1]: (i,i+1) centered
void manacher(char *s) {
	int n=strlen(s),id=0,mx=0;
	ch[0]='$'; ch[1]='#';
	for(int i=1;i<=n;i++)
		ch[i*2]=s[i-1], ch[i*2+1]='#';
	ch[n*2+2]='#';
	for(int i=0;i<=2*n+10;i++) f[i]=0;
	for(int i=1;i<=2*n+2;i++) {
		if(i>mx) f[i]=1; else f[i]=min(f[id*2-i],mx-i);
		while(ch[i-f[i]]==ch[i+f[i]]) f[i]++;
		if(i+f[i]>mx) {mx=i+f[i]; id=i;}
	}
}
