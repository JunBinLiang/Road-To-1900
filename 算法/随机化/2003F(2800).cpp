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
using ll = long long;
const int N = 3010;

unsigned long long seed = 131;
unsigned long long rands(){ return seed = (seed << 15) + (seed << 8) + (seed >> 3);}

struct BIT {
	int c[3010];
	  int n;
	  inline void init() {
	    n = 3005;
	    for(int i = 0; i < N; i++) c[i] = -1e9;
	  }
	
	  inline void update(int x, int d) {
	      x++;
		    for (int i = x; i <= n; i += (i & (-i))) {
  			    c[i] = max(c[i], d);
		    }
	  }
	
	  inline int query(int x) {
	      x++;
		    int res = -1e9;
		    for (int i = x; i; i -= (i & (-i))) {
			    res = max(res, c[i]);
		    }
		    return res;
	  }
} T[32];

int rnd[N];
int dp[N][32];
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n), c(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    for(int i = 0; i < n; i++) cin >> c[i];

    int t = 300;
    int ans = -1;
    while(t--) {
        for(int i = 0; i <= n; i++) {
            rnd[i] = rands() % m;
        }

        for(int i = 0; i <= n; i++) {
            for(int st = 0; st < (1 << m); st++) {
                dp[i][st] = -1;
            }
        }

        for(int st = 0; st < (1 << m); st++) {
            T[st].init();
        }
        T[0].update(1, 0);
        for(int i = 0; i < n; i++) {
            int bit = rnd[b[i]];
            for(int st = 0; st < (1 << m); st++) {
                if((st & (1 << bit)) == 0) continue;
                int pst = st ^ (1 << bit);
                int val = T[pst].query(a[i]);
                if(val >= 0) {
                    T[st].update(a[i], val + c[i]);
                }
            }
        }
        ans = max(ans, T[(1 << m) - 1].query(n));
    }
    cout << ans << endl;
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
