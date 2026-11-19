const int N = 50000 + 50;
struct Node {
    int l, r;
    int g;
} tr[N * 4];

void build(int u) {
    if(tr[u].l == tr[u].r) {
        return;
    }
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    tr[u * 2 + 1] = {l, mid, -1};
    tr[u * 2 + 2] = {mid + 1, r, -1};
    build(u * 2 + 1);
    build(u * 2 + 2);
}

void pushup(int u) {
    int L = u * 2 + 1, R = u * 2 + 2;
    if(tr[L].g == -1) {
        tr[u].g = tr[R].g;
    } else if(tr[R].g == -1) {
        tr[u].g = tr[L].g;
    } else {
        tr[u].g = __gcd(tr[L].g, tr[R].g);
    }
}

void update(int u, int index, int val) {
    if(tr[u].l == tr[u].r) {
        tr[u].g = val;
        return;
    }
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    if(index <= mid) {
        update(u * 2 + 1, index, val);
    } else {
        update(u * 2 + 2, index, val);
    }
    pushup(u);
}

int merge(int x, int y) {
    if(x == -1) return y;
    else if(y == -1) return x;
    return __gcd(x, y);
}

int query(int u, int s, int e) {
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    if(l == s && r == e) {
        return tr[u].g;
    }
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
    int countGoodSubseq(vector<int>& a, int k, vector<vector<int>>& queries) {
        int n = a.size();
        tr[0] = {0, n - 1, -1};
        build(0);
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            if(a[i] % k == 0) {
                update(0, i, a[i] / k);
            } else {
                update(0, i, -1);
                cnt++;
            }
        }
        
        int ans = 0;
        for(auto& q : queries) {
            int index = q[0], x = q[1];
            if(a[index] % k != 0) cnt--;
            a[index] = x;
            if(x % k == 0) update(0, index, x / k);
            else {
                update(0, index, -1);
                cnt++;
            }
            if(tr[0].g == 1) {
                if(cnt > 0 || n > 20) ans++;
                else {
                    for(int i = 0; i < n; i++) {
                        int g1 = -1, g2 = -1;
                        if(i - 1 >= 0) g1 = query(0, 0, i - 1);
                        if(i + 1 < n) g2 = query(0, i + 1, n - 1);
                        int g = merge(g1, g2);
                        if(g == 1) {
                            ans++;
                            break;
                        }
                    }
                }
            }
        }
        return ans;
    }
};
