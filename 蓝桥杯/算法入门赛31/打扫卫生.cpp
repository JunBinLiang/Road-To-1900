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

int main()
{
  // 请在此输入您的代码
  int n, k;
  cin >> k >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  sort(a.begin(), a.end());
  long long ans = 1e16 + 10;
  for(int i = 0; i < n; i++) {
    if(i + 1 >= k) {
      int l = i - k + 1, r = i;
      if(a[r] <= 0) {
        ans = min(ans, 0ll - a[l]);
      } else if(a[l] >= 0) {
        ans = min(ans, a[r] + 0ll);
      } else if(a[l] < 0 && a[r] > 0) {
        long long ld = abs(a[l]);
        long long rd = abs(a[r]);
        ans = min(ans, min(ld, rd) * 2 + max(ld, rd));
      }
    }
  }
  cout << ans << endl;
  return 0;
}
