#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string.h>
#include <random>
#include <chrono>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)

const int N = 52;
long long f[N];
void solve() {
    int n;
    long long k;
    cin >> n >> k;

    f[0] = 0;
    f[1] = 1;
    f[2] = 2;
    for(int i = 3; i < N; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    
    for(int i = 1; i <= n; i++) {
        int t = n - i + 1;
        if(t == 1) {
            cout << i << " ";
            break;
        }
        if(k > f[t - 1]) {
            cout << i + 1 << " " << i << " ";
            k -= f[t - 1]; 
            i++;
        } else {
            cout << i << " ";
        }
    } 
    cout << endl;
}

int main(){
    int t = 1;
    //cin >> t;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    while(t--) {
        solve();
    }
    return 0;
}
