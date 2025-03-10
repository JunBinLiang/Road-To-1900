#include <iostream>
//https://www.lanqiao.cn/problems/19733/learning/?page=1&first_category_id=1&name=%E5%B0%81%E9%97%AD%E5%9B%BE%E5%BD%A2%E4%B8%AA%E6%95%B0
#include <vector>
#include <algorithm>
using namespace std;
int f[10] = {1, 0, 0, 0, 1, 0, 1, 0, 2, 1};
bool comp(int& x, int& y) {
  int n1 = x;
  int n2 = y;

  int cnt1 = 0, cnt2 = 0;
  while(n1) {
    int d = n1 % 10;
    n1 /= 10;
    cnt1 += f[d];
  }
  while(n2) {
    int d = n2 % 10;
    n2 /= 10;
    cnt2 += f[d];
  }
  if(cnt1 == cnt2) return x < y;
  return cnt1 < cnt2;
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
  sort(a.begin(), a.end(), comp);
  for(int x : a) cout << x << " ";
  cout << endl;
  return 0;
}
