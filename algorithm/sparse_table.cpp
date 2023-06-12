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

	T func(T a, T b){
		return a < b ? a : b;
	}

	sparse_table(vector <T> data){
		SZ = data.size() + 1;
		MAXLOG = ceil(log2(data.size() + 1)) + 1;
		lgm.resize(SZ, 0);

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

	T query(int l, int r){
		if(l > r) swap(l, r);
		int lgg = lgm[r - l + 1];
		return func(sparse[lgg][l], sparse[lgg][r - (1 << lgg) + 1]);
	 }
};
