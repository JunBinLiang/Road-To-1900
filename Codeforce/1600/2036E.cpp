#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string.h>

using namespace std;  
//6:30 - 6:42
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> a(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    for(int c = 0; c < m; c++) {
        for(int r = 1; r < n; r++) {
            a[r][c] |= a[r - 1][c];
        }
    }
    
    while(q--) {
        int t;
        cin >> t;
        int L = 0, R = n - 1;
        for(int i = 0; i < t; i++) {
            int c; char op; int val;
            cin >> c >> op >> val; //column operation val
            c--;
            
            //cout << c << " " << op << " " << val << endl; continue;
            if(L == -1 || R == -1) continue;
            if(op == '<') { //less than
                if(a[L][c] >= val) {
                    L = -1; R = -1;
                    continue;
                }
                int l = L; int r = R;
                int p = -1;
                while(l <= r) {
                    int mid = l + (r - l) / 2;
                    if(a[mid][c] >= val) {
                        r = mid - 1;
                    } else {
                        p = mid;
                        l = mid + 1;
                    }
                }
                R = p;
                
            } else { 
                if(a[R][c] <= val) {
                    L = -1; R = -1;
                    continue;
                }
                int l = L; int r = R;
                int p = -1;
                while(l <= r) {
                    int mid = l + (r - l) / 2;
                    if(a[mid][c] <= val) {
                        l = mid + 1;
                    } else {
                        p = mid;
                        r = mid - 1;
                    }
                }
                L = p;
            }

        }
        if(L == -1) cout << -1 << endl;
        else cout << L + 1 << endl;
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
