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


int f1(vector<int> a) {
    vector<int> dp(a.size());
    for(int i = 0; i < a.size(); i++) {
        dp[i] = 1;
        for(int j = i - 1; j >= 0; j--) {
            if(a[i] > a[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    int ans = 0;
    for(int x : dp) ans = max(ans, x);
    return ans;
}

int f2(vector<int> a) {
    vector<int> dp(a.size());
    for(int i = a.size() - 1; i >= 0; i--) {
        dp[i] = 1;
        for(int j = i + 1; j < a.size(); j++) {
            if(a[i] > a[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    int ans = 0;
    for(int x : dp) ans = max(ans, x);
    return ans;
}

vector<int> sub(vector<int>& a, int l, int r) {
    vector<int> ans;
    for(int i = l; i <= r; i++) ans.push_back(a[i]);
    return ans;
}

const int N = 1e5 + 10;


const int INF = 1e8;
const int MAX = 200000 + 100;
struct MinSeg {
    struct Node {
        int l, r;
        int mn;
    } tr[MAX * 4];

    void build(int id) {
        int l = tr[id].l, r = tr[id].r;
        if(l == r) {
            return;
        }
        int mid = l + (r - l) / 2;
        tr[id * 2 + 1] = {l, mid, INF};
        tr[id * 2 + 2] = {mid + 1, r, INF};
        build(id * 2 + 1);
        build(id * 2 + 2);
    }

    void update(int id, int index, int val) { 
        int l = tr[id].l, r = tr[id].r;
        if(l == r) {
            tr[id].mn = min(tr[id].mn, val);  
            return;
        }
        int mid = l + (r - l) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        if(index <= mid) {
            update(left, index, val);
        } else {
            update(right, index, val);
        }
        tr[id].mn = min(tr[left].mn, tr[right].mn);
    }

    int query(int id, int s, int e) {
        int l = tr[id].l, r = tr[id].r;
        if(l == s && r == e){
            return tr[id].mn;
        }
        int mid = l + (r - l) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        if(e <= mid){
            return query(left, s, e);
        } else if(s >= mid + 1) {
            return query(right, s, e);
        } else {
            return min(query(left, s, mid), query(right, mid + 1, e));
        }
    }
} minseg;

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
            tr[id].mx = max(tr[id].mx, val);  
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


bool comp(pair<int, int>& p1, pair<int, int>& p2) {
    return p1.first < p2.first;
}

long long over(pair<int, int>& p1, pair<int, int>& p2) {
    int L = max(p1.first, p2.first);
    int R = min(p1.second, p2.second);
    int sz = R - L + 1;
    long long ans = 0;
    ans += ((sz + 1ll) * (sz) / 2);
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> p(n + 1);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        p[a[i]] = i;
    }
    
    vector<int> L(n), R(n);
    for(int i = 0; i < n; i++) {
        L[i] = R[i] = i;
    }

    maxseg.tr[0] = {0, n + 1};
    maxseg.build(0);

    for(int i = 0; i < n; i++) {
        if(i == 0) {
            maxseg.update(0, a[i], i);
            continue;
        }

        if(a[i - 1] < a[i]) {
            int pos = maxseg.query(0, a[i - 1] + 1, n + 1);
            if(pos >= 0 && a[pos] < a[i]) {
                L[i] = max(L[i - 1], pos + 1);
            } else {
                L[i] = L[i - 1];
            }

        } else {
            int pos = maxseg.query(0, 0, a[i - 1] - 1);
            if(pos >= 0 && a[pos] > a[i]) {
                L[i] = max(L[i - 1], pos + 1);
            } else {
                L[i] = L[i - 1];
            }
        }
        maxseg.update(0, a[i], i);
    }

    minseg.tr[0] = {0, n + 1};
    minseg.build(0);
    for(int i = n - 1; i >= 0; i--) {
        if(i == n - 1) {
            minseg.update(0, a[i], i);
            continue;
        }

        if(a[i + 1] < a[i]) {
            int pos = minseg.query(0, a[i + 1] + 1, n + 1);
            if(pos < n && a[pos] < a[i]) {
                R[i] = min(R[i + 1], pos - 1);
            } else {
                R[i] = R[i + 1];
            }

        } else {
            int pos = minseg.query(0, 0, a[i + 1] - 1);
            if(pos < n && a[pos] > a[i]) {
                R[i] = min(R[i + 1], pos - 1);
            } else {
                R[i] = R[i + 1];
            }
        }
        minseg.update(0, a[i], i);
    }


    vector<pair<int, int>> b;
    for(int i = 0; i < n; i++) {
        //cout << i << "  " << L[i] << " " << R[i] << endl;
        b.push_back({L[i], R[i]});
    }
    //cout << endl;

    long long ans = 0;
    sort(b.begin(), b.end());
    vector<pair<int, int>> stk;
    for(int i = 0; i < b.size(); i++) {
        int l = b[i].first, r = b[i].second;
        int sz = r - l + 1;
        ans += ((sz + 1ll) * (sz) / 2);
        if(stk.size() == 0 || l > stk.back().second) {
            stk.push_back({l, r});
        } else {
            ans -= over(stk.back(), b[i]);
            stk.back().second = max(stk.back().second, r);
        }
        //cout << i << "  " << l << "  " << r << "  " << ans << endl;
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
