#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string.h>
#include <random>
#include <chrono>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)

//3:24 - 3:40

int find(vector<int>& a, int cur) {
    int l = 0, r = a.size() - 1;
    int p = 1000000;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(a[mid] >= cur) {
            p = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return p;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> p1, p2;
    for(int i = 0; i < n; i++) {
        if(a[i] == 1) {
            p1.push_back(i);
        } else {
            p2.push_back(i);
        }
    }

    vector<pair<int, int>> ans;
    for(int t = 1; t <= n; t++) {
        int cur = 0;
        int s1 = 0, s2 = 0;
        bool ok = true;
        vector<int> win;
        while(cur < n) {
            int po1 = find(p1, cur);
            int po2 = find(p2, cur);
            if(po1 + t - 1 < p1.size() && po2 + t - 1 < p2.size()) {
                if(p1[po1 + t - 1] < p2[po2 + t - 1]) {
                    s1++;
                    win.push_back(1);
                } else {
                    win.push_back(2);
                    s2++;
                }
                cur = min(p1[po1 + t - 1], p2[po2 + t - 1]) + 1;
            } else if(po1 + t - 1 < p1.size()) {
                cur = p1[po1 + t - 1] + 1;
                s1++;
                win.push_back(1);
            } else if(po2 + t - 1 < p2.size()) {
                cur = p2[po2 + t - 1] + 1;
                s2++;
                win.push_back(2);
            } else {
                ok = false;
                break;
            }
        }
        if(ok && (s1 != s2)) {
            if(s1 > s2 && win.back() == 1) {
                ans.push_back({max(s1, s2), t});
            } else if(s2 > s1 && win.back() == 2) {
                ans.push_back({max(s1, s2), t});
            }
        }
    }

    //s t
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for(auto p : ans) {
        cout << p.first << " " << p.second << endl;
    }
}

int main(){
    int t = 1;
    //cin >> t;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    while(t--) {
        solve();
    }
    return 0;
}
