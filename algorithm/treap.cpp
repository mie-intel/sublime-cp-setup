#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fi first
#define se second

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct node{
	ll prior, size, key, lazy;
	node *L, *R;
	node(int val) : prior(rng()), size(1), key(val), lazy(0), L(NULL), R(NULL) {}
};

typedef node* pnode;

struct Treap{
	// 0 based 
	pnode treap;

	// mendapatkan size
	int getsz(pnode T){
		return T ? T->size : 0;
	}
	
	// update size
	void upd_sz(pnode T){
		if(T) T->size = getsz(T->L) + 1 + getsz(T->R);
	}

	// propagate
	void prop(pnode T){
		if(!T || T->lazy == 0) return;
		T->key += T->lazy;
		if(T->L) T->L->lazy += T->lazy;
		if(T->R) T->R->lazy += T->lazy;
		T->lazy = 0;
	}
		
	// split treap
	void split(pnode T, pnode &L, pnode &R, int x, int add = 0){
		if(!T){
			L=R=NULL;
			return;
		}
		int cur_key = add + getsz(T->L);
		if(cur_key <= x) split(T->R, T->R, R, x, cur_key + 1), L = T;
		else split(T->L, L, T->L, x, add), R = T;
		upd_sz(T), prop(T);
	}
	
	// merge treap
	void merge(pnode &T, pnode L, pnode R){
		if(!L || !R) T = L?L:R; // base case
		else if(L->prior > R->prior) merge(L->R, L->R, R), T = L;
		else merge(R->L, L, R->L), T = R;
		upd_sz(T), prop(T);
	}
	
	// insert val in position pos
	void insert(ll val, int pos){
		pnode tmp, L, R, X = new node(val);;
		split(treap, L, R, pos - 1);
		merge(tmp, L, X);
		merge(treap, tmp, R);
	}
		
	// erase position pos
	void erase(int pos){
		pnode L1, R1, L2, R2;
		split(treap, L1, R1, pos);
		split(L1, L2, R2, pos - 1);
		merge(treap, L2, R1);
	}

	// increase all value
	void increase(ll val){
		if(!treap) return;
		treap->lazy += val;
		prop(treap);
	}

	// print
	void print(pnode T){
		if(!T) return;
		prop(T);
		if(getsz(T) == 1){
			cout << T->key << " ";
		}
		else{
			if(T->L) print(T->L);
			cout << T->key << " ";
			if(T->R) print(T->R);
		}
	}
};

Treap T;

int main(){
	ios_base::sync_with_stdio(0);
	// cin.tie(0);

	int q, pos, x;
	while(cin >> q >> x){
		if(q == 0){
			cin >> pos;
			T.insert(x, pos);
			T.increase(1);
		}
		else{
			T.erase(x);
		}
		T.print(T.treap);
		cout << '\n';
	}

	return 0;
}
