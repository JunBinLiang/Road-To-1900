#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string.h>

using namespace std;  

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for(int i = 1; i < n; i++) {
        if(abs(a[i] - a[i - 1]) == 5 || abs(a[i] - a[i - 1]) == 7) continue;
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
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
