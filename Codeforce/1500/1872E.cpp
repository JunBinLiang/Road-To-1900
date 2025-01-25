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
const long long INF = 1e9;

int get(vector<int>& p, int l, int r) {
    return l == 0 ? p[r] : p[r] ^ p[l - 1];
}

void solve() {
    int n, m;
    cin >> n;
    string s;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    cin >> s;
    cin >> m;
    vector<int> p0(n), p1(n);
    int xo0 = 0, xo1 = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') {
            xo0 ^= a[i];
        } else {
            xo1 ^= a[i];
        }
        p0[i] = xo0;
        p1[i] = xo1;
    }
    
    for(int i = 0; i < m; i++) {
        int op;
        cin >> op;
        if(op == 1) {
            int l, r;
            cin >> l >> r;
            l--; r--;
            xo0 ^= get(p0, l, r);
            xo0 ^= get(p1, l, r);
            xo1 ^= get(p0, l, r);
            xo1 ^= get(p1, l, r);
        } else {
            int t;
            cin >> t;
            if(t == 0) cout << xo0 << " ";
            else cout << xo1 << " ";
        }
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
