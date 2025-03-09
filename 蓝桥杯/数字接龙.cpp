//https://www.lanqiao.cn/problems/19712/learning/
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;
const int N = 15;
int a[N][N];
bool vis[N][N];
vector<vector<int>> dir = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
bool to[N][N][N][N];
int n, k;
bool ok = false;
void dfs(int r, int c, string& s) {
  if(s.size() + 1 == n * n && r == n - 1 && c == n - 1) {
    cout << s << endl;
    ok = true;
    return;
  }
  //cout << s << endl;
  if(ok) return;
  vis[r][c] = true;
  for(int i = 0; i < 8; i++) {
    int newr = r + dir[i][0];
    int newc = c + dir[i][1];
    if(newr < 0 || newr >= n || newc < 0 || newc >= n || vis[newr][newc] || a[newr][newc] != ((s.size() + 1) % k)) continue; 

    int dif = abs(newr - r) + abs(newc - c);
    if(dif == 2) {
      bool can = true;
      int r1 = r, c1 = c;
      int r2 = newr, c2 = newc;
      if(r1 > r2) {
        swap(r1, r2);
        swap(c1, c2);
      }
      if(r + c == newr + newc) {
        if(c1 > 0 && to[r1][c1 - 1][r2][c2 + 1]) can = false;
      } else {
        if(c2 > 0 && to[r1][c1 + 1][r2][c2 - 1]) can = false;
      }
      if(can) {
        to[r][c][newr][newc] = true;
        to[newr][newc][r][c] = true;
        s += to_string(i);
        dfs(newr, newc, s);
        s.pop_back();
        to[r][c][newr][newc] = false;
        to[newr][newc][r][c] = false;
      }
    } else {
        to[r][c][newr][newc] = true;
        to[newr][newc][r][c] = true;
        s += to_string(i);
        dfs(newr, newc, s);
        s.pop_back();
        to[r][c][newr][newc] = false;
        to[newr][newc][r][c] = false;
    }
  }
  vis[r][c] = false;
}

int main()
{
  // 请在此输入您的代码
  cin >> n >> k;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cin >> a[i][j];
    }
  }

  memset(to, 0, sizeof to);
  memset(vis, 0, sizeof vis);

  string s = "";
  dfs(0, 0, s);
  if(!ok) cout << -1 << endl;

  return 0;
}
