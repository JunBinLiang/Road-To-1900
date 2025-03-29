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

const int N = 5e4 + 10;
int a[N];

struct Node {
    int l, r;
    map<int, int> mp;
} tr[N * 4];

int id = 0;
int newnode(int l, int r) {
    int u = ++id;
    tr[u] = {l, r};
    return u;
}

void del(map<int, int>& mp, int k) {
    mp[k]--;
    if(mp[k] == 0) {
        mp.erase(k);
    }
}

void build(int u) {
    int l = tr[u].l, r = tr[u].r;
    if(l == r) {
        tr[u].mp[a[l]]++;
        return;
    }
    int mid = l + (r - l) / 2;
    int left = u * 2 + 1, right = u * 2 + 2;
    tr[left] = {l, mid};
    tr[right] = {mid + 1, r};
    build(left);
    build(right);
    for(int i = l; i <= r; i++) {
        tr[u].mp[a[i]]++;
    }
}

void update(int u, int index, int val) {
    int l = tr[u].l, r = tr[u].r;
    del(tr[u].mp, a[index]);
    if(l == r ){
        a[index] = val;
        tr[u].mp[a[index]]++;
        return;
    }
    int mid = l + (r - l) / 2;
    if(index <= mid) {
        update(u * 2 + 1, index, val);
    } else {
        update(u * 2 + 2, index, val);
    }
    tr[u].mp[a[index]]++;
}

int get(map<int, int>& mp, int k) {
    auto it = mp.upper_bound(k - 1);
    if(it != mp.begin()) {
        it--;
        return it -> first;
    }
    return -1;
}

int merge(int a, int b) {
    if(a == -1) return b;
    if(b == -1) return a;
    return max(a, b);
}

int query(int u, int s, int e, int k) {
    int l = tr[u].l, r = tr[u].r;
    if(l == s && r == e) {
        return get(tr[u].mp, k);
    }
    int mid = l + (r - l) / 2;
    if(e <= mid) return query(u * 2 + 1, s, e, k);
    else if(s >= mid + 1) return query(u * 2 + 2, s, e, k);
    else {
        return merge(query(u * 2 + 1, s, mid, k), query(u * 2 + 2, mid + 1, e, k));
    }
}


void solve() {
    int n, m;
    cin >> n >> m;

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    tr[0] = {1, n};
    build(0);

    for(int i = 0; i < m; i++) {
        int op; cin >> op;
        if(op == 1) {
            int pos, val;
            cin >> pos >> val;
            update(0, pos, val);
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            int ans = query(0, l, r, k);
            cout << ans << endl;
        }
    }
    
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
