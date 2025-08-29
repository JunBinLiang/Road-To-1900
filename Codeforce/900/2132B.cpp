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


void solve() {
    long long n;
    cin >> n;
    vector<long long> ans;

    long long mul = 10;
    for(int i = 1; i < 19; i++) {
        if(n % (mul + 1) == 0) {
            ans.push_back(n / (mul + 1));
        }
        mul *= 10;
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for(long long x : ans) cout << x << " ";
    if(ans.size() > 0)
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
