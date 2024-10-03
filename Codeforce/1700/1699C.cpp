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

//9:52 - 10:14
const int MOD = 1e9 + 7;
const int N = 2e5 + 10;
long long fact[N];

ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  

ll C(int n,int m) {
  return fact[n] * fpow(fact[n - m], MOD - 2) % MOD * fpow(fact[m], MOD - 2) % MOD;
}

void solve() {
    int n;
    scanf("%d", &n);
    vector<int> a(n + 1), p(n + 1);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        p[a[i]] = i;
    }

    fact[0] = 1;
    for(int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;
    }
    
    //cout << a << " " << p << endl;

    //0 must in the same place
    long long ans = 1;
    int l = p[0], r = p[0];
    int extra = 0;
    set<int> s;
    for(int i = 1; i <= n + 1; i++) s.insert(i);

    for(int i = 1; i < n; i++) {
        int pos = p[i];
        if(pos >= l && pos <= r) {
            continue;
        }
        
        //cout <<"before  " << l << " " << r << " " << i << endl;

        if(pos > r) {
            while(r != pos) {
                r++;
                extra++;
                s.erase(a[r]);
            }
        } else if(pos < l) {
            while(l != pos) {
                l--;
                extra++;
                s.erase(a[l]);
            }
        }
        auto it = s.begin();
        int mex = *it;
        int add = mex - i;
        add--;
        extra--;
        ans *= C(extra, add);
        ans %= MOD;
        ans *= fact[add];
        extra -= add;
        ans %= MOD;
        
        //cout <<"after  " << l << " " << r << " " << mex << "   | " << extra <<" "  << add << endl << endl;
    }
    cout << ans << endl;
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
