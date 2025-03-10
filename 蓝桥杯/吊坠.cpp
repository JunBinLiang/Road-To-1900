//https://www.lanqiao.cn/problems/19719/learning/?page=1&first_category_id=1&name=%E5%90%8A%E5%9D%A0
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
const int N = 210;
int p[N];
int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
}

struct E {
    int u, v, w;
    bool operator<(const E& other) {
        return w < other.w;
    }
};

const int BASE = 26;
const int MOD = 1e9 + 7;
long long h1[150], h2[150], po[150];

long long get(long long h[150], int l, int r) {
    if(l == 0) return h[r];
    int sz = r - l + 1;
    return ((h[r] - (h[l - 1] * po[sz] % MOD)) + MOD) % MOD; 
}

bool ok(string& s, string& t, int k) {
    long long h = 0;
    for(int i = 0; i < s.size(); i++) {
        h = h * BASE  + (s[i] - 'a' + 1);
        h %= MOD;
        h1[i] = h;
    }

    h = 0;
    for(int i = 0; i < t.size(); i++) {
        h = h * BASE  + (t[i] - 'a' + 1);
        h %= MOD;
        h2[i] = h;
    }

    unordered_set<long long> us;
    for(int i = 0; i < s.size(); i++) {
        if(i + k > s.size()) break;
        us.insert(get(h1, i, i + k - 1));
    }

    for(int i = 0; i < t.size(); i++) {
        if(i + k > t.size()) break;
        long long val = get(h2, i, i + k - 1);
        if(us.find(val) != us.end()) {
            return true;
        }
    }

    return false;
}

int cal(string& s, string& t) {
    string news = s + s;
    string newt = t + t;
    int ans = 0;
    int l = 1, r = min(t.size(), s.size());
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(ok(news, newt, mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    po[0] = 1;
    for(int i = 1; i < 150; i++) po[i] = (po[i - 1] * BASE) % MOD;
    vector<E> e;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            e.push_back({i, j, cal(a[i], a[j])});
        }
    }
    
    
    for(int i = 0; i < n; i++) p[i] = i;
    int ans = 0;
    sort(e.begin(), e.end());
    reverse(e.begin(), e.end());
    for(int i = 0; i < e.size(); i++) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        int r1 = find(u), r2 = find(v);
        //cout << u << " " << v << " " << w << endl;
        if(r1 != r2) {
            ans += w;
            p[r1] = r2;
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
