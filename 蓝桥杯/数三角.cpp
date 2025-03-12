//https://www.lanqiao.cn/problems/17107/learning/?page=1&first_category_id=1&second_category_id=3&name=%E6%95%B0%E4%B8%89%E8%A7%92
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    
#include <deque>  

using namespace std;

long long cal(pair<int, int>& p1, pair<int, int>& p2) {
  long long x = p1.first - p2.first;
  long long y = p1.second - p2.second;
  return x * x + y * y;
}

pair<int, int> calSlope(pair<int, int>& p1, pair<int, int>& p2) {
  int y = p1.second - p2.second;
  int x = p1.first - p2.first;
  int g = __gcd(x, y);
  return {y / g, x / g};
}

const int N = 2010;
pair<int, int> slope[N][N];


int main()
{
  // 请在此输入您的代码
  int n;
  cin >> n;
  vector<pair<int, int>> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i].first >> a[i].second;
  }

  //都是正数没有等边三角形, 根据等边三角形计算公式
  vector<unordered_map<long long, vector<int>>> b(n);
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      if(i == j) continue;
      long long dis = cal(a[i], a[j]);
      b[i][dis].push_back(j);
      slope[i][j] = calSlope(a[i], a[j]);
    }
  }

  int ans = 0;
  for(int i = 0; i < n; i++) {
    unordered_map<long long, vector<int>>& mp = b[i];
    for(auto it = mp.begin(); it != mp.end(); it++) {
      vector<int>& vec = it -> second;
      map<pair<int, int>, int> m;
      int sz = vec.size();
      ans += ((sz - 1) * sz / 2);
      for(int j : vec) {
        if(m.find(slope[i][j]) != m.end()) {
            ans -= m[slope[i][j]];
        }
        m[slope[i][j]]++;
      }
      //remove line
    }
  }
  
  
  cout << ans << endl;
  return 0;
}
