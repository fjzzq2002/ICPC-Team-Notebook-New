/**
 * Author: https://www.cnblogs.com/Charlie-Vinnie/p/17093065.html
 * Description: Basic substring structure. The triangle is partitioned into substairs and each group is of several identical substairs. Total perimeter of substairs is linear.
 */
template<int NN,int Z>
class SAM{
    static constexpr int N=NN*2;
public:
    int OO,tot,n,Lst,ch[N][Z],fa[N],len[N],pre[N],posl[N],posr[N],occ[N],lis[N],tcnt[N],tmp[N],_ffa[__lg(N)+1][N],ffa[N][__lg(N)+1]; vector<int> son[N];
    SAM(int OOO=0) : OO(OOO) { tot=Lst=1; }
    inline void push_back(int c){
        int np=++tot,p=Lst; Lst=np; occ[np]=1; len[np]=++n; pre[n]=np; posr[np]=n;
        while(p&&!ch[p][c]) ch[p][c]=np,p=fa[p];; if(!p) return fa[np]=1,void();
        int v=ch[p][c]; if(len[v]==len[p]+1) return fa[np]=v,void();
        int nv=++tot; memcpy(ch[nv],ch[v],sizeof(ch[nv])); fa[nv]=fa[v]; posr[nv]=posr[v]; len[nv]=len[p]+1; fa[v]=fa[np]=nv;
        while(p&&ch[p][c]==v) ch[p][c]=nv,p=fa[p];
    }
    inline void build(int oo=0){
        For(u,2,tot) _ffa[0][u]=fa[u];; For(i,1,__lg(n)) For(u,2,tot) _ffa[i][u]=_ffa[i-1][_ffa[i-1][u]];
        For(u,1,tot) For(i,0,__lg(n)) ffa[u][i]=_ffa[i][u];
        For(u,2,tot) son[fa[u]].push_back(u);;
        function<void(int)> dfs; dfs = [&](int u) { for(int v:son[u]) dfs(v),posr[u]=max(posr[u],posr[v]); };  if(oo) dfs(1);
        For(u,2,tot) posl[u]=posr[u]-len[u]+1;
        For(u,1,tot) tcnt[posl[u]]++;; For(i,1,n) tcnt[i]+=tcnt[i-1];; For(u,1,tot) tmp[tcnt[posl[u]]--]=u;; if(oo) reverse(tmp+1,tmp+1+tot);
        For(i,1,n) tcnt[i]=0;; For(i,1,tot) tcnt[len[tmp[i]]]++;; For(i,1,n) tcnt[i]+=tcnt[i-1];; Rev(i,tot,1) lis[tcnt[len[tmp[i]]]--]=tmp[i];
        Rev(i,tot,1) { int u=lis[i]; for(int v:son[u]) occ[u]+=occ[v]; }
    }
    inline int find(int l,int r) const { int u=pre[r]; Rev(i,__lg(n),0) if(len[ffa[u][i]]>=r-l+1) u=ffa[u][i];; return u; }
};
template<int NN,int Z>
class BasicStringStructure{
public:
    static constexpr int N=NN*2; struct Node { int u,r; }; using pii = pair<int,int>; struct Stair { int posl,posr; vector<Node> X,Y; } st[N];
    int n,stcnt,num0[N],num1[N]; SAM<NN,Z> S0,S1;
    BasicStringStructure<NN,Z>() : S0(0), S1(1) {}
    inline void build(int _n,int* s){
        n=_n; For(i,1,n) S0.push_back(s[i]);; Rev(i,n,1) S1.push_back(s[i]);; fprintf(stderr,"T1:%ld\n",clock()); S0.build(0); S1.build(1);
        stcnt=0; Rev(i,S0.tot,2){
            int u=S0.lis[i],l=S0.posl[u],r=S0.posr[u],l2=l+S0.len[u]-S0.len[S0.fa[u]]-1,v=0; For(c,0,Z-1) if(S0.ch[u][c]&&S0.occ[S0.ch[u][c]]==S0.occ[u]) { v=S0.ch[u][c]; break; }
            if(!v) {  num0[u]=++stcnt; st[stcnt].posl=l; st[stcnt].posr=r; st[stcnt].X.push_back(Node{u,l2}); }
            else { st[num0[u]=num0[v]].X.push_back(Node{u,l2}); }
        }
        stcnt=0; Rev(i,S1.tot,2){
            int u=S1.lis[i],l=n-S1.posr[u]+1,r=n-S1.posl[u]+1,r2=r-(S1.len[u]-S1.len[S1.fa[u]])+1,v=0; For(c,0,Z-1) if(S1.ch[u][c]&&S1.occ[S1.ch[u][c]]==S1.occ[u]) { v=S1.ch[u][c]; break; }
            if(!v) { num1[u]=++stcnt; assume(st[stcnt].posl==l&&st[stcnt].posr==r); st[stcnt].Y.push_back(Node{u,r2}); }
            else { st[num1[u]=num1[v]].Y.push_back(Node{u,r2}); }
        }
        // For(i,1,stcnt){
        //     printf("Stair #%d (%d,%d): X = ",i,st[i].posl,st[i].posr);
        //     for(auto x:st[i].X) printf("%d[%d,%d] ",x.u,x.l,x.r);
        //     printf(" Y = "); for(auto y:st[i].Y) printf("%d[%d,%d] ",y.u,y.l,y.r);; puts("");
        // }
    }
};