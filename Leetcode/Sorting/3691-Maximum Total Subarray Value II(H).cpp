const int INF = 2e9;
const int MAX = 50000 + 100;
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

vector<int> A;

struct Node {
    int l, r, i;
};

struct Comp {
    bool operator()(const Node& a, const Node& b) {
        // Max-heap 
        return A[a.i] - minseg.query(0, a.l, a.r) < A[b.i] - minseg.query(0, b.l, b.r);
    }
};

pair<int, int> find(vector<int>& p, int ind) {
    int l = 0, r = p.size() - 1;
    int p1 = -1, p2 = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(p[mid] < ind) {
            p1 = p[mid];
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    l = 0; r = p.size() - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(p[mid] > ind) {
            p2 = p[mid];
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return {p1, p2};
}

class Solution {
public:
    long long maxTotalValue(vector<int>& a, int k) {
        A = a;
        int n = a.size();
        vector<int> R(n, n), L(n, -1);
        vector<int> stk;
        for(int i = 0; i < n; i++) { //
            while(stk.size() > 0 && a[i] > a[stk.back()]) {
                int j = stk.back(); stk.pop_back();
                R[j] = i;
            }
            stk.push_back(i);
        }
        stk.clear();
        for(int i = n - 1; i >= 0; i--) {
            while(stk.size() > 0 && a[i] >= a[stk.back()]) {
                int j = stk.back(); stk.pop_back();
                L[j] = i;
            }
            stk.push_back(i);
        }

        unordered_map<int, vector<int>> mp;
        for(int i = 0; i < n; i++) mp[a[i]].push_back(i);

        minseg.tr[0] = {0, n - 1, INF};
        minseg.build(0);
        for(int i = 0; i < n; i++) {
            minseg.update(0, i, a[i]);
        }

        priority_queue<Node, vector<Node>, Comp> pq;
        for(int i = 0; i < n; i++) {
            int l = L[i] + 1, r = R[i] - 1;
            pq.push({l, r, i});
        }

        long long ans = 0;
        while(k) {
            auto node = pq.top(); pq.pop();
            int l = node.l, r = node.r, i = node.i;
            long long tot = (i - l + 1ll) * (r - i + 1ll);
            int mn = minseg.query(0, l, r);
            if(mn == a[i]) {
                k -= tot;
                k = max(0, k);
                continue;
            }
            vector<int>& po = mp[mn];
            pair<int, int> p = find(po, i);
            int sz1 = 0, sz2 = 0;
            if(p.first != -1 && p.first < l) p.first = -1;
            if(p.second != -1 && p.second > r) p.second = -1;
            if(p.first != -1 && p.second != -1) {
                sz1 = i - p.first - 1;
                sz2 = p.second - i - 1;
                node.l = p.first + 1;
                node.r = p.second - 1;
            } else if(p.first != -1) {
                sz1 = i - p.first - 1;
                sz2 = r - i;
                node.l = p.first + 1;
            } else if(p.second != -1) {
                sz1 = i - l;
                sz2 = p.second - i - 1;
                node.r = p.second - 1;
            }

            long long non = (sz1 + 1ll) * (sz2 + 1ll);
            long long yes = tot - non;
            ans += min((k + 0ll), yes) * (a[i] - mn);
            k -= yes;
            k = max(k, 0);
            pq.push(node);
        }
        return ans;
    }
};
