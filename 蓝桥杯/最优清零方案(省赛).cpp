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

const int N = 1e6 + 100; 
struct Node {
    int l, r, add;
    long long val = 0;
} tr[N * 4];

void tag(int u, int val) {
    tr[u].add += val;
    tr[u].val += val;
}

void pushdown(int u) {
    if(tr[u].add && tr[u].l != tr[u].r) {
        tag(u * 2 + 1, tr[u].add);
        tag(u * 2 + 2, tr[u].add);
        tr[u].add = 0;
    }
}

void pushup(int u) {
    int left = u * 2 + 1, right = u * 2 + 2;
    tr[u].val = min(tr[left].val, tr[right].val);
}

void build(vector<int>& a, int u) {
    int l = tr[u].l, r = tr[u].r;
    if(l == r) {
        tr[u].val = a[l];
        return;
    }
    int mid = l + (r - l) / 2;
    int left = u * 2 + 1, right = u * 2 + 2;
    tr[left] = {l, mid, 0, 0};
    tr[right] = {mid + 1, r, 0, 0};
    build(a, left);
    build(a, right);
    pushup(u);
}


void update(int u, int s, int e, int val) {
    int l = tr[u].l, r = tr[u].r;
    if(l == s && r == e) {
        tag(u, val);
        return;
    }
    int left = u * 2 + 1, right = u * 2 + 2;
    int mid = l + (r - l) / 2; 
    pushdown(u);
    if(e <= mid) {
        update(left, s, e, val);
    } else if(s >= mid + 1) {
        update(right, s, e, val);
    } else {
        update(left, s, mid, val);
        update(right, mid + 1, e, val);
    }
    pushup(u);
}

long long query(int u, int s, int e) {
    int l = tr[u].l, r = tr[u].r;
    if(l == s && r == e) {
        return tr[u].val;
    }
    int left = u * 2 + 1, right = u * 2 + 2;
    int mid = l + (r - l) / 2;
    pushdown(u);
    if(e <= mid) {
        return query(left, s, e);
    } else if(s >= mid + 1) {
        return query(right, s, e);
    } else {
        return min(query(left, s, mid), query(right, mid + 1, e));
    }
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long ans = 0;
    tr[0] = {0, n - 1, 0, 0};
    build(a, 0);
    for(int i = 0; i < n; i++) {
        if(i + k - 1 < n) {
            int l = i, r = i + (k - 1);
            int mn = query(0, l, r);
            if(mn == 0) {
                ans += query(0, l, l);
            } else {
                ans += mn;
                update(0, l, r, -mn);
                i--;
            }
        } else {
            ans += query(0, i, i);
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
