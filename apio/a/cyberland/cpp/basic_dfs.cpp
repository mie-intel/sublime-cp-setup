#include "cyberland.h"

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fi first
#define se second

const int maxn = 1e5 + 1;
vector <vector <pair <ll, long double>>> v(maxn);
bitset <maxn> vis;

long double mx = LLONG_MAX;
int H;
vector <int> ability;
bool ada = 0;

void dfs(int a, long double dis, int k){
    if(a == H){
        ada = 1;
        if(mx < 0) mx = dis;
        else mx = min(mx, dis);
        return;
    }
    vis[a] = 1;
    for(auto [p, w] : v[a]){
        if(vis[p]) continue;
        if(ability[a] == 0) dfs(p, w, k);
        else if(ability[a] == 1) dfs(p, dis + w, k);
        else{
            if(k){
                dfs(p, dis / 2 + w, k - 1);
                dfs(p, dis + w, k);
            }
            else dfs(p, dis + w, k);
        }
    }
    vis[a] = 0;
}

double solve(int N, int M, int K, int _H, vector<int> x, vector<int> y, vector<int> c, vector<int> arr) {
    H = _H;
    mx = LLONG_MAX;
    v.clear();
    v.resize(N);
    for(int a = 0; a < M; ++a){
        v[x[a]].emplace_back(y[a], c[a]);
        v[y[a]].emplace_back(x[a], c[a]);
    }

    ada = 0;
    ability = arr;

    vis = 0;
    dfs(0, 0, K);

    if(!ada) return -1;
    return mx;
}