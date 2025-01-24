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

const int N = 5000 + 50;
int dp[N][N];
int pre[N];
int n, m;

int dfs(vector<pair<int, int>>& a, int i, int zero) {
    if(i >= a.size()) {
        return 0;
    }
    if(dp[i][zero] != -1) return dp[i][zero];
    
    int ans = 0;
    pair<int, int> p = a[i];
    int s = (i > 0 ? pre[i - 1] : 0);
    int one = s - zero;
    if(p.first == -1) { //any
        //0
        int w0 = s;
        ans = max(ans, w0 + dfs(a, i + 1, zero + 1));
        //1
        int w1 = one;
        ans = max(ans, w1 + dfs(a, i + 1, zero));

    } else if(p.first == 0) {
        int w0 = s;
        ans = max(ans, w0 + dfs(a, i + 1, zero + 1));
    } else if(p.second == 1) {
        int w1 = one;
        ans = max(ans, w1 + dfs(a, i + 1, zero));
    } else {
        int len = a[i].second;
        for(int x = 1; x < len; x++) { //add x zero   y one
            int y = len - x;
            int w = (x) * (x - 1) / 2 + (y) * (y - 1) / 2;
            w += (len * one);
            w += (zero * x);
            ans = max(ans, w + dfs(a, i + 1, zero + x));
        }
    }
    return dp[i][zero] = ans;
}

bool upd(vector<int>& a, int l, int r, int val) {
    for(int i = l; i <= r; i++) {
        if(a[i] != -1 && a[i] != val) return false;
        a[i] = val;
    }
    return true;
}

void solve() {
    cin >> n >> m;
    set<pair<int, int>> s;
    vector<int> b(n + 1, -1);
    for(int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        s.insert({l, r});
    }

    if(m == 0) {
        cout << (n * (n - 1)) / 2 << endl;
        return;
    }

    //reset dp
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            dp[i][j] = -1;
        }
    }
    
    vector<pair<int, int>> a (s.begin(), s.end()); //filter
    vector<pair<int, int>> vec; //filter
    for(int i = 0; i < a.size(); i++) {
        int l = a[i].first, r = a[i].second;
        int j = i + 1;
        while(j < a.size() && a[j].first <= r) {
            bool ok1 = upd(b, l, a[j].first - 1, 0);
            bool ok2 = upd(b, min(r, a[j].second) + 1, max(r, a[j].second), 1);
            if(!ok1 || !ok2) {
                cout << -1 << endl;
                return;
            }
            l = a[j].first;
            r = min(r, a[j].second);
            j++;
        }
        if(r - l + 1 < 2) {
            cout << -1 << endl;
            return;
        } else {
            if(b[l] == 1) {
                cout << -1 << endl;
                return;
            }
            vec.push_back({l, r});
        }
        i = j - 1;
    }
    
    //for(auto& p : vec) cout << p.first << " " << p.second << endl;
    //cout << endl;

    a.clear();
    if(vec[0].first > 1) {
        for(int i = 1; i < vec[0].first; i++) {
            a.push_back({b[i], 1});
        }
    }
    a.push_back({2, vec[0].second - vec[0].first + 1});
    for(int i = 1; i < vec.size(); i++) {
        for(int j = vec[i - 1].second + 1; j < vec[i].first; j++) {
            a.push_back({b[j], 1});
        }
        a.push_back({2, vec[i].second - vec[i].first + 1});
    }

    if(vec.back().second < n) {
        for(int i = vec.back().second + 1; i <= n; i++) {
            a.push_back({b[i], 1});
        }
    }

    for(int i = 0; i < a.size(); i++) {
        pre[i] = a[i].second;
        if(i) pre[i] += pre[i - 1];
    }
    
    //for(auto& p : a) cout << p.first << " " << p.second << endl;
    //cout << endl;
    
    int ans = dfs(a, 0, 0);
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
