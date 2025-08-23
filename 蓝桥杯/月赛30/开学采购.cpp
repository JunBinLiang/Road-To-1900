//https://www.lanqiao.cn/problems/20649/learning/?contest_id=258
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

long long get(vector<long long>& p, int l, int r) {
  if(l == 0) return p[r];
  return p[r] - p[l - 1];
}

int main()
{
  int n;
  cin >> n;
  vector<int> a(n), b(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  for(int i = 0; i < n; i++) cin >> b[i];
 
  vector<pair<int, int>> c, d;
  for(int i = 0; i < n; i++) {
    int di = a[i] - b[i];
    if(di >= 0) {
      c.push_back({di, i});
    } else{
      d.push_back({-di, i});
    }
  }

  long long ans1 = 0, ans2 = 0;
  sort(c.begin(), c.end());
  sort(d.begin(), d.end());

  for(int i = 0; i < c.size(); i++) {
    ans1 += a[c[i].second];
  }
  int cnt = 0;
  for(int i = d.size() - 1; i >= 0; i--) {
    if((cnt + 1) * 2 <= n) {
      cnt++;
      ans1 += b[d[i].second];
    } else {
      ans1 += a[d[i].second];
    }
  }
  

  for(int i = 0; i < d.size(); i++) {
    ans2 += a[d[i].second];
  }
  cnt = 0;
  for(int i = c.size() - 1; i >= 0; i--) {
    if((cnt + 1) * 2 <= n) {
      cnt++;
      ans2 += b[c[i].second];
    } else {
      ans2 += a[c[i].second];
    }
  }


  cout << ans1 << " " << ans2;
  return 0;
}
