//https://www.cnblogs.com/1024th/p/10807095.html
#include <iostream>
using namespace std;

const int N = 1e7 + 10;
int phi[N]; long long p[N];
void euler(int n){
    for (int i = 1; i <= n; i++) phi[i]=i;
    p[1] = 1;
    for (int i = 2;i <= n;i++){
        if (phi[i] == i){//这代表i是质数
            for (int j = i;j <= n;j += i){
                phi[j] = phi[j] / i * (i - 1);//把i的倍数更新掉
            }
        }
        p[i] = phi[i] + p[i - 1];
    }
}

int main()
{
  // 请在此输入您的代码
  euler(10000001);
  int t;
  cin >> t;
  while(t--) {
    int n;
    cin >> n;
    cout << p[n] << endl;
  }
  return 0;
}
