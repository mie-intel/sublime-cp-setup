#include "cyberland.h"

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fi first
#define se second

const int maxn = 1e5 + 1;
vector <vector <pair <ll, long double>>> v(maxn);
ll dis[maxn];
bitset <maxn> vis;

long double mx = LLONG_MAX;
int H;
vector <int> ability;

long double INF = 10000000000000;

double solve(int N, int M, int K, int _H, vector<int> x, vector<int> y, vector<int> c, vector<int> arr) {
    H = _H;

    long double dp[N][K + 1];
    for(int a = 0; a < N; ++a)
        for(int b = 0; b <= K; ++b) dp[a][b] = INF;

    for(int a = 0; a <= K; ++a) dp[0][a] = INF;
    dp[0][0] = 0;
    
    int used = 0;
    for(int a = 1; a < N; ++a){
        // kalo a = 0, maka semua dp jadi 0
        if(arr[a] == 0){
            for(int b = 0; b <= K; ++b){
                if(b <= used) dp[a][b] = 0;
                else dp[a][b] = dp[a - 1][b];
            }
        }
        else if(arr[a] == 1){
            for(int b = 0; b <= K; ++b){
                dp[a][b] = dp[a - 1][b] + c[a - 1];
            }
        }
        else{
            dp[a][0] = dp[a - 1][0] + c[a - 1];
            for(int b = 1; b <= K; ++b){
                long double lq = dp[a - 1][b] + c[a - 1];
                long double rq = (dp[a - 1][b - 1] + (long double)c[a - 1]) / 2.0;
                dp[a][b] = min(lq, rq);
                // cout << bool(lq >= rq) << '\n';
                // cout << "A " << a << " "  << b << " " << dp[a][b] << '\n';
                // cout << lq << " " << rq << '\n';
            }
            used++;
        }
    }

    long double ans = INF;
    for(int a = 0; a <= K; ++a){
        ans = min(ans, dp[H][a]);
    }

    for(int a = 0; a < N; ++a){
        // cout << "A " << a << ": ";
        for(int b = 0; b <= K; ++b){
            // cout << dp[a][b] << " ";
        }
        // cout << '\n';
    }

    return ans;
}

/*
3 2
1
2
0 1 2
1 2 3
1 2 1

*/