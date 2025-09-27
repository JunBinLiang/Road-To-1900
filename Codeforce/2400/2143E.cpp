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

bool ok(string& s) {
    int cnt = 0;
    for(char c : s) {
        if(c == '(') cnt++;
        else {
            if(cnt == 0) return false;
            cnt--;
        }
    }
    if(cnt != 0) return false;
    return true;
}

void solve() {
    int n; string s;
    cin >> n >> s;
    if(n % 2 == 1) {
        cout << -1 << endl;
        return;
    }

    int open = 0;
    for(char c : s) {
        if(c == '(') {
            open++;
        }
    }

    vector<pair<char, int>> a;
    for(int i = 0; i < n; i++) {
        int j = i;
        while(j < n && s[i] == s[j]) {
            j++;
        }
        a.push_back({s[i], j - i});
        //cout << s[i] << "  " << j - i << endl;
        i = j - 1;
    }

    int tot = 0;
    vector<char> stk;
    for(int i = 0; i < a.size(); i++) {
        char c = a[i].first, cnt = a[i].second;
        if(cnt % 2 == 1) {
            if(stk.size() > 0 && c == stk.back()) {
                tot += 2;
                stk.pop_back();
            } else {
                stk.push_back(c);
            }
            tot += (cnt - 1);
        } else {
            tot += cnt;
        }
    }
    
    if(tot % 4 != 0) {
        cout << -1 << endl;
        return;
    }

    string ans = "";
    for(int i = 0; i < tot / 2; i++) ans += "(";
    for(char c : stk) ans += c;
    for(int i = 0; i < tot / 2; i++) ans += ")";
    if(!ok(ans)) {
        cout << -1 << endl;
        return;
    }
    cout << ans << endl;
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
