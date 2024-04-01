/**
 * Author: ?
 * Description: Min25 sieve with DP. Sieving $F(p^k)=p^k$.
 */
using ll = long long;
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) / 2;
const int N = 1e6 + 5;
ll n, D[N], p[N];
int m, cnt, tot;
bool vis[N];
inline int id(ll x) {
	return x <= m ? cnt - x + 1 : n / x;
}
void sieve(int n) {
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) p[++tot] = i;
		for (int j = 1; j <= tot && i * p[j] <= n; j++) {
			vis[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
}
ll s0[N], s[N], sump[N], g[N], sumf[N];
ll min_25() {
	for (int i = 1; i <= cnt; i++)
		s0[i] = D[i] - 1;
	for (int j = 1; j <= tot; j++)
		for (int i = 1; i <= cnt && D[i] >= p[j] * p[j]; i++)
			s0[i] -= s0[id(D[i] / p[j])] - (j - 1);
	
	for (int i = 1; i <= cnt; i++)
		s[i] = (D[i] % mod * (D[i] % mod + 1) % mod * inv2 % mod - 1) % mod;
	for (int j = 1; j <= tot; j++)
		sump[j] = sump[j - 1] + p[j];
	for (int j = 1; j <= tot; j++)
		for (int i = 1; i <= cnt && D[i] >= p[j] * p[j]; i++)
			s[i] = (s[i] - p[j] * (s[id(D[i] / p[j])] - sump[j - 1] + mod) % mod + mod) % mod;

	for (int i = 1; i < cnt; i++)
		g[i] = (s[i] - s0[i] + 2) % mod;
	for (int j = 1; j <= tot; j++)
		sumf[j] = (sumf[j - 1] + (p[j] ^ 1)) % mod;
	for (int j = tot; j; j--)
		for (int i = 1; i <= cnt && D[i] >= p[j] * p[j]; i++) {
			ll pk = p[j];
			for (int k = 1; pk * p[j] <= D[i]; pk *= p[j], ++k)
				(g[i] += (p[j] ^ k) % mod * (g[id(D[i] / pk)] - sumf[j] + mod) % mod
					  + (p[j] ^ (k + 1))
				) %= mod;
		}
	std::set<ll> sv;
	for (int i = 1; i <= cnt; i++)
		sv.insert((g[i] + 1) % mod);
	ll ans = 0;
	for (auto g : sv) ans ^= g;
	return ans % mod;
}
signed main() {
	scanf("%lld", &n);
	m = sqrt(n);
	sieve(m);
	for (ll x = 1; x <= n; x = n / (n / x) + 1)
		D[++cnt] = n / x;
	printf("%lld\n", min_25());
	return 0;
}
