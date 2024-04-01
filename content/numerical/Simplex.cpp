/**
 * Author: ?
 * Description: Simplex. Maximize $\sum_j c_j x_j$ subject to $\sum_j a_{i,j}x_j\le b_i$ and $x_j\ge 0$.
 */
const int N=25;const double eps=1e-7;
int n,m,op,lid[N],cid[N];double a[N][N],b[N];
void pivot(int l,int e){
	int i,j;double r=a[l][e];a[l][e]=1;for(i=0;i<=m;i++)a[l][i]/=r;swap(lid[l],cid[e]);
	for(i=0;i<=n;i++)if(i!=l)for(r=a[i][e],a[i][e]=j=0;j<=m;j++)a[i][j]-=r*a[l][j];
}
int main(){
	int i,j,l,e;double t,tt;scanf("%d%d%d",&m,&n,&op);
	for(i=1;i<=m;i++)scanf("%lf",&a[0][i]),cid[i]=i;
	for(i=1;i<=n;scanf("%lf",&a[i++][0]))for(j=1;j<=m;j++)scanf("%lf",&a[i][j]);
	while(true){
		for(l=0,i=1,t=-eps;i<=n;i++)if(a[i][0]<t)t=a[l=i][0];if(!l)break;
		for(e=0,i=1,t=-eps;i<=m;i++)if(a[l][i]<t&&(!e||(rand()&1)))t=a[l][e=i];
		if(!e)puts("Infeasible"),exit(0);pivot(l,e);
	}
	while(true){
		for(e=0,i=1,t=eps;i<=m;i++)if(a[0][i]>t)t=a[0][e=i];if(!e)break;
		for(l=0,i=1;i<=n;i++)if(a[i][e]>eps&&((tt=a[i][0]/a[i][e])<t||!l))t=tt,l=i;
		if(!l)puts("Unbounded"),exit(0);pivot(l,e);
	}
	printf("%.10lf\n",-a[0][0]);
	if(op){
		for(i=1;i<=n;i++)if(lid[i])b[lid[i]]=a[i][0];
		for(i=1;i<=m;i++)printf("%.10lf%c",b[i]," \n"[i==m]);
	}
	return 0;
}
