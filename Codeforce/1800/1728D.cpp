#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include<set>
#include<unordered_set>
#include <string.h>


using namespace std;

//8:45 - 9:21
const int N = 2010;
pair<int, int> dp[N][N];
pair<int, int> dfs(string& s, int l, int r) { //0 : draw, 1 : win  2: lost
    if(l + 1 == r) {
        if(s[l] == s[r]) {
            return {0, s[l]};
        } else {
            //Alice win
            return {1, min(s[l], s[r])};
        }
    }
    if(dp[l][r].first != -1) return dp[l][r];
    pair<int, int> ans;

    int taken = s.size() - (r - l + 1);
    pair<int, int> p1 = dfs(s, l + 1, r);
    pair<int, int> p2 = dfs(s, l, r - 1);
    if(taken % 2 == 0) { //alice
        if(p1.first == 2 || p2.first == 2) {
            ans = {1, s[l]}; //chosse any
        } else if(p1.first == 1 && p2.first == 1) { //Bob both win
            ans = {2, s[l]};
        } else if(p1.first == 1) {
            if(s[r] == p2.second) {
                ans = {0, s[r]};
            } else if(s[r] < p2.second) {
                ans = {1, s[r]};
            } else if(s[r] > p2.second) {
                ans = {2, s[r]};
            }
        } else if(p2.first == 1) {
            if(s[l] == p2.second) {
                ans = {0, s[l]};
            } else if(s[l] < p2.second) {
                ans = {1, s[l]};
            } else if(s[l] > p2.second) {
                ans = {2, s[l]};
            }
        } else {
            if(s[l] < p1.second) {
                ans = {1, s[l]};
            } else if(s[r] < p2.second) {
                ans = {1, s[r]};
            } else if(s[l] == p1.second) {
                ans = {0, s[l]};
            } else if(s[r] == p2.second) {
                ans = {0, s[r]};
            } else {
                ans = {2, s[r]};
            }
        }
    } else { //bob
        if(p1.first == 2 || p2.first == 2) { //A lost
            ans = {1, s[l]}; //chosse any
        } else if(p1.first == 1 && p2.first == 1) { //Alice both win
            ans = {2, s[l]};
        } else if(p1.first == 1) {
            ans = {0, s[r]};
        } else if(p2.first == 1) {
            ans = {0, s[l]};
        } else if(p1.first == 0 && p2.first == 0) {
            ans = {0, min(s[l], s[r])};
        }
    }
    return dp[l][r] = ans;
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            dp[i][j] = {-1, -1};
        }
    }

    pair<int, int> ans = dfs(s, 0, s.size() - 1);
    if(ans.first == 0) cout << "Draw" << endl;
    else if(ans.first == 1) cout << "Alice" << endl;
    else cout << "Bob" << endl;
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
