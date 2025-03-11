//https://www.lanqiao.cn/problems/17105/learning/?page=1&first_category_id=1&second_category_id=3&name=%E5%8F%8C%E5%AD%90%E6%95%B0
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

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

const int N = 4830458 + 100;
vector<int> pro[N];
bool is[N], isp[N];
void init() {
    memset(is, 0, sizeof is);
    memset(isp, 0, sizeof isp);
    for(int i = 2; i < N; i++) {
        if(is[i]) continue;
        isp[i] = true;
        for(int j = i; j < N; j += i) {
            is[j] = true;
            pro[j].push_back(i);
        }
    }
}

long long get(int n) {
    //p * q <= n
    long long ans = 0;
    
    for(int i = 1; i <= n; i++) {
        for(int p : pro[i]) {
            int q = i / p;
            if(isp[q] && p != q) {
                ans++;
                //cout << p << " " << q << endl;
                break;
            }
        }
    }
    return ans;
}

void solve() {
    init();
    cout << get(4830458) - get(48) << endl;
    cout << get(48) << endl;
}

int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
