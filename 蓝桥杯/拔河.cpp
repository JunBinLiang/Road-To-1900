//https://www.lanqiao.cn/problems/19713/learning/?page=1&first_category_id=1&second_category_id=3&name=%E6%8B%94%E6%B2%B3
#include <iostream>
#include <vector>
#include <set>
using namespace std;
int main()
{
  // 请在此输入您的代码
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  long long ans = 1e18;
  
  vector<set<long long>> all(n); 
  for(int i = 0; i < n; i++) {
    long long sum = 0; //[i : j]
    for(int j = i; j < n; j++) {
      sum += a[j];
      all[j].insert(sum);

      if(i > 0) {
        auto& s = all[i - 1];
        auto it = s.upper_bound(sum);
        if(it != s.end()) ans = min(ans, *it - sum);
        if(it != s.begin()) {
          it--;
          ans = min(ans, sum - *it);
        }
      }
    }

    if(i > 0) {
      swap(all[i], all[i - 1]);
      for(auto& x : all[i - 1]) all[i].insert(x); 
      all[i - 1].clear();
    }
  }

  cout << ans << endl;
  return 0;
}
