https://www.lanqiao.cn/problems/2172/learning/?page=1&first_category_id=1&name=%E6%9C%80%E5%A4%A7%E5%85%AC%E7%BA%A6%E6%95%B0//
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

const int MAX = 200000 + 100;
struct Seg {
    struct Node {
        int l, r;
        int val;
    } tr[MAX * 4];

    void build(int id, vector<int>& a) {
        int l = tr[id].l, r = tr[id].r;
        if(l == r) {
            tr[id].val = a[l];
            return;
        }
        int mid = l + (r - l) / 2;
        tr[id * 2 + 1] = {l, mid};
        tr[id * 2 + 2] = {mid + 1, r};
        build(id * 2 + 1, a);
        build(id * 2 + 2, a);
        tr[id].val = __gcd(tr[id * 2 + 1].val, tr[id * 2 + 2].val);
    }

    int query(int id, int s, int e) {
        int l = tr[id].l, r = tr[id].r;
        if(l == s && r == e){
            return tr[id].val;
        }
        int mid = l + (r - l) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        if(e <= mid){
            return query(left, s, e);
        } else if(s >= mid + 1) {
            return query(right, s, e);
        } else {
            return __gcd(query(left, s, mid), query(right, mid + 1, e));
        }
    }
} seg;


bool ok(int n, int k) {
    for(int i = 0; i < n; i++) {
        if(i + k - 1 >= n) break;
        int g = seg.query(0, i, i + k - 1);
        if(g == 1) {
            return true;
        }
    }
    return false;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    
    int g = a[0];
    for(int i = 1; i < n; i++) g = __gcd(g, a[i]);

    if(g != 1) {
        cout << -1 << endl;
        return;
    }

    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] == 1) {
            cnt++;
        }
    }

    if(cnt) {
        cout << n - cnt << endl;
        return;
    }

    seg.tr[0] = {0, n - 1};
    seg.build(0, a);

    int l = 1, r = n;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(ok(n, mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << (n - 1) + (ans - 1) << endl;
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
