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
    vector<string> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long ans = 0;
    vector<map<pair<int, int>, int>> b(6);
    for(int i = 0; i < n; i++) {
        string& s = a[i];
        int ls = 0, rs = 0;
        for(int j = 0; j < s.size(); j++) rs += (s[j] - '0');
        b[s.size()][{0, -rs}]++;
        for(int j = 0; j < s.size(); j++) {
            rs -= (s[j] - '0');
            ls += (s[j] - '0');
            b[s.size()][{j + 1, ls - rs}]++;
        }
    }

    for(int i = 0; i < n; i++) {
        string& s = a[i];
        int sz = s.size();
        int sum = 0;
        for(int j = 0; j < s.size(); j++) sum += (s[j] - '0');
        for(int j = 1; j <= 5; j++) {
            if((sz + j) % 2 != 0) continue;
            int tot = sz + j;
            int h = tot / 2;
            
            auto& mp = b[j];
            if(sz <= h) {
                if(mp.find({h - sz, -sum}) != mp.end()) {
                    ans += mp[{h - sz, -sum}];
                }
            } else {
                int halfs = 0;
                for(int k = 0; k < h; k++) halfs += (s[k] - '0');
                if(mp.find({0, (sum - halfs) - halfs}) != mp.end()) {
                    ans += mp[{0, (sum - halfs) - halfs}];
                }
            }
        }
    }

    cout << ans << endl;
}


int main() {
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
