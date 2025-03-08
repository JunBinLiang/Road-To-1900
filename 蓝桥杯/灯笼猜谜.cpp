//https://www.lanqiao.cn/problems/20256/learning/?page=1&first_category_id=1&name=%E7%81%AF%E7%AC%BC
#include <iostream>
#include <cstring>
#include <algorithm>
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
  int n, m;
  cin >> n >> m;
  int p = 1;
  long long ans = 0;
  for(int i = 0; i < n; i++) {
    int L, R;
    cin >> L >> R;
    if(p >= L && p <= R) continue;
    if(p < L) {
      ans += (L - p);
      p = L;
    } else if(p > R) {
      ans += (p - R);
      p = R;
    }
  }
  cout << ans << endl;
  return 0;
}
