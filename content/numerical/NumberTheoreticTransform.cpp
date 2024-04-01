/**
 * Author: Ziqian Zhong
 * Description: NTT.
 */
typedef long long ll;
const int MOD=998244353;
ll w[2][666666];
ll qp(ll a,ll b) {
    ll ans=1;
    while(b) {
        if(b&1) ans=ans*a%MOD;
        a=a*a%MOD; b>>=1;
    }
    return ans;
}
int K;
void fftinit(int n) {
    for(K=1;K<n;K<<=1);
    w[0][0]=w[0][K]=1;
    ll g=qp(3,(MOD-1)/K); //change 3 to g
    for(int i=1;i<K;i++) w[0][i]=w[0][i-1]*g%MOD;
    for(int i=0;i<=K;i++) w[1][i]=w[0][K-i];
}
void fft(int* x,int v) {
    for(int i=0,j=0;i<K;i++) {
        if(i>j) swap(x[i],x[j]);
        for(int l=K>>1;(j^=l)<l;l>>=1);
    }
    for(int i=2;i<=K;i<<=1) {
        for(int j=0;j<K;j+=i) {
            for(int l=0;l<i>>1;l++) {
                ll t=(ll)x[j+l+(i>>1)]*w[v][K/i*l]%MOD;
                x[j+l+(i>>1)]=(x[j+l]-t+MOD)%MOD;
                x[j+l]=(x[j+l]+t)%MOD;
            }
        }
    }
    if(!v) return;
    ll rv=qp(K,MOD-2);
    for(int i=0;i<K;i++) x[i]=x[i]*rv%MOD;
}
