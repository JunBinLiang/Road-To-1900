const int N = 1e5 + 100;
struct Node {
    int l, r;
    int mx, mn;
} tr[N * 4];

void pushup(int u) {
    int L = u * 2 + 1, R = u * 2 + 2;
    tr[u].mx = max(tr[L].mx, tr[R].mx);
    tr[u].mn = min(tr[L].mn, tr[R].mn);
}

pair<int, int> merge(pair<int, int> p1, pair<int, int> p2) {
    return {min(p1.first, p2.first), max(p1.second, p2.second)};
}

pair<int, int> query(int u, int s, int e) {
    if(tr[u].l == s && tr[u].r == e) {
        return {tr[u].mn, tr[u].mx};
    }

    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    if(e <= mid) {
        return query(u * 2 + 1, s, e);
    } else if(s >= mid + 1) {
        return query(u * 2 + 2, s, e);
    } else {
        return merge(query(u * 2 + 1, s, mid), query(u * 2 + 2, mid + 1, e));
    }
}

void build(vector<int>& a, int u) {
    if(tr[u].l == tr[u].r) {
        tr[u].mn = tr[u].mx = a[tr[u].l];
        return;
    }

    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    tr[u * 2 + 1] = {l, mid};
    tr[u * 2 + 2] = {mid + 1, r};
    build(a, u * 2 + 1);
    build(a, u * 2 + 2);
    pushup(u);
}



class Solution {
public:
    long long maxTotalValue(vector<int>& a, int k) {
        int n = a.size();
        tr[0] = {0, n - 1};
        build(a, 0);
        priority_queue<pair<int, int>> pq;
        vector<int> to(n, n - 1);
        for(int i = 0; i < n; i++) {
            pair<int, int> p = query(0, i, n - 1);
            pq.push({p.second - p.first, i});
        }

        unordered_map<int, vector<int>> mp;
        for(int i = 0; i < n; i++) {
            mp[a[i]].push_back(i);
        }

        long long ans = 0;
        while(k > 0) {
            pair<int, int> p = pq.top();
            pq.pop();
            int index = p.second;
            int L = index, R = to[index];
            p = query(0, L, R);
            int mn = p.first, mx = p.second;
            int val = mx - mn;
            vector<int>& v1 = mp[mn];
            vector<int>& v2 = mp[mx];

            //find maximum and minimum index <= R
            int p1 = find(v1, R);
            int p2 = find(v2, R);
            int pos = max(p1, p2);
            to[index] = pos - 1;
            int seg = R - pos + 1;

            if(k <= seg) {
                ans += (k + 0ll) * val;
                k = 0;
            } else {
                ans += (seg + 0ll) * val;
                k -= seg;
            }
            if(L <= to[index]) {
                p = query(0, L, to[index]);
                pq.push({p.second - p.first, index});
            }
        }
        return ans;
    }

    int find(vector<int>& a, int R) {
        int l = 0, r = a.size() - 1;
        int ans = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(a[mid] <= R) {
                ans = a[mid];
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};
