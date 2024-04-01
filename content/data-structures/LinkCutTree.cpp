/**
 * Author: Ziqian Zhong
 * Description: Link cut tree.
 */
int ch[SZ][2],fa[SZ],sum[SZ],vv[SZ],mx[SZ];
bool rev[SZ];
bool top(int x) {return !(ch[fa[x]][0]==x||ch[fa[x]][1]==x);}
void pd(int x) {
    if(!rev[x]) return;
    rev[x]=0;
    rev[ch[x][0]]^=1;
    rev[ch[x][1]]^=1;
    swap(ch[x][0],ch[x][1]);
}
void upd(int x) {
    sum[x]=sum[ch[x][0]]+sum[ch[x][1]]+vv[x];
    if(vv[mx[ch[x][0]]]>vv[mx[ch[x][1]]]
	&&vv[mx[ch[x][0]]]>vv[x]) mx[x]=mx[ch[x][0]];
    else if(vv[mx[ch[x][1]]]>vv[x]) mx[x]=mx[ch[x][1]];
    else mx[x]=x;
}
void rot(int x) {
    if(top(x)) return;
    int y=fa[x],c=ch[y][0]==x;
    int f=fa[y];
    if(!top(y)) ch[f][ch[f][1]==y]=x;
    if(ch[x][c]) fa[ch[x][c]]=y;
    ch[y][!c]=ch[x][c];
    ch[x][c]=y; fa[x]=f; fa[y]=x;
    upd(y); upd(x);
}
int ss[SZ],sn;
void splay(int x) {
    sn=0;
    for(int c=x;;c=fa[c]) {
        ss[++sn]=c;
        if(top(c)) break;
    }
    while(sn) pd(ss[sn--]);
    while(!top(x)) {
        int y=fa[x];
        if(!top(y)) {
            if(ch[fa[y]][0]==y^ch[y][0]==x) rot(x);
            else rot(y);
        }
        rot(x);
    }
}
void access(int x) {
    for(int c=0;x;c=x,x=fa[x]) splay(x), ch[x][1]=c, upd(x);
}
void makeroot(int x) {access(x); splay(x); rev[x]^=1;}
void link(int a,int b) {makeroot(a); fa[a]=b;}
void cut(int a,int b) {makeroot(a); access(b); splay(b); ch[b][0]=fa[a]=0;}
int findroot(int x) {
    access(x); splay(x);
    int lc=x;
    while(ch[lc][0]) lc=ch[lc][0];
    splay(lc); return lc;
}
int getrd(int a,int b) {makeroot(a); access(b); splay(b); return b;}
