/**
 * Author: wzd?
 * Description: Floor sum.
 */
typedef long long ll;
ll flr(ll x, ll y) { // floor(x / y). need y > 0
	ll res = x / y;
	if (res * y > x) res -= 1;
	return res;
}
ll f(ll a, ll b, ll c, ll n) { // sum_{0<=i<=n} flr((ai+b)/c). need c > 0
	ll pls = (a / c) * n * (n + 1) / 2; 
	a %= c; 
	if (a < 0) pls -= n * (n + 1) / 2, a += c;
	pls += (n + 1) * (b / c); 
	b %= c;
	if (b < 0) pls -= (n + 1), b += c;
	if (a == 0) {
		ll ans = flr(b, c) * (n + 1);
		return ans + pls;
	}
	ll m = flr(a * n + b, c);
	ll res = n * m - f(c, c - b - 1, a, m - 1);
	return res + pls;
}
