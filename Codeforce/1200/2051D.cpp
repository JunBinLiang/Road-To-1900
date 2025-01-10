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

long long cal(vector<int>& a, long long x) {
    int n = a.size();
    int l = 0, r = a.size() - 1;
    int ans = 0;
    while(l < r) {
        if(a[l] + a[r] >= x) {
            ans += (r - l);
            r--;
        } else {
            l++;
        }
    }
    return ans;
}

void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> a(n);
    long long sum = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    sort(a.begin(), a.end());
    cout << cal(a, sum - y) - cal(a, sum - (x - 1)) << endl;
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
