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
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> L(n), R(n + 1);
    for(int i = 0; i < n; i++) {
        L[i] = a[i];
        if(i) L[i] = max(L[i], L[i - 1]);
    }

    for(int i = n - 1; i >= 0; i--) {
        R[i] = a[i];
        if(i + 1 < n) R[i] = min(R[i], R[i + 1]);
    }
    R[n] = 2e9;

    vector<int> ans(n);
    for(int i = 0; i < n; i++) {
        int j = i;
        while(j < n) {
            if(L[j] > R[j + 1]) {
                j++;
            } else {
                break;
            }
        }
        for(int k = i; k <= j; k++) {
            ans[k] = L[j];
        }
        i = j;
    }

    for(int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
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
