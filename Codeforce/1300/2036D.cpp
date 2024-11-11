#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <string.h>

using namespace std;  

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < m; j++) {
            a[i][j] = s[j] - '0';
        }
    }

    int ans = 0;
    vector<vector<bool>> vis(n, vector<bool>(m));
    vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(vis[i][j]) continue;

            vector<int> b;
            int r = i, c = j;
            int index = 0;
            while(index < 4) {
                if(!vis[r][c]) {
                    vis[r][c] = true;
                    b.push_back(a[r][c]);
                }

                int newr = r + dir[index][0], newc = c + dir[index][1];
                if(newr < 0 || newr >= n || newc < 0 || newc >= m || vis[newr][newc]) {
                    index++;
                } else {
                    r = newr;
                    c = newc;
                }
            }
            
            //for(int x : b) cout << x << " ";
            //cout << endl;

            for(int k = 0; k < b.size(); k++) {
                if(b[k] == 1 && b[(k + 1) % b.size()] == 5 && b[(k + 2) % b.size()] == 4 && b[(k + 3) % b.size()] == 3) {
                    ans++;
                }
            }
        }
    }
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
