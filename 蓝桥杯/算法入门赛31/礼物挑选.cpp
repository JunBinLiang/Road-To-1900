#include <iostream>
#include <map>
using namespace std;
int main()
{
  // 请在此输入您的代码
  int n, x;
  cin >> n >> x;
  map<int, int> mp;
  for(int i = 0; i < n; i++) {
    int v;
    cin >> v;
    mp[v]++;
  }
  long long ans = 0;
  for(auto it = mp.begin(); it != mp.end(); it++) {
    int v = it -> first, cnt = it -> second;
    ans = max(ans, (v + 0ll) * min(cnt, x));
  }
  cout << ans << endl;
  return 0;
}
