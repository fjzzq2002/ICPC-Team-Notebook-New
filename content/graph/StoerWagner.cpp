const int N=502,inf=1000000000;
int v[N],w[N],c[N],g[N][N],S,T,now,n,m,x,y,z;
void search(){
  int i,j,k,t;
  for(i=0;i<n;i++)v[i]=w[i]=0;
  for(S=T=-1,i=0;i<n;i++){
    for(k=-inf,j=0;j<n;j++)if(!c[j]&&!v[j]&&w[j]>k)k=w[t=j];
    if(T==t)return;
    S=T,T=t,now=k,v[t]=1;
    for(j=0;j<n;j++)if(!c[j]&&!v[j])w[j]+=g[t][j];
  }
}
int stoerwagner(){
  int i,j,ans=inf;
  for(i=0;i<n;i++)c[i]=0;
  for(i=0;i<n-1;i++){
    search();
    if(now<ans)ans=now;
    if(ans==0)return 0;
    for(c[T]=1,j=0;j<n;j++)if(!c[j])g[S][j]+=g[T][j],g[j][S]+=g[j][T];
  }
  return ans;
}
int main(){
  scanf("%d%d",&n,&m);
  while(m--)scanf("%d%d%d",&x,&y,&z),g[x][y]+=z,g[y][x]+=z;
  printf("%d",stoerwagner());
}
