const int N = 1e5 + 10;
bool yes = false;
bool isp[N], vis[N];
void init() {
    if(yes) return;
    yes = true;
    memset(isp, 0, sizeof isp);
    memset(vis, 0, sizeof vis);
    for(int i = 2; i < N; i++) {
        if(vis[i]) continue;
        isp[i] = true;
        for(int j = i; j < N; j += i) {
            vis[j] = true;
        }
    }
}

struct Node {
    int l, r;
    int tag = 0, mx = 0;
} tr[N * 4];

void build(int u) {
    if(tr[u].l == tr[u].r) {
        return;
    }
    int l = tr[u].l, r = tr[u].r;
    int mid =l + (r - l) / 2;
    tr[u * 2 + 1] = {l, mid, 0, 0};
    tr[u * 2 + 2] = {mid + 1, r, 0, 0};
    build(u * 2 + 1);
    build(u * 2 + 2);
}

void pushdown(int u) {
    if(tr[u].tag == 0 || tr[u].l == tr[u].r) {
        return;
    }
    int left = u * 2 + 1, right = u * 2 + 2;
    tr[left].tag += tr[u].tag;
    tr[right].tag += tr[u].tag;
    tr[left].mx += tr[u].tag;
    tr[right].mx += tr[u].tag;
    tr[u].tag = 0;
}

void pushup(int u) {
    if(tr[u].l == tr[u].r) {
        return;
    }
    int left = u * 2 + 1, right = u * 2 + 2;
    tr[u].mx = max(tr[left].mx, tr[right].mx);
}

void update(int u, int s, int e, int val) {
    if(tr[u].l == s && tr[u].r == e) {
        tr[u].mx += val;
        tr[u].tag += val;
        return;
    }
    pushdown(u);
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    if(e <= mid) {
        update(u * 2 + 1, s, e, val);
    } else if(s >= mid + 1) {
        update(u * 2 + 2, s, e, val);
    } else {
        update(u * 2 + 1, s, mid, val);
        update(u * 2 + 2, mid + 1, e, val);
    }
    pushup(u);
}

class Solution {
public:
    vector<int> maximumCount(vector<int>& a, vector<vector<int>>& q) {
        init();
        int n = a.size();
        tr[0] = {0, n - 1};
        build(0);
        
        unordered_map<int, set<int>> mp;
        for(int i = 0; i < n; i++) {
            if(isp[a[i]]) {
                mp[a[i]].insert(i);
            }
        }

        int one = 0;
        for(auto it = mp.begin(); it != mp.end(); it++) {
            set<int>& s = it -> second;
            int L = *(s.begin());
            auto sit = s.end(); sit--;
            int R = *sit;
            if(L - 1 >= 0) update(0, 0, L - 1, 1);
            if(R < n - 1) update(0, R, n - 1, 1);
            if(L != R) update(0, L, R - 1, 2);
        }

        vector<int> ans(q.size());
        for(int i = 0; i < q.size(); i++) {
            int j = q[i][0], val = q[i][1];
            int old = a[j];
            a[j] = val;

            if(isp[old]) {
                upd1(mp[old], n);
                mp[old].erase(j);
                if(mp[old].size() == 0) mp.erase(old);
                if(mp.find(old) != mp.end()) {
                    upd2(mp[old], n);
                }
            }   

            if(isp[val]) {
                if(mp.find(val) != mp.end()) {
                    upd1(mp[val], n);
                }
                mp[val].insert(j);
                upd2(mp[val], n);
            }
            ans[i] = tr[0].mx;
        }
        return ans;
    }

    void upd1(set<int>& s, int n) {
        int L = *(s.begin());
        auto it = s.end(); it--;
        int R = *it;
        if(L - 1 >= 0) update(0, 0, L - 1, -1);
        if(R < n - 1) update(0, R, n - 1, -1);
        if(L != R) update(0, L, R - 1, -2);
    }

    void upd2(set<int>& s, int n) {
        int L = *(s.begin());
        auto it = s.end(); it--;
        int R = *it;
        if(L - 1 >= 0) update(0, 0, L - 1, 1);
        if(R < n - 1) update(0, R, n - 1, 1);
        if(L != R) update(0, L, R - 1, 2);
    }
};
