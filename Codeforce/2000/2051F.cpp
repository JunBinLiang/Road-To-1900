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

vector<pair<int, int>> merge(vector<pair<int, int>>& a) {
    sort(a.begin(), a.end());
    vector<pair<int, int>> b;
    for(auto& p : a) {
        if(b.size() == 0) b.push_back(p);
        else {
            if(p.first > b.back().second) {
                b.push_back(p);
            } else {
                b.back().second = max(b.back().second, p.second);
            }
        }
    }
    return b;
}

void solve() {
    int n, k, m;
    cin >> n >> k >> m;
    vector<pair<int, int>> a;
    a.push_back({k, k});
    while(m--) {
        int x;
        cin >> x;
        int sz = a.size();
        vector<pair<int, int>> b;
        for(int i = 0; i < sz; i++) {
            int l = a[i].first, r = a[i].second;
            if(x < l) {
                b.push_back({l - 1, r});
            } else if(x > r) {
               b.push_back({l, r + 1});
            } else {
                b.push_back({1, 1});
                b.push_back({n, n});
                if(l != r) {
                    b.push_back({l, r});
                }
            }
        }

        a = merge(b);
        //for(auto p : b) cout << p.first << "  " << p.second << endl;
        //cout << endl;
        int ans = 0;
        for(auto& [L, R] : a) {
            ans += (R - L + 1);
        }
        cout << ans << " ";
    }
    cout << endl;
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
