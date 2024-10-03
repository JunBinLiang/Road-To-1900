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

//7:47 - 7:53
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<long long> l(n + 1), r(n + 1);
    for(int i = 2; i <= n; i++) {
        if(a[i - 1] > a[i]) {
            l[i] = a[i - 1] - a[i];
        }
        l[i] += l[i - 1];
    }
    for(int i = n - 1; i >= 1; i--) {
        if(a[i + 1] > a[i]) {
            r[i] = a[i + 1] - a[i];
        }
        r[i] += r[i + 1];
    }
    //cout << a << endl;
    //cout << l << endl;
    //cout << r << endl;

    for(int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;

        if(x < y) { //2 -> 4
            cout << l[y] - l[x] << endl;
        } else {
            cout << r[y] - r[x] << endl;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
