/**
 * Author: Claris?
 * Description: Find the directed cycle with minimum average.
 */
const int N=3005,M=10005;
const double inf=1e18;
int n,m,i,j,u[M],v[M];double w[M],f[N][N],ans=1e9,now,tmp;
inline void up(double&a,double b){a>b?(a=b):0;}
int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)scanf("%d%d%lf",&u[i],&v[i],&w[i]);
	for(i=1;i<=n;i++)for(j=1;j<=n;j++)f[i][j]=inf;
	for(i=0;i<n;i++)for(j=1;j<=m;j++)up(f[i+1][v[j]],f[i][u[j]]+w[j]);
	for(i=1;i<=n;i++)if(f[n][i]<inf/2){
		now=-1e9;
		for(j=0;j<n;j++)if(f[j][i]<inf/2){
			tmp=1.0*(f[n][i]-f[j][i])/(n-j);
			if(now<tmp)now=tmp;
		}
		up(ans,now);
	}
	printf("%.8f",ans);
}
