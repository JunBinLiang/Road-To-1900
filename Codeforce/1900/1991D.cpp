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

const int N = 2e5 + 100;

void solve() {
    int n;
    cin >> n;
    if(n == 1) {
        cout << 1 << endl;
        cout << 1 << endl;
        return;
    }

    if(n == 2) {
        cout << 2 << endl;
        cout << "1 2" << endl;
        return;
    }

    if(n == 3) {
        cout << 2 << endl;
        cout << "1 2 2" << endl;
        return;
    }

    if(n == 4) {
        cout << 3 << endl;
        cout << "1 2 2 3" << endl;
        return;
    }

    if(n == 5) {
        cout << 3 << endl;
        cout << "1 2 2 3 3" << endl;
        return;
    }

    if(n == 6) {
        cout << 4 << endl;
        cout << "1 2 2 3 3 4" << endl;
        return;
    }

    cout << 4 << endl;
    for(int i = 1; i <= n; i++) {
        cout << (i % 4) + 1  << " ";
    }
    cout << endl;
}    


int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    init();
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

