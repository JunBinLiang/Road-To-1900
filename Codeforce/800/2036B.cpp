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
    int n, k;
    cin >> n >> k;
    map<int, long long> mp;
    for(int i = 0; i < k; i++) {
        int ty, w;
        cin >> ty >> w;
        mp[ty] += w;
    }

    vector<long long> a;
    for(auto it = mp.begin(); it != mp.end(); it++) {
        a.push_back(it -> second);
    }

    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    long long ans = 0;
    for(int i = 0; i < min(n, (int)(a.size())); i++) {
        ans += a[i];
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
