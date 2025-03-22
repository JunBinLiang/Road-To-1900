//https://www.lanqiao.cn/problems/20271/learning/?contest_id=250
#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    
#include <deque>  

using namespace std;

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

bool comp(pair<int, int>& p1, pair<int, int>& p2) {
    return (p1.first - p1.second) > (p2.first - p2.second);
}

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    long long s = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        s += a[i].second;
    }

    sort(a.begin(), a.end(), comp);
    for(int i = 0; i < n / 2; i++) {
        s += a[i].first;
        s -= a[i].second;
    }
    cout << s << endl;
}


int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
