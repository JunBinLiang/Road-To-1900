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

//11:51 - 11:58
bool same(char c1, char c2) {
    if(c1 == '?' || c2 == '?') return true;
    return c1 == c2;
}

void solve() {
    string s;
    cin >> s;
    vector<vector<bool>> b(s.size() + 1, vector<bool>(s.size())); 
    for(int i = 0; i < s.size(); i++) {
        for(int j = i + 1; j < s.size(); j++) {
            if(same(s[i], s[j])) {
                int len = j - i + 1;
                b[len - 1][i] = true;
                //cout << i << " " << j << " " << len << endl;
            }
        }
    }

    int ans = 0;
    for(int len = 1; len <= s.size(); len++) {
        auto& v = b[len];
        int mx = 0;
        int cnt = 0;
        for(int i = 0; i < v.size(); i++) {
            if(v[i]) cnt++;
            else cnt = 0;
            mx = max(mx, cnt);
        }
        if(mx >= len) ans = max(ans, 2 * len);
    }

    cout << ans << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
