#include <iostream>
using namespace std;
//一堆n个物品，两个人轮流从这堆物品中取物， 规定每次取[1,m]个，最后取光者得胜，问先手必胜还是后手必胜。
//https://cloud.tencent.com/developer/article/2033965
//n%(m+1) == 0则后手必胜，否则先手必胜。
int main()
{
  
  int t;
  cin >> t;
  while(t--) {
    long long n, m;
    cin >> n >> m;
    if(n % (m + 1) == 0) cout << "YES" << endl;
    else cout << "NO" << endl;
  }

  return 0;
}
