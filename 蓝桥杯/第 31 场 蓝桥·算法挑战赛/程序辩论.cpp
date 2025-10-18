//https://www.lanqiao.cn/problems/21068/learning/?contest_id=263
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

bool ok(vector<int>& a, long long cur) {
  for(int i = 0; i < a.size(); i++) {
    if(cur < a[i]) return false;
    cur += a[i] / 2;
  }
  return true;
}

int main()
{
  // 请在此输入您的代码
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  sort(a.begin(), a.end());
  int l = a[0], r = a.back();
  int ans = -1;
  while(l <= r) {
    int mid = l + (r - l) / 2;
    if(ok(a, mid)) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << ans << endl;
  return 0;
}
