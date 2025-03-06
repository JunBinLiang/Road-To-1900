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
const int MOD = 1e9 + 7;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    

    int ans = 0, l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        int g1 = 0, g2 = 0;
        for(int j = i + 1; j <= n; j++) {;
            if(a[j] > a[i]) {
                g1++;
            } else if(a[j] < a[i]) {
                g2++;
            }

            int cnt = g2 -g1;
            if(cnt > ans) {
                ans = cnt;
                l = i;
                r = j;
            }
        }
    }

    cout << l << " " << r << endl;
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
