#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    
#include <deque>  

using namespace std;

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;


void solve() {
    int n;
    cin >> n;
    long long ans1 = 0, ans2 = 0, s = 0;
    deque<int> q;
    int d = 0;
    for(int i = 0; i < n; i++) {
        int op;
        cin >> op;
        int sz = q.size();
        if(op == 3) { //append
            int x; cin >> x;
            if(d == 0) {
                q.push_back(x);
                ans1 += ((q.size() + 0ll) * x);
                ans2 += x;
                ans2 += s;
            } else {
                q.push_front(x);
                ans2 += ((q.size() + 0ll) * x);
                ans1 += x;
                ans1 += s;
            }
            s += x;
        } else if(op == 2) { //reverse
            d ^= 1;
        } else { //cyclic shift  [n 1 2 3 4 5 6 7 ...]
            if(d == 0) {
                int x = q.back(); 
                ans1 -= ((x + 0ll) * q.size());
                ans2 -= s;
                q.pop_back();

                q.push_front(x);
                ans1 += s;
                ans2 += ((q.size() + 0ll) * x);
            } else {
                int x = q.front();
                ans2 -= ((x + 0ll) * q.size());
                ans1 -= s;
                q.pop_front(); 
                q.push_back(x);
                ans2 += s;
                ans1 += ((q.size() + 0ll) * x);
            }
        }
        if(d == 0) cout << ans1 << endl;
        else cout << ans2 << endl;
    }
}


int main() {
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
