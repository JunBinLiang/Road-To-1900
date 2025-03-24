#include <iostream>
using namespace std;
// 每次行动拿走不超过上一次的两倍，取走最后的人获胜。
//结论 : 当石头的数量为斐波那契数列时，后手必胜，否则先手必胜。
//证明 : https://zhuanlan.zhihu.com/p/574189420

void solve(long long n) {
  if(n == 1) {
    cout << "NO" << endl;
    return;
  }
  long long a = 1, b = 1;
  for(int i = 1; i < 63; i++) {
    long long tem = a + b;
    if(tem == n) {
      cout << "YES" << endl;
      return;
    }
    a = b;
    b = tem;
  }
  cout << "NO" << endl;
}

int main()
{
  int t;
  cin >> t;
  while(t--) {
    long long n; cin >> n;
    solve(n);
  }
  return 0;
}
