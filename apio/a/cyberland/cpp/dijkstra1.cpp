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
    bitset <maxn> vis, bawa;

    memset(dis, 1, sizeof dis);
    dis[0] = 0;
    vis = 0;

    priority_queue <pair <pair <ll, ll>, ll>> pq;
    pq.emplace(make_pair(1, -dis[0]), 0);
    bawa[0] = 1;
    for(int a = 1; a < N; ++a){
        if(arr[a] == 0){
            dis[a] = 0;
            pq.emplace(make_pair(0, -dis[0]), 0);
        }
    }
    while(!pq.empty()){
        int i = pq.top().se;
        pq.pop();
        if(vis[i]) continue;
        vis[i] = 1;
        if(i == H) continue;
        for(auto [p, w] : v[i]){
            if(dis[p] > dis[i] + w){
                dis[p] = dis[i] + w;
                if(bawa[i]) bawa[p] = 1;
                pq.emplace(make_pair(bawa[p], -dis[p]), p);
            }
            if(!bawa[p]){
                dis[p] = dis[i] + w;
                pq.emplace(make_pair(bawa[p], -dis[p]), p);
            }
        }
    }

    if(!bawa[H]) return -1;
    return (double)dis[H];
}