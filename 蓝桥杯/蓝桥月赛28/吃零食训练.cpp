//https://www.lanqiao.cn/problems/20315/learning/?contest_id=254
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



void solve() {
    vector<int> a(3);
    for(int i = 0; i < 3; i++) cin >> a[i];
    long long s = 0;
    
    s += (a[1] / 2 * 2);
    a[1] %= 2;

    int x = min(a[0], a[2]);
    s += (2 * x);
    a[0] -= x;
    a[2] -= x;

    if(a[0]) {
        s += (a[1]);
    }
    if(a[2]) {
        s += (a[2] / 2);
    }
    
    cout << s << endl;
}


int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
