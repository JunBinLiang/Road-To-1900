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

const int N = 1e5 + 10;
struct Node {
    int l, r;
    int to[26];
    void init() {
        for(int i = 0; i < 26; i++) to[i] = i;
    }
} tr[N * 4];

string s;

void build(int u) {
    tr[u].init();
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    if(l == r) {
        return;
    }
    
    int left = u * 2 + 1, right = u * 2 + 2;
    tr[left] = {l, mid};
    tr[right] = {mid + 1, r};
    build(left);
    build(right);
}

void pushdown(int u) {
    if(tr[u].l == tr[u].r) {
        return;
    }
    int left = u * 2 + 1, right = u * 2 + 2;
    for(int i = 0; i < 26; i++) {
        int c = tr[left].to[i];
        tr[left].to[i] = tr[u].to[c];
    }

    for(int i = 0; i < 26; i++) {
        int c = tr[right].to[i];
        tr[right].to[i] = tr[u].to[c];
    }

    //clear tag
    for(int i = 0; i < 26; i++) {
        tr[u].to[i] = i;
    }
}

void tag(int u, int c1, int c2) {
    for(int i = 0; i < 26; i++) {
        if(tr[u].to[i] == c1) {
            tr[u].to[i] = c2;
        }
    }
}

void update(int u, int s, int e, int c1, int c2) {
    int l = tr[u].l, r = tr[u].r;
    if(l == s && r == e) {
        tag(u, c1, c2);
        return;
    }
    pushdown(u);
    int mid = l + (r - l) / 2;
    int left = u * 2 + 1, right = u * 2 + 2;
    if(e <= mid) {
        update(left, s, e, c1, c2);
    } else if(s >= mid + 1) {
        update(right, s, e, c1, c2);
    } else {
        update(left, s, mid, c1, c2);
        update(right, mid + 1, e, c1, c2);
    }
}

void dfs(string& ans, int u) {
    int left = u * 2 + 1, right = u * 2 + 2;
    if(tr[u].l == tr[u].r) {
        int c = s[tr[u].l] - 'a';
        ans += (char)(tr[u].to[c] + 'a');
        return;
    }
    pushdown(u);
    dfs(ans, left);
    dfs(ans, right);
}

void solve() {
    cin >> s;
    int m;
    cin >> m;
    int n = s.size();

    tr[0] = {0, n - 1};
    build(0);

    while(m--) {
        int l, r;
        char c1, c2;
        cin >> l >> r >> c1 >> c2;
        int d1 = c1 - 'a', d2 = c2 - 'a';
        l--; r--;
        update(0, l, r, d1, d2);
    }
    string ans = "";
    dfs(ans, 0);
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
