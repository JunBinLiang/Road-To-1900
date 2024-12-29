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

using namespace std;

struct MatrixQuery {
  int n, m;
  vector<vector<long long>> dp;
  void init(vector<vector<long long>>& a) {
    n = a.size();
    m = a[0].size();
    dp = vector<vector<long long>>(n + 1, vector<long long>(m + 1)); 
    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= m; j++) {
        dp[i][j] = a[i - 1][j - 1];
        dp[i][j] += dp[i - 1][j];
        dp[i][j] += dp[i][j - 1];
        dp[i][j] -= dp[i - 1][j - 1];
      }
    }
  }

  long long query(int r1, int c1, int r2, int c2) {
    r1++;
    c1++;
    r2++;
    c2++;
    return dp[r2][c2] - dp[r1 - 1][c2] - dp[r2][c1 - 1] + dp[r1 - 1][c1 - 1];
  }
} ma1, ma2, ma3;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> a(n, vector<long long>(n));
    vector<vector<long long>> p1(n, vector<long long>(n));
    vector<vector<long long>> p2(n, vector<long long>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            p1[i][j] = a[i][j] * (j + 1);
        }
    }

    for(int c = 0; c < n; c++) {
        for(int r = 0; r < n; r++) {
            p2[r][c] = (r) * a[r][c];
        }
    }

    ma1.init(a);
    ma2.init(p1);
    ma3.init(p2);


    while(m--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        r1--; c1--; r2--; c2--;
        int M = (c2 - c1 + 1);
        long long ans = 0;
        long long s1 = ma2.query(r1, c1, r2, c2);
        s1 -= (ma1.query(r1, c1, r2, c2) * c1);
        ans += s1;
        long long s2 = ma3.query(r1, c1, r2, c2);
        s2 -= (ma1.query(r1, c1, r2, c2) * r1);
        ans += (s2 * M);
        cout << ans << " ";
    }
    cout << endl;
}   


int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
