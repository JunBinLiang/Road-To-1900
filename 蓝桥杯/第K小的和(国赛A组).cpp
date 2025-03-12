//https://www.lanqiao.cn/problems/17098/learning/?page=1&first_category_id=1&name=%E7%AC%ACK%E5%B0%8F%E7%9A%84%E5%92%8C
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
  // 请在此输入您的代码
  int n, m;
  long long k;
  cin >> n >> m >> k;
  vector<int> a(n), b(m);
  for(int i = 0; i < n; i++) cin >> a[i];
  for(int i = 0; i < m; i++) cin >> b[i];
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  int l = 0, r = 1e9, ans = -1;
  while(l <= r) {
    int mid = l + (r - l) / 2;
    long long cnt = 0;

    int j = b.size() - 1;
    for(int i = 0; i < n; i++) {
      while(j >= 0 && a[i] + b[j] > mid) j--;
      cnt += (j + 1);
    }
    if(cnt >= k) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }

  cout << ans << endl;
  return 0;
}
