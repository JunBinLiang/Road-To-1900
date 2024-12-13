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


bool ok(vector<string>& a) {
    int n = a.size(), m = a[0].size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '.') {
                return false;
            }
        }
    }
    return true;
}

vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int n, m;
bool in(int r, int c) {
    if(r < 0 || r >= n || c < 0 || c >= m) return false;
    return true;
}

void solve() {
    cin >> n >> m;
    vector<string> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for(int i = 0; i < n; i++) {
        int idx = 0;
        for(int j = 0; j < m - 1; j++) {
            vector<char> s = {'1' + i % 3 * 2, '2' + + i % 3 * 2};
            if(a[i][j] == '.' && a[i][j + 1] == '.') {
                a[i][j] = a[i][j + 1] = s[(idx % 2)];
                idx++;
            }
        }
    }
    
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '.' && a[i + 1][j] == '.') {
                set<char> s = {'7', '8', '9'};
                if(in(i - 1, j)) s.erase(a[i - 1][j]);
                if(in(i + 1, j)) s.erase(a[i + 1][j]);
                if(in(i, j - 1)) s.erase(a[i][j - 1]);
                if(in(i, j + 1)) s.erase(a[i][j + 1]);
                if(in(i + 1, j - 1)) s.erase(a[i + 1][j - 1]);
                if(in(i + 1, j + 1)) s.erase(a[i + 1][j + 1]);
                auto it = s.begin();
                char c = *it;
                a[i][j] = a[i + 1][j] = c;
            }
        }
    }
    

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '.') {
                for(auto d : dir) {
                    int r = i + d[0], c = j + d[1];
                    if(r < 0 || r >= n || c < 0 || c >= m) continue;
                    if(a[r][c] != '.' && a[r][c] != '#') {
                        a[i][j] = a[r][c];
                        break;
                    }
                }
            }
        }
    }

    if(!ok(a)) {
        cout << -1 << endl;
        return;
    }

    //ok
    for(string& s : a) {
        cout << s << endl;
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
