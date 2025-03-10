//https://www.lanqiao.cn/problems/19721/learning/?page=1&first_category_id=1&name=%E6%9C%80%E5%A4%A7%E5%BC%82%E6%88%96%E7%BB%93%E7%82%B9
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

const int N = 2e5 + 100;
int tr[N * 33][2];
int cnt[N * 33 * 2];
int id = 0;
void add(long long n) {
    int u = 0;
    for(int i = 32; i >= 0; i--) {
        int b = 0;
        if(n & (1ll << i)) b = 1;
        if(tr[u][b] == -1) tr[u][b] = id++;
        u = tr[u][b];
        cnt[u]++;
    }
}

void del(long long n) {
    int u = 0;
    for(int i = 32; i >= 0; i--) {
        int b = 0;
        if(n & (1ll << i)) b = 1;
        u = tr[u][b];
        cnt[u]--;
    }
}

long long find(long long n) {
    int u = 0;
    long long ans = 0;
    for(int i = 32; i >= 0; i--) {
        int b = 0;
        if(n & (1ll << i)) b = 1;
        if(tr[u][b ^ 1] != -1 && cnt[tr[u][b ^ 1]]) {
            ans += (1ll << i);
            u = tr[u][b ^ 1];
        } else {
            u = tr[u][b];
        }
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> g(n);
    for(int i = 0; i < n; i++) {
        int p;
        cin >> p;
        if(p != -1) {
            g[p].push_back(i);
            g[i].push_back(p);
        }
    }

    memset(tr, -1, sizeof tr);
    memset(cnt, 0, sizeof cnt);
    id = 1;

    for(int i = 0; i < n; i++) {
        add(a[i]);
    }

    long long ans = 0;
    for(int u = 0; u < n; u++) {
        int val = a[u];
        for(int v : g[u]) {
            del(a[v]);
        }
        ans = max(ans, find(val));
        for(int v : g[u]) {
            add(a[v]);
        }
    }
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
