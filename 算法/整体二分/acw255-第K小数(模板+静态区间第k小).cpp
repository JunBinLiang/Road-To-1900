#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string.h>
#include <random>
#include <chrono>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)

const int N = 2e5 + 10;
int n, m;
int a[N], ans[N];
vector<pair<int, int>> b; 
int bi = 0;
struct Query {
    int l, r, k, i;
} q[N], q1[N], q2[N];

//整体二分，对多个query 同时进行二分
//每个query 最多会被分割在O(log n)个range 里
//Fenwick Tree
const int FENWICK_SIZE = 200000 + 100;
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


void dfs(long long l, long long r, int L, int R) { //L R specify the range of q[] so we can use 1 array only
    if(l == r) {
        for(int i = L; i <= R; i++) {
            ans[q[i].i] = l;
        }
        return;
    }

    long long mid = l + (r - l) / 2;
    /*
    这样会引起超时。
    vector<int> p(n + 1); //prefix sum
    for(int i = 1; i <= n; i++) {
        if(a[i] <= mid) {
            p[i] = 1;
        }
        p[i] += p[i - 1];
    }*/
    

    /*
    这里的总体移动是n log n次，每次fenwick update => 参考divide conquer 的tree高度
    */
    while(bi < b.size() && b[bi].first <= mid) {
        tr.update(b[bi].second, 1);
        bi++;
    }
    while(bi - 1 >= 0 && b[bi - 1].first > mid) {
        tr.update(b[bi - 1].second, -1);
        bi--;
    }

    int t1 = 0, t2 = 0;
    for(int i = L; i <= R; i++) {
        int cnt = tr.query(q[i].l, q[i].r);
        if(q[i].k <= cnt) {
            q1[t1++] = q[i];
        } else {
            q2[t2++] = q[i];
        }
    }
    for(int i = 0; i < t1; i++) {
        q[i] = q1[i];
    }
    for(int i = 0; i < t2; i++) {
        q[i + t1] = q2[i];
    }
    
    if(t1 > 0)
      dfs(l, mid, 0, t1 - 1);
    if(t2 > 0)
      dfs(mid + 1, r, t1, t1 + t2 - 1);
}

void solve() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        b.push_back({a[i], i});
    }

    for(int i = 0; i < m; i++) {
        cin >> q[i].l >> q[i].r >> q[i].k;
        q[i].i = i;
    }

    tr.init(200000 + 50);
    sort(b.begin(), b.end());
    dfs(-1000000000, 1000000000, 0, m - 1);

    for(int i = 0; i < m; i++) {
        cout << ans[i] << endl;
    }
}

int main(){
    int t = 1;
    //cin >> t;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    while(t--) {
        solve();
    }
    return 0;
}
