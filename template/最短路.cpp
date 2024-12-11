#include <vector>
using namespace std;

vector<int> dijkstrasAlgorithm(int s, vector<vector<vector<int>>> edges) {
  // Write your code here;
  const int INF = 1e9;
  int n = edges.size();
  vector<int> dis(n, INF);
  vector<bool> st(n);
  dis[s] = 0;

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.push({0, s});
  while(pq.size()) {
    auto p = pq.top(); pq.pop();
    int u = p.second;
    if(st[u]) continue;
    st[u] = true;
    for(auto& e : edges[u]) {
      int v = e[0], w = e[1];
      if(dis[u] + w < dis[v]) {
        dis[v] = dis[u] + w;
        pq.push({dis[v], v});
      }
    }
  }

  for(int i = 0; i < dis.size(); i++) {
    if(dis[i] == INF) {
      dis[i] = -1;
    }
  }
  
  return dis;
}
