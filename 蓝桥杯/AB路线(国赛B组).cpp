//https://www.lanqiao.cn/problems/17109/learning/?page=1&first_category_id=1&second_category_id=3&name=AB%E8%B7%AF%E7%BA%BF
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
const int N = 1010;
int d[N][N][11];
const int INF = 1e9;
vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
struct P {
    int r, c, step;
};
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(int c = 0; c <= k; c++) {
                d[i][j][c] = INF;
            }
        }
    }
    
    queue<P> q;
    q.push({0, 0, 1});
    d[0][0][1] = 0;

    while(q.size()) {
        auto p = q.front(); q.pop();
        int r = p.r, c = p.c, step = p.step;
        for(auto& di : dir) {
            int newr = r + di[0], newc = c + di[1];
            if(newr < 0 || newr >= n || newc < 0 || newc >= m) continue;
            if(step == k) {
                if(a[r][c] == a[newr][newc]) continue;
                if(d[r][c][step] + 1 < d[newr][newc][1]) {
                    d[newr][newc][1] = d[r][c][step] + 1;
                    q.push({newr, newc, 1});
                }
            } else {
                if(a[r][c] != a[newr][newc]) continue;
                if(d[r][c][step] + 1 < d[newr][newc][step + 1]) {
                    d[newr][newc][step + 1] = d[r][c][step] + 1;
                    q.push({newr, newc, step + 1});
                }
            }
        }
    }

    int ans = INF;
    for(int i = 1; i <= k; i++) ans = min(ans, d[n - 1][m - 1][i]);
    if(ans == INF) cout << -1 << endl;
    else cout << ans << endl;
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
