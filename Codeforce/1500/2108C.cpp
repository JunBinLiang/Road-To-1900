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
    vector<int> a(n);
    map<int, vector<int>> mp;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]].push_back(i);
    }

    auto it = mp.end();
    it--;
    int ans = 0;
    vector<bool> vis(n + 1);
    while(true) {
        vector<int>& vec = it -> second;
        for(int i = 0; i < vec.size(); i++) {
            int j = i + 1;
            while(j < vec.size() && vec[j] == vec[j - 1] + 1) {
                j++;
            }
            int l = vec[i], r = vec[j - 1];
            i = j - 1;
            bool ok = false;
            if(l > 0 && a[l - 1] > a[l]) ok = true;
            if(r + 1 < n && a[r + 1] > a[l]) ok = true;
            if(!ok) ans++;
        }

        if(it == mp.begin()) {
            break;
        }
        it--;
    }
    cout << ans << endl;
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
