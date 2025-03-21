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


const int MOD = 1e9 + 7;
const int N = 1e5 + 100;
struct Mat {
    int n, m;
    int a[2][2];
    void init(int x, int y) {
        n = x; m = y;
        //a = vector<vector<int>>(n, vector<int>(m));
        //memset(a, 0, sizeof a);
    }

    Mat operator+(const Mat& other) {
        Mat ans = {n, m};
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                ans.a[i][j] = a[i][j] + other.a[i][j];
                ans.a[i][j] %= MOD;
            }
        }
        return ans;
    }

    Mat operator*(const Mat& other) { // n * n in generally 
        Mat ans = {n, m};
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                long long sum = 0;
                for(int k = 0; k < m; k++) {
                    sum += (a[i][k] + 0ll) * other.a[k][j];
                    sum %= MOD;
                }
                ans.a[i][j] = sum;
            }
        } 

        return ans;
    }
};

struct Node {
    int l, r;
    long long add;
    Mat mat;
} tr[N * 4];


Mat base[52];
void init() {
    base[0].a[0][0] = 0;
    base[0].a[0][1] = 1;
    base[0].a[1][0] = 1;
    base[0].a[1][1] = 1;
    base[0].init(2, 2);
    for(int i = 1; i <= 50; i++) {
        base[i] = base[i - 1] * base[i - 1];
        base[i].init(2, 2);
    }
}


void tag(int u, long long add) {
    if(add == 0) return;
    tr[u].add += add;
    //reset base
    int j = 0;
    while(add) {
        if (add & 1) {
            tr[u].mat = tr[u].mat * base[j];
        }
        j++;
        add >>= 1;
    }
}

void pushdown(int u) {
    if(tr[u].add != 0 && tr[u].l != tr[u].r) {
        tag(u * 2 + 1, tr[u].add);
        tag(u * 2 + 2, tr[u].add);
        tr[u].add = 0;
    }
}

void pushup(int u) {
    if(tr[u].l != tr[u].r) {
        int left = u * 2 + 1, right = u * 2 + 2;
        tr[u].mat = tr[left].mat + tr[right].mat;
    }
}

void build(int u) {
    int l = tr[u].l, r = tr[u].r;
    if(l == r) {
        tr[u].mat.init(1, 2);
        auto& a = tr[u].mat.a;
        a[0][0] = a[0][1] = 1;
        return;
    }
    int left = u * 2 + 1, right = u * 2 + 2;
    int mid = l + (r - l) / 2;
    tr[left] = {l, mid};
    tr[right] = {mid + 1, r};
    build(left);
    build(right);
    pushup(u);
}

void update(int u, int s, int e, int val) {
    int l = tr[u].l, r = tr[u].r;
    if(l == s && r == e) {
        tag(u, val);
        return;
    }
    pushdown(u);
    int left = u * 2 + 1, right = u * 2 + 2;
    int mid = l + (r - l) / 2;
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

Mat query(int u, int s, int e) {
    int l = tr[u].l, r = tr[u].r;
    if(l == s && r == e) {
        return tr[u].mat;
    }
    pushdown(u);
    int left = u * 2 + 1, right = u * 2 + 2;
    int mid = l + (r - l) / 2;
    if(e <= mid) {
        return query(left, s, e);
    } else if(s >= mid + 1) {
        return query(right, s, e);
    } else {
        return query(left, s, mid) + query(right, mid + 1, e);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
  
    tr[0] = {0, n - 1};
    build(0);

    for(int i = 0; i < n; i++) {
        update(0, i, i, a[i] - 1);
    } 
    
    for(int i = 0; i < m; i++) {
        int op; cin >> op;
        if(op == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            l--; r--;
            update(0, l, r, x);
        } else {
            int l, r;
            cin >> l >> r;
            l--; r--;
            Mat mat = query(0, l, r);
            cout << mat.a[0][0] << endl;
        }
    }
}


int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  //cin >> t;
  init();
  while(t--) {
    solve();
  }
  return 0;
}
