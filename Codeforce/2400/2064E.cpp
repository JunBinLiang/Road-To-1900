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

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)

using ll = long long;
const int MOD = 998244353;


const int MAX = 200000 + 100, INF = 1e8;
struct MaxSeg {
    struct Node {
        int l, r;
        int mx;
    } tr[MAX * 4];

    void build(int id) {
        int l = tr[id].l, r = tr[id].r;
        if(l == r) {
            return;
        }
        int mid = l + (r - l) / 2;
        tr[id * 2 + 1] = {l, mid, -INF};
        tr[id * 2 + 2] = {mid + 1, r, -INF};
        build(id * 2 + 1);
        build(id * 2 + 2);
    }

    void update(int id, int index, int val) { 
        int l = tr[id].l, r = tr[id].r;
        if(l == r) {
            tr[id].mx = val;  
            return;
        }
        int mid = l + (r - l) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        if(index <= mid) {
            update(left, index, val);
        } else {
            update(right, index, val);
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
} maxseg;

const int N = 2e5 + 10;
int p[N], sz[N], L[N], R[N], used[N];

int search(vector<int>& a, int val) {
    int l = 0, r = a.size() - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(a[mid] == val) return mid;
        if(a[mid] > val) r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}

int find(int u) {
    return p[u] == u ? p[u] : p[u] = find(p[u]);
}

void merge(int u, int v) {
    int r1 = find(u), r2 = find(v);
    if(r1 == r2) return;
    used[r2] += used[r1];
    sz[r2] += sz[r1];
    p[r1] = r2;
    L[r2] = min(L[r2], L[r1]);
    R[r2] = max(R[r2], R[r1]);
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];

    map<int, vector<pair<int, int>>> mp1;
    map<int, vector<int>> mp2;
    for(int i = 0; i < n; i++) {
        mp1[b[i]].push_back({a[i], i});
        mp2[b[i]].push_back(i);
        vector<int>& vec = mp2[b[i]];
        L[i] = R[i] = vec.size() - 1;
    }

    //init
    for(int i = 0; i < n; i++) {
        p[i] = i;
        sz[i] = 1;
        used[i] = 0;
    }

    maxseg.tr[0] = {0, n - 1, -INF};
    maxseg.build(0);
    for(int i = 0; i < n; i++) {
        maxseg.update(0, i, a[i]);
    }

    long long ans = 1;
    for(auto it = mp1.begin(); it != mp1.end(); it++) {
        vector<pair<int, int>> vec = it -> second;
        vector<int>& indexs = mp2[it -> first];
        sort(vec.begin(), vec.end());
        for(int ind : indexs) maxseg.update(0, ind, 0);
        for(auto& p : vec) {
            int ind = search(indexs, p.second);
            for(int j = ind - 1; j >= 0; j--) {
                if(indexs[j] + 1 == indexs[ind] || maxseg.query(0, indexs[j] + 1, indexs[ind] - 1) < p.first) {
                    merge(indexs[ind], indexs[j]);
                    j = L[find(indexs[j])];
                } else {
                    break;
                }
            }

            for(int j = ind + 1; j < indexs.size(); j++) {
                if(indexs[ind] + 1 == indexs[j] || maxseg.query(0, indexs[ind] + 1, indexs[j] - 1) < p.first) {
                    merge(indexs[ind], indexs[j]);
                    j = R[find(indexs[j])];
                } else {
                    break;
                }
            }
            int r = find(p.second);
            ans *= (sz[r] - used[r]);
            ans %= MOD;
            used[r]++;
        }
        for(int ind : indexs) maxseg.update(0, ind, a[ind]);
    }
    cout << ans << endl;
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
