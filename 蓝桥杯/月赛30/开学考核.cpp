//https://www.lanqiao.cn/problems/20648/learning/?contest_id=258
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

  int n, k, X;
  cin >> n >> k >> X;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a.begin(), a.end());
  long long l = -100000000000000ll, r = a.back();
  long long ans = l;
  while(l <= r) {
    long long mid = l + (r - l) / 2;
    long long cnt = 0;
    for(int i = 0; i < n; i++) {
      long long x = a[i];
      if(x > mid) {
        long long d = x - mid;
        cnt += (d / X);
        if(d % X != 0) cnt++;
      } 
      if(cnt > k) break;
    }
    if(cnt <= k) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << ans << endl;
  return 0;
}
