//https://cloud.tencent.com/developer/article/2033965
#include <iostream>
using namespace std;
//有 n 堆石子，第 i 堆石子有 ai个，每次可以从某一堆中取走若干个，先后手轮流取，最后无石子可取的人负。
//将n堆石子每堆石子的数量求异或和（ans = a[1] ^ a[2] ^ … ^a[n]），若ans == 0，先手必败，否则先手必胜。
int main()
{
  // 请在此输入您的代码

  int t;
  cin >> t;
  while(t--) {
    int n; cin >> n;
    int o = 0;
    for(int i = 0; i < n; i++) {
      int x; cin >> x;
      o ^= x;
    }
    if(o == 0) cout << "YES" << endl;
    else cout << "NO" << endl;
  }
  
  return 0;
}
