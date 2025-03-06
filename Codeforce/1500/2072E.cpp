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
    int k;
    cin >> k;
    int x = 0, y = 0;
    vector<pair<int, int>> ans;
    while(k) {
        int p = -1;
        for(int i = 1; i <= 500; i++) {
            if((i - 1) * i / 2 <= k) {
                p = i;
            } else {
                break;
            }
        }
        for(int i = 0; i < p; i++) {
            ans.push_back({x, y});
            y++;
        }
        x++;
        k -= ((p - 1) * p / 2);
    }
    cout << ans.size() << endl;
    for(auto p : ans) cout << p.first << " " << p.second << endl;
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
