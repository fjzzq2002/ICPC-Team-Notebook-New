/**
 * Author: Web
 * Description: "ext/rope" contains a data structure that is a generalization of a string.
 */
// rope: push_back(x), insert(pos,x), erase(pos,x),
// replace(pos,x), substr(pos,x), copy(x), at[x], +=, mutable
#include<bits/stdc++.h>
#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;
const int maxn=1e5+10;
rope<char> *his[maxn];
int n,d[maxn];
inline void updata(int x){
	while(x<=n) d[x]++, x+=x&-x;
}
inline int get(int x){
	int res=0;
	while(x) res+=d[x], x-=x&-x;
	return res;
}
void deb(rope<char> s){
	for(int i=0;i<s.length();i++)
	cout<<s[i];puts("");
}
int main(){
	cin>>n;
	his[0]=new rope<char>();
	for(int i=1;i<=n;i++){
		his[i]=new rope<char>(*his[i-1]);
//		deb(*his[i]);
		char opt; cin>>opt;
		if(opt=='T'){
			cin>>opt;
			his[i]->push_back(opt);
			updata(i);
		}else if(opt=='U'){
			updata(i);
			int x,l=1,r=i,mid,now=get(i);
			cin>>x;
			while(l<r){
				mid=(l+r)>>1;
				if(now-get(mid)>x) l=mid+1;
				else r=mid;
			}
			his[i]=his[l-1];
			
		}else if(opt=='Q'){
			int x; cin>>x; --x;
			putchar(his[i]->at(x));
			putchar('\n');	
		}
	}
	return 0;
}