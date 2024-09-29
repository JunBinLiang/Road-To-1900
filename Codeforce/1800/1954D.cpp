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

//8:55 - 9:33
const int MOD = 998244353;
const int N = 5010;
long long C[N][N];
void init() {
    C[0][0] = 1;
    for(int i = 1;i < N; i++) {
      C[i][0]=1;
      for(int j = 1;j <= i;j++) {
        C[i][j] = ( C[i-1][j] + C[i-1][j-1] ) % MOD;
      }
    }
}

void solve() {
    init();
    int n;
    cin >> n;
    vector<int> a(n);
    vector<long long> p(n + 1);
    for(int i = 0; i < n; i++) cin >> a[i];
    p[0] = 1;
    for(int i = 1; i < p.size(); i++) {
        p[i] = p[i - 1] * 2;
        p[i] %= MOD;
    }
    sort(a.begin(), a.end());
    
    long long ans = 0;
    vector<long long> dp(5010);
    vector<long long> cur(5010);
    dp[0] = 1;
    //other < max
    //other >= max
    for(int i = 0; i < n; i++) {
        int j = i;
        int cnt = 0;
        while(j < n && a[j] == a[i]) {
            j++;
            cnt++;
        }
        int mx = a[i];
        
        for(int s = 0; s < dp.size(); s++) { //put 1 current ball as max
            if(s < mx) {
                long long ways = (dp[s] * cnt) % MOD;
                ans += (ways * mx);
                ans %= MOD;
            } else {
                long long ways = (dp[s] * cnt) % MOD;
                ans += (ways * ((s + mx + 1) / 2));
                ans %= MOD;
            }

            for(int ball = 2; ball <= cnt; ball++) { //put multiple ball
                long long ways = dp[s] * C[cnt][ball];
                ways %= MOD;
                ans += (ways * ((s + ball * mx + 1) / 2));
                ans %= MOD;
            }
        }

        //dp[s] : how many combination with sum as s
        for(int ball = 1; ball <= cnt; ball++) {
            for(int s = 0; s < cur.size(); s++) cur[s] = 0;
            for(int s = 0; s < cur.size(); s++) {
                cur[s] = dp[s];
                if(s >= mx) {
                    cur[s] += dp[s - mx];
                    cur[s] %= MOD;
                }
            }
            //copy dp
            for(int s = 0; s < dp.size(); s++) dp[s] = cur[s];
        }
        i = j - 1;
        //cout << ans << endl;
        //for(int x = 0; x < 5; x++) cout << dp[x] << " ";
        //cout << endl << endl;
    }

    cout << ans << endl;

    /*int ans = 0;
    for(int i = 0; i < (1 << n); i++) {
        int mx = 0;
        int sum = 0;
        for(int j = 0; j < n; j++) {
            if(i & (1 << j)) {
                mx = max(mx, a[j]);
                sum += a[j];
            }
        }
        //cotu << mx << " " << sum << endl;
        if(mx >= sum - mx) ans += mx;
        else ans += ((sum + 1) / 2);
    }
    cout << ans << endl;*/
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
