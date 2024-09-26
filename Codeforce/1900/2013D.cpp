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

//3:42
long long cal(long long sum, int cnt) {
    return sum / cnt;
}

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    vector<pair<long long, int>> stk;
    for(int i = 0; i < n; i++) {
        long long curSum = a[i];
        int cnt = 1;
        while(stk.size() > 0 &&  cal(curSum, cnt) < stk.back().first) {
            pair<long long, int> p = stk.back(); stk.pop_back();
            curSum += (p.first * p.second);
            cnt += p.second;
        }

        long long avg = curSum / cnt;
        int m = curSum % cnt;

        stk.push_back({avg, cnt - m});
        if(m > 0) {
            stk.push_back({avg + 1, m});
        }
    }
    cout << stk.back().first - stk[0].first << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
