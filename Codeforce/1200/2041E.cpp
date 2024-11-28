#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>

using namespace std;

void solve() {
    int a, b;
    cin >> a >> b;
    //Mean : a
    //Median : b
    if(a == b) {
        cout << 1 << endl;
        cout << a << endl;
        return;
    }

    vector<int> ans;
    ans.push_back(a);

    int dif = abs(b - a);
    if(b > a) {
        ans.push_back(b + dif);
        ans.push_back(a - 10 * dif);
        ans.push_back(a + 8 * dif);

    } else {
        ans.push_back(b - dif);
        ans.push_back(a + 10 * dif);
        ans.push_back(a - 8 * dif);
    }

    cout << ans.size() << endl;
    for(int x : ans) cout << x << " ";
    cout << endl; 
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
