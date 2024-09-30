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

//4:32 - 4:45
void solve() {
    long long n;
    cin >> n;

    vector<long long> f(16);
    f[0] = 1;
    for(int i = 1; i < f.size(); i++) {
        f[i] = f[i - 1] *  (i + 1);
    }

    int ans = -1;
    for(int st = 0; st < (1 << 16); st++) {
        long long s = 0;
        int cnt = 0;
        vector<bool> vec(2);
        for(int i = 0; i < 16; i++) {
            if(st & (1 << i)) {
                s += f[i];
                cnt++;
                if(f[i] == 0 || f[i] == 1) {
                    vec[f[i]] = true;
                }
            }
        }

        if(s > n) continue;
        long long t = n - s;
        bool ok = true;
        for(int i = 0; i < 55; i++) {
            if(t & (1ll << i)) {
                if(i == 0 || i == 1) {
                    if(vec[i]) ok = false;
                }
                cnt++;
            }
        }
        if(ok) {
            if(ans == -1) ans = cnt;
            else ans = min(ans, cnt);
        }
    }
    cout << ans << endl;
}

int main(){
    ios::sync_with_stdio(false);
    //cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
