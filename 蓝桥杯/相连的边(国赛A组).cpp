//https://www.lanqiao.cn/problems/17099/learning/?page=1&first_category_id=1&name=%E7%9B%B8%E8%BF%9E%E7%9A%84%E8%BE%B9
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
const long long INF = 1e14;
vector<pair<long long, int>> g[N];

struct T {
    long long a;
    int b, c;
    bool operator<(const T& other) {
        return a > other.a;
    }
};

bool comp(pair<long long, int>& p1, pair<long long, int>& p2) {
  return p1.first > p2.first;
}

void solve() {
    int n;
    cin >> n;
    for(int u = 2; u <= n; u++) {
        int v, w;
        cin >> v >> w;
        g[u].push_back({w, v});
        g[v].push_back({w, u});
    }

    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        sort(g[i].begin(), g[i].end(), comp);
        if(g[i].size() >= 3) {
            ans = max(ans, g[i][0].first + g[i][1].first + g[i][2].first);
        }
    }
    

    for(int u = 1; u <= n; u++) {
        vector<pair<long long, int>>& vec = g[u];
        if(vec.size() < 2) continue;
        vector<T> a;
        for(int i = 0; i < vec.size(); i++) {
            int v = vec[i].second;
            long long best = -1;
            for(pair<long long, int>& p : g[v]) {
                if(p.second != u) {
                    best = p.first;
                    break;
                }
            }
            if(best != -1) {
                a.push_back({vec[i].first + best, v, 0});
            }
            a.push_back({vec[i].first, v, 1});
        }
        sort(a.begin(), a.end());
        set<int> s;
        vector<bool> take(2);
        long long sum = 0;
        //cout << "gg " << u << endl;
        for(int i = 0; i < a.size(); i++) {
            //cout << a[i].a << "  " << a[i].b << "  " << a[i].c << endl;
            if(!take[a[i].c] && s.find(a[i].b) == s.end()) {
                take[a[i].c] = true;
                s.insert(a[i].b);
                sum += a[i].a;
            }
        }
        //cout << endl;
        ans = max(ans, sum);
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
