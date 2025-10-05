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

const int N = 3e5 + 10;
int a[N];

struct Node {
    int l, r, mx;
    int add;
} tr[N * 4];

void build(int u) {
    int l = tr[u].l, r = tr[u].r;
    if(l == r) {
        return;
    }
    int mid = l + (r - l) / 2;
    int left = u * 2 + 1, right = u * 2 + 2;
    tr[left] = {l, mid, 0, 0};
    tr[right] = {mid + 1, r, 0, 0};
    build(left);
    build(right);
}

void pushdown(int u) {
    if(tr[u].l == tr[u].r) {
        return;
    }
    if(tr[u].add) {
        int left = u * 2 + 1, right = u * 2 + 2;
        tr[left].add += tr[u].add;
        tr[left].mx += tr[u].add;
        tr[right].add += tr[u].add;
        tr[right].mx += tr[u].add;
        tr[u].add = 0;
    }
}

void pushup(int u) {
    int left = u * 2 + 1, right = u * 2 + 2;
    tr[u].mx = max(tr[left].mx, tr[right].mx);
}

void update(int u, int s, int e, int add) {
    int l = tr[u].l, r = tr[u].r, mid = l + (r - l) / 2; 
    //cout << "update " << l << " " << r << "  " << s << "  " << e << "   " << add << endl;
    if(s == l && e == r) {
        tr[u].add += add;
        tr[u].mx += add;
        return;
    }
    pushdown(u);
    int left = u * 2 + 1, right = u * 2 + 2; 
    if(e <= mid) {
        update(left, s, e, add);
    } else if(s >= mid + 1) {
        update(right, s, e, add);
    } else {
        update(left, s, mid, add);
        update(right, mid + 1, e, add);
    }
    pushup(u);
}

int query(int u, int s, int e) {
    int l = tr[u].l, r = tr[u].r, mid = l + (r - l) / 2; 
    if(l == s && r == e) {
        return tr[u].mx;
    } 
    pushdown(u);
    int left = u * 2 + 1, right = u * 2 + 2;
    if(e <= mid) {
        return query(left, s, e);
    } else if(s >= mid + 1) {
        return query(right, s, e);
    } else {
        return max(query(left, s, mid), query(right, mid + 1, e));
    }
}

void solve() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    tr[0] = {0, n + 3, 0, 0};
    build(0);
    

    for(int i = 0; i < n; i++) {
        int x = a[i];
        int v = query(0, x, x);
        update(0, x, x, -v);
        if(x != 0 )
            update(0, 0, x - 1, 1);
        cout << tr[0].mx << " ";
        
        //for(int j = 0; j <= 5; j++) cout << query(0, j, j) << " ";
        //cout << endl;
        
    }
    cout << endl;
    
    //for(int i = 0; i <= 5; i++) cout << query(0, i, i) << " ";
   // cout << endl;
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


