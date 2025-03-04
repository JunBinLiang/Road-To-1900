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
vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    set<int> all;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
            all.insert(a[i][j]);
        }
    }   

    set<int> s;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(auto& d : dir) {
                int newi = i + d[0], newj = j + d[1];
                if(newi < 0 || newi >= n || newj < 0 || newj >= m) continue;
                if(a[i][j] == a[newi][newj]) {
                    s.insert(a[i][j]);
                }
            }
        }
    }

    int ans = (all.size() - s.size()) + (s.size() * 2);
    if(s.size() > 0) ans -= 2;
    else ans -= 1;
    cout << ans << endl;
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
