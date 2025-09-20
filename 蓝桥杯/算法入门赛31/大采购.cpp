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
  int n; long long x;
  cin >> n >> x;
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  sort(a.begin(), a.end());
  long long ans = 0;
  for(int i = 0; i < n; i++) {
    ans += max(0ll, (a[i] + 0ll) - x * i);
  }
  cout << ans << endl;
  return 0;
}
