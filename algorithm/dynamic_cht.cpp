#include <bits/stdc++.h>
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fi first
#define se second

ll eval(pair <ll, ll> d, ll val){
	return d.fi * val + d.se;
}

double inter(pair <ll, ll> a, pair <ll, ll> b){
	return double(b.se - a.se) / double(a.fi - b.fi);
}

const int maxn = 2e5 + 1;
int n;
ll arr[maxn], sum[maxn];

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef tree<pair <ll, ll>,null_type,less<pair <ll, ll>>,rb_tree_tag,
tree_order_statistics_node_update> iset;

iset dq;

bool bad(iset::iterator y){
	auto z = next(y);
	if(y == dq.begin()){
		if(z == dq.end()) return 0;
		else return y->fi == z->fi && y->se <= z->se;
	}
	auto x = prev(y);
	if(z == dq.end()) return y->fi == x->fi && y->se <= x->se;
	else return (x->se - y->se) * (z->fi - y->fi) >= (y->se - z->se) * (y->fi - x->fi);
}

bool operator<(pair <ll, ll> a, pair <ll, ll> b){
	if(a.fi != b.fi) return a.fi < b.fi;
	else return a.se > b.se;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	sum[0] = 0;
	cin >> n;
	ll cost = 0, add = 0;
	for(ll a = 1; a <= n; ++a){
		cin >> arr[a];
		sum[a] = arr[a] + sum[a - 1];
		cost += arr[a] * a;
	}
	for(int a = 1; a <= n; ++a){
		if(dq.size() == 1){
			add = max(add, eval(*dq.begin(), a) - sum[a]);
			// cout << eval(*(prev(dq.end())), a) - sum[a] << '\n';
		}
		else if(dq.size() == 2){
			add = max(add, max(eval(*dq.begin(), a), eval(*next(dq.begin()), a)) - sum[a]);
		}
		else if(!dq.empty()){
			int l = 1, r = dq.size() - 1;
			while(l <= r){
				int m = (l + r)/2;
				auto mm = dq.find_by_order(m);
				auto mi = prev(mm);
				if(inter(*mm, *mi) <= a){
					add = max(add, eval(*mm, a) - sum[a]);
					l = m + 1;
				}
				else{
					add = max(add, eval(*mi, a) - sum[a]);
					r = m - 1;
				}
			}
		}

		pair <ll, ll> line = make_pair(arr[a], sum[a] - arr[a] * a);
		
		dq.insert(line);
		auto bb = dq.lower_bound(line);
		// cout << (*bb).fi << '\n';
		if(bad(bb)) {dq.erase(bb); continue;}
		while(next(bb) != dq.end() && bad(next(bb))) dq.erase(next(bb));
		while(bb != dq.begin() && bad(prev(bb))) dq.erase(prev(bb));
	}
	dq.clear();
	ll add2 = 0;
	for(int a = 1; a <= n; ++a){
		if(dq.size() == 1){
			add2 = max(add2, eval(*dq.begin(), arr[a]) + sum[a - 1] - arr[a] * a);
		}
		else if(dq.size() == 2){
			add2 = max(add2, max(eval(*dq.begin(), arr[a]), eval(*next(dq.begin()), arr[a])) + sum[a - 1] - arr[a] * a);
		}
		else if(!dq.empty()){
			int l = 1, r = dq.size() - 1;
			while(l <= r){
				int m = (l + r)/2;
				auto mm = dq.find_by_order(m);
				auto mi = prev(mm);
				if(inter(*mm, *mi) <= arr[a]){
					add2 = max(add2, eval(*mm, arr[a]) + sum[a - 1] - arr[a] * a);
					l = m + 1;
				}
				else{
					add2 = max(add2, eval(*mi, arr[a]) + sum[a - 1] - arr[a] * a);
					r = m - 1;
				}
			}
		}
		pair <ll, ll> line = make_pair(a, -sum[a - 1]);

		dq.insert(line);
		auto bb = dq.lower_bound(line);

		// hapus elemen
		if(bad(bb)) {dq.erase(bb); continue;}
		while(next(bb) != dq.end() && bad(next(bb))) dq.erase(next(bb));
		while(bb != dq.begin() && bad(prev(bb))) dq.erase(prev(bb));
	}	
	cout << cost + max(add, add2) << '\n';

	return 0;
}
