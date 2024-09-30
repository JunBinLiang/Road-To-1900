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

//1:52 - 2:01
void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(n); 
    vector<int> b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }

    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    vector<int> c;
    for(int i = k; i < n; i++) {
        c.push_back(b[i]);
    }

    for(int i = 0; i < k; i++) {
        c.push_back(b[i]);
    }

    int score = 0;
    for(int i = 0; i < n; i++) {
        if(a[i].first > c[i]) {
            score++;
        }
    }
    if(score != k) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        vector<int> ans(n);
        for(int i = 0; i < n; i++) {
            ans[a[i].second] = c[i];
        }
        for(int x : ans) cout << x << " ";
        cout << endl;
    }
    
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
