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
#include <deque>  

using namespace std;
const int MOD = 1e9 + 7;

void solve() {
    int n, x;
    cin >> n >> x;

    int o = 0;
    for(int i = 0; i < n; i++) {
        o |= i;
    }

    if(o == x) {
        for(int i = 0; i < n; i++) cout << i << " ";
        cout << endl;
    } else {
        o = 0;
        for(int i = 0; i < n - 1; i++) {
            o |= i;
            if(((x | o) == x) && (x & o) == o) { //submask
                cout << i << " ";
            } else {
                cout << x << " ";
            }
        }
        cout << x;
        cout << endl;
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
