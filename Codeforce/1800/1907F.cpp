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

pair<int, int> get(vector<int>& a) {
    //4 5 1 2 3
    int n = a.size();
    int i = 1;
    while(i < a.size() && a[i] >= a[i - 1]) { //increase
        i++;
    }
    
    if(i == n) {
        return {0, 0};
    }

    int j = i + 1;
    while(j < a.size() && a[j] >= a[j - 1]) {
        j++;
    }

    if(j != n || a.back() > a[0]) {
        return {-1, -1};
    }

    int cnt1 = i, cnt2 = n - cnt1;
    return {cnt1, cnt2};
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if(n == 1) {
        cout << 0 << endl;
        return;
    }

    int ans = 1e9;

    pair<int, int> p1 = get(a);
    reverse(a.begin(), a.end());
    pair<int, int> p2 = get(a);

    if(p1.first != -1) {
        int cnt1 = p1.first, cnt2 = p1.second;
        ans = min(ans, cnt2);
        ans = min(ans, 1 + cnt1 + 1);
    }

    if(p2.first != -1) { //reverse
        int cnt1 = p2.first, cnt2 = p2.second;
        ans = min(ans, 1 + cnt2);
        ans = min(ans, 1 + cnt1);
    }
    
    if(ans == 1e9) cout << -1 << endl;
    else cout << ans << endl;
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
