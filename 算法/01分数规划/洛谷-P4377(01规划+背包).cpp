//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P4377
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

double eps = 0.00001;

bool ok(vector<int>& a, vector<int>& b, int w, double mid) {
    //b[i] has sum >= w
    int n = a.size();
    vector<double> dp(w + 1, -2000000000);
    dp[0] = 0;
    for(int i = 0; i < n; i++) {
        //take b[i]
        double val = (b[i] + 0.0) - mid * a[i];
        for(int j = w; j >= 0; j--) {
            if(dp[j] == -1) continue;
            dp[min(w, j + a[i])] = max(dp[min(w, j + a[i])], dp[j] + val);
        }
    }
    //cout << dp << endl;
    return dp.back() > 0;
}

void solve() {
    int n, w;
    cin >> n >> w;

    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        cin >> b[i];
    }

    double l = 0, r = 1e6;
    while(r - l > eps) {
        double mid = (l + r) / 2;
        if(ok(a, b, w, mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << (int)(l * 1000) << endl;
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
