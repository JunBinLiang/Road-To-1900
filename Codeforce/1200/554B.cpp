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


//2:34 - 2:40

bool check(string& s) {
    for(int i = 0; i < s.size(); i++) if(s[i] == '0') return false;
    return true;
}

int get(vector<string>& a) {
    int cnt = 0;
    for(string& s : a) {
        if(check(s)) cnt++;
    }
    return cnt;
}

void solve() {
    int n, m;
    cin >> n;
    vector<string> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    m = a[0].size();

    int ans = 0;
    for(int i = 0; i < n; i++) { //assume make the ith row as complete
        string& s = a[i];
        vector<int> flip;
        for(int j = 0; j < m; j++) {
            if(s[j] == '0') {
                flip.push_back(j);
            }
        }

        for(int c : flip) {
            for(int r = 0; r < n; r++) {
                if(a[r][c] == '0') a[r][c] = '1';
                else a[r][c] = '0';
            }
        }

        ans = max(ans, get(a));
        //flip back
        for(int c : flip) {
            for(int r = 0; r < n; r++) {
                if(a[r][c] == '0') a[r][c] = '1';
                else a[r][c] = '0';
            }
        }
    }

    cout << ans << endl;
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
