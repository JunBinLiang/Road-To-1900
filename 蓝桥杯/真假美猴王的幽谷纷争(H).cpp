//https://www.lanqiao.cn/problems/19749/learning/?contest_id=196
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

void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  sort(a.begin(), a.end());
  int index = -1;
  vector<int> b;
  for(int i = 0; i < n; i++) {
    if(a[i] <= k) {
      index = i;
      b.push_back(a[i]);
    }
  }

  long long ans = 0;
  reverse(b.begin(), b.end());
  for(int i = 0; i < b.size(); i += 2) {
    ans += b[i];
  }
  
  int e = 0;
  long long s1 = 0, s2 = 0;
  int cnt = 0;
  for(int i = index + 1; i < n; i++) {
    if(a[i] % 2 == 0) {
      ans += (a[i] / 2);
      e++;
    } else { //切的少一点
      s1 += (a[i] / 2);
      cnt++;
    }
  }

  if((b.size() + e) % 2 == 0) { 
    ans += s1;
    ans += (cnt / 2);
  } else {
    ans += s1;
    ans += ((cnt + 1) / 2);
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
