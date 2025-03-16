//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P8767
#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    
#include <deque>  

using namespace std;

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

const int N = 8e5 + 100, MOD = 998244353;
unsigned long long seed = 1;
struct FHQ {
    struct {
        int l, r;  // 左右孩子
        long long val;   // BST 的权值
        int rnd;   // 堆的随机值
        long long size;  // 树的大小
        long long add;
        long long cnt;
        long long sum = 0;
    } tr[N];
    int root = 0, n = 0;  // 根节点, 最新节点的下标
    int gctop = -1, stk[N];
    //垃圾回收减少memory使用
    void gc(int u) {
        if(!u) return;
        stk[++gctop] = u;
        gc(tr[u].l);
        gc(tr[u].r);
    }
    
    inline int _rand() {
        seed *= 260817;
        return int(seed);
    }
    
    // 创建一个新节点
    int newnode(int val, int cnt) {
        int id = -1;
        if(gctop >= 0) {
            id = stk[gctop--];
        } else {
            id = ++n;
        }
        tr[id].val = val;
        tr[id].rnd = _rand();
        tr[id].size = cnt;
        tr[id].cnt = cnt;
        tr[id].sum = ((tr[id].val + 0ll) * tr[id].size);
        tr[id].sum %= MOD;
        tr[id].add = 0;
        return id;
    }

    // 更新树的大小
    void pushup(int p) { 
        tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + tr[p].cnt; 
        tr[p].size %= MOD;
        tr[p].sum = tr[tr[p].l].sum + tr[tr[p].r].sum;
        tr[p].sum %= MOD; 
        tr[p].sum += ((tr[p].val + 0ll) * tr[p].cnt);
        tr[p].sum %= MOD;
    }

    void pushdown(int u) {
        if(tr[u].add) {
            int addv = tr[u].add;
            add(tr[u].l, addv);
            add(tr[u].r, addv);
            tr[u].add = 0; 
        }
    }

    void add(int u, int add) {
        tr[u].val += add;
        tr[u].add += add;
        tr[u].sum += ((add + 0ll) * tr[u].size);
        tr[u].sum %= MOD;
        if(tr[u].sum < 0) tr[u].sum += MOD;
    }

    // 按值 v 进行分裂, 左子树 <=v, 右子树 > v
    // x, y 是分裂后的两颗子树的根, 执行完成后 x.val <= v < y.val
    void split(int p, int v, int &x, int &y) {
        if (!p) {  // 空树
            x = y = 0;
            return;
        }
        pushdown(p);
        if (tr[p].val <= v) {
            // 递归分裂 p 的右子树
            // 左子树的根 x 已确定, y 需要继续向下带
            // 同时, p 的右节点需要指向下一层指向的左子树的根 x
            x = p;
            split(tr[p].r, v, tr[p].r, y);
        } else {  // 递归分裂 p 的左子树
            y = p;
            split(tr[p].l, v, x, tr[p].l);
        }

        // 最后, 向上更新每个子树的大小
        pushup(p);
    }

    // 按堆的随机值合并两颗子树, 返回合并后的根
    // 要求 x 树所有节点的 val 要 <= y 树所有节点的 val 值
    int merge(int x, int y) {
        if (!x || !y) return x + y;  // 存在空树的情况
        if (tr[x].rnd < tr[y].rnd) {
            // 应把 x 放上面, 先递归合并 x 的右子树 r 和 y 得到新树 z
            // 因为 x 权值更小, 所以把 z 作为 x 的右孩子
            pushdown(x);
            tr[x].r = merge(tr[x].r, y);
            pushup(x);
            return x;
        } else {
            pushdown(y);
            tr[y].l = merge(x, tr[y].l);
            pushup(y);
            return y;
        }
    }
    explicit FHQ() { memset(tr, 0, sizeof tr); }

    int size() { return tr[root].size; }
    int sum() { return tr[root].sum; }

    // 插入一个值
    void insert(int v, int sz) {
        // 按 v 分裂, 找到插入点 x <=v < y
        int x, y;
        split(root, v, x, y);
        // 新建节点
        int z = newnode(v, sz);
        // 依次合并 x, z 和 y (权值 val 也满足如此顺序)
        root = merge(merge(x, z), y);
    }

    // 删除一个值
    void del(int v) {
        int x, y, z;
        // 先找到 v 的分割点 => x <= v < z
        split(root, v, x, z);
        // 再按 v-1 分裂 x 树 => x <= v-1 < y <= v
        split(x, v - 1, x, y);
        // y 就是值等于 v 的节点, 删除它
        // 如果找不到 v, y 就是空树, 其左右孩子都是 0, 不影响
        int oldy = y;
        y = merge(tr[y].l, tr[y].r);
        tr[oldy].l = tr[oldy].r = 0; gc(oldy);
        // 再把 x, y, z 合并起来
        root = merge(merge(x, y), z);
    }

    // 查找排名, 满足 < v 的个数+1
    int rank(int v) {
        int x, y;
        split(root, v - 1, x, y);
        int ans = tr[x].size + 1;
        root = merge(x, y);
        return ans;
    }

    // 从子树 p 找第 k 小
    int topk(int p, int k) {
        int lsz = tr[tr[p].l].size;
        if (k == lsz + 1) return tr[p].val;
        if (k <= lsz) return topk(tr[p].l, k);
        return topk(tr[p].r, k - lsz - 1);
    }

    // 前驱, 严格 <v 的值
    int get_pre(int v) {
        int x, y;
        split(root, v - 1, x, y);
        int ans = topk(x, tr[x].size);
        root = merge(x, y);
        return ans;
    }

    // 后继, 严格 > v 的值
    int get_suc(int v) {
        int x, y;
        split(root, v, x, y);
        int ans = topk(y, 1);
        root = merge(x, y);
        return ans;
    }
} fhq;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        fhq.insert(x, 1);
    }
    
    while(m--) {
        int X, Y;
        cin >> X >> Y;
        if(X > 0) { //add
            int x, y;
            fhq.split(fhq.root, k - X - 1, x, y);
            
            /*cout << "  " << fhq.root << "   |" << x << "  " << y << "  " <<"  " << X << " " << Y << endl;
            cout << "  " << fhq.tr[x].size << "  " << fhq.tr[x].sum << "  " << endl;
            cout << "  " << fhq.tr[y].size << "  " << fhq.tr[y].sum << "  " << endl;*/

            int sz = fhq.tr[y].size;
            long long newsum = fhq.tr[y].sum + ((X + 0ll) * sz);
            newsum %= MOD;
            long long onecnt = newsum - ((k + 0ll) * sz);
            onecnt %= MOD;
            if(onecnt < 0) onecnt += MOD;
            
            int node1 = fhq.newnode(1, onecnt);
            int node2 = fhq.newnode(k, sz);
            
            /*cout << "gg " << sz << " " << onecnt << " " << newsum << endl;
            cout << "newadd " << onecnt << "  |" << k << " " << sz << endl;*/
            
            if(x) {
                fhq.add(x, X);
            }
            
            fhq.root = x;
            if(onecnt) {
                fhq.insert(1, onecnt);
            }
            if(sz) {
                fhq.insert(k, sz);
            }
            //cout << "after " << "  " << fhq.tr[fhq.root].sum << "  " << fhq.tr[fhq.root].size << endl  << endl << endl;
        } else if(X < 0) {
            int x, y;
            X = abs(X);
            fhq.split(fhq.root, X, x, y);
            
            /*cout << "del " << x << "  " << y <<"   " << X << " " << Y << endl;
            cout << "  " << fhq.tr[x].size << "  " << fhq.tr[x].sum << "  " << endl;
            cout << "  " << fhq.tr[y].size << "  " << fhq.tr[y].sum << "  " << endl;
            cout << endl << endl;*/
            
            if(y) {
                fhq.add(y, -X);
            }
            fhq.root = y;
            //cout << "after " << "  " << fhq.tr[fhq.root].sum << "  " << fhq.tr[fhq.root].size << endl  << endl << endl;
        }
        if(Y) {
            fhq.insert(Y, 1);
        }
        //cout << "ans  " << fhq.root << "  " << fhq.tr[fhq.root].sum <<"  " << fhq.tr[fhq.root].size << endl  << endl << endl;
        cout << fhq.tr[fhq.root].sum << endl;
        
    }
}

int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
