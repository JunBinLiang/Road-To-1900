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


void solve() {
    int n;
    cin >> n;
    vector<long long> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = a[i] - 1 + i;
    }

    vector<pair<long long, long long>> b;
    for(int i = 1; i <= n; i++) {
        b.push_back({a[i], i - 1});
    }

    sort(b.begin(), b.end());
    vector<bool> dp(n);
    set<long long> s;
    s.insert(n);

    for(int i = 0; i < b.size(); i++) {
        if(s.find(b[i].first) != s.end()) {
            s.insert(b[i].first + b[i].second);
        }
    }

    auto it = s.end(); it--;
    cout << *it << endl;
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
