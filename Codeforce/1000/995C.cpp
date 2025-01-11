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

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(m);
    for(int i = 0; i < m; i++) {
        cin >> a[i];
    }

    vector<bool> vis(m + 1);
    for(int i = 0; i < k; i++) {
        int x;
        cin >> x;
        vis[x] = true;
    }

    string ans = "";
    for(int i = 0; i < m; i++) {
        if(k < n - 1) {
            ans += "0";
            continue;
        }
        if(k == n) {
            ans += "1";
            continue;
        }

        bool ok = true;
        if(vis[a[i]]) {
            ok = false;
        }

        if(ok) ans += "1";
        else ans += "0";
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
