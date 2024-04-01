/**
 * Author: ??
 * Description: Randomized maximum matching.
 */
#include<bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int n,m,ct,a[505],mt[505],vs[505],lim=5;vector<int> v[505];
bool dfs(int x){
	vs[x]=1;shuffle(v[x].begin(),v[x].end(),rng);
	for(int i=0;i<v[x].size();i++){
		int y=v[x][i],z=mt[y];if(vs[z])continue;
		mt[x]=y,mt[y]=x,mt[z]=0;if(!z||dfs(z))return 1;mt[x]=0,mt[y]=z,mt[z]=y;
	}return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	while(m--){int x,y;scanf("%d%d",&x,&y);v[x].push_back(y);v[y].push_back(x);}
	for(int t=1;t<=lim;t++){
		for(int i=1;i<=n;i++){if(!mt[i]){for(int j=1;j<=n;j++)vs[j]=0;dfs(i);}}
		int tp=0;for(int i=1;i<=n;i++)tp+=bool(mt[i]);
		if(tp>ct){ct=tp;for(int i=1;i<=n;i++)a[i]=mt[i];}
	}printf("%d\n",ct/2);for(int i=1;i<=n;i++)printf("%d ",a[i]);
	return 0;
}
