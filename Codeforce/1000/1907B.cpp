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

bool isL(char c) {
    int d = c - 'a';
    return d >= 0 && d < 26;
}

void solve() {
    string s;
    cin >> s;
    vector<int> lo, up;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'b') {
            if(lo.size() > 0) lo.pop_back();
        } else if(s[i] == 'B') {
            if(up.size() > 0) up.pop_back();
        } else {
            if(isL(s[i])) lo.push_back(i);
            else up.push_back(i);
        }
    }

    vector<int> a;
    for(int i : lo) a.push_back(i);
    for(int i : up) a.push_back(i);
    sort(a.begin(), a.end());
    string ans = "";
    for(int i : a) {
        ans += s[i];
    }
    cout << ans << endl;
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
