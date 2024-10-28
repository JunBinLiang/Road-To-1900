#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <string.h>


using namespace std;  

void solve() {
    int n, k, d;
    cin >> n >> k >> d;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    map<int, int> mp;
    int ans = k;
    for(int i = 0; i < n; i++) {
        mp[a[i]]++;
        if(i + 1 >= d) {
            ans = min(ans, (int)(mp.size()));
            mp[a[i - d + 1]]--;
            if(mp[a[i - d + 1]] == 0) mp.erase(a[i - d + 1]);
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
