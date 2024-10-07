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
#include <deque>

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

//4:02 - 4:11
const int N = 2e5 + 10;
int a[N];
void yes() { //not lost
    cout << "YES" << endl;
}

void no() { //lost
    cout << "NO" << endl;
}


unsigned long long seed=131;
unsigned long long rands(){return seed = (seed << 15) + (seed << 8) + (seed >> 3);}

void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    unordered_map<int, unsigned long long> mp;
    for(int i = 1; i <= n; i++) {
        if(mp.find(a[i]) == mp.end()) {
            mp[a[i]] = rands();
        }
    }

    unsigned long long xo = 0;
    vector<unsigned long long> p;
    p.push_back(0);
    for(int i = 1; i <= n; i++) {
        xo ^= mp[a[i]];
        p.push_back(xo);
    }

    for(int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        int sz = (r - l + 1);
        if(sz % 2 == 1) {
            no();
            continue;
        }
        //In order to not lost, every number in this range should have equal frequency
        unsigned long long h = p[r] ^ p[l - 1];
        if(h == 0) yes();
        else no();
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
