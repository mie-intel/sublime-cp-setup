#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fi first
#define se second

template <class T> struct sparse_table{
	vector <vector <T>> sparse;
	vector <int> lgm;
	int SZ = 0;
	int MAXLOG = 0;
	T neutral;

	// function that return the desired value for each node
	T func(T a, T b){
		return a < b ? a : b;
	}

	// parameters : vector of data and neutral value
	sparse_table(vector <T> data, T _neutral){
		SZ = data.size() + 1;
		MAXLOG = ceil(log2(data.size() + 1)) + 1;
		lgm.resize(SZ, 0);
		neutral = _neutral;

		// initialize lgm
		for(int a = 2; a < SZ; ++a) lgm[a] = lgm[a / 2] + 1;

		// init first dimension
		sparse.push_back(vector <T> ());
		for(int a = 0; a < (int)data.size(); ++a) sparse[0].push_back(data[a]);

		// transition sparse table
		for(int bit = 1; bit < MAXLOG; ++bit){
			sparse.push_back(vector <T> ());
			for(int a = 0; a + (1ll << bit) - 1 < (int)data.size(); ++a){
				sparse.back().push_back(func(sparse[bit - 1][a], sparse[bit - 1][a + (1 << (bit - 1))]));
			}		
		}
	}

	// O(1) query
	// make sure that the query is solveable despite having overlaped query
	// gcd, min, max query can be solved fast using this function
	T query(int l, int r){
		if(l > r) swap(l, r);
		int lgg = lgm[r - l + 1];
		return func(sparse[lgg][l], sparse[lgg][r - (1 << lgg) + 1]);
	}

	// basic O(log N) query
	T query2(int l, int r){
		if(l > r) swap(l, r);
		int len = r - l + 1;
		T res = neutral; // neutral value
		for(int bit = 0; bit < MAXLOG && l <= r; ++bit){
			if(len & (1 << bit)){
				res = func(res, sparse[bit][l]);
				l += (1 << bit);
			}
		}
		return res;
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, q;
	cin >> n >> q;

	vector <int> v(n);
	for(int a = 0; a < n; ++a){
		cin >> v[a];
	}

	sparse_table sp(v, 1000000001);

	for(int a = 1; a <= q; ++a){
		int l, r;
		cin >> l >> r;
		l--, r--;
		cout << sp.query2(l, r) << '\n';
	}

	return 0;
}
