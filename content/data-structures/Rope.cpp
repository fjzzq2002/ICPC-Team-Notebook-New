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
int n;
int d[maxn];
inline int lowbit(int x){return x&-x;}
inline void updata(int x){
	while(x<=n)
		d[x]++, x+=lowbit(x);
}
inline int get(int x){
	int res=0;
	while(x){
		res+=d[x];
		x-=lowbit(x);
	}return res;
}
inline char getC(){
	char ch=getchar();
	while(!isalpha(ch))ch=getchar();
	return ch;
}
inline int getint(){
	int res=0;
	char ch,ok=0;
	while(ch=getchar()){
		if(isdigit(ch)){
			res*=10;res+=ch-'0';ok=1;
		}else if(ok)break;
	}return res;
}
void deb(rope<char> s){
	for(int i=0;i<s.length();i++)
	cout<<s[i];puts("");
}
int main(){
	n=getint();
	his[0]=new rope<char>();
	for(int i=1;i<=n;i++){
		his[i]=new rope<char>(*his[i-1]);
//		deb(*his[i]);
		char opt=getC();
		if(opt=='T'){
			char x=getC();
			his[i]->push_back(x);
			updata(i);
		}else
		if(opt=='U'){
			updata(i);
			int x=getint();
			int l=1,r=i,mid,now=get(i);
			while(l<r){
				mid=(l+r)>>1;
				if(now-get(mid)>x)
					l=mid+1;
				else
					r=mid;
			}
			his[i]=his[l-1];
			
		}else
		if(opt=='Q'){
			int x=getint()-1;
			putchar(his[i]->at(x));
			putchar('\n');	
		}
//		deb(*his[i]);
	}
	return 0;
}
// another example below
crope a,b,tmp;
char s[10];
int now,n,len,size;
char str[2000000],rstr[2000000];
int main(){
    scanf("%d",&n);
    while(n--){
        scanf("%s",s);
        switch(s[0]){
            case 'M':{scanf("%d",&now);break;}
            case 'P':{now--;break;}
            case 'N':{now++;break;}
            case 'G':{putchar(a[now]);putchar('\n');break;}
            case 'I':{
                scanf("%d",&size);
                len=a.length();
                for(int i=0;i<size;i++){
                    do{str[i]=getchar();}
                    while(str[i]=='\n');
                    rstr[size-i-1]=str[i];
                }
                rstr[size]=str[size]='\0';
                a.insert(now,str);
                b.insert(len-now,rstr);
                break;
            }
            case 'D':{
                scanf("%d",&size);
                len=a.length();
                a.erase(now,size);
                b.erase(len-now-size,size);
                break;
            }
            case 'R':{
                scanf("%d",&size);
                len=a.length();
                tmp=a.substr(now,size);
                a=a.substr(0,now)+b.substr(len-now-size,size)+a.substr(now+size,len-now-size);
                b=b.substr(0,len-now-size)+tmp+b.substr(len-now,now);               
                break;
            }
        }       
    }
    return 0;
}
