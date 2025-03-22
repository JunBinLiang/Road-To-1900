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


const int N = 2e5 + 100, MOD = 998244353;
long long p[N];

long long modInverse(long long a, long long m) {
    long long m0 = m;
    long long y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
          // q is quotient
        long long q = a / m;
        long long t = m;
        // m is remainder now, process
        // same as Euclid's algo
        m = a % m;
        a = t;
        t = y;
        // Update x and y
        y = x - q * y;
        x = t;
    }
    // Make x positive
    if (x < 0)
        x += m0;
    return x;
}

struct Node {
    int l, r;
    int sz;
    int a = 0, b = 0;
    long long tota = 0, totb = 0;
    long long aa = 0, bb = 0;
    long long ab = 0;
    void reset() {
        a = 0; b = 0;
        tota = totb = aa = bb = ab = 0;
        sz = r - l + 1;
    }

} tr[N * 4];

void build(int u) {
    tr[u].reset();
    if(tr[u].l == tr[u].r) {
        return;
    }
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    int left = u * 2 + 1, right = u * 2 + 2;
    tr[left] = {l, mid};
    tr[right] = {mid + 1, r}; 
    build(left);
    build(right);
}

void pushup(int u) {
    if(tr[u].l == tr[u].r) return;
    int left = u * 2 + 1, right = u * 2 + 2;
    tr[u].a = (tr[left].a + tr[right].a) % MOD;
    tr[u].b = (tr[left].b + tr[right].b) % MOD;
    
    tr[u].tota = (tr[left].tota * p[tr[right].sz] + tr[right].tota * p[tr[left].sz]);
    tr[u].tota %= MOD;
    tr[u].totb = (tr[left].totb * p[tr[right].sz] + tr[right].totb * p[tr[left].sz]);
    tr[u].totb %= MOD;

    tr[u].ab = ((tr[left].ab * p[tr[right].sz]) + (tr[right].ab * p[tr[left].sz])) + (tr[left].tota * tr[right].totb) + (tr[left].totb * tr[right].tota);
    tr[u].ab %= MOD;


    tr[u].aa = ((tr[left].aa * p[tr[right].sz]) + (tr[right].aa * p[tr[left].sz]));
    tr[u].aa += (tr[left].tota * tr[right].tota * 2);
    tr[u].aa %= MOD;
   
    tr[u].bb = ((tr[left].bb * p[tr[right].sz]) + (tr[right].bb * p[tr[left].sz]));
    tr[u].bb += (tr[left].totb * tr[right].totb * 2);
    tr[u].bb %= MOD;

    
    //cout << "pushup " << tr[u].l << " " << tr[u].r << "  |" << tr[u].tota << "  " << tr[u].totb << "   |" << "   " << tr[u].aa << " " << tr[u].bb << " " << tr[u].ab << endl;
    //cout << "pushup " << tr[left].l << " " << tr[left].r << "  |" << tr[left].tota << "  " << tr[left].totb << "   |" << "   " << tr[left].aa << " " << tr[left].bb << " " << tr[left].ab << endl;
   // cout << "pushup " << tr[right].l << " " << tr[right].r << "  |" << tr[right].tota << "  " << tr[right].totb << "   |" << "   " << tr[right].aa << " " << tr[right].bb << " " << tr[right].ab << endl << endl;
}

void update(int u, int index, int val) {
    if(tr[u].l == tr[u].r) {
        tr[u].reset();
        if(val == 0) {
            tr[u].a = tr[u].tota = tr[u].aa = 1;
        } else {
            tr[u].b = tr[u].totb = tr[u].bb = 1;
        }
        return;
    }
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    if(index <= mid) {
        update(u * 2 + 1, index, val);
    } else {
        update(u * 2 + 2, index, val);
    }
    pushup(u);
}

void solve() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    p[0] = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = p[i - 1] * 2;
        p[i] %= MOD;
    }

    tr[0] = {0, n - 1};
    build(0);
    for(int i = 0; i < n; i++) {
        update(0, i, s[i] - '0');
        //cout << endl;
    }
    
    //cout << endl << endl;

    long long inv4 = modInverse(4, MOD);
    for(int i = 0; i < m; i++) {
        int j;
        cin >> j;
        j--;
        if(s[j] == '0') s[j] = '1';
        else s[j] = '0';
        update(0, j, s[j] - '0');
        long long ans = tr[0].aa + tr[0].bb - 2 * tr[0].ab;
        ans %= MOD;
        if(ans < 0) ans += MOD;
        int oddlen = p[n - 1];
        ans -= oddlen;
        if(ans < 0) ans += MOD;
        cout << (ans * inv4) % MOD << endl;
    }
}


int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
