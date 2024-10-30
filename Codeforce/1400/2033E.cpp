#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <string.h>


using namespace std;


void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int ans = 0;
    vector<bool> vis(n + 1);
    for(int i = 1; i <= n; i++) {
        if(i == a[i]) continue;
        int index = i;
        int cnt = 0;
        while(!vis[index]) {
            vis[index] = true;
            index = a[index];
            cnt++;
        }
        ans += (cnt - 1) / 2;
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
