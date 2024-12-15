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

void solve() {
    int n;
    string s;
    cin >> n >> s;
    vector<int> cnt(26);
    int mx = 0;
    for(char c : s) {
        cnt[c - 'a']++;
        mx = max(mx, cnt[c - 'a']);
    }

    if(mx <= (n - mx)) {
        cout << n % 2 << endl;
    } else {
        cout << mx - (n - mx) << endl;
    }
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
