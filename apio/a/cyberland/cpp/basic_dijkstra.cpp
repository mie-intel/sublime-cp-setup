#include "cyberland.h"

#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#define gc getchar
namespace fastio{
    template <typename T> void sca(T &angka){
        T kali = 1; angka = 0; char input = gc();
        while (input < '0' || input > '9'){if (input == '-') kali = -1; input = gc();}
        while(input >= '0' && input <= '9')angka = (angka << 3) + (angka << 1) + input - 48, input = gc();
        angka *= kali;
    }
    template < typename FIRST, typename... REST > void scan( FIRST& first, REST&... rest ); // utama
    void scan() {}
      template < typename FIRST, typename... REST > void scan( FIRST& first, REST&... rest ){sca(first);scan(rest...);}
}using namespace fastio;

typedef long long ll;
#define fi first
#define se second

// ide ac, ganti dis sama vis jadi gp hash table

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const ll RANDOM = rng();
struct chash{
    const ll operator() (ll x) const {return x ^ RANDOM;}
};

const int maxn = 1e5 + 2;
double solve(int N, int M, int K, int H, vector<int> x, vector<int> y, vector<int> c, vector<int> arr) {

    // w, dan div
    vector <vector <pair <ll, ll>>> v(maxn);
    for(int a = 0; a < M; ++a){
        v[x[a]].emplace_back(y[a], c[a]);
        v[y[a]].emplace_back(x[a], c[a]);
    }

    gp_hash_table <ll, double, chash> dis[N], vis[N];
    // cout << "AMAN" << endl;
    // 1e15

    dis[0][0] = 0;

    priority_queue <pair <double, pair <ll, ll>>> pq;
    pq.emplace(dis[0][0], make_pair(0, 0));
    while(!pq.empty()){
        int j = pq.top().se.se;
        int i = pq.top().se.fi;
        pq.pop();
        // cout << "VISIT " << i << " " << j << " " << -pq.top().fi << endl;
        if(vis[i][j] != 0) continue;
        vis[i][j] = 1;
        if(i == H) continue;
        for(auto [p, w] : v[i]){
            if(arr[p] == 0){
                if(vis[p][0] == 0 || dis[p][0] > 0){
                    dis[p][0] = 0;
                    vis[p][0] = 0;
                    pq.emplace(-dis[p][0], make_pair(p, 0));
                }
            }
            else{
                if(vis[p][j] == 0 || dis[p][j] > dis[i][j] + w){
                    dis[p][j] = dis[i][j] + w;
                    vis[p][j] = 0;
                    pq.emplace(-dis[p][j], make_pair(p, j));
                }
            }
        }

        if(arr[i] == 2 && j + 1 <= K){
            for(auto [p, w] : v[i]){
                if(arr[p] != 0){
                    if(vis[p][j + 1] == 0 || dis[p][j + 1] > (dis[i][j] / 2.0) + w){
                        dis[p][j + 1] = (dis[i][j] / 2.0) + w;
                        vis[p][j + 1] = 0;
                        pq.emplace(-dis[p][j + 1], make_pair(p, j + 1));
                    }
                }
            }            
        }
    }

    double ans = LLONG_MAX;
    bool ada = 0;

    for(auto p : dis[H]){
        ada = 1;
        ans = min(ans, p.se);
    }

    if(!ada) return -1;
    return ans;
}

/*
1
4 3 17
3
1 2 0 1
0 1 100000
1 2 1
1 3 5

*/