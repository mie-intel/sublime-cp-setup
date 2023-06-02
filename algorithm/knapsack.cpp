#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fi first
#define se second

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, x;
	cin >> n >> x;
	ll dp[2][x + 1];
	memset(dp, -1, sizeof dp); // magic
	dp[0][0] = 0;
	// inputin barangnya
	vector <pair <ll, ll>> v(n + 1);
	for(int a = 1; a <= n; ++a) cin >> v[a].fi; // ini tu harga
	for(int a = 1; a <= n; ++a) cin >> v[a].se; // ini tu value

	// isi aja dp-nya
	for(int barang = 1; barang <= n; ++barang){
		ll now = barang % 2;
		ll pref = 1 - now;
		// kita pertama turunin dulu semua value di atas barang
		for(int a = 0; a <= x; ++a) dp[now][a] = dp[pref][a];
		// transisi
		for(int a = 1; a <= x; ++a){
			if(a - v[barang].fi >= 0 && dp[pref][a - v[barang].fi] != -1){
				dp[now][a] = max(dp[now][a], dp[pref][a - v[barang].fi] + v[barang].se);
			}
		}
	}

	// terakhir, cari nilai maximum dari dp[barang[n]][...]
	ll mx = 0;
	for(int a = 1; a <= x; ++a) mx = max(mx, dp[n % 2][a]);
	cout << mx << '\n';

	return 0;
}