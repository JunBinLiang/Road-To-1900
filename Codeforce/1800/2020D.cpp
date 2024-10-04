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
ostream &operator<<(ostream &out, const set<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

//11:35 - 11:55
int find(vector<int>& p, int u) {
    return p[u] == u ? u : p[u] = find(p, p[u]);
}

set<int> sets[11][11];
void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> p(n + 1);
    for(int i = 0; i < p.size(); i++) {
        p[i] = i;
    }

    for(int i = 0; i <= 10; i++) {
        for(int j = 0; j <= 10; j++) {
            sets[i][j].clear();
        }
    }


    for(int i = 1; i <= n; i++) {
        for(int d = 1; d <= 10; d++) {
            sets[d][i % d].insert(i);
        }
    }
    
    //for(int i = 0; i <= 10; i++) cout << sets[i] << endl;

    for(int i = 0; i < m; i++) {
        int x, d, k;
        cin >> x >> d >> k; 
        int m = x % d;
        auto& s = sets[d][m];
        while(true) {
            auto it = s.upper_bound(x);
            if(it == s.end()) break;
            int v = *it;
            if(v > x + d * k) break;
            int r1 = find(p, x), r2 = find(p, v);
            if(r1 == r2) {
                s.erase(v);
            } else {
                s.erase(v);
                p[r2] = p[r1];
            }
        }
    }

    set<int> s;
    for(int i = 1; i <= n; i++) {
        s.insert(find(p, i));
        //cout << i << "  " << find(p, i) << endl;
    }
    cout << s.size() << endl;
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
