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

//5:48 - 6:21
const int N = 2e5 + 10;
int a[N], b[N], p1[N], p2[N];

bool within(int l, int r, int p) {
    return p >= l && p <= r;
}

void solve() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        p1[a[i]] = i;
    }
    for(int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
        p2[b[i]] = i;
    }

    long long ans = 1;
    //handel MEX 1 first
    int j = 1;
    for(int i = 1; i <= n; i++) {
        if(a[i] == 1 || b[i] == 1) {
            j = i + 1;
            continue;
        }
        ans += (i - j + 1);
    }
    
    int l = min(p1[1], p2[1]), r = max(p1[1], p2[1]);
    for(int mex = 2; mex <= n; mex++) {
        //make sure 2 does not exist in the range from l to r
        int pos1 = p1[mex], pos2 = p2[mex];
        if(pos1 > pos2) swap(pos1, pos2);
        if(!within(l, r, pos1) && !within(l, r, pos2)) {
            //cout << "ok  " << mex << "  " << l << " " << r << endl;
            //cout << pos1 << "  " << pos2 << endl;
            if(pos1 < l && pos2 > r) {
                long long w = (l - pos1 + 0ll) * (pos2 - r);
                //cout << "w1 " << w << endl << endl;
                ans += w; 
            } else if(pos2 < l) {
                long long w = (l - pos2 + 0ll) * (n - r + 1);
                ans += w;
                //cout << "w2 " << w << endl << endl;
            } else if(pos1 > r) {
                long long w = (pos1 - r + 0ll) * (l);
                ans += w;
                //cout << "w3 " << w << endl << endl;
            }
        }
        l = min(l, min(pos1, pos2));
        r = max(r, max(pos1, pos2));
    }
    printf("%lld\n", ans);
}

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
