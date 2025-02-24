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
using ll = long long;

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int N = 3e5 + 100, MOD = 1e9 + 7;
const long long INF = 1e9;
int a[N], b[N];

map<int, int> mps1[N], mps2[N];
int L[N];
long long dps[N], s[N];

void del(map<int, int>& mp, int k) {
    mp[k]--;
    if(mp[k] == 0) {
        mp.erase(k);
    }
}

int getMin(map<int, int>& mp) {
    auto it = mp.begin();
    return it -> first;
}

int getMax(map<int, int>& mp) {
    auto it = mp.end();
    it--;
    return it -> first;
} 

void solve() {
    int n, m;
    cin >> n >> m;
    int mx1 = 0, mx2 = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        mx1 = max(mx1, a[i]);
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
        mx2 = max(mx2, b[i]);
    }

    if(mx2 < mx1) {
        cout << -1 << endl;
        return;
    }

    for(int i = 0; i <= m; i++) {
        s[i] = 0;
        L[i] = 1;
    }

    vector<vector<int>> dp1(n + 1, vector<int>(m + 1, INF));
    vector<vector<long long>> dp2(n + 1, vector<long long>(m + 1, 0));
    
    vector<vector<int>> pdp1(n + 1, vector<int>(m + 1, INF));
    vector<vector<long long>> pdp2(m + 1, vector<long long>(n + 1, 0));
    
    for(int i = 0; i <= m; i++) pdp2[i][0] = 1;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int w = m - j; 
            if(b[j] >= a[i]) {
                s[j] += a[i];
                while(b[j] < s[j]) {
                    int l = L[j];
                    s[j] -= a[l];
                    L[j]++;
                }

                int mn = w;
                if(L[j] == 1) {
                    
                } else {
                    mn += pdp1[L[j] - 1][j];
                }
                dp1[i][j] = mn;
                int l = L[j], r = i;
                int p = -1;
                while(l <= r) {
                    int mid = l + (r - l) / 2;
                    int c = w;
                    if(mid != 1) c += pdp1[mid - 1][j];
                    if(c == mn) {
                        p = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                
                dp2[i][j] = (pdp2[j][p - 1] - (L[j] - 2 >= 0 ? pdp2[j][L[j] - 2] : 0));
                if(dp2[i][j] < 0) dp2[i][j] += MOD;
               // cout << "gg " << i << "  " << j << "   |" << L[j] << "  " << i << "  " << p << endl;
                //cout << mn << endl;
                //cout << dp2[i][j] <<"     |" << p - 1 << "  " << L[j] - 1 << endl;
                //cout << endl;

            } else {
                s[j] = 0;
                L[j] = i + 1;
            }
        }

        long long s = 0;
        for(int j = 1; j <= m; j++) {
            if(pdp1[i][j - 1] >= dp1[i][j]) {
                if(pdp1[i][j - 1] > dp1[i][j]) {
                    pdp1[i][j] = dp1[i][j];
                    s = dp2[i][j];
                } else {
                    pdp1[i][j] = pdp1[i][j - 1];
                    s += dp2[i][j];
                    s %= MOD;
                }
            } else {
                pdp1[i][j] = pdp1[i][j - 1];
            }
            pdp2[j][i] = s;
        }
        
        for(int j = 1; j <= m; j++) {
            pdp2[j][i] += pdp2[j][i - 1];
            pdp2[j][i] %= MOD;
            
        }
    }

    long long w = 0;
    for(int i = 1; i <= m; i++) {
        if(dp1[n][i] == pdp1[n][m]) {
            w += dp2[n][i];
            w %= MOD;
        }
    }

    cout << pdp1[n][m] << " " << w << endl;
}    


int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

