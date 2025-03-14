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

void solve() {
    int n;
    cin >> n;
    vector<int> a;
    for(int i = 2; i <= n - 1; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    for(int i = 0; i + 2 < a.size(); i++) {
        if(a[i] == 1 && a[i + 1] == 0 && a[i + 2] == 1) {
            cout << "NO" << endl;
            return; 
        }
    }
    cout << "YES" << endl;
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
