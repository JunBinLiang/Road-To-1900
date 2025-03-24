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

map<int, int> lmp, rmp;
long long lsum = 0, rsum = 0;
int lsz = 0, rsz = 0;

void del(map<int, int>& mp, int k, int& sz, long long& sum) {
    mp[k]--;
    if(mp[k] == 0) {
        mp.erase(k);
    }
    sum -= k;
    sz--;
}

void add(map<int, int>& mp, int k, int& sz, long long& sum) {
    mp[k]++;
    sum += k;
    sz++;
}

void adjust() {
    while(lsz > rsz + 1) {
        auto it = lmp.end();
        it--;
        int k = it -> first;
        del(lmp, k, lsz, lsum);
        add(rmp, k, rsz, rsum);
    }
    while(lsz < rsz + 1) {
        auto it = rmp.begin();
        int k = it -> first;
        del(rmp, k, rsz, rsum);
        add(lmp, k, lsz, lsum);
    }
}

void add(int k) {
    if(lsz == 0) {
        add(lmp, k, lsz, lsum);
    } else {
        auto it = lmp.end();
        it--;
        if(k <= it -> first) {
            add(lmp, k, lsz, lsum);
        } else {
            add(rmp, k, rsz, rsum);
        }
    }
    adjust();
}

void del(int k) {
    if(lmp.find(k) != lmp.end()) {
        del(lmp, k, lsz, lsum);
    } else {
        del(rmp, k, rsz, rsum);
    }
    adjust();
}

bool ok(int j, int i, long long m) {
    int mid = 0;
    if(lsz > rsz) {
        auto it = lmp.end(); it--;
        mid = it -> first;
    } else {
        auto it = rmp.begin();
        mid = it -> first;
    }

    long long tot = ((mid + 0ll) * lsz - lsum) + (rsum - (mid + 0ll) * rsz);
    return tot <= m;
}


void solve() {
    int n; long long m;
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long ans = 0;
    for(int i = 0, j = 0; i < n; i++) {
        add(a[i]);
        while(!ok(j, i, m)) {
            del(a[j]);
            j++;
        }
        ans += (i - j + 1);
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
