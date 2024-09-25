#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
#include<set>
#include<unordered_map>
#include<map>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>
#include <cmath>

using namespace std;
//4:36 - 4:48
void solve() {
    int n;
    string s;
    cin >> n >> s;
    map<char, int> f;
    for(char c : s) {
        f[c]++;
    }

    priority_queue<pair<int, char>> pq;
    for(auto it = f.begin(); it != f.end(); it++) {
        pq.push({it -> second, it -> first});
    }
    string ans = "";
    while(pq.size() > 0) {
        pair<int, char> p = pq.top(); pq.pop();
        ans += p.second;
        p.first--;
        if(p.first) pq.push(p);
    }
    cout << ans << endl;
}   

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
