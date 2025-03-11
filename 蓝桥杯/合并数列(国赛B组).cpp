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
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for(int i = 0; i < m; i++) {
        cin >> b[i];
    }

    long long s1 = 0, s2 = 0;
    int i = 0, j = 0;
    int chunk = 0;
    while(i < n && j < m) {
        if(s1 == s2) {
            if(a[i] > b[j]) {
                s1 += a[i++];
            } else {
                s2 += b[j++];
            }
        } else if(s1 > s2) {
            s2 += b[j++];
        } else {
            s1 += a[i++];
        }
        if(s1 == s2) {
            chunk += 2;
        }
        //cout << i << "  " << j << "  |" << s1 << " " << s2 << " " << chunk << endl;
    }

    cout << (n + m) - chunk - 2 << endl;
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
