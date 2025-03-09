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

namespace Fenwick {
    const int FENWICK_SIZE = 200000 + 100;
    struct Fenwick {
        long long tree[FENWICK_SIZE];
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

        long long pre(int i) {
            long long sum = 0;
            while(i > 0){
                sum += tree[i];
                i -= ( i & -i);
            }
            return sum;
        }
        long long query(int i, int j) {
            return pre(j + 1) - pre(i);
        }
    } tr;
}

using namespace Fenwick; 

using ll = long long;
const int N = 2e5 + 10;
int lmin[N], lmax[N], rmin[N], rmax[N];
vector<int> p[N];
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    for(int i = 0; i <= n; i++) {
        rmax[i] = rmin[i] = n + 1;
        lmin[i] = lmax[i] = 0;
    }
    for(int i = 0; i <= n; i++) p[i].clear();

    vector<int> stk1, stk2;
    for(int i = n; i >= 1; i--) {
        while(stk1.size() > 0 && a[i] > a[stk1.back()]) {
            int j = stk1.back(); stk1.pop_back();
            lmax[j] = i;
        }
        stk1.push_back(i);

        while(stk2.size() > 0 && a[i] <= a[stk2.back()]) {
            int j = stk2.back(); stk2.pop_back();
            lmin[j] = i;
        }
        stk2.push_back(i);
    } 

    stk1.clear();
    stk2.clear();
    for(int i = 1; i <= n; i++) {
        while(stk1.size() > 0 && a[i] >= a[stk1.back()]) {
            int j = stk1.back(); stk1.pop_back();
            rmax[j] = i;
        }
        stk1.push_back(i);

        while(stk2.size() > 0 && a[i] < a[stk2.back()]) {
            int j = stk2.back(); stk2.pop_back();
            rmin[j] = i;
        }
        stk2.push_back(i);
    }

    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        p[a[i]].push_back(i);
    }
    
    tr.init(n + 5);
    for(int x = 1; x <= n; x++) { //maximum
        int y = k - x;
        if(y < 1 || y > n) continue;  // no such elements
        
        int j = 0;
        for(int pos : p[x]) {
            while(j < p[y].size() && p[y][j] < pos) {
                int l = lmin[p[y][j]] + 1, r = rmin[p[y][j]] - 1;
                int lcnt = p[y][j] - l + 1;
                tr.update(r, lcnt);
                j++;
            }
            
            int l = lmax[pos] + 1, r = rmax[pos] - 1;
            int rcnt = r - pos + 1;
            long long lcnt = tr.query(l - 1, n + 1);
            ans += (rcnt * lcnt);
        }
        
        j--;
        while(j >= 0) {
            int l = lmin[p[y][j]] + 1, r = rmin[p[y][j]] - 1;
            int lcnt = p[y][j] - l + 1;
            tr.update(r, -lcnt);
            j--;
        }
    }

    cout << ans << endl;
}

int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
