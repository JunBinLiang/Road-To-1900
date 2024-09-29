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

//11:22 - 11:32
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> b(n + 1);
    vector<int> c(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i] + i;
        c[i] = a[i] - i;
    }

    int ans = 0;
    vector<int> ldp(n + 1);
    for(int i = 1; i <= n; i++) {
        ldp[i] = b[i];
        if(i > 1) ldp[i] = max(ldp[i], ldp[i - 1]);
    }
    vector<int> rdp(n + 1);
    for(int i = n; i >= 1; i--) {
        rdp[i] = c[i];
        if(i + 1 <= n) rdp[i] = max(rdp[i], rdp[i + 1]);
    }
    
    //cout << b << endl;
    //cout << ldp << endl << endl;
    //cout << c << endl;
    //cout << rdp << endl;

    for(int i = 2; i <= n - 1; i++) {
        ans = max(ans, a[i] + ldp[i - 1] + rdp[i + 1]);
        //cout <<i << "    |" <<  a[i] << " " << ldp[i - 1] << " " << rdp[i + 1] << endl;
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
