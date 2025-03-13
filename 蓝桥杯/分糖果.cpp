#include <iostream>
#include <vector>
using namespace std;

bool notSame(vector<int>& a) {
  for(int i = 1; i < a.size(); i++) {
    if(a[i] != a[i - 1]) {
      return true;
    }
  }
  return false;
}
int main()
{
  // 请在此输入您的代码
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  int ans = 0;
  while(notSame(a)) {
    vector<int> add(n);
    for(int i = 0; i < n; i++) {
      add[i] = a[(i + 1) % n] / 2;
    }
    for(int i = 0; i < n; i++) {
      a[i] = (a[i] / 2) + add[i];
      ans += ((a[i] % 2) ? ((a[i]++) % 2) : 0);
    }
  }
  cout << ans << endl;
  return 0;
}
