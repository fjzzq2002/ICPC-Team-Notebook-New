/**
 * Author: Ziqian Zhong
 * Description: A hash table. TODO: test if it's faster than e.g. cuckoo.
 */
#define MOD 1000007
struct my_hash_table{
	int h[MOD],nxt[SZ],vv[SZ],ec; ll fl[SZ];
	int &operator[](ll v){
		for(int e=h[v%MOD];e;e=nxt[e])if(fl[e]==v)return vv[e];
		++ec,fl[ec]=v,nxt[ec]=h[v%MOD],h[v%MOD]=ec;
		vv[ec]=0; return vv[ec];
	}
	bool count(int v){
		for(int e=h[v%MOD];e;e=nxt[e])if(fl[e]==v)return true;
		return false;
	}
	void clear() {
		for(int i=1;i<=ec;++i) h[fl[i]%MOD]=0;ec=0;
	}
};
