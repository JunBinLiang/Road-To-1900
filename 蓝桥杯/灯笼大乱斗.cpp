//https://www.lanqiao.cn/problems/20255/learning/?contest_id=241
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

const int N = 1e5 + 100;
const int INF = 2e9 + 100;
struct MaxSeg {
    struct Node {
        int l, r;
        int mx;
        map<int, int> mp;
    } tr[N * 4];

    void build(int id) {
        int l = tr[id].l, r = tr[id].r;
        if(l == r) {
            tr[id].mp[-INF]++;
            return;
        }
        int mid = l + (r - l) / 2;
        tr[id * 2 + 1] = {l, mid, -INF};
        tr[id * 2 + 2] = {mid + 1, r, -INF};
        build(id * 2 + 1);
        build(id * 2 + 2);
    }

    void update(int id, int index, int val, int op) { 
        int l = tr[id].l, r = tr[id].r;
        if(l == r) {
            if(op == 0) tr[id].mp[val]++;
            else {
              tr[id].mp[val]--;
              if(tr[id].mp[val] == 0) tr[id].mp.erase(val);
            }
            auto it = tr[id].mp.end();
            it--;
            tr[id].mx = it -> first;
            return;
        }
        int mid = l + (r - l) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        if(index <= mid) {
            update(left, index, val, op);
        } else {
            update(right, index, val, op);
        }
        tr[id].mx = max(tr[left].mx, tr[right].mx);
    }

    int query(int id, int s, int e) {
        int l = tr[id].l, r = tr[id].r;
        if(l == s && r == e){
            return tr[id].mx;
        }
        int mid = l + (r - l) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        if(e <= mid){
            return query(left, s, e);
        } else if(s >= mid + 1) {
            return query(right, s, e);
        } else {
            return max(query(left, s, mid), query(right, mid + 1, e));
        }
    }
} maxseg1, maxseg2;

int id = 1;
map<int, int> mp;
void solve() {
  int n;
  cin >> n;
  vector<int> a(n), b(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for(int i = 0; i < n; i++) {
    cin >> b[i];
  }

  vector<int> c(b.begin(), b.end());
  sort(c.begin(), c.end());
  for(int x : c) {
    if(mp.find(x) == mp.end()) {
      mp[x] = id++;
    }
  }

  long long ans = 0;
  maxseg1.tr[0] = {0, id + 2, -INF};
  maxseg1.build(0);
  maxseg2.tr[0] = {0, id + 2, -INF};
  maxseg2.build(0);

  for(int i = 0, j = 0; i < n; i++) {
    int x = a[i] - b[i]; //change
    int y = a[i] + b[i]; //no change
    int index = mp[b[i]];
    while(true) {
      if(maxseg1.query(0, 0, index) >= x) { //change
        int cur = maxseg1.query(0, 0, index); 
        while(j < i) {
          int xx = a[j] - b[j];
          int yy = a[j] + b[j];
          int ind = mp[b[j]];
          maxseg1.update(0, ind, xx, 1);
          maxseg2.update(0, ind, yy, 1);
          j++;
          if(xx == cur) break;
        }
        continue;
      }

      if(maxseg2.query(0, index + 1, id + 1) >= y ) { //change
        int cur = maxseg2.query(0, index + 1, id + 1); 
        while(j < i) {
          int xx = a[j] - b[j];
          int yy = a[j] + b[j];
          int ind = mp[b[j]];
          maxseg1.update(0, ind, xx, 1);
          maxseg2.update(0, ind, yy, 1);
          j++;
          if(yy == cur) break;
        }
        continue;
      }
      break;
    }
    maxseg1.update(0, index, x, 0);
    maxseg2.update(0, index, y, 0);
    ans += (i - j);
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
