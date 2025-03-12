//https://www.lanqiao.cn/problems/17102/learning/?page=1&first_category_id=1&name=%E6%A0%91%E4%B8%8A%E7%9A%84%E8%B7%AF%E5%BE%84
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
#include <deque>  

using namespace std;

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

const int N = 1000010, M = N * 2;
int n, D;
int h[N], e[M], w[M], ne[M], idx;
bool st[N];
int p[N], q[N];

void add(int a, int b, int c)
{
  e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int get_size(int u, int fa)  // 求子树大小
{
    if (st[u]) return 0;
    int res = 1;
    for (int i = h[u]; ~i; i = ne[i])
        if (e[i] != fa)
            res += get_size(e[i], u);
    return res;
}

void get_dist(int u, int fa, int dist, int& qt)
{
    if (st[u]) return;
    q[qt ++ ] = dist;
    for (int i = h[u]; ~i; i = ne[i])
        if (e[i] != fa)
            get_dist(e[i], u, dist + w[i], qt);
}

long long get(int a[], int k)
{
    sort(a, a + k);
    long long res = 0;
    long long s = 0;
    
    for(int i = 0; i < k; i++) {
        s += a[i];
    }

    int l = 0, r = k - 1;
    while(l < r) {
        if(a[l] + a[r] <= D) {
            s -= a[l];
            int cnt = r - l;
            res += ((a[l] + 0ll) * cnt);
            res += s;
            l++;
        } else {
            s -= a[r];
            r--;
        }
    }
    return res;
}

int get_wc(int u, int fa, int tot, int& wc)  // 求重心
{
    if (st[u]) return 0;
    int sum = 1, ms = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == fa) continue;
        int t = get_wc(j, u, tot, wc);
        ms = max(ms, t);
        sum += t;
    }
    ms = max(ms, tot - sum);
    if (ms <= tot / 2) wc = u;
    return sum;
}


long long calc(int u)
{
    if (st[u]) return 0;
    long long res = 0;
    get_wc(u, -1, get_size(u, -1), u);
    st[u] = true;  // 删除重心
    int pt = 0;

    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i], qt = 0;
        get_dist(j, -1, w[i], qt);
        res -= get(q, qt);
        for (int k = 0; k < qt; k ++ )
        {
            if (q[k] <= D) res += q[k] ;
            p[pt ++ ] = q[k];
        }
    }
    res += get(p, pt);
    for (int i = h[u]; ~i; i = ne[i]) res += calc(e[i]);
    return res;
}


void solve() {
    int n, L, R;
    cin >> n >> L >> R;
    memset(h, -1, sizeof h);
    for(int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        add(p, i, 1);
        add(i, p, 1);
    }    

    memset(st, 0, sizeof st);
    D = R;
    long long ans = 0;
    ans += calc(1);
    

    memset(st, 0, sizeof st);
    D = L - 1;
    ans -= calc(1);
    cout << ans << endl;
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
