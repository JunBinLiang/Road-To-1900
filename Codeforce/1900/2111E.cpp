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

int find1(map<pair<int, int>, set<int>>& mp, vector<pair<char, char>> vec) {
    int idx = -1;
    vector<int> d;
    for(int i = 0; i < vec.size(); i++) {
        set<int>& s = mp[vec[i]];
        auto it = s.upper_bound(idx);
        if(it == s.end()) {
            return 0;
        }
        idx = *it;
        d.push_back(idx);
    }

    for(int i = 0; i < vec.size(); i++) {
        mp[vec[i]].erase(d[i]);
    }
    return d.size();
}

int find2(map<pair<int, int>, set<int>>& mp, vector<pair<char, char>> vec) {
    int idx = -1;
    vector<int> d;
    for(int i = 0; i < vec.size(); i++) {
        set<int>& s = mp[vec[i]];
        auto it = s.upper_bound(idx);
        if(it == s.end()) {
            break;
        }
        idx = *it;
        d.push_back(idx);
    }

    for(int i = 0; i < d.size(); i++) {
        mp[vec[i]].erase(d[i]);
    }
    return d.size();
}


void solve() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<pair<int, int>> vec;
    for(int i = 0; i < m; i++) {
        char c1, c2;
        cin >> c1 >> c2;
        if(c1 == 'a') continue;
        vec.push_back({c1, c2});
    }

    vector<string> bits = {"00", "01", "10", "11"};
    string ans = s;
    for(int i = 0; i < bits.size(); i++) {
        map<pair<int, int>, set<int>> mp;
        for(int j = 0; j < vec.size(); j++) {
            mp[vec[j]].insert(j);
        }

        int b1 = bits[i][0] - '0', b2 = bits[i][1] - '0';
        string t = "";
        for(char c : s) {
            if(c == 'a') {
                t += c;
            } else {
                if(c == 'b') {
                    if(b1 == 0) { //ba
                        int ok1 = find1(mp, {{'b', 'a'}});
                        if(ok1) {
                            t += 'a';
                        } else {
                            int ok2 = find1(mp, {{'b', 'c'}, {'c', 'a'}});
                            if(ok2) t += 'a';
                            else t += c;
                        }
                    } else { //bc ca
                        int ok1 = find1(mp, {{'b', 'c'}, {'c', 'a'}});
                        if(ok1) {
                            t += 'a';
                        } else {
                            int ok2 = find1(mp, {{'b', 'a'}});
                            if(ok2) t += 'a';
                            else t += c;
                        }
                    }
                } else {
                    if(b2 == 0) { //ca
                        int ok1 = find2(mp, {{'c', 'a'}});
                        if(ok1) {
                            t += 'a';
                        } else {
                            int ok2 = find2(mp, {{'c', 'b'}, {'b', 'a'}});
                            if(ok2 == 2) {
                                t += 'a';
                            } else if(ok2 == 1) {
                                t += 'b';
                            } else {
                                t += c;
                            }
                        }
                    } else { //cb ba
                        int ok1 = find1(mp, {{'c', 'b'}, {'b', 'a'}});
                        if(ok1) {
                            t += 'a';
                        } else {
                            int ok2 = find1(mp, {{'c', 'a'}});
                            if(ok2) {
                                t += 'a';
                            } else {
                                int ok3 = find1(mp, {{'c', 'b'}});
                                if(ok3) t += 'b';
                                else t += c;
                            }
                        }
                    }
                }
            }
        }
        if(t < ans) {
            ans = t;
        }
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
