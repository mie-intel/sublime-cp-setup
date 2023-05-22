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

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef tree<int,null_type,less_equal<int>,rb_tree_tag,
tree_order_statistics_node_update> iset;

int sequence(int n, vector<int> arr) {
    gp_hash_table <ll, ll, chash> gp;
    iset st;
    ll ans = 0;
    // cari maks
    int mx = -1, id = -1, rd = -1;
    for(int a = 0; a < n; ++a){
        if(arr[a] > mx){
            mx = arr[a];
            id = a;
            rd = a;
        }
        else if(a > 0 && arr[a] == arr[a - 1]) rd = a;
    }
    for(int a = 0; a <= rd; ++a){
        st.insert(arr[a]);
        gp[arr[a]]++;
        int sz = a + 2;
        if(sz % 2 == 1){
            int m = sz / 2;
            ans = max(ans, gp[*st.find_by_order(m)]);
        }
        else{
            int rq = sz / 2;
            int lq = sz / 2 - 1;
            ans = max(ans, gp[*st.find_by_order(lq)]);
            ans = max(ans, gp[*st.find_by_order(rq)]);
        }
    }

    st.clear();
    gp.clear();
    for(int a = n - 1; a >= id; --a){
        st.insert(arr[a]);
        gp[arr[a]]++;
        int sz = a + 2;
        if(sz % 2 == 1){
            int m = sz / 2;
            ans = max(ans, gp[*st.find_by_order(m)]);
        }
        else{
            int rq = sz / 2;
            int lq = sz / 2 - 1;
            ans = max(ans, gp[*st.find_by_order(lq)]);
            ans = max(ans, gp[*st.find_by_order(rq)]);
        }       
    }

    st.clear();
    gp.clear();
    if(rd == n - 1 || id == 0) return ans;
    for(int a = rd, r = rd + 1; a >= 0; --a){
        st.insert(arr[a]);
        gp[arr[a]]++;
        while(r < n && arr[r] >= arr[a]){
            st.insert(arr[r]);
            gp[arr[r]]++;
            r++;
        }
        int sz = st.size();
        if(sz % 2 == 1){
            int m = sz / 2;
            int med = *st.find_by_order(m);
            while(r < n && arr[r] >= med){
                st.insert(arr[r]);
                gp[arr[r]]++;
                r++;
            }
        }
        else{
            int lq = sz / 2 - 1;
            int med = *st.find_by_order(lq);
            while(r < n && arr[r] >= med){
                st.insert(arr[r]);
                gp[arr[r]]++;
                r++;
            }
        }
        sz = st.size();
        if(sz % 2 == 1){
            int m = sz / 2;
            ans = max(ans, gp[*st.find_by_order(m)]);
        }
        else{
            int rq = sz / 2;
            int lq = sz / 2 - 1;
            ans = max(ans, gp[*st.find_by_order(lq)]);
            ans = max(ans, gp[*st.find_by_order(rq)]);
        }         
    }

    return ans;
}
