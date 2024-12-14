#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>

using namespace std;

const int N = 2e5 + 100;
const long long INF = 10000000000000000ll;
struct Node {
    int l, r;
    long long ls0 = -INF, rs0 = -INF, ls1 = -INF, rs1 = -INF, s1 = -INF, s2 = -INF, sum = 0, mid = -INF;
} tr[N * 4];
int a[N], b[N];

Node merge(Node node1, Node node2) {
    Node node = {node1.l, node2.r};
    node.sum = node1.sum + node2.sum; 
    node.s1 = max({node1.s1, node2.s1, node1.rs0 + node2.ls0});
    node.s2 = max({node1.s2, node2.s2, node1.rs1 + node2.ls0, node1.rs0 + node2.ls1, node1.s1 + node2.s1});
    
    node.ls0 = max({node1.ls0, node2.ls0 + node1.sum});
    node.rs0 = max({node2.rs0, node1.rs0 + node2.sum});

    node.ls1 = max({node1.ls1, node1.sum + node2.ls1, node1.ls0 + node2.s1, node1.mid + node2.ls0});
    node.rs1 = max({node2.rs1, node2.sum + node1.rs1, node2.rs0 + node1.s1, node2.mid + node1.rs0});

    node.mid = max({node1.mid + node2.sum, node2.mid + node1.sum, node1.ls0 + node2.rs0});
    return node;
}

void build(int u) {
    if(tr[u].l == tr[u].r) {
        return;
    }
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    tr[u * 2 + 1] = {l, mid, };
    tr[u * 2 + 2] = {mid + 1, r, };
    build(u * 2 + 1);
    build(u * 2 + 2);
}

void update(int u, int index, pair<int, int> p) {
    if(tr[u].l == tr[u].r) {
        tr[u].sum = p.first;
        tr[u].s1 = (p.first + 0ll) + 2 * p.second;
        tr[u].ls0 = (p.first  + 0ll) + p.second;
        tr[u].rs0 = (p.first  + 0ll) + p.second;
        tr[u].ls1 = tr[u].rs1 = tr[u].s2 = tr[u].mid = -INF;
        return;
    }
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    if(index <= mid) {
        update(u * 2 + 1, index, p);
    } else {
        update(u * 2 + 2, index, p);
    }
    tr[u] = merge(tr[u * 2 + 1], tr[u * 2 + 2]);
}

Node query(int u, int s, int e) {
    int l = tr[u].l, r = tr[u].r;
    if(l == s && r == e){
        return tr[u];
    }
    int mid = l + (r - l) / 2;
    int left = u * 2 + 1, right = u * 2 + 2;
    if(e <= mid){
        return query(left, s, e);
    } else if(s >= mid + 1) {
        return query(right, s, e);
    } else {
        return merge(query(left, s, mid), query(right, mid + 1, e));
    }
}

void solve() {
    int n, m;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    tr[0] = {0, n};
    build(0);

    for(int i = 1; i <= n; i++) {
        update(0, i, {a[i], b[i]});
    }

    cin >> m;
    for(int i = 0; i < m; i++) {
        int op;
        cin >> op;
        if(op == 1) {
            int index, x;
            cin >> index >> x;
            a[index] = x;
            update(0, index, {a[index], b[index]});
        } else if(op == 2) {
            int index, x;
            cin >> index >> x;
            b[index] = x;
            update(0, index, {a[index], b[index]});
        } else {
            int l, r;
            cin >> l >> r;
            Node node = query(0, l, r);
            cout << node.s2 << endl;
        }
    }
}   


int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
