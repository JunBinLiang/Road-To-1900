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

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

void del(map<int, int>& mp, int k, int& sz) {
    sz--;
    mp[k]--;
    if(mp[k] == 0) {
        mp.erase(k);
    }
}

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    vector<int> ans;
    map<int, int> mp;
    int sz = 0;
    for(int i = 0; i < n; i++) {
        int l = a[i].first, r = a[i].second;
        if(i == 0) {
            mp[l]++;
            sz++;
            ans.push_back(1);
            continue;
        }
        //cout << mp << "  " << sz << endl;
        auto it = mp.upper_bound(l);
        if(it != mp.end()) {
            int old = it -> first;
            mp[l]++;
            sz++;

            it = mp.upper_bound(r);
            if(it != mp.end()) {
                del(mp, it -> first, sz);
            } else {

            }
        } else {
            mp[l]++;
            sz++;
        }
        //cout << mp << "  " << sz << endl << endl;

        ans.push_back(sz);
    }

    for(int x : ans) {
        cout << x << " ";
    }
    cout << endl;
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
