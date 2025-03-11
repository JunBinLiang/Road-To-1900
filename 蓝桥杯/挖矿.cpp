//https://www.lanqiao.cn/problems/19717/learning/?page=1&first_category_id=1&name=%E6%8C%96%E7%9F%BF
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
  // 请在此输入您的代码
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  sort(a.begin(), a.end());
  vector<int> b, c;
  int ans = 0;
  int zero = 0;
  for(int i = 0; i < n; i++) {
    if(a[i] == 0) {
      zero++;
      continue;
    } else if(a[i] > 0) {
      b.push_back(a[i]);
    } else {
      c.push_back(-a[i]);
    }
  }

  reverse(c.begin(), c.end());
  for(int i = 0; i < b.size(); i++) {
    int d = b[i];
    if(d > k) break;
    ans = max(ans, i + 1);
    if(k >= 2 * d) {
      int x = k - 2 * d;
      int l = 0, r = c.size() - 1;
      int p = -1;
      while(l <= r) {
        int mid = l + (r - l) / 2;
        if(c[mid] <= x) {
          p = mid;
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      ans = max(ans, i + 1 + p + 1);
    }
  }

  swap(b, c);
  for(int i = 0; i < b.size(); i++) {
    int d = b[i];
    if(d > k) break;
    ans = max(ans, i + 1);
    if(k >= 2 * d) {
      int x = k - 2 * d;
      int l = 0, r = c.size() - 1;
      int p = -1;
      while(l <= r) {
        int mid = l + (r - l) / 2;
        if(c[mid] <= x) {
          p = mid;
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      ans = max(ans, i + 1 + p + 1);
    }
  }

  cout << ans + zero << endl;
  return 0;
}
