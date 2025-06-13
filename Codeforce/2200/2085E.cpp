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

bool same(vector<int>& a, vector<int>& b) {
    for(int i = 0; i < a.size(); i++) {
        if(a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool ok(vector<int>& a, vector<int>& b, long long m) {
    vector<int> c;
    for(int i = 0; i < a.size(); i++) {
        c.push_back(a[i] % m);
    }
    sort(c.begin(), c.end());
    return same(c, b);
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    if(same(a, b)) {
        cout << 10000000 << endl;
        return;
    }

    long long s1 = 0, s2 = 0;
    for(int x : a) s1 += x;
    for(int x : b) s2 += x;
    if(s1 < s2) {
        cout << -1 << endl;
        return;
    }

    long long d = s1 - s2;
    for(long long i = 1; i * i <= d; i++) {
        if(d % i != 0) continue;
        long long k = i;
        if(ok(a, b, k)) {
            cout << k << endl;
            return;
        }
        if(d % k == 0) {
            k = d / k;
            if(ok(a, b, k)) {
                cout << k << endl;
                return;
            }
        }
    }
    cout << -1 << endl;
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
