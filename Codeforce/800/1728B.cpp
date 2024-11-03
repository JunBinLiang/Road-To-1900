#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include<set>
#include<unordered_map>
#include <string.h>
using namespace std;

//4:24 - 4：30
void solve() {
    int n;
    cin >> n;
    if(n % 2 == 0) {
        for(int i = n - 2; i >= 1; i--) cout << i << " ";
        cout << n - 1 << " " << n << endl;
    } else {
        for(int i = n; i >= 1; i--) {
            if(i == 1 || i == n || i == n - 2) continue;
            cout << i << " ";
        }
        cout << 1 << " " << n - 2 << " " << n << endl;
    }
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
