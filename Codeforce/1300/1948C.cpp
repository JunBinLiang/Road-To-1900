#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

template <typename T>
ostream &operator<<(ostream &out, const set<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

//9:55 - 10:06

const int N = 2e5 + 10;
int n;
bool ok = false;
bool vis[2][N];
vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
void dfs(vector<string>& a, int r, int c) {
    if(r < 0 || c < 0 || r >= 2 || c >= n) return;
    if(r == 1 && c == n - 1) {
        ok = true;
        return;
    }
    if(vis[r][c]) return;
    vis[r][c] = true;
    for(auto& d : dir) {
        int newr = r + d[0], newc = c + d[1];
        if(newr < 0 || newr >= 2 || newc < 0 || newc >= n) continue;
        if(a[newr][newc] == '>') {
            if(newc + 1 == c && newr == r) {
            } else {
                dfs(a, newr, newc + 1);
            }
        } else {
            if(newc - 1 == c && newr == r) {
              
            } else {
                dfs(a, newr, newc - 1);
            }
        }
    }
}

void solve() {
    cin >> n;
    vector<string> a(2);
    for(int i = 0; i < 2; i++) {
        cin >> a[i];
    }

    for(int i = 0; i <= n; i++) {
        vis[0][i] = vis[1][i] = false;
    }

    ok = false;
    dfs(a, 0, 0);

    if(ok) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }



}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
