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

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

/*
计算 
n / 1 + n / 2 + ... n / n

对于 n / i => 只有sqrt(n) 种取值
*/

long long H(long long n) {
    long long res = 0;  // 储存结果
    long long l = 1, r;       // 块左端点与右端点
    while (l <= n) {
      r = n / (n / l);  // 计算当前块的右端点
      // 累加这一块的贡献到结果中。乘上 1LL 防止溢出
      res += 1LL * (r - l + 1) * (n / l);
      l = r + 1;  // 左端点移到下一块
    }
    return res;
}

void solve() {
    long long n;
    cin >> n;
    cout << H(n) << endl;
}


int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
