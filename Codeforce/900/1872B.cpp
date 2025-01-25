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
const long long INF = 1e9;


void solve() {
    int n;
    cin >> n;
    int ans = 1e9;
    for(int i = 0; i < n; i++) {
        int d, s;
        cin >> d >> s;
        ans = min(ans, d + (s - 1) / 2);
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
