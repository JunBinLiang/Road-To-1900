//https://www.lanqiao.cn/problems/19721/learning/?page=1&first_category_id=1&name=%E6%9C%80%E5%A4%A7%E5%BC%82%E6%88%96%E7%BB%93%E7%82%B9
#include <iostream>
#include <vector>
using namespace std;

int main()
{
  // 请在此输入您的代码
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  long long ans = 0;
  int l = 1, r = n - 2;
  ans = abs(a[0] - a.back());
  int extra = abs(a[0] - a.back());
  while(l < r) {
    int d = abs(a[l] - a[r]);
    if(a[l] == a[r]) {
      //nothing
      extra = 0;
    } else if(a[l] < a[r]) {
      if(a[l - 1] < a[r + 1]) {
        if(extra <= d) {
          ans += (d - extra);
          extra = d - extra;
        } else {
          extra = 0;
        }
      } else {
        extra = d;
        ans += d;
      }
    } else {
      if(a[l - 1] > a[r + 1]) {
        if(extra <= d) {
          ans += (d - extra);
          extra = d - extra;
        } else {
          extra = 0;
        }
      } else {
        extra = d;
        ans += d;
      }
    }
    l++;
    r--;
  }

  cout << ans << endl;
  return 0;
}
