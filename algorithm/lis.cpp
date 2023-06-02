#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fi first
#define se second

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	int arr[n];
	for(int a = 0; a < n; ++a) cin >> arr[a];
	vector <int> dp;
	for(int a = 0; a < n; ++a){
		int i = lower_bound(dp.begin(), dp.end(), arr[a]) - dp.begin();
		if(i == dp.size()) dp.push_back(arr[a]);
		else dp[i] = arr[a];
	}
	cout << dp.size() << '\n';

	return 0;
}