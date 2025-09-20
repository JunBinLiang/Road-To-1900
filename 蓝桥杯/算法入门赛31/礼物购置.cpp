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

void solve() {
  long long n;
  cin >> n;
  long long ans = 0;
  if(n % 10 == 0) {
    int cnt = 0;
    long long p1 = 1, p2 = 1;
    while(n % 2 == 0) {
      n /= 2;
      p1 *= 2;
    }
    while(n % 5 == 0) {
      n /= 5;
      p2 *= 5;
    }
    cout << min(p1, p2) + max(p1, p2) * n << endl;
  } else {
    cout << 1 + n << endl;
  }
}

int main()
{
  // 请在此输入您的代码
  int t;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
