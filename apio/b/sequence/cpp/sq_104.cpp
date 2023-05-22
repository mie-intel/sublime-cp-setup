#include "sequence.h"

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fi first
#define se second

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const ll RANDOM = rng();
struct chash{
    const ll operator() (ll x) const {return x ^ RANDOM;}
};

int sequence(int N, vector<int> A) {
    ll mx = 0;
    for(int a = 0; a < N; ++a){
        vector <int> v;
        gp_hash_table <ll, ll, chash> gp;
        for(int b = a; b < N; ++b){
            v.push_back(A[b]);
            gp[A[b]]++;
            // sesuaikan
            int i = v.size() - 1;
            while(i - 1 >= 0 && v[i] < v[i - 1]){
                swap(v[i], v[i - 1]);
                i--;
            }
            // get mid
            if(v.size() % 2 == 1){
                mx = max(mx, gp[v[v.size() / 2]]);
            }
            else{
                mx = max(mx, max(gp[v[v.size() / 2]], gp[v[v.size() / 2 - 1]]));
            }
        }
    }
    return mx;
}
