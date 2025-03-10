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

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> ans(n + 1, vector<int>(m + 1));
    vector<pair<int, int>> row(n + 1), col(m + 1);
    for(int i = 0; i <= n; i++) row[i] = {0, -1};
    for(int i = 0; i <= m; i++) col[i] = {0, -1};

    int t = 0;
    while(k--) {
        int op;
        cin >> op;
        if(op == 1) {
            int r, x;
            cin >> r >> x;
            row[r] = {x, t};
        } else {
            int c, x;
            cin >> c >> x;
            col[c] = {x, t};
        }
        t++;
    }
    
    for(int r = 1; r <= n; r++) {
        for(int c = 1; c <= m; c++) {
            if(row[r].second > col[c].second) {
                cout << row[r].first << " ";
            } else{
                cout << col[c].first << " ";
            }
        }
        cout << endl;
    }
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
