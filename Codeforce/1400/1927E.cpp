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

void check(vector<int>& a, int k) {
    int s = 0;
    int mx = 0, mn = 1e9;
    for(int i = 0; i < a.size(); i++) {
        s += a[i];
        if(i + 1 >= k) {
            mx = max(mx, s);
            mn = min(mn, s);
            s -= a[i - k + 1];
        }
    }
    cout << mx - mn << endl;
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> ans(n);
    int l = 1, r = n;
    for(int i = 0; i < k; i++) {
        if(i % 2 == 0) { //add
            int j = i;
            while(j < n) {
                ans[j] = l++;
                j += k;
            }
        } else { //del
            int j = i;
            while(j < n) {
                ans[j] = r--;
                j += k;
            }
        }
    }

    for(int x : ans) cout << x << " ";
    cout << endl;

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
