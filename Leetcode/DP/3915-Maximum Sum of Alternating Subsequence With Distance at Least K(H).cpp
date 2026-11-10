const int MAX = 1e5 + 100;
const long long INF = 1e15;
struct MaxSeg {
    struct Node {
        int l, r;
        long long mx;
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

    void update(int id, int index, long long val) { 
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

    long long query(int id, int s, int e) {
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
} seg0, seg1;


class Solution {
public:
    long long maxAlternatingSum(vector<int>& a, int k) {
        int mx = *max_element(a.begin(), a.end());
        seg0.tr[0] = {0, mx + 10};
        seg0.build(0);
        seg1.tr[0] = {0, mx + 10};
        seg1.build(0);

        int n = a.size();
        vector<vector<long long>> dp(n, vector<long long>(2));
        for(int i = 0; i < n; i++) {
            dp[i][0] = a[i];
            dp[i][1] = a[i];
            if(i - k >= 0) {
                seg0.update(0, a[i - k], dp[i - k][0]);
                seg1.update(0, a[i - k], dp[i - k][1]);
                dp[i][0] = max(dp[i][0], a[i] + seg1.query(0, 0, a[i] - 1));
                dp[i][1] = max(dp[i][1], a[i] + seg0.query(0, a[i] + 1, mx + 1));
            }
        }

        long long ans = 0;
        for(auto& v : dp) {
            ans = max(ans, v[0]);
            ans = max(ans, v[1]);
        }
        return ans;
    }
};
