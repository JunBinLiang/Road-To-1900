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

//2:00 - 2:17
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    map<int, int> p;
    vector<int> connect(n + 1, 0);
    vector<int> dp(n + 1, 0);
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(p.find(a[i]) != p.end()) {
            connect[i] = (-i + 1) + dp[i - 1];
            //if(i == 3) cout << "gg " << (i + p[a[i]]) << endl;
            dp[i] = i + p[a[i]];
            p[a[i]] = max(p[a[i]], connect[i]);
        } else {
            connect[i] = (-i + 1) + dp[i - 1];
            p[a[i]] = connect[i];
        }
        dp[i] = max(dp[i], dp[i - 1]);
        //cout << dp << endl;
    }
    cout << dp.back() << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
