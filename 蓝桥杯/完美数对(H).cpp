#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    
#include <deque>  

using namespace std;

const int FENWICK_SIZE = 1000000 + 100;
struct Fenwick {
  int tree[FENWICK_SIZE];
  int sz;
  void init(int n) {
      sz = n;
      for(int i = 0; i <= n + 1; i++) tree[i] = 0;
  }

  void update(int i, int val) {
      i++;
      while(i < sz){
        tree[i] += val;
        i += (i & -i);
      }
  }

  int pre(int i) {
      int sum = 0;
      while(i > 0){
        sum += tree[i];
        i -= ( i & -i);
      }
      return sum;
  }
  int query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
} tr;

bool comp(pair<int, int>& p1, pair<int, int>& p2) {
  return p1.second < p2.second;
}

void solve() {
  int n;
  cin >> n;
  map<int, int> mp;
  for(int i = 0; i < n; i++) {
    int x;
    cin >> x;
    mp[x]++;
  }
  
  vector<pair<int, int>> a, b;
  for(auto it = mp.begin(); it != mp.end(); it++) {
    a.push_back({it -> first, it -> second});
    b.push_back({it -> first, it -> second});
  }
  tr.init(1000000 + 10);
  sort(a.begin(), a.end());
  sort(b.begin(), b.end(), comp);

  long long ans = 0;
  int j = 0;
  for(int i = 0; i < b.size(); i++) {
    int val = b[i].first, cnt = b[i].second;
    while(j < a.size() && a[j].first <= cnt) {
      tr.update(a[j].second, 1);
      j++;
    }
    ans += tr.query(b[i].first, 1000000);
  }

  cout << ans << endl;
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
