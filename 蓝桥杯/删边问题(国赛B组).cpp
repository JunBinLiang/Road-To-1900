//https://www.lanqiao.cn/problems/17108/learning/?page=1&first_category_id=1&second_category_id=3&name=%E5%88%A0%E8%BE%B9%E9%97%AE%E9%A2%98
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    
#include <deque>  

using namespace std;

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

const int N = 2e5 + 10;
map<pair<int, int>, int> mp;
vector<int> g[N];
int dfn[N], low[N], ids[N];
vector<int> stk;
int ti = 0, com = 0;

vector<pair<int, int>> bridges;

long long ans = 1e18, tot = 0;
long long sums[N], dp[N];
long long comSum[N];
int cnt = 0;
int a[N];


void tarjan(int pa, int u) {
    dfn[u] = low[u] = ++ti;
    stk.push_back(u);
    comSum[cnt] += a[u];
    for(int v : g[u]) {
        if(!dfn[v]) {
            tarjan(u, v);
            low[u] = min(low[u], low[v]);
            if(dfn[u] < low[v]) { //u v is bridge
                bridges.push_back({u, v});
            }
        } else if(v != pa) {
            low[u] = min(low[u], dfn[v]);
        } else if(v == pa &&  mp[{u, v}]> 1) {
            //not from parent and make sure there is no duplicate edge, duplicate edges should be considered as the same component
            low[u] = min(low[u], dfn[v]);
        }
    }

    if(dfn[u] == low[u]) { //不能走到上面
        com++;
        while(stk.size() > 0) {
            int top = stk.back();  
            stk.pop_back();
            ids[top] = com;
            if(top == u) break;
        }
    } 
}

void dfs(int pa, int u) {
    dp[u] = sums[u];
    for(int v : g[u]) {
        if(v == pa) {
            continue;
        }
        dfs(u, v);
        dp[u] += dp[v];
    }
    ans = min(ans, abs(dp[u] - (tot - dp[u])));
}

void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        tot += a[i];
    }

    vector<pair<int, int>> e;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        mp[{u, v}]++;
        mp[{v, u}]++;
        e.push_back({u, v});
    }

    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(sums, 0, sizeof sums);
    memset(comSum, 0, sizeof comSum);
    ti = 0;

    for(int i = 1; i <= n; i++) {
      if(!dfn[i]) {
        tarjan(-1, i);
        cnt++;
      }
    }

    if(cnt > 2 || com == 1) { //more than 2 disconnect components
      cout << -1 << endl;
      return;
    }

    if(cnt == 2) { //need to cut a non brige edge
        if(bridges.size() == m) {
            cout << -1 << endl;
            return;
        }
        cout << abs(comSum[0] - comSum[1]) << endl;
        return;
    }

    for(int i = 0; i <= n; i++) g[i].clear();
    set<pair<int, int>> s;
    for(auto& edge : e) {
        int u = ids[edge.first], v = ids[edge.second];
        if(u > v) swap(u, v);
        if(u == v) continue;
        if(s.find({u, v}) == s.end()) {
            s.insert({u, v});
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }

    for(int i = 1; i <= n; i++) {
        sums[ids[i]] += a[i];
    }
    dfs(-1, 1);
    cout << ans << endl;
}

int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
