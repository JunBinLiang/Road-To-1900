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
using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    reverse(a.begin(), a.end());
    int ans = 0;
    for(int i = 0; i < n; i++) {
        if(a[i]) {
            ans++;
        }
    }

    int pos = -1;
    for(int i = 0; i < n; i++) {
        if(!a[i]) {
            pos = i;
        }
    }

    if(pos == -1) {
        cout << ans << endl;
        return;
    }
    

    set<int> s;
    for(int i = 0; i <= n + 10; i++) {
        s.insert(i);
    }

    for(int i = 0; i < n; i++) {
        if(i <= pos) {
            s.erase(a[i]);
        } else {
            if(a[i] == 0) continue;
            int mex = *(s.begin());
            if(a[i] < mex) {
                cout << ans << endl;
                return;
            }
            if(s.find(a[i]) != s.end()) {
                s.erase(a[i]);
            }
        }
    }
    cout << ans + 1 << endl;
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

