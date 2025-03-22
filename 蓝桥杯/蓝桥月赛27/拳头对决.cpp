//https://www.lanqiao.cn/problems/20272/learning/?contest_id=250
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

const int FENWICK_SIZE = 4e5 + 100;
    struct Fenwick {
        int tree[FENWICK_SIZE];
        int sz;
        void init(int n) {
            sz = n;
            for(int i = 0; i <= n + 1; i++) tree[i] = 0;
        }

        void update(int i, int val) {
            i++;
            while(i < sz){
            tree[i] += val;
            i += (i & -i);
            }
        }

        int pre(int i) {
            int sum = 0;
            while(i > 0){
            sum += tree[i];
            i -= ( i & -i);
            }
            return sum;
        }
        int query(int i, int j) {
            return pre(j + 1) - pre(i);
        }
    } tr;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i]; //blue
    for(int i = 0; i < n; i++) cin >> b[i]; //red
    swap(a, b);

    vector<int> c;
    for(int i = 0; i < n; i++) {
        c.push_back(a[i]);
        c.push_back(b[i]);
    }
    sort(c.begin(), c.end());
    int id = 1;
    unordered_map<int, int> mp;
    for(int i = 0; i < c.size(); i++) {
        if(mp.find(c[i]) == mp.end()) {
            mp[c[i]] = id++;
        }
    }
    tr.init(id + 10);
    for(int i = 0; i < n; i++) {
        tr.update(mp[a[i]], 1);
    }

    sort(b.begin(), b.end());
    int j = n - 1;
    long long ans = 0;
    for(int i = n - 1; i >= 0; i--) {
        int val = mp[b[j]];
        ans += tr.query(0, val - 1);
        tr.update(mp[a[i]], -1);
        j--;
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
