/*
	This is currently one of my favourite algorithm so far
	Heavy Light Decomposition
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fi first
#define se second

const int maxn = 2e5 + 1;
vector <vector <int>> graf(maxn);
int sz[maxn];  // store the size of subtree with node i is the top most node on the subtree
int hv[maxn];  // store the heavy child of each node
int par[maxn]; // store the parent of each node
int st[maxn];  // store the index of each node in segment tree
int dep[maxn]; // store the depth of each node
int top[maxn]; // store the top-most node in a single range in segment tree from each node
int h[maxn];   // store the value of each node
vector <int> euler; // this array store the node order in the segment tree

void dfs(int a, int pr){
	// set up everything
	sz[a] = 1;
	par[a] = pr;
	hv[a] = -1;
	int mx = -1;

	// dfs
	for(auto child : graf[a]){
		if(child == pr) continue;
		dep[child] = dep[a] + 1;
		dfs(child, a);

		// getting heavy child
		if(sz[child] > mx){
			hv[a] = child;
			mx = sz[child];
		}
		sz[a] += sz[child];
	}
}

int tt = 0;
void decompose(int a, int pr, int tp){
	// decompose
	st[a] = tt++;
	top[a] = tp;
	euler.push_back(a);

	// decompose to heavy child
	if(hv[a] != -1) decompose(hv[a], a, tp);

	// decompose to another child
	for(auto child : graf[a]){
		if(child == pr || child == hv[a]) continue;
		decompose(child, a, child);
	}
}

// classic segment tree
int seg[4 * maxn];

int merge(int a, int b){
	return a + b;
}

void build(int l, int r, int v){
	if(l == r){
		seg[v] = h[euler[l]];
	}
	else{
		int m = (l + r)/2;
		build(l, m, 2 * v);
		build(m + 1, r, 2 * v + 1);
		seg[v] = merge(seg[2 * v], seg[2 * v + 1]);
	}
}

int query(int l, int r, int v, int lq, int rq){
	if(lq <= l && r <= rq) return seg[v];
	if(l > rq || r < lq) return 0;
	int m = (l + r)/2;
	return merge(query(l, m, 2 * v, lq, rq), query(m + 1, r, 2 * v + 1, lq, rq));
}

int lca(int a, int b){ // Complexity O(log^2(N)) beacuse of segment tree
	// with bin-lift
	int res = 0;
	while(top[a] != top[b]){
		if(dep[top[a]] > dep[top[b]]) swap(a, b);
		res = merge(res, query(0, euler.size() - 1, 1, st[top[b]], st[b]));
		b = par[top[b]];
	}
	if(st[a] > st[b]) swap(a, b);
	res = merge(res, query(0, euler.size() - 1, 1, st[a], st[b]));
	return res;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	dfs(1, -1);
	decompose(1, -1, 1);
	build(0, euler.size() - 1, 1);
	
	// if there is a query from certain node to another
	cout << lca(node_i, node_j) << '\n';

	return 0;
}
