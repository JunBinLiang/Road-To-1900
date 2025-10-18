//https://www.lanqiao.cn/problems/21067/learning/?contest_id=263
#include <iostream>
#include <vector>
using namespace std;
int main()
{
  // 请在此输入您的代码
  int n;
  cin >> n;
  vector<int> a(n);
  int e = 0, o = 0;
  int ans = 0;
  for(int i = 0; i < n; i++) {
    cin >> a[i];
    if(a[i] % 2 == 0) e++;
    else o++;
    if(e == o) ans++;
  }
  if(e != o) {
    cout << -1 << endl;
    return 0;
  }
  cout << ans << endl;
  return 0;
}
