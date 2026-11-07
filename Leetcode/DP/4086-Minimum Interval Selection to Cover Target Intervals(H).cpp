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

int q(vector<int>& p, int l, int r) {
    if(l > r) return 0;
    if(l == 0) return p[r];
    return p[r] - p[l - 1];
}

bool comp(vector<int>& p1, vector<int>& p2) {
    if(p1[1] == p2[1]) {
        return p1[0] < p2[0];
    }
    return p1[1] < p2[1];
}

class Solution {
public:
    int minSelection(vector<vector<int>>& a, vector<vector<int>>& b) {
        int mx = 0;
        for(auto& in : a) {
            in[0] *= 2;
            in[1] *= 2;
            mx = max(mx, in[1]);
        }
        for(auto& in : b) {
            in[0] *= 2;
            in[1] *= 2;
            mx = max(mx, in[1]);
        }

        vector<int> line(mx + 5);


        for(auto& in : b) {
            int l = in[0], r = in[1];
            line[l]++;
            line[r + 1]--;
        }

        int s = 0;
        for(int i = 0; i < line.size(); i++) {
            s += line[i];
            if(s > 0) {
                line[i] = 1;
            } else {
                line[i] = 0;
            }
        }

        for(int i = 1; i < line.size(); i++) {
            line[i] += line[i - 1]; // prefix sum
        }

        sort(a.begin(), a.end(), comp); //sort by end
        vector<int> dp(a.size(), INF);
        minseg.tr[0] = {0, (int)dp.size(), INF};
        minseg.build(0);
        for(int i = 0; i < a.size(); i++) {
            int s = a[i][0], e = a[i][1];
            // can do it my self
            if(s == 0 || q(line, 0, s - 1) == 0) {
                dp[i] = 1;
            }

            int l = 0, r = i - 1;
            int pos = -1;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                if(q(line, a[mid][1] + 1, s - 1) == 0) {
                    pos = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }

            if(pos != -1) {
                dp[i] = min(dp[i], 1 + minseg.query(0, pos, i - 1));
            }
            minseg.update(0, i, dp[i]);
        }

        int ans = INF;
        for(int i = 0; i < a.size(); i++) {
            int e = a[i][1];
            if(q(line, e + 1, line.size() - 1) == 0) {
                ans = min(ans, dp[i]);
            }
        }
        return ans > a.size() ? -1 : ans;
    }
};
