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

const int N = 5050;
int dp[N][N];
int p1[N][N], p2[N][N];

int dfs(vector<int>& b, int i, int stren) {
    if(i >= b.size()) {
        return 0;
    }
    if(dp[i][stren] != -1) {
        return dp[i][stren];
    }

    int intel = i - stren;
    int add1 = p1[i][intel] + p2[i][stren + 1];
    int add2 = p1[i][intel + 1] + p2[i][stren];
    
    int ans = 0;
    ans = max(ans, add1 + dfs(b, i + 1, stren + 1));
    ans = max(ans, add2 + dfs(b, i + 1, stren));
    return dp[i][stren] = ans;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    memset(dp, -1, sizeof dp);
    memset(p1, 0, sizeof p1);
    memset(p2, 0, sizeof p2);

    vector<int> b;
    for(int i = 0; i < n; i++) {
        if(a[i] == 0) {
            b.push_back(i);
        }
    }

    // > 0 intel
    // < 0 strength
    int index = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] == 0) {
            int j = i + 1;
            while(j < n && a[j] != 0) {
                if(a[j] > 0) p1[index][a[j]]++;
                else p2[index][-a[j]]++;
                j++;
            }

            for(int x = 1; x <= k; x++) {
                p1[index][x] += p1[index][x - 1];
                p2[index][x] += p2[index][x - 1];
            }
            i = j - 1;
            index++;
        }
    }

    int ans = dfs(b, 0, 0);
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

