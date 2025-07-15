#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    
#include <deque>  

using namespace std;

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

const int N = 1e5 + 10;

void solve() {
    int n;
    cin >> n;
    vector<int> ans(n + 1);
    vector<bool> bad(n + 1, true);
    ans[1] = 1;

    for(int i = 2; i <= n; i++) {
        ans[i] = i; //no swap
        bool done = false;
        for(int j = 2; j * j <= i && !done; j++) {
            if(i % j != 0) continue;
            if(bad[j] && !done) {
                swap(ans[j], ans[i]);
                bad[j] = false;
                bad[i] = false;
                done = true;
            } 
            if(bad[i / j] && !done) {
                swap(ans[i], ans[i / j]);
                bad[i / j] = false;
                bad[i] = false;
                done = true;
            }
        }

        if(!done) { //not doing swap
            for(int j = 2; j * j <= i; j++) {
                if(i % j != 0) continue;
                swap(ans[j], ans[i]);
                break;
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}


int main() {
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
