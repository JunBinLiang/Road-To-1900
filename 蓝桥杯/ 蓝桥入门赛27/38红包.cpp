//https://www.lanqiao.cn/oj-contest/newbie-27/
#include <iostream>
using namespace std;
int main()
{
  // 请在此输入您的代码
  int ans = 0;
  for(int i = 1; i <= 2025; i++) {
    if(i % 3 == 0 || i % 8 == 0 || i % 38 == 0) ans++;
  }
  cout << ans << endl;
  return 0;
}
