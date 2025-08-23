//https://www.lanqiao.cn/problems/20647/learning/?contest_id=258
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
  int n, m;
  cin >> n >> m;
  vector<int> a(n), b(m);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for(int i = 0; i < m; i++) {
    cin >> b[i];
  }
  long long ans = 0;
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  int j = n - 1;
  for(int i = m - 1; i >= 0; i--) {
    while(j >= 0 && b[i] < a[j]) {
      j--;
    }
    if(j >= 0) {
      ans += a[j];
      j--;
    }
  }

  cout << ans << endl;
  return 0;
}
