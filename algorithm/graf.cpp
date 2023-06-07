#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fi first
#define se second

template <typename T> struct adjl{
	int sz = 0;
	vector <long long> distance;
	vector <bool> visit;
	vector <vector <pair <T, T>>> node;
	adjl(unsigned int SZ = 0){
		try{
			if(SZ >= 0){
				node.resize(SZ);
				distance.resize(SZ);
				visit.resize(SZ);
				sz = SZ;
			}
			else throw(sz);
		}
		catch (unsigned int SZ){
			cout << "size must be equal or bigger than 0!\n";
		}	
	}

	void reset(unsigned int SZ){
		try{
			if(SZ >= 0){
				node.clear();
				node.resize(SZ);
				distance.resize(SZ);
				visit.resize(SZ);
				sz = SZ;
			}
			else throw(SZ);
		}
		catch (unsigned int SZ){
			cerr << "size must be equal or bigger than 0!" << endl;
		}	
	}

	void addedge(T i, T j, T k = 0){
		try{
			if(i < sz) node[i].emplace_back(j, k);
			else throw(i);
		}
		catch (unsigned int num){
			cerr << "node value has to be less than size!" << endl;
		}
	}

	void dijkstra(int now){
		distance.clear();
		distance.resize(sz, LLONG_MAX);
		visit.clear();
		visit.resize(sz, 0);
		priority_queue <pair <T, T>> pq;
		distance[now] = 0;
		pq.emplace(0, now);
		while(!pq.empty()){
			int i = pq.top().se;
			pq.pop();
			if(visit[i]) continue;
			visit[i] = 1;
			for(auto [child, weight] : node[i]){
				if(distance[child] > distance[i] + weight){
					distance[child] = distance[i] + weight;
					pq.emplace(-distance[child], child);
				}
			}
		}
	}

	void bfs(int now){
		distance.clear();
		distance.resize(sz, LLONG_MAX);
		visit.clear();
		visit.resize(sz, 0);
		queue <T> q;
		distance[now] = 0;
		q.emplace(now);
		while(!q.empty()){
			int i = q.front();
			q.pop();
			if(visit[i]) continue;
			visit[i] = 1;
			for(auto [child, weight] : node[i]){
				if(!visit[child]){
					distance[child] = min(distance[child], distance[i] + weight);
					q.emplace(child);
				}
			}
		}
	}

	void rec(int now){
		visit[now] = 1;
		for(auto [child, weight] : node[now]){
			if(!visit[child]){
				distance[child] = min(distance[child], distance[now] + weight);
				rec(child);
			}
		}
	}

	void dfs(int now){
		distance.clear();
		distance.resize(sz, LLONG_MAX);
		visit.clear();
		visit.resize(sz, 0);
		rec(now);
	}

	// make sure to call this after call dijkstra
	long long getDist(int now){
		return distance[now];
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, s, t;
	cin >> n >> m >> s >> t;
	adjl <ll> v(n + 1);
	for(int a = 1; a <= m; ++a){
		int i, j, k;
		cin >> i >> j >> k;
		v.addedge(i, j, k);
		v.addedge(j, i, k);
	}

	v.dijkstra(s);

	cout << v.getDist(t) << '\n';

	return 0;
}