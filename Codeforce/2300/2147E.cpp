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

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

int cal(vector<int>& a) {
    int cnt = 0;
    for(int i = 0; i < a.size(); i++) {
        if(a[i] > 0) {
            cnt++;
        }
    }
    return cnt;
}

int bitcount(int n) {
    int ans = 0;
    for(int i = 0; i < 31; i++) {
        if(n & (1 << i)) {
            ans++;
        }
    }
    return ans;
}

const int N = 1e5 + 10;
int temp[N];

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int o = 0;
    for(int x : a) {
        o |= x;
    }

    
    /*vector<int> cnt(32);
    for(int x : a) {
        for(int i = 0; i < 31; i++) {
            if(x & (1 << i)) {
                cnt[i]++;
            }
        }
    }*/

    long long cost = 0;
    int cur = 0;
    vector<pair<long long, int>> b;
    b.push_back({0, bitcount(o)});
    for(int i = 0; i < 31; i++) {
        for(int j = i; j >= 0; j--) {
            int off = (1 << j) - 1;
            bool ok = false;
            for(int k = 0; k < n; k++) {
                if(a[k] & (1 << j)) {
                    ok = true;
                    break;
                }
            }
            if(ok) continue;
            int mncost = 2e9 + 10, idx = -1;
            int target = (1 << j);
            for(int k = 0; k < n; k++) {
                int x = a[k] & off;
                int cost = (target - x);
                if(cost < mncost) {
                    mncost = cost;
                    idx = k;
                }
            }
            cost += mncost;
            int old = a[idx];
            for(int k = 0; k < j; k++) {
                if(a[idx] & (1 << k)) a[idx] ^= (1 << k);
            }
            a[idx] += target; 
        }
        int oo = 0;
        for(int x : a) oo |= x;
        b.push_back({cost, bitcount(oo)});
    }
    
    //for(auto p : b) cout << p.first << "  " << p.second << endl;
    for(int i = 0; i < m; i++) {
        int k; cin >> k;
        int ans = 0;
        for(int j = 0; j < b.size(); j++) {
            if(k >= b[j].first) {
                ans = max(ans, b[j].second);
            }
        }
        cout << ans << endl;
    }
}

int main()
{
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}


