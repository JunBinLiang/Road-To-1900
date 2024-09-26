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

//5:08 - 5:41
void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }

    long long s = 0;
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        s += abs(a[i] - b[i]);
        ans = max(ans, s);
    }

    /*
    |a - b| + |c - d|
    -a + b + c - d 
    -a + b - c + d  
    a - b + c - d   
    a - b - c + d


    swap
    -a + d + c - b 
    -a + d - c + b  
    a - d + c - b  
    a - d - c + b
    */

    //Do swap
    long long INF = 10000000000000000ll;
    vector<long long> dp(4, -INF);
    for(int i = 0; i < n; i++) {
        long long d2 = b[i] * 2;
        vector<long long> vec = {a[i] + b[i], -a[i] + b[i], a[i] - b[i], -a[i] - b[i]};
        if(i > 0) {
            long long cur = s - abs(a[i] - b[i]);
            for(int j = 0; j < 4; j++) {
                ans = max(ans, cur + vec[j] + dp[j]);
            }
            
        }
        long long sub = abs(a[i] - b[i]);
        dp[0] = max(dp[0], vec[3] - sub);
        dp[1] = max(dp[1], vec[1] - sub);
        dp[2] = max(dp[2], vec[2] - sub);
        dp[3] = max(dp[3], vec[0] - sub);
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
