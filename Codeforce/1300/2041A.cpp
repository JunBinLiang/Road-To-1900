#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

void solve() {
    vector<bool> a(6);
    for(int i = 0; i < 4; i++) {
        int x;
        cin >> x;
        a[x] = true;
    } 

    for(int i = 1; i <= 5; i++) {
        if(!a[i]) {
            cout << i << endl;
        }
    }
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
