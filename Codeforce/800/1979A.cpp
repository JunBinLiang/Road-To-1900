#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
#include<set>
#include<unordered_map>
#include<map>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>
#include <cmath>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];   
    }

    int t = -1;
    for(int i = 0; i < n - 1; i++) {
        int mx = max(a[i], a[i + 1]);
        if(t == -1) t = mx;
        else t = min(t, mx);
    }
    cout << t - 1 << endl;
}   

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
