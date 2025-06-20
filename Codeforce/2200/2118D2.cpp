#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
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

const int N = 4e5 + 100;
map<long long, set<int>> f;
vector<int> g[N];
bool vis[N];
bool cycle[N];
bool is = false;
void dfs(set<int>& cur, int u) {
    for(int v : g[u]) {
        if(vis[v]) {
            if(cur.find(v) != cur.end() || cycle[v]) { //cycle
                is = true;
            }
        } else {
            vis[v] = true;
            cur.insert(v);
            dfs(cur, v);
        }
    }
}

void solve() {
    int n; long long k;
    cin >> n >> k;
    f.clear();
    vector<pair<long long, long long>> a(n); 
    for(int i = 0; i < n; i++) cin >> a[i].first;
    for(int i = 0; i < n; i++) cin >> a[i].second;
    sort(a.begin(), a.end());
    for(int i = 0; i <= 2 * n; i++) {
        g[i].clear();
        vis[i] = false;
        cycle[i] = false;
    }

    for(int i = 0; i < n; i++) {
        long long p = a[i].first, d = a[i].second;
        if(p >= d) {
            f[(p - d) % k].insert(i);
        }
    }

    //x * k + d
    map<long long, int> mp;
    for(int i = 0; i < n; i++) {
        long long p = a[i].first, d = a[i].second;
        long long t = p + d;
        long long need = (k - t) % k;
        if(need < 0) need += k;
        if(mp.find(need) != mp.end()) {
            g[i].push_back(mp[need] + n);
        }
        mp[((-d - p) % k + k) % k] = i;
    }
    mp.clear();

    for(int i = n - 1; i >= 0; i--) {
        long long p = a[i].first, d = a[i].second;
        long long t = d - p;
        long long need = (k - t) % k;
        if(need < 0) need += k;
        if(mp.find(need) != mp.end()) {
            g[i + n].push_back(mp[need]);
        }
        mp[((p - d) + k) % k] = i;
    }

    //do cycle
    for(int i = 0; i < 2 * n; i++) {
        if(!vis[i]) {
            set<int> cur;
            cur.insert(i);
            is = false;
            vis[i] = true;
            dfs(cur, i);
            if(is) {
                for(int u : cur) {
                    cycle[u] = true;
                }
            }
        }
    }


    int m;
    cin >> m;
    for(int i = 0; i < m; i++) {
        long long po;
        cin >> po;
        
        if(f.find(po % k) == f.end()) {
            cout << "YES" << endl;
            continue;
        }
        
        int l = 0, r = a.size() - 1;
        int p = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(po <= a[mid].first) {
                p = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        
        if(p == -1) {
            cout << "YES" << endl;
            continue;
        }
        
        set<int>& s = f[po % k];
        auto it = s.upper_bound(p - 1);
        if(it == s.end()) {
            cout << "YES" << endl;
        } else {
            int j = *it;
            if(cycle[j]) {
                cout << "NO" << endl;
            } else {
                cout << "YES" << endl;
            }
        }
    }
}


int main() {
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
