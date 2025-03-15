//https://www.lanqiao.cn/problems/17120/learning/?page=1&first_category_id=1&name=%E9%80%89%E6%AE%B5%E6%8E%92%E5%BA%8F
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

void add(map<int, int>& mp, int k) {
    mp[k]++;
}
void del(map<int, int>& mp, int k) {
    mp[k]--;
    if(mp[k] == 0) mp.erase(k);
}

int first(map<int, int>& mp) {
    auto it = mp.begin();
    return it -> first;
}

int last(map<int, int>& mp) {
    auto it = mp.end();
    it--;
    return it -> first;
}

void solve() {
    int n, p, q;
    cin >> n >> p >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    } 

    if(p == q) {
        cout << 0 << endl;
        return;
    }

    if(n == 2) {
        sort(a.begin(), a.end());
        cout << a[1] - a[0] << endl;
        return;
    }

    const int INF = 1e9;
    int ans = INF;
    map<int, int> mp1, mp2;
    for(int i = p; i <= q; i++) {
        mp1[a[i]]++;
        mp2[a[i]]++;
    }

    ans = min(ans, last(mp1) - first(mp1));
    
    //cout << mp1 << endl;
    //cout << mp2 << endl;
    
    //remove max + add
    for(int i = q + 1; i <= n; i++) {
        if(a[i] > last(mp1)) continue;
        int mx = last(mp1);
        del(mp1, mx);
        mp1[a[i]]++;
        ans = max(ans, last(mp1) - first(mp1));
    }

    //remove min + add
    for(int i = p - 1; i >= 0; i--) {
        if(a[i] < first(mp2)) continue;
        int mn = first(mp2);
        del(mp2, mn);
        mp2[a[i]]++;
        ans = max(ans, last(mp2) - first(mp2));
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
