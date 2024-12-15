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
    cin >> n;
    long long ans = 1;
    while(n) {
        int d = n % 10;
        n /= 10;
        int cnt = 0;
        for(int i = 0; i <= d; i++) {
            for(int j = 0; j <= d; j++) {
                for(int k = 0; k <= d; k++) {
                    if(i + j + k == d) {
                        cnt++;
                    }
                }
            }
        }
        ans *= cnt;
    }
    cout << ans << endl;
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
