#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string.h>


using namespace std;  

const int INF = 1e8;
const int MAX = 200000 + 100;
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

const int N = 2e5 + 10;
vector<int> pos[N];
void solve() {
    string s;
    cin >> s;
    int n = s.size();
    for(int i = 0; i <= n; i++) pos[i].clear();
    //revert [L : R]
    //p[L - 1] = p[R], any(p[L : R]) - p[L - 1] <= p[L - 1]
    //any(p[L : R]) <= 2 * p[L - 1]
    long long ans = 0;
    int cnt = 0;
    vector<int> p(n + 1);
    maxseg.tr[0] = {0, n, 0};
    maxseg.build(0);
    maxseg.update(0, 0, 0);

    for(int i = 1, j = 0; i <= n; i++) {
        if(s[i - 1] == '(') cnt++;
        else cnt--;

        if(pos[cnt].size() > 0 && maxseg.query(0, pos[cnt].back() + 1, i) > cnt * 2) {
            pos[cnt].clear();
        }

        ans += pos[cnt].size();
        pos[cnt].push_back(i);
        p[i] = cnt;
        maxseg.update(0, i, cnt);
    }
    
    cout << ans << endl;
}

int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
