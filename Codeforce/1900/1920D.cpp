#include <bits/stdc++.h>
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

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

template <typename T>
ostream &operator<<(ostream &out, const set<T> &a) {
  out << "[";
  bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;}
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}


//11:55 - 12:30
const long long INF = 1000000000000000000ll;

int find(vector<pair<long long, int>>& a, set<pair<long long, int>>& s, long long k) {
    auto it = s.upper_bound({k, 2000000000});
    if(it == s.end()) {
        it--;
        pair<long long, int> p = *it; //last
        int more = k - p.first;
        return a[p.second + more].second;
    } else {
        pair<long long, int> p = *it; //last
        int index = p.second;
        long long oldk = k;
        k = k % a[index - 1].first;
        if(k == 0) k += a[index - 1].first;
        if(oldk == k) {
            it--;
            p = *it;
            index = p.second;
            int more = k - p.first;
            return a[p.second + more].second;
        } else {
            return find(a, s, k);
        }

    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<long long, int>> a;
    a.push_back({0ll, 0});
    set<pair<long long, int>> s;
    s.insert({0, 0});
    for(int i = 0; i < n; i++) {
        int op, x;
        cin >> op >> x;
        if(a.back().first > INF) continue; //FULL
        if(op == 1) { //append
            a.push_back({a.back().first + 1, x});
        } else { //duplicate
            long long sz = a.back().first;
            x++;
            //x * sz > INF
            long long newsz = 0;
            if(INF / x < sz) {
                newsz = INF + 10;
            } else {
                newsz = sz * x;
            }
            a.push_back({newsz, a.back().second});
            s.insert({newsz, a.size() - 1});
        }
    }
    s.insert({INF + 10, a.size()});

    for(int i = 0; i < m; i++) {
        long long k;
        cin >> k;
        int ans = find(a, s, k);
        cout << ans << " ";
    }
    cout << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
