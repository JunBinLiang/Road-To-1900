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

const int N = 4e5 + 100;

struct T {
    int fax, fay, w;
};

struct Node {
    int l, r;
} tr[4 * N];

vector<pair<int, int>> q[2][4 * N];
vector<T> stks[2][4 * N];
int ans[N];
int cnt[2];
int n, m;

void build(int u) {
    int l = tr[u].l, r = tr[u].r;
    if(l == r) {
        return;
    }
    int left = u * 2 + 1, right = u * 2 + 2;
    int mid = l + (r - l) / 2;
    tr[left] = {l, mid};
    tr[right] = {mid + 1, r};
    build(left);
    build(right);
}

void update(int u, int s, int e, int op, pair<int, int>& p) {
    int l = tr[u].l, r = tr[u].r;
    if(l == s && r == e) {
        q[op][u].push_back(p);
        return;
    }
    int mid = l + (r - l) / 2;
    int left = u * 2 + 1, right = u * 2 + 2;
    if(e <= mid) {
        update(left, s, e, op, p);
    } else if(s >= mid + 1) {
        update(right, s, e, op, p);
    } else {
        update(left, s, mid, op, p);
        update(right, mid + 1, e, op, p);
    }
}

int p1[N], p2[N], rk1[N], rk2[N];
void undo(int u) {
    vector<T>& stk1 = stks[0][u];
    vector<T>& stk2 = stks[1][u];
    while(stk1.size()) {
        auto pa = stk1.back(); stk1.pop_back();
        int fax = pa.fax, fay = pa.fay, w = pa.w;
        p1[fax] = fax;
        rk1[fay] -= w;
        cnt[0]++;
    }

    while(stk2.size()) {
        auto pa = stk2.back(); stk2.pop_back();
        int fax = pa.fax, fay = pa.fay, w = pa.w;
        p2[fax] = fax;
        rk2[fay] -= w;
        cnt[1]++;
    }
}

int find(int p[], int x) {
    if (p[x] != x) return find(p, p[x]);
    return p[x];
}

bool merge(int op, int u, int p[], int rk[], int v1, int v2) {
    int fax = find(p, v1), fay = find(p, v2);
    if(rk[fax] > rk[fay]) {
        swap(fax, fay);
    }
    if(fax != fay) {
        cnt[op]--;
        p[fax] = fay;
        stks[op][u].push_back({fax, fay, rk[fax] == rk[fay]});
        if(rk[fay] == rk[fax]) rk[fay]++;
        return true;
    }
    return false;
}

void dfs(int u) {
    int l = tr[u].l, r = tr[u].r;
    
    int left = u * 2 + 1, right = u * 2 + 2;
    //do
    //Merge A 
    for(int i = 0; i < q[0][u].size(); i++) {
        pair<int, int>& p = q[0][u][i];
        merge(0, u, p1, rk1, p.first, p.second);
        //cout << "merge0 " << p.first << " " << p.second << endl;
    }

    //Merge A B
    for(int i = 0; i < q[0][u].size(); i++) {
        pair<int, int>& p = q[0][u][i];
        merge(1, u, p2, rk2, p.first, p.second);
        //cout << "merge1 " << p.first << " " << p.second << endl;
    }

    for(int i = 0; i < q[1][u].size(); i++) {
        pair<int, int>& p = q[1][u][i];
        merge(1, u, p2, rk2, p.first, p.second);
        //cout << "merge2 " << p.first << " " << p.second << endl;
    }

    /*cout << u << "  " << l << " " << r << endl;
    for(int i = 0; i < n; i++) {
        cout << find(p1, i) << " ";
    }
    cout << endl;

    for(int i = 0; i < n; i++) {
        cout << find(p2, i) << " ";
    }
    cout << endl << endl;*/

    if(l == r) {
        ans[l] = cnt[0] - cnt[1];
        
    } else {
        dfs(left);
        dfs(right);
    }
    undo(u);
}

void solve() {
    cin >> n >> m;
    map<pair<int, int>, vector<int>> mps[2];
    for(int i = 0; i < m; i++) {
        char c; 
        int u, v;
        cin >> c >> u >> v;
        if(u > v) swap(u, v);
        int op = c - 'A';
        mps[op][{u, v}].push_back(i);
    }

    for(int i = 0; i <= n; i++) {
        p1[i] = i;
        p2[i] = i;
        rk1[i] = 0;
        rk2[i] = 0;
    }
    cnt[0] = cnt[1] = n;

    tr[0] = {0, m - 1};
    build(0);
    for(int op = 0; op < 2; op++) {
        auto& mp = mps[op];
        for(auto it = mp.begin(); it != mp.end(); it++) {
            pair<int, int> p = it -> first;
            vector<int> vec = it -> second;
            for(int j = 0; j < vec.size(); j += 2) {
                int l = vec[j], r = m - 1;
                if(j + 1 < vec.size()) {
                    r = vec[j + 1] - 1;
                }
                update(0, l, r, op, p);
            }
        }
    }

    dfs(0);

    for(int i = 0; i < m; i++) cout << ans[i] << endl; 
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
