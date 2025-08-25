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
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }

    if(a.back() != b[0]) {
        cout << "NO" << endl;
        return;
    }

    int g = b[0];

    for(int i = 1; i < n; i++) {
        if(a[i] > a[i - 1]) {
            cout << "NO" << endl;
            return;
        }
        if(a[i - 1] % a[i] != 0) {
            cout << "NO" << endl;
            return;
        }
    }

    for(int i = n - 2; i >= 0; i--) {
        if(b[i] > b[i + 1]) {
            cout << "NO" << endl;
            return;
        }
        if(b[i + 1] % b[i] != 0) {
            cout << "NO" << endl;
            return;
        }
    }

    for(int i = 0; i < n - 1; i++) {
        if(g != __gcd(a[i], b[i + 1])) {
            cout << "NO" << endl;
            return;
        }
    }

    cout << "YES" << endl;
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
