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

const int MOD = 998244353;
const int FENWICK_SIZE = 5005;
const int N = 5005;
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
            if(tree[i] >= MOD) tree[i] -= MOD;
            i += (i & -i);
        }
    }

    int pre(int i) {
        int sum = 0;
        while(i > 0){
            sum += tree[i];
            if(sum >= MOD) sum -= MOD;
            i -= ( i & -i);
        }
        return sum;
    }
    int query(int i, int j) {
        return (pre(j + 1) - pre(i) + MOD) % MOD;
    }
} tr[N];

int to[N][N];
int dp[N][N];
int sums[N];
void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i <= n; i++) {
        sums[i] = 0;
        for(int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }

    unordered_map<int, vector<int>> mp;
    for(int i = 0; i < m; i++) {
        int idx, j;
        cin >> idx >> j;
        mp[j - idx].push_back(idx);       
    }

    for(auto it = mp.begin(); it != mp.end(); it++) {
        vector<int>& vec = it -> second;
        sort(vec.begin(), vec.end());
    }
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            //j - i = current
            int t = j - i;
            //find the first t
            if(mp.find(t) == mp.end()) {
                to[i][j] = n;
            } else {
                vector<int>& vec = mp[t];
                int l = 0, r = vec.size() - 1;
                int p = n + 1;
                while(l <= r) {
                    int mid = l + (r - l) / 2;
                    if(vec[mid] < i) {
                        l = mid + 1;
                    } else {
                        p = vec[mid];
                        r = mid - 1;
                    }
                }
                to[i][j] = p - 1;
            }
        }
    }

    /*
         1
       1 2
     1 2 3   
    */
    for(int i = 0; i <= n + 1; i++) {
        tr[i].init(n + 3);
    }
    
    dp[0][0] = 1;
    sums[0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) { //[i : j]
            int sz = j - i + 1;
            if(to[i][1] >= j) { //can replace with 1 2 3 ...
                dp[j][sz] += sums[i - 1];
                dp[j][sz] %= MOD;
                int t = sz + 1;
                dp[j][0] += tr[t].query(i - 1, n + 1);
                dp[j][0] %= MOD;
            } else {
                break;
            }
        }
              
        for(int j = 0; j <= n; j++) {
            sums[i] += dp[i][j];
            sums[i] %= MOD;
        }
        for(int j = 2; j <= n; j++) {
            int s = sums[i - 1] - dp[i - 1][j - 1];
            if(s < 0) s += MOD;
            if(to[i][j] >= i)
                tr[j].update(to[i][j], s);
        }
    }
    cout << sums[n] << endl;
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
