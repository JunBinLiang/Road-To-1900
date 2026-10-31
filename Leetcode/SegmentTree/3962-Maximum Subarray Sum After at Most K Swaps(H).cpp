const int N = 1555 * 4;
int val[N];
struct Node {
    int l, r;
    int sum, cnt, cnt0, cnt1;
    void init() {
        sum = 0;
        cnt = 0;
        cnt0 = 0;
        cnt1 = 0;
    }
} tr1[N], tr2[N], tr3[N];

void build(Node tr[], int u) {
    tr[u].init();
    int l = tr[u].l, r = tr[u].r;
    if(l == r) {
        return;
    }
    int mid = l + (r - l) / 2;
    tr[u * 2 + 1] = {l, mid};
    tr[u * 2 + 2] = {mid + 1, r};
    build(tr, u * 2 + 1);
    build(tr, u * 2 + 2);
}

void update1(Node tr[], int u, int index, int val, int which) {
    int l = tr[u].l, r = tr[u].r;
    if(l == r) {
        if(val == -1) { //move from outside to inside
            tr[u].cnt1--;
            tr[u].cnt0++;
            return;
        }

        if(which == 0) { //outside : 1  inside : 0
            tr[u].cnt0 += val;
        } else {
            tr[u].cnt1 += val;
        }
        return;
    }
    int mid = l + (r - l) / 2;
    int L = u * 2 + 1, R = u * 2 + 2;
    if(index <= mid) {
        update1(tr, L, index, val, which);
    } else {    
        update1(tr, R, index, val, which);
    }
    tr[u].cnt0 = tr[L].cnt0 + tr[R].cnt0;
    tr[u].cnt1 = tr[L].cnt1 + tr[R].cnt1;
}

void update2(Node tr[], int u, int index, int val, int cnt) {
    int l = tr[u].l, r = tr[u].r;
    if(l == r) {
        tr[u].sum += val;
        tr[u].cnt += cnt;
        return;
    }
    int mid = l + (r - l) / 2;
    int L = u * 2 + 1, R = u * 2 + 2;
    if(index <= mid) {
        update2(tr, L, index, val, cnt);
    } else {    
        update2(tr, R, index, val, cnt);
    }
    tr[u].sum = tr[L].sum + tr[R].sum;
    tr[u].cnt = tr[L].cnt + tr[R].cnt;
}

// find topk sum
int dfs1(Node tr[], int u, int k) {
    if(tr[u].l == tr[u].r) {
        return k * val[tr[u].l];
    }
    int L = u * 2 + 1, R = u * 2 + 2;
    if(k <= tr[L].cnt) {
        return dfs1(tr, u * 2 + 1, k);
    } else {
        return tr[L].sum + dfs1(tr, R, k - tr[L].cnt);
    }
}

int dfs2(Node tr[], int u, int k) {
    if(tr[u].l == tr[u].r) {
        return k * val[tr[u].l];
    }
    int L = u * 2 + 1, R = u * 2 + 2;
    if(k <= tr[R].cnt) {
        return dfs2(tr, R, k);
    } else {
        return tr[R].sum + dfs2(tr, L, k - tr[R].cnt);
    }
}

int dfs3(Node tr[], int u, int add0, int add1) {
    if(tr[u].l == tr[u].r) {
        return tr[u].l;
    }
    int L = u * 2 + 1, R = u * 2 + 2;
    if(add0 + tr[L].cnt0 < tr[R].cnt1 + add1) { // ok
         return dfs3(tr, R, add0 + tr[L].cnt0, add1);
    } else {
        return dfs3(tr, L, add0, add1 + tr[R].cnt1);
    }
}

int query(Node tr[], int u, int s, int e) {
    int l = tr[u].l, r = tr[u].r;
    if(l == s && r == e) {
        return tr[u].cnt0;
    }
    int mid = l + (r - l) / 2;
    if(e <= mid) {
        return query(tr, u * 2 + 1, s, e);
    } else if(s >= mid + 1) {
        return query(tr, u * 2 + 2, s, e);
    } else {
        return query(tr, u * 2 + 1, s, mid) + query(tr, u * 2 + 2, mid + 1, e);
    }
}

class Solution {
public:
    long long maxSum(vector<int>& a, int k) {
        int n = a.size();
        if(k == 0) { // nothing
            int ans = -1e9;
            for(int i = 0; i < n; i++) {
                int s = 0;
                for(int j = i; j < n; j++) {
                    s += a[j];
                    ans = max(ans, s);
                }
            }
            return ans;
        }

        int ans = -1e9;
        vector<int> b(a.begin(), a.end());
        sort(b.begin(), b.end());
        int sum = 0;
        for(int i = n - 1; i >= n - k; i-- ) {
            sum += b[i];
            ans = max(ans, sum);
        }

        map<int, int> rk; 
        int id = 0;
        for(int x : b) {
            if(rk.find(x) == rk.end()) {
                rk[x] = id;
                val[id] = x;
                id++;
            }
        }

        for(int i = 0; i < n; i++) { //starting index
            tr1[0] = {0, n - 1};
            tr2[0] = {0, n - 1}; //inside top k
            tr3[0] = {0, n - 1}; //outside top k
            build(tr1, 0);
            build(tr2, 0);
            build(tr3, 0);
            int L = i, R = i + k - 1;
            int s = 0;
            for(int j = 0; j < n; j++) {
                int x = a[j], rank = rk[x];
                if(j < L || j > R) {
                    update1(tr1, 0, rank, 1, 1); // outside
                    update2(tr3, 0, rank, x, 1);
                } else {
                    update1(tr1, 0, rank, 1, 0); // inside
                    s += x;
                    update2(tr2, 0, rank, x, 1);
                }
            }
            ans = max(ans, s);

            for(int j = i + k; j < n; j++) {
                //taking from outside to inside
                int x = a[j], rank = rk[x];
                update1(tr1, 0, rank, -1, 1); //outside
                update2(tr2, 0, rank, x, 1);
                update2(tr3, 0, rank, -x, -1);
                s += x;
                ans = max(ans, s);
                int index = dfs3(tr1, 0, 0, 0);
                int maxtake = min(k, query(tr1, 0, 0, index));
                if(maxtake > 0) {
                    int out = dfs1(tr2, 0, maxtake);
                    int in = dfs2(tr3, 0, maxtake);
                    ans = max(ans, s - out + in);
                }
            }
        }
        return ans;
    }
};
