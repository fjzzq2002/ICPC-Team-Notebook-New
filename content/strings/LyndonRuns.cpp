/**
 * Author: yjz?
 * Description: Compute lyndon and runs. TODO: check whether it works
 */
#include <bits/stdc++.h>
using namespace std;
using ull = uint64_t;
const ull base = 131; 
const int N = 1e6 + 5, mod = 1e9 + 7;
ull pw[N], h[N], pw2[N], h2[N];
char s[N];
int n, ly[N], stk[N], tp, tot;
void init_hash(const char *s, int n) {
    pw[0] = 1;
    for(int i=1; i<=n; i++) {
        h[i] = (h[i-1]*base+s[i])%mod;
        pw[i] = pw[i-1]*base%mod;
    }
}
ull get(int l, int r) { return (h[r] - h[l-1]*pw[r-l+1]%mod+mod)%mod; }
int lcp(int x, int y) {
    int l = 1, r = n - max(x, y) + 1, ans = 0;
    while(l<=r) {
        int mid = (l+r)>>1;
        if(get(x, x+mid-1)==get(y, y+mid-1)) l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    return ans;
}
int lcs(int x, int y) {
    int l = 1, r = min(x, y), ans = 0;
    while(l<=r) {
        int mid = (l+r)>>1;
        if(get(x-mid+1, x)==get(y-mid+1, y)) l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    return ans;
}
struct runs {
    int l, r, p;
    bool operator < (const runs &oth) {
        return l==oth.l ? (r==oth.r ? p<oth.p : r<oth.r) : l<oth.l;
    }
}r[N<<1];
void check(int x, int y) {
    int L = lcs(x-1, y-1), R = lcp(x, y);
    if(L+R>=y-x) r[++tot] = {x-L, y+R-1, y-x};
}
bool cmp(int x, int y) {
    int len = lcp(x, y);
    return s[x+len]<s[y+len];
}
void lyndon(bool op) {
    ly[n] = n, stk[0] = n + 1, stk[tp=1] = n;
    for(int i=n-1; i>=1; i--) {
        while(tp && cmp(i, stk[tp])==op) --tp;
        stk[++tp] = i;
        ly[i] = stk[tp-1] - 1;
    }
}
int main() {
    scanf("%s", s+1);
    n = strlen(s+1);
    init_hash(s, n);
    for(int op=0; op<=1; op++) {
        lyndon(op);
        for(int i=1; i<n; i++) check(i, ly[i]+1);
    }
    sort(r+1, r+tot+1);
    int cnt = 0;
    for(int i=1; i<=tot; i++) {
        if(r[i].l!=r[i-1].l||r[i].r!=r[i-1].r) r[++cnt] = r[i];
    }
    printf("%d\n", cnt);
    for(int i=1; i<=cnt; i++) printf("%d %d %d\n", r[i].l, r[i].r, r[i].p);
    return 0;
}
