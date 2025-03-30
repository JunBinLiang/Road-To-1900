//https://blog.csdn.net/weixin_43238423/article/details/102705549
#include <iostream>
using namespace std;
const int MOD = 1e9 + 7;

const int N = 1e6 + 100;
int phi[N];
void euler(int n){
    for (int i = 1; i <= n; i++) phi[i]=i;
    for (int i = 2;i <= n;i++){
        if (phi[i] == i){//这代表i是质数
            for (int j = i;j <= n;j += i){
                phi[j] = phi[j] / i * (i - 1);//把i的倍数更新掉
            }
        }
    }
}

long long fpow(long long x, long long y){
	long long res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  

/*
处理幂数过大时
(a ^ b) % p => (a ^ ((b % phi[p] + phi[p]) % p)) % p
*/

int main()
{
  // 请在此输入您的代码

  int n, m;
  cin >> n >> m;
  long long b = 1;
  for(int i = 1; i <= m; i++) {
      b *= i;
      b %= (MOD - 1);
  }
  b += (MOD - 1);
  cout << fpow(n, b) << endl;
  return 0;
}
