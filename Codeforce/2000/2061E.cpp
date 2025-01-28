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
const int N = 1e5 + 10;
int f[N][11];
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for(int i = 0; i < n; i++) cin >> a[i];    
    for(int i = 0; i < m; i++) cin >> b[i];    

    vector<pair<int, int>> c;
    for(int st = 1; st < (1 << m); st++) {
        int an = -1;
        int cnt = 0;
        for(int i = 0; i < m; i++) {
            if(st & (1 << i)) {
                cnt++;
                if(an == -1) an = b[i];
                else an &= b[i];
            }
        }
        c.push_back({cnt, an});
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= m; j++) {
            f[i][j] = -1;
        }
    }

    for(int i = 0; i < n; i++) {
        f[i][0] = a[i];
        for(auto& p : c) {
            int val = a[i] & p.second;
            int cnt = p.first;
            if(f[i][cnt] == -1) f[i][cnt] = val;
            else f[i][cnt] = min(f[i][cnt], val);
        }
    }
    
    priority_queue<pair<int, pair<int, int>>> pq;
    for(int i = 0; i < n; i++) {
        pq.push({f[i][0] - f[i][1], {i, 0}});
    }
    long long s = 0;
    for(int i = 0; i < n; i++) {
        s += a[i];
    }
    
    while(k > 0) {
        k--;
        pair<int, pair<int, int>> p = pq.top(); pq.pop();
        int i = p.second.first;
        int cur = p.second.second + 1;
        s -= p.first;
        if(cur + 1 <= m) {
            pq.push({f[i][cur] - f[i][cur + 1], {i, cur}});
        }
    }
    cout << s << endl;
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

