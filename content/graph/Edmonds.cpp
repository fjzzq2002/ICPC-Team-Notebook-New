const int N=1010,inf=1e9;
//clear pre before sending, stores father node of each node
int edmonds(int n,int G[][N],int pre[]){
	static int vis[N][N],l[N],p[N];
	int m=n,cnt,ret=0,i,j,k;
	for(i=0;i<n;++i)l[i]=i;
	do{
		memset(vis,0,sizeof(vis));
		memset(p,0xff,sizeof(p));
		cnt=m;
		for(i=0;i<m;++i)vis[i][i]=1;
		for(i=0;i<cnt;++i)if(l[i]==i&&pre[i]!=-1){
			for(j=0;j<m;++j)
				if(l[j]==j&&i!=j&&G[j][i]<inf&&(p[i]==-1||G[j][i]<G[p[i]][i]))p[i]=j;
			if((pre[i]=p[i])==-1)return -1;//no solution
			if(vis[i][p[i]]){
				for(j=0;j<=m;++j)G[j][m]=G[m][j]=inf;
				for(k=i;l[k]!=m;l[k]=m,k=p[k])for(j=0;j<m;++j)if(l[j]==j){
					if(G[j][k]-G[p[k]][k]<G[j][m])G[j][m]=G[j][k]-G[p[k]][k];
					if(G[k][j]<G[m][j])G[m][j]=G[k][j];
				}
				vis[m][m]=1;l[m]=m;m++;
			}
			for(j=0;j<m;++j)if(vis[i][j])for(k=p[i];k!=-1&&l[k]==k; k=p[k])vis[k][j]=1;
		}
	}while(cnt<m);
	for(;m-->n;pre[k]=pre[m])for(i=0;i<m;++i)if(l[i]==m){
		for(j=0;j<m;++j)if(pre[j]==m&&G[i][j]==G[m][j])pre[j]=i;
		if(G[pre[m]][m]==G[pre[m]][i]-G[pre[i]][i])k=i;
	}
	for(i=0;i<n;++i)if(pre[i]!=-1)ret+=G[pre[i]][i];
	return ret;
}
