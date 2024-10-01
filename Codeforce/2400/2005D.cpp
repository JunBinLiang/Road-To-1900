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

const int N = 2e5 + 100;
int a[N], b[N];
int pa[N], pb[N], sa[N], sb[N];
int n;
int ans = 0; long long cnt = 0;
void update(int curg, long long ways) {
    if(curg > ans) {
        ans = curg;
        cnt = ways;
    }
    else if(curg == ans) cnt += ways;
}

void solve() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
    a[0] = b[0] = a[n + 1] = b[n + 1] = 0;
    pa[0] = pb[0] = sa[n + 1] = sb[n + 1] = 0;

    for(int i = 1; i <= n; i++) {
        pa[i] = __gcd(a[i], pa[i - 1]);
        pb[i] = __gcd(b[i], pb[i - 1]);
    }

    for(int i = n; i >= 1; i--) {
        sa[i] = __gcd(a[i], sa[i + 1]);
        sb[i] = __gcd(b[i], sb[i + 1]);
    }
    
    /*int maxg = pa[n] + pb[n];

    for(int i = 1; i <= n; i++) {
        if(pa[i - 1] == pa[i] && pb[i - 1] == pb[i]) continue;
        int ga = 0, gb = 0;
        for(int j = i; j <= n; j++) {
            ga = __gcd(ga, a[j]);
            gb = __gcd(gb, b[j]);
            int s1 = __gcd(gb, __gcd(pa[i - 1], sa[j + 1]));
            int s2 = __gcd(ga, __gcd(pb[i - 1], sb[j + 1]));;
            maxg = max(maxg, s1 + s2);
        }
    }*/
    ans = 0;
    cnt = 0;
    
    map<pair<int, int>, long long> f;
    for(int i = 1; i <= n; i++) {
        map<pair<int, int>, long long> g = move(f);
        f[{__gcd(pa[i - 1], b[i]), __gcd(pb[i - 1], a[i])}]++; //start swapping at point i
        for(auto it = g.begin(); it != g.end(); it++) {
            pair<int, int> p = it -> first;
            long long c = it -> second;
            int ag = p.first, bg = p.second;
            ag = __gcd(ag, b[i]);
            bg = __gcd(bg, a[i]);
            f[{ag, bg}] += c;
        }

        for(auto it = f.begin(); it != f.end(); it++) {
            pair<int, int> p = it -> first;
            long long c = it -> second;
            int ag = p.first, bg = p.second;
            ag = __gcd(ag, sa[i + 1]);
            bg = __gcd(bg, sb[i + 1]);
            update(ag + bg, c);
        }
    }

    cout << ans << " " << cnt << endl;
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
