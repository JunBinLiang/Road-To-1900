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

struct MaxSeg {
    struct Node {
        int l, r;
        int mx;
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

    void update(int id, int index, int val) { 
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

    int query(int id, int s, int e) {
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
} maxseg;

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

namespace Combination {
    const int MOD = 1e9 + 7;
    int C[2010][2010];
    bool isInit = false;
    
    long long fpow(long long x, int y){
    	long long res = 1;
    	while(y){
    		if(y & 1) res = (res * x) % MOD;
    		x = (x * x) % MOD;
    		y >>= 1;
    	}
	    return res;
    } 
    
    void init() {
        if(isInit) return;
        isInit = true;
        C[0][0] = 1;
        for(int i = 1;i <= 2000; i++) {
          C[i][0]=1;
          for(int j = 1; j <= i;j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
          }
        }
    }
}

namespace Graph {
    struct E {
        int v, w, ei;
    };
    vector<E> g1[N];
    int ei = 0;

    void add(vector<E> g[N], int u, int v, int w) {
        g[u].push_back({v, w, ei++});
        g[v].push_back({u, w, ei++});
    }
}

namespace MaxFlow {
    const int N = 1e5 + 10, M = 2e5 + 10;
    long long INF = 1e16;
    int n, m, S, T;
    long long f[M]; //流量
    int d[N], cur[N]; //分层图

    struct E {
        int v, ei;
    };
    vector<E> g[N];
    int ei = 0;
    void add(vector<E> g[N], int u, int v, int w) {
        g[u].push_back({v, ei});
        f[ei++] = w;
        g[v].push_back({u, ei});
        f[ei++] = 0;
    }
    /*
    void add(vector<E> g[N], int u, int v, int w) {
        g[u].push_back({v, ei});
        to[ei] = v; //what each edge point to
        f[ei++] = w;
        g[v].push_back({u, ei});
        to[ei] = u;
        f[ei++] = 0;
    }
    
    */

    bool bfs() {
        memset(d, -1, sizeof d);
        queue<int> q;
        q.push(S);
        d[S] = 0;
        cur[S] = 0;
        while(q.size()) {
            int u = q.front(); q.pop();
            for(auto& e : g[u]) {
                if(d[e.v] == -1 && f[e.ei]) {
                    d[e.v] = d[u] + 1;
                    cur[e.v] = 0; 
                    q.push(e.v);
                    if(e.v == T) return true;
                }
            }
        }
        return false;
    }

    long long find(int u, long long limit) {
        if (u == T) return limit;
        long long flow = 0;
        for (int i = cur[u]; i < g[u].size() && flow < limit; i++) {
            int v = g[u][i].v;
            cur[u] = i;  // 当前弧优化
            if (d[v] == d[u] + 1 && f[g[u][i].ei]) {
                long long t = find(v, min(f[g[u][i].ei], limit - flow));
                if (!t) d[v] = -1;
                f[g[u][i].ei] -= t, f[g[u][i].ei ^ 1] += t, flow += t;
            }
        }
        return flow;
    }

    long long dinic() {
        long long r = 0, flow;
        while (bfs()) while (flow = find(S, INF)) r += flow;
        return r;
    }
}

namespace Interval {
    int sz = 0;
    map<int, int> mp;
    
    void init() {
        mp.clear();
        sz = 0;
    }
    
    void add(int l, int r) {
        while(true) {
            auto it = mp.upper_bound(l);
            if(it != mp.end()) {
                if(it -> first > r) break;
                else {
                    r = max(r, it -> second);
                    sz -= (it -> second - it -> first + 1);
                    mp.erase(it -> first);
                }
            } else {
                break;
            }
        }
        
        while(true) {
            auto it = mp.upper_bound(l);
            if(it == mp.begin()) break;
            else {
                it--;
                if(it -> second < l) break;
                else {
                    l = min(l, it -> first);
                    r = max(r, it -> second);
                    sz -= (it -> second - it -> first + 1);
                    mp.erase(it -> first);
                }
            }
        }
        
        
        mp[l] = r;
        sz += (r - l + 1);
    }
    
    int getSize() {
        return sz;
    }
};
