namespace Fenwick {
    const int FENWICK_SIZE = 100000 + 100;
    struct Fenwick {
        int tree[FENWICK_SIZE];
        int sz;
        void init(int n) {
            sz = n;
            for(int i = 0; i <= n + 1; i++) tree[i] = 0;
        }

        void update(int i, int val) {
            i++;
            while(i < sz){
            tree[i] += val;
            i += (i & -i);
            }
        }

        int pre(int i) {
            int sum = 0;
            while(i > 0){
            sum += tree[i];
            i -= ( i & -i);
            }
            return sum;
        }
        int query(int i, int j) {
            return pre(j + 1) - pre(i);
        }
    } tr;
}


namespace SegmentTreeRangeAdd {
    struct Node { //Segment Tree for range update
        int l, r, add; long long s;
    } tr[N * 4];
    void build(int u) {
        if(tr[u].l == tr[u].r) return;
        int left = u * 2 + 1, right = u * 2 + 2;
        int l = tr[u].l, r = tr[u].r;
        int mid = l + (r - l) / 2;
        tr[left] = {l, mid, 0, 0};
        tr[right] = {mid + 1, r, 0, 0};
        build(left); build(right);
    }   

    void pushdown(int u) {
        if(tr[u].l == tr[u].r || tr[u].add == 0) return;
        int left = u * 2 + 1, right = u * 2 + 2;
        tr[left].s += ((tr[left].r - tr[left].l + 1ll) * tr[u].add);
        tr[right].s += ((tr[right].r - tr[right].l + 1ll) * tr[u].add);
        tr[right].add += tr[u].add;
        tr[left].add += tr[u].add;
        tr[u].add = 0;
    }

    void pushup(int u) {
        int left = u * 2 + 1, right = u * 2 + 2;
        tr[u].s = tr[left].s + tr[right].s;
    }

    void update(int u, int s, int e, int val) { 
        int l = tr[u].l, r = tr[u].r;
        if(l == s && r == e) {
            tr[u].add += val;
            tr[u].s += ((tr[u].r - tr[u].l + 1ll) * val); 
            return;
        }

        int mid = l + (r - l) / 2;
        int left = u * 2 + 1, right = u * 2 + 2;
        pushdown(u);

        if(e <= mid) {
            update(left, s, e, val);
        } else if(s >= mid + 1) {
            update(right, s, e, val);
        } else {
            update(left, s, mid, val);
            update(right, mid + 1, e, val);
        }
        pushup(u);
    }

    long long query(int u, int s, int e) { // query sum from [0 : l]
        int l = tr[u].l, r = tr[u].r;
        if(l == s && r == e){
            return tr[u].s;
        }
        pushdown(u);
        int mid = l + (r - l) / 2;
        int left = u * 2 + 1, right = u * 2 + 2;
        if(e <= mid){
            return query(left, s, e);
        } else if(s >= mid + 1) {
            return query(right, s, e);
        } else {
            return query(left, s, mid) + query(right, mid + 1, e);
        }
    }
}