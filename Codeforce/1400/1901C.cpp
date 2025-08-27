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

//12:11 - 12:21

bool same(vector<int>& a) {
    sort(a.begin(), a.end());
    return a[0] == a.back();
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    vector<int> ans;
    while(!same(a)) {
        if(a.back() % 2 == 1) {
            ans.push_back(0);
            for(int& x : a) x /= 2;
        } else {
            ans.push_back(1);
            for(int& x : a) {
                x = (x + 1) / 2;
            }
        }
    }
    
    cout << ans.size() << endl;
    if(ans.size() <= n && ans.size() > 0) {
        for(int x : ans) cout << x << " ";
        cout << endl;
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
