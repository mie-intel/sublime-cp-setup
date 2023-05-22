#include "sequence.h"

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fi first
#define se second

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const ll RANDOM = rng();
struct chash{
    const ll operator() (ll x) const {return x ^ RANDOM;}
};

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> iset;

int sequence(int N, vector<int> A) {
    ll mx = 0;
    for(int a = 0; a < N; ++a){
        iset v;
        gp_hash_table <ll, ll, chash> gp;
        for(int b = a; b < N; ++b){
            v.insert(A[b]);
            gp[A[b]]++;
            // get mid
            if(v.size() % 2 == 1){
                int id = v.size() / 2;
                mx = max(mx, gp[*v.find_by_order(id)]);
            }
            else{
                int id = v.size() / 2;
                int ld = v.size() / 2 - 1;
                mx = max(mx, max(gp[*v.find_by_order(id)], gp[*v.find_by_order(ld)]));
            }
        }
    }
    return mx;
}
