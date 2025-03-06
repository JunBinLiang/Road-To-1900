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

const int N = 1e6 + 10;
int p[N];

int C(int n, int c) {
    //cout << n << " " << c << endl;
    int c1 = p[c];
    int c2 = p[n] - p[n - c];
    return c2 - c1;
}

void solve() {
    int n, x;
    cin >> n >> x;

    p[0] = 0;
    for(int i = 1; i <= n; i++) {
        int v = i;
        p[i] = 0;
        while(v % 2 == 0) {
            p[i]++;
            v /= 2;
        }
        p[i] += p[i - 1];
    }

    for(int i = 0; i < n; i++) {
        if(i == 0 || i == n - 1) cout << x << " ";
        else {
            //C(n - 1, i)
            int c = C(n - 1, i);
            if(c) cout << 0 << " ";
            else cout << x << " ";
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
