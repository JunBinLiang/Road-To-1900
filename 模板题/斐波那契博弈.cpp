#include <iostream>
using namespace std;
// 有一堆物品，两人轮流取，先手第一次可以取任意个但不能全部取完。之后每次取的数量必须大于等于 1且小于等于上次取的数量的两倍，最后把物品全部取完者胜利
//结论 : 当石头的数量为斐波那契数列时，后手必胜，否则先手必胜。
//证明 : https://zhuanlan.zhihu.com/p/574189420
//https://www.cnblogs.com/tttkf/p/15895646.html

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
