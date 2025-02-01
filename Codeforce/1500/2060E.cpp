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
using ll = long long;

int find(vector<int>& p, int u) {
    return p[u] == u ? u : p[u] = find(p, p[u]);
}

void solve() {
    int n, m1, m2;
    cin >> n >> m1 >> m2;
    vector<pair<int, int>> e;
    vector<int> p1(n + 1), p2(n + 1);
    for(int i = 0; i <= n; i++) p1[i] = i;
    for(int i = 0; i <= n; i++) p2[i] = i;

    for(int i = 0; i < m1; i++) {
        int u, v;
        cin >> u >> v;
        e.push_back({u, v});
    }

    for(int i = 0; i < m2; i++) {
        int u, v;
        cin >> u >> v;
        int r1 = find(p2, u);
        int r2 = find(p2, v);
        if(r1 != r2) {
            p2[r1] = r2;
        }
    }
    
    int ans = 0;
    for(int i = 0; i < e.size(); i++) {
        int u = e[i].first, v = e[i].second;
        int r1 = find(p2, u);
        int r2 = find(p2, v);
        if(r1 == r2) { //on the same component
            r1 = find(p1, u);
            r2 = find(p1, v);
            if(r1 != r2) {
                p1[r1] = r2;
            }
        } else {
            ans++;
        }
    }
    
    for(int i = 1; i <= n; i++) {
        int r1 = find(p1, i);
        int r2 = find(p2, i);
        //cout << i << " " << r1 << " " << r2 << endl;
        r1 = find(p1, r1);
        r2 = find(p1, r2);
        //cout << i << " " << r1 << " " << r2 << endl;
        if(r1 != r2) {
            ans++;
            p1[r1] = r2;
        }
    }
    cout << ans << endl;
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

