//https://www.lanqiao.cn/problems/3381/learning/?page=1&first_category_id=1&name=%E5%8D%96%E8%B4%A7
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

  vector<int> stk;
  vector<int> dp(n);
  long long ans = 0;
  for(int i = 0; i < n; i++) {
    if(a[i] > 0) {
      stk.push_back(i);
    } else {
      if(stk.size() == 0) {

      } else {
        int top = stk.back(); stk.pop_back();
        int cnt = 1;
        dp[i] = cnt;
        if(top - 1) {
          dp[i] += dp[top - 1];
        }
        ans += dp[i];
      }
    }
  }

  cout << ans << endl;
  return 0;
}
