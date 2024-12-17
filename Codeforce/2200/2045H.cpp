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
const int N = 5050;
int dp[N][N];
pair<int, int> pdp[N][N];
vector<int> p[N];

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    vector<vector<int>> lcp(n, vector<int>(n));
    for(int i = n - 1; i >= 0; i--) {
        for(int j = i; j < n; j++) {
            if(s[i] == s[j]) {
                if(i + 1 < n && j + 1 < n) {
                    lcp[i][j] = 1 + lcp[i + 1][j + 1];
                } else {
                    lcp[i][j] = 1;
                }
            } else {
                lcp[i][j] = 0;
            }
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            pdp[i][j] = {-1, -1};
            dp[i][j] = -1;
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= n; j++) {
            p[j].clear();
        }
        if(i != 0) {
            for(int j = 0; j < i; j++) {
                p[min(lcp[j][i], i - j)].push_back(j);
            }
        }

        int com = 0;
        int curMax = -1, l = -1, r = -1;
        for(int j = i; j < n; j++) {
            if(i == 0) {
                dp[i][j] = 1;
                continue;
            }
            int len = j - i + 1;
            
            for(int index : p[com]) {
                if(dp[index][i - 1] == -1) continue;
                if((index + com == i || s[index + com] < s[i + com])) {
                    if(dp[index][i - 1] > curMax) {
                        curMax = dp[index][i - 1];
                        l = index;
                        r = i - 1;
                    }
                }
            }
            if(curMax != -1 && curMax + 1 > dp[i][j]) {
                dp[i][j] = curMax + 1;
                pdp[i][j] = {l, r};
            }
            com++;
            //[i : j]
        }
    }
    
    /*cout << endl;
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        cout << dp[i][j] << " ";
      } cout << endl;
    }*/
    

    int mx = -1;
    int ci = -1, cj = n - 1;
    for(int i = 0; i < n; i++) {
        if(dp[i][n - 1] > mx) {
            mx = dp[i][n - 1];
            ci = i;
        }
    }
    
    vector<string> ans;
    while(ci != -1 && cj != -1) {
        ans.push_back(s.substr(ci, cj - ci  + 1));
        pair<int, int> p = pdp[ci][cj];
        ci = p.first;
        cj = p.second; 
    }

    cout << ans.size() << endl;
    for(int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i] << endl;
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
