#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

void solve() {
    int n;
    cin >> n;
    if(n <= 4) {
        cout << -1 << endl;
        return;
    }

    for(int i = 1; i <= n; i += 2) {
        if(i == 5) continue;
        cout << i << " ";
    }
    cout << 5 << " " << 4 << " ";
    for(int i = 2; i <= n; i += 2) {
        if(i == 4) continue;
        cout << i << " ";
    }
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

