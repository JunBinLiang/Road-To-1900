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

//5:15 - 6:27
const int N = 1e6 + 10;
int f[N];
long long dp[N];
bool vis[N];

void test (vector<int>& a) {
    int n = a.size();
    set<int> s(a.begin(), a.end());
    vector<int> b(s.begin(), s.end());
    map<int, int> f;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            for(int k = 0; k < b.size(); k++) {
                if(a[i] % b[k] == 0 && a[j] % b[k] == 0) {
                    f[b[k]]++;
                    break;
                }
            }
        }
    }
    //cout << f << endl << endl;
}

void solve() {
    int n;
    scanf("%d", &n);
    //reset
    vector<int> a(n); 
    for(int i = 0; i <= n; i++) {
        f[i] = 0;
        dp[i] = 0;
        vis[i] = false;
    }

    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        f[a[i]]++;
    }

    long long ans = (n + 0ll) * (n - 1) / 2;
    for(int i = n; i >= 1; i--) {
        int cnt = 0;
        for(int j = i; j <= n; j += i) {
            cnt += f[j];
        }
        
        long long w = (cnt + 0ll) * (cnt - 1) / 2; 
        dp[i] = w;
        for(int j = i + i; j <= n; j += i) {
            dp[i] -= dp[j];
        }
    }

    for(int i = 0; i <= n; i++) {
        if(f[i]) {
            for(int j = i; j <= n; j += i) {
                if(!vis[j]) {
                    vis[j] = true;
                    ans -= dp[j];
                }
            }
        }
    }
    printf("%lld\n", ans);
    
}

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
