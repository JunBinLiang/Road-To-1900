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
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> ans(n);

    for(int i = 0; i < n; i++) {
        ans[i] = i % 2;
    }
    x--;
    y--;
    if(n % 2 == 1) ans[n - 1] = 2;
    
    if(n % 2 == 1) {
        ans[y] = 2;
        if(y % 2 == 0) {
            for(int i = 0; i < n; i++) {
                if(i < y) {
                    ans[i] = (i + 1) % 2;
                } else if(i > y) {
                    ans[i] = (i) % 2;
                }
            }
        } else {
            for(int i = 0; i < n; i++) {
                if(i < y) {
                    ans[i] = i % 2;
                } else if(i > y) {
                    ans[i] = (i + 1) % 2;
                }
            }
        }
    } else {
        if(ans[x] == ans[y]) {
            if(x + 2 == y && y == n - 1) {
                ans[x] = 2;
            }
            else {
                ans[y] = 2;
            }
        }
    }

    //1 0 1 2 0 1 0
    //0 1 0 1 0(2) 1 0 1 0 

    //0 1 0 1 0 1         
    //0 1 0 1
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " ";
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
