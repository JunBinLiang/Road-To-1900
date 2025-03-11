//https://www.lanqiao.cn/problems/17110/learning/?page=1&first_category_id=1&second_category_id=3&name=%E6%8A%93%E5%A8%83
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

int find1(vector<double>& p, int L) {
    int l = 0, r = p.size() - 1;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(p[mid] >= L) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int find2(vector<double>& p, int R) {
    int l = 0, r = p.size() - 1;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(p[mid] <= R) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(n);
    vector<double> p;
    for(int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        p.push_back((l + 0.0 + r) / 2);
    }

    //计算有多少个中点落在区间内
    sort(p.begin(), p.end());

    while(m--) {
        int L, R;
        cin >> L >> R;
        int l = find1(p, L), r = find2(p, R);
        if(l == -1) {
            cout << 0 << endl;
            continue;
        }
        cout << r - l + 1 << endl;
    }
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
