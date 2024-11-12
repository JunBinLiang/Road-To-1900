#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <string.h>

using namespace std;  

//4:30 - 4:46
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    int ans = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for(int i = 1; i <= n; i++) {
        if(n % i != 0) continue;
        if(i == n) {
            ans++;
            continue;
        }

        if(i == 1) {
            vector<int> b(a.begin(), a.end());
            sort(b.begin(), b.end());
            
            int g = b[1] - b[0];
            for(int j = 2; j < n; j++) {
                g = __gcd(g, b[j] - b[j - 1]);
            }
            if(g > 1 || g == 0) {
                ans++;
            }
            continue;
        }

        vector<bool> vis(n);
        int g = -1;
        bool ok = true;
        for(int j = 0; j < n; j++) {
            if(vis[j]) continue;
            vector<int> b;
            int x = j;
            while(x < n) {
                vis[x] = true;
                b.push_back(a[x]);
                x += i;
            }
            sort(b.begin(), b.end());
            int cg = b[1] - b[0];
            for(int j = 1; j < b.size(); j++) {
                cg = __gcd(cg, b[j] - b[j - 1]);
            }

            if(g == -1) {
                g = cg;
            } else if(g != cg) {
                g = __gcd(g, cg);
            }
        }
        //cout << i << " " << g << endl;
        if(g > 1 || g == 0) {
            ans++;
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
