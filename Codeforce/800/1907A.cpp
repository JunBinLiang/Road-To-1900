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

void solve() {
    string s;
    cin >> s;
    
    for(int i = 1; i <= 8; i++) {
        if(s[1] - '0' == i) continue;
        cout << s[0] << i << endl;
    }

    for(char c = 'a'; c <= 'h'; c++) {
        if(c == s[0]) continue;
        cout << c << s[1] << endl;
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
