const int N = 1e5 + 100;
struct Node {
    int l, r;
    int cnt;
    int lcolor, rcolor;
    void init() {
        cnt = 0;
    }
} tr[N * 4];

void build(int u) {
    if(tr[u].l == tr[u].r) {
        return;
    }
    tr[u].init();
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    tr[u * 2 + 1] = {l, mid};
    tr[u * 2 + 2] = {mid + 1, r};
    build(u * 2 + 1);
    build(u * 2 + 2);
}

void pushup(int u) {
    if(tr[u].l == tr[u].r) {
        return;
    }
    int lid = u * 2 + 1, rid = u * 2 + 2;
    tr[u].lcolor = tr[lid].lcolor;
    tr[u].rcolor = tr[rid].rcolor;
    if(tr[lid].rcolor == tr[rid].lcolor) {
        tr[u].cnt = tr[lid].cnt + tr[rid].cnt - 1;
    } else {
        tr[u].cnt = tr[lid].cnt + tr[rid].cnt;
    }

}

void update(int u, int index, char c) {
    if(tr[u].l == tr[u].r) {
        if(c == 'A') tr[u].lcolor = tr[u].rcolor = 0;
        else tr[u].lcolor = tr[u].rcolor = 1;
        tr[u].cnt = 1;
        return;
    }
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    if(index <= mid) {
        update(u * 2 + 1, index, c);
    } else {
        update(u * 2 + 2, index, c);
    }
    pushup(u);
}

vector<int> merge(vector<int> v1, vector<int> v2) {
    int cnt = v1[2] + v2[2];
    if(v1[1] == v2[0]) {
        cnt--;
    }
    return {v1[0], v2[1], cnt};
}

vector<int> query(int u, int s, int e) {
    if(tr[u].l == s && tr[u].r == e) {
        return {tr[u].lcolor, tr[u].rcolor, tr[u].cnt};
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

class Solution {
public:
    vector<int> minDeletions(string s, vector<vector<int>>& queries) {
        int n = s.size();
        tr[0] = {0, n - 1};
        build(0);
        for(int i = 0; i < n; i++) {
            update(0, i, s[i]);
        }

        vector<int> ans;
        for(auto& q : queries) {
            if(q[0] == 1) {
                int index = q[1];
                char c = s[index];
                if(c == 'A') {
                    update(0, index, 'B');
                    s[index] = 'B';
                } else {
                    update(0, index, 'A');
                    s[index] = 'A';
                }
            } else {
                int l = q[1], r = q[2], sz = r - l + 1;
                vector<int> vec = query(0, l, r);
                ans.push_back(sz - vec[2]);
            }
        }
        return ans;
    }
};
