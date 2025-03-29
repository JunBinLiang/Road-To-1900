#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool comp(pair<int, int>& p1, pair<int, int>& p2) {
  return p1.second < p2.second;
}
int main()
{
  // 请在此输入您的代码
  int n; long long k;
  cin >> n >> k;
  vector<pair<int, int>> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  long long ans = 1e18;
  sort(a.begin(), a.end(), comp);

  long long tot = 0, s = 0;
  for(int i = 0; i < a.size(); i++) {
    tot += ((a[i].first + 0ll) * a[i].second);
    s += a[i].first;
  }
  ans = min(ans, tot);

  int j = 0;
  for(int t = 1; t <= a.back().second; t++) {
    long long s1 = (t + 0ll) * k;
    tot -= s;
    while(j < a.size() && a[j].second <= t) {
      s -= a[j].first;
      j++;
    }
    ans = min(ans, s1 + tot);
  }

  cout << ans << endl;
  return 0;
}
