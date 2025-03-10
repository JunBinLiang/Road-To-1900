//https://www.lanqiao.cn/problems/19716/learning/
#include <iostream>
#include <vector>
using namespace std;
int main()
{
  // 请在此输入您的代码
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> b;
  vector<int> line(n + 1);
  for(int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    b.push_back({l, r});
    line[l]++;
    if(r + 1 <= n) {
      line[r + 1]--;
    }
  }

  int s = 0;
  int zero = 0;
  for(int i = 1; i < line.size(); i++) {
    s += line[i];
    line[i] = (s == 1);
    if(s == 0) zero++;
    if(i) line[i] += line[i - 1];
  }

  for(int i = 0; i < m; i++) {
    int l = b[i].first, r = b[i].second;
    cout << line[r] - line[l - 1] + zero << endl;
  }

  return 0;
}
