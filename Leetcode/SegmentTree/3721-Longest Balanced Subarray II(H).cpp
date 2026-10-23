const int N = 1e5 + 10;
const int INF = 1e9;
struct Node {
    int l, r, mn, mx;
    int tag = 0;
    void init() {
        tag = 0;
        mx = 0;
        mn = 0;
    }
} tr[N * 4];

void build(int u) {
    tr[u].init();
    if(tr[u].l == tr[u].r) return;
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    tr[u * 2 + 1] = {l, mid};
    tr[u * 2 + 2] = {mid + 1, r};
    build(u * 2 + 1); build(u * 2 + 2);
}

void pushdown(int u) {
    if(tr[u].l == tr[u].r) {
        return;
    }
    int L = u * 2 + 1, R = u * 2 + 2;
    if(tr[u].tag) {
        tr[L].tag += tr[u].tag;
        tr[R].tag += tr[u].tag;
        tr[L].mn += tr[u].tag;
        tr[L].mx += tr[u].tag;
        tr[R].mn += tr[u].tag;
        tr[R].mx += tr[u].tag;
        tr[u].tag = 0;
    }
}

void pushup(int u) {
    if(tr[u].l == tr[u].r) {
        return;
    }
    int L = u * 2 + 1, R = u * 2 + 2;
    tr[u].mn = min(tr[L].mn, tr[R].mn);
    tr[u].mx = max(tr[L].mx, tr[R].mx);

}

void update(int u, int s, int e, int val) {
    if(tr[u].l == s && tr[u].r == e) {
        tr[u].tag += val;
        tr[u].mn  += val;
        tr[u].mx  += val;
        return;
    }
    pushdown(u);
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    if(e <= mid) {
        update(u * 2 + 1, s, e, val);
    } else if(s > mid) {
        update(u * 2 + 2, s, e, val);
    } else {
        update(u * 2 + 1, s, mid, val);
        update(u * 2 + 2, mid + 1, e, val);
    }
    pushup(u);
}

// walk directly over segmeng tree
int dfs(int u) {
    if(tr[u].l == tr[u].r) {
        if(tr[u].mx != 0) {
            return 0;
        }
        return 1;
    }
    pushdown(u);
    int l = tr[u].l, r = tr[u].r;
    if(tr[u].mx >= 0 && tr[u].mn <= 0) {
        int L = u * 2 + 1;
        int R = u * 2 + 2;
        if(tr[R].mx >= 0 && tr[R].mn <= 0) {
            return (tr[L].r - tr[L].l + 1) + dfs(R);
        } else {
            return dfs(u * 2 + 1);
        }
    } else {
        return 0; //bad segmengt
    }
}

class Solution {
public:
    int longestBalanced(vector<int>& a) {
        int n = a.size();
        map<int, queue<int>> mp;
        for(int i = 0; i < n; i++) {
            mp[a[i]].push(i);
        }

        tr[0] = {0, n - 1};
        build(0);

        for(auto it = mp.begin(); it != mp.end(); it++) {
            int x = it -> first;
            if(x % 2 == 0) { // +1
                update(0, (it -> second).front(), n - 1, 1);
            } else { // -1
                update(0, (it -> second).front(), n - 1, -1);
            }
        }

        int ans = 0;
        for(int i = 0; i < n; i++) {
            // find
            int len = dfs(0);
            ans = max(ans, len - i);
            //reset
            int x = a[i];
            if(x % 2 == 0) update(0, i, n - 1, -1);
            else update(0, i, n - 1, 1); 
            mp[x].pop();
            if(mp[x].size() > 0) {
                int idx = mp[x].front();
                if(x % 2 == 0) update(0, idx, n - 1, 1);
                else update(0, idx, n - 1, -1);
            }
        }
        return ans;
    }
};
