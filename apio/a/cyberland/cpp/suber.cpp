#include "cyberland.h"

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fi first
#define se second

const int maxn = 1e5 + 2;
double solve(int N, int M, int K, int H, vector<int> x, vector<int> y, vector<int> c, vector<int> arr) {
    vector <vector <pair <ll, ll>>> v(N);
    for(int a = 0; a < M; ++a){
        v[x[a]].emplace_back(y[a], c[a]);
        v[y[a]].emplace_back(x[a], c[a]);
    }

    ll dis[maxn];
    bitset <maxn> vis;

    memset(dis, 1, sizeof dis);
    dis[0] = 0;
    vis = 0;

    priority_queue <pair <ll, ll>> pq;
    pq.emplace(-dis[0], 0);
    while(!pq.empty()){
        int i = pq.top().se;
        pq.pop();
        // cout << "VISITING " << i << '\n';
        // for(int a = 0; a < N; ++a) cout << dis[a] << " \n"[a == N - 1];
        // for(int a = 0; a < N; ++a) cout << vis[a] << " \n"[a == N - 1];
        if(vis[i]) continue;
        vis[i] = 1;
        if(i == H) continue;
        for(auto [p, w] : v[i]){
            if(arr[p] == 0){
                if(dis[p] > 0){
                    dis[p] = 0;
                    vis[p] = 0;
                    pq.emplace(-dis[p], p);
                }
            }
            else if(dis[p] > dis[i] + w){
                dis[p] = dis[i] + w;
                vis[p] = 0;
                pq.emplace(-dis[p], p);
            }
        }
    }

    // for(int a = 0; a < N; ++a){
    //     cout << dis[a] << " \n"[a == N - 1];
    // }
    // cout << H << '\n';
    if(vis[H]) return dis[H];
    return -1;
}