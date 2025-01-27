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
using ll = long long;

void solve() {
    int l, r;
    cin >> l >> r;
    
    for(int i = l; i <= min(l + 5, r); i++) {
        if(i % 2 == 0) {
            int x = i / 2;
            if(x > 1) {
                cout << x << " " << x << endl;
                return;
            }
        }
    }

    if((l == 1 && r == 1) || (l == 1 && r == 2) || (l == 1 && r == 3) || (l == 2 && r == 2) || (l == 2 && r == 3) || (l == 3 && r == 3)) {
        cout << -1 << endl;
        return;
    }

    //odd number
    for(int i = 2; i * i <= l; i++) {
        if(l % i == 0) {
            int g = l / i;
            cout << g << " " << l - g << endl;
            return;
        }
    }
    cout << -1 << endl;
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

