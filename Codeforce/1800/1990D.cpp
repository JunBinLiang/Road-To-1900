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

//2:25 - 2:57
const int N = 2e5 + 10;
int dp[N][(1 << 6) + 10];
int f[1000];
int check(int pst, int st) {
    st |= pst;
    int cnt = 0;
    for(int i = 0; i < 8; i++) {
        if(st & (1 << i)) cnt++;
        else break;
    }
    //if(st == 48) cout << "gg " << cnt << endl;
    return cnt;
}

string bin(int n) {
    string s = "";
    for(int i = 0; i < 6; i++) {
        if(n & (1 << i)) s += "1";
        else s += "0";
    }
    return s;
}

void solve() {
    int n;
    scanf("%d", &n);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= (1 << 6); j++) {
            dp[i][j] = -1;
        } 
    }

    dp[0][0] = 0;

    vector<int> cur = {0, 2, 4};
    vector<int> allstate;

    for(int st = 0; st < (1 << 3); st++) {
        int b = 0;
        int cnt = 0;
        for(int j = 0; j < 3; j++) {
            if(st & (1 << j)) {
                b |= (1 << cur[j]);
                b |= (1 << (cur[j] + 1));
                cnt++;
            }
        }
        allstate.push_back(b);
        f[b] = cnt;
        //cout << b << " "  << bin(b) << endl;
    }

    
    for(int i = 1; i <= n; i++) {
        for(int lst = 0; lst < (1 << 6); lst++) {
            if(dp[i - 1][lst] == -1) continue;
            for(int st : allstate) {
                int cover = check(lst, st);
                if(cover >= a[i]) {
                    if(dp[i][st] == -1)
                        dp[i][st] = dp[i - 1][lst] + f[st];
                    else dp[i][st] = min(dp[i][st], dp[i - 1][lst] + f[st]);
                } else {
                    if(dp[i][st] == -1)
                        dp[i][st] = dp[i - 1][lst] + f[st] + 1;
                    else dp[i][st] = min(dp[i][st], dp[i - 1][lst] + f[st] + 1);
                }
                //cout << bin(st) << "  " << bin(lst) << "  " << cover <<"  " << f[st] << "   |" <<dp[i - 1][lst] << "  " << dp[i][st] << endl;
            }
        }
        //cout << endl;
    }

    int ans = 1e9;
    for(int st = 0; st < (1 << 6); st++) {
        if(dp[n][st] != -1) {
            ans = min(ans, dp[n][st]);
        }
    }
    
    printf("%d\n", ans);
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
