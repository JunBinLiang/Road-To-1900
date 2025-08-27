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


const int N = 7e6 + 10;
bool is[N];
vector<int> p;
void init() {
    memset(is, 0, sizeof is);
    for(int i = 2; i < N; i++) {
        if(is[i]) continue;
        p.push_back(i);
        for(int j = i; j < N; j += i) {
            is[j] = true;
        }
    }
    //cout << p.size() << endl;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());

    long long s1 = 0, s2;
    int t = 0;
    for(int i = 0; i < n; i++) {
        s1 += a[i];
        s2 += p[i];
        if(s1 >= s2) {
            t = i + 1;
        } else {
            break;
        }
    }
    cout << n - t << endl;

}


int main() {
    init();
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
