#include <bits/stdc++.h>
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
ostream &operator<<(ostream &out, const set<T> &a) {
  out << "[";
  bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;}
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int MOD = 998244353;
long long dp[18][(1 << 18) + 10];
long long p[18][1010];

long long fpow(long long x, int y){
	long long res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}

int bitcount(int n) {
    int ans = 0;
    for(int i = 0; i < 18; i++) {
        if(n & (1 << i)) ans++;
    }
    return ans;
}

void solve() {
    int n, m; string s;
    cin >> n >> s;

    memset(dp, 0, sizeof dp);
    memset(p, 0, sizeof p);

    for(int i = 1; i < 18; i++) { //power
        long long s = 1;
        p[i][0] = s;
        for(int j = 1; j < 1010; j++) {
            s *= i;
            s %= MOD;
            p[i][j] = s;
        }
    }
    
    int tot = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '?') tot++;
    }

    for(int i = 0; i < n; i++) {
        int l = i, r = i;
        int free = 0, st = 0;
        int cnt = 0;
        while(l >= 0 && r < n) {
            if(s[l] == '?' && s[r] == '?') {
                if(l == r) cnt++;
                else cnt += 2;
                free++;
            } else if(s[l] == '?') {
                st |= (1 << (s[r] - 'a'));
                cnt++;
            } else if(s[r] == '?') {
                st |= (1 << (s[l] - 'a'));
                cnt++;
            } else if(s[l] == s[r]) {
                //do nothing
            } else {
                break;
            }
            for(int j = 0; j < 18; j++) {
                dp[j][st] += p[j][(tot - cnt) + free];
                dp[j][st] %= MOD;
            }
            l--;
            r++;
        }
    }

    for(int i = 0; i < n; i++) {
        int l = i, r = i + 1;
        int free = 0, st = 0;
        int cnt = 0;
        while(l >= 0 && r < n) {
            if(s[l] == '?' && s[r] == '?') {
                free++;
                cnt += 2;
            } else if(s[l] == '?') {
                st |= (1 << (s[r] - 'a'));
                cnt++;
            } else if(s[r] == '?') {
                st |= (1 << (s[l] - 'a'));
                cnt++;
            } else if(s[l] == s[r]) {
                //do nothing
            } else {
                break;
            }

            for(int j = 0; j < 18; j++) {
                dp[j][st] += p[j][tot - cnt + free];
                dp[j][st] %= MOD;
            }
            l--;
            r++;
        }
    }

    //SOS DP
    for(int i = 0; i < 18; i++) {
        for(int j = 0; j < 18; j++) {
            for(int st = (1 << 18) - 1; st >= 0; st--) {
                if(st & (1 << j)) {
                    dp[i][st] += dp[i][st ^ (1 << j)];
                    dp[i][st] %= MOD;
                }
            }
        }
    }

    cin >> m;
    while(m--) {
        string t;
        cin >> t;
        int m = t.size();
        int st = 0;
        for(char& c : t) {
            st |= (1 << (c - 'a'));
        }
        cout << dp[m][st] << endl;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
