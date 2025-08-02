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

const int N = 2e5 + 10;
const long long INF = 1e16;
long long dp[N][35];

vector<int> get(int cur, int bit) {
    if(cur <= bit) {
        vector<int> ans = {bit};
        return ans;
    }

    //cur > temp
    vector<int> ans;
    int temp = bit;
    for(int i = 30; i >= 0; i--) {
        if(temp & (1 << i)) continue;
        if((temp + (1 << i)) >= cur) {
            ans.push_back(temp + (1 << i));
        } else {
            temp += (1 << i);
        }
        //cout << temp << " " << cur << endl;
    }
    sort(ans.begin(), ans.end());
    return ans;
}

void upd(long long& x, long long y) {
    if(x == -1) x = y;
    else x = min(x, y);
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n - 1; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j < 35; j++) {
            dp[i][j] = -1;
        }
    }

    vector<int> pd = get(b[0], a[0]);
    for(int i = 0; i < pd.size(); i++) {
        dp[0][i] = pd[i] - b[0];
        //cout << pd[i] << " ";
    }
    //cout  << endl;

    for(int i = 1; i < n; i++) {
        int o = a[i - 1];
        if(i != n - 1) o |= a[i];
        vector<int> d = get(b[i], o);
        for(int j = 0; j < pd.size(); j++) {
            if(dp[i - 1][j] == -1) continue;
            int pv = pd[j];
            for(int k = 0; k < d.size(); k++) {
                int v = d[k];
                if(v >= b[i] && (pv & v) == a[i - 1]) {
                    upd(dp[i][k], (v - b[i]) + dp[i - 1][j]);
                }
            }
        }
        //for(int x : d) cout << x << " ";
        //cout << endl;
        pd = d;
    }

    long long ans = INF;
    for(int i = 0; i < 33; i++) {
        if(dp[n - 1][i] != -1) {
            ans = min(ans, dp[n - 1][i]);
        }   
    }  

    if(ans == INF) cout << -1 << endl;
    else cout << ans << endl;
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
