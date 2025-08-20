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

const int N = 1e5 + 10;
vector<int> d[N];

void init() {
    for(int i = 2; i < N; i++) {
        for(int j = i; j < N; j += i) {
            d[j].push_back(i);
        }
    }
}

int find(vector<int>& vec, int L) {
    int l = 0, r = vec.size() - 1;
    int p = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(vec[mid] >= L) {
            p = vec[mid];
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    } 
    return p;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    unordered_map<int, vector<int>> mp;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        mp[a[i]].push_back(i);
    }

    for(int i = 0; i < m; i++) { //50000
        int k, l, r;
        cin >> k >> l >> r;
        long long ans = 0;
        int j = l;
        while(true) {
            int mn = -1;
            int t = -1;
            for(int div : d[k]) {
                if(mp.find(div) == mp.end()) continue;
                int pos = find(mp[div], j);
                if(pos != -1 && pos <= r) { 
                    if(mn == -1) {
                        mn = pos;
                        t = div;
                    }
                    else if(pos < mn) {
                        mn = pos;
                        t = div;
                    }
                }
            }
            if(mn == -1) {
                ans += (r - j + 1ll) * k;
                break;
            } else {
                ans += ((k + 0ll) * (mn - j));
                while(k % t == 0) k /= t;
                ans += k;
                j = mn + 1;
            }
        }
        cout << ans << endl;
    }
}


int main() {
    init();
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
