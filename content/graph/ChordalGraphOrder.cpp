/**
 * Author: Claris?
 * Description: Ordering for chordal graph.
 */
int i,j,k,col[N],ans;bool vis[N];
int main(){
	for(i=n;i;i--){
		for(k=0,j=1;j<=n;j++)if(!vis[j]&&col[j]>=col[k])k=j; //optimize this
		for(vis[k]=1,j=g[k];j;j=nxt[j])if(!vis[v[j]])if(++col[v[j]]>ans)ans=col[v[j]];
	}
	printf("%d",ans+1);
}
