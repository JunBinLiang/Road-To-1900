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

using namespace std;


//1:22 - 1:46
struct T {
    int l, r, i;
    bool operator<(const T& other) {
        if(l == other.l) {
            return r > other.r;
        }
        return l < other.l;
    }
};

const int INF = 2e9;
const int MAX = 400000 + 1000;
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
int ans[N];
void solve() {
    int n;
    cin >> n;
    vector<T> a;
    vector<int> all;
    for(int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        a.push_back({l, r, i});
        all.push_back(l);
        all.push_back(r);
        ans[i] = 0;
    }

    sort(all.begin(), all.end());
    int id = 1;
    unordered_map<int, int> mp1;
    for(int i = 0; i < all.size(); i++) {
        if(mp1.find(all[i]) == mp1.end()) {
            mp1[all[i]] = id;
            id++;
        }
    }

    maxseg.tr[0] = {0, id + 10, -INF};
    maxseg.build(0);

    sort(a.begin(), a.end());
    set<int> s;
    for(int i = 0; i < n; i++) {
        int j = i;
        int cnt = 0;
        while(j < n && a[j].l == a[i].l && a[j].r == a[i].r) {
            cnt++;
            j++;
        }
        
        int l = a[i].l, r = a[i].r;
        if(cnt > 1) {
            i = j - 1;
            maxseg.update(0, mp1[r], l);
            s.insert(r);
            continue;
        }

        auto it = s.upper_bound(r - 1);
        if(it != s.end()) {
            int maxL = maxseg.query(0, mp1[r], id + 2);
            int minR = *it;
            ans[a[i].i] = (minR - maxL + 1) - (r - l + 1);
        }
        maxseg.update(0, mp1[r], l);
        s.insert(r);
    }

    //print answer
    for(int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
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
