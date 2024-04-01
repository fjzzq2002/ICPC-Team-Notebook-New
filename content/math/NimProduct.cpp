/**
 * Author: Claris?
 * Description: Nim product.
 */
typedef long long ll;
const int N=50;
ll nm[N][N];
ll nimmul(ll x,ll y,int o);
void niminit(){
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)nm[i][j]=nimmul(i,j,0);
}
ll nimpow(ll x,ll y,int o=1){
	if(o&&x<N&&y<N)return nm[x][y];
	if(!x)return 0;
	if(x==1)return y==1;
	ll t=2;
	while(t*t<=x)t*=t;
	ll c1=nimpow(x/t,y/t,o),
		 c2=nimpow(x/t,y%t,o);
	return (c1^c2)*t^nimpow(t>>1,c1,o);
}
ll nimmul(ll x,ll y,int o=1){
	if(o&&x<N&&y<N)return nm[x][y];
	if(x<y)swap(x,y);
	if(!y)return 0;
	if(x==1)return 1;
	ll t=2;
	while(t*t<=x)t*=t;
	ll c1=nimmul(x/t,y/t,o),
		 c2=nimmul(x/t,y%t,o)^nimmul(x%t,y/t,o),
		 c3=nimmul(x%t,y%t,o);
	return (c1^c2)*t^c3^nimpow(t>>1,c1,o);
}
