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

namespace Fenwick {
    const int FENWICK_SIZE = 200000 + 100;
    struct Fenwick {
        long long tree[FENWICK_SIZE];
        int sz;
        void init(int n) {
            sz = n;
            for(int i = 0; i <= n + 1; i++) tree[i] = 0;
        }

        void update(int i, int val) {
            i++;
            while(i < sz){
                tree[i] += val;
                i += (i & -i);
            }
        }

        long long pre(int i) {
            long long sum = 0;
            while(i > 0){
                sum += tree[i];
                i -= ( i & -i);
            }
            return sum;
        }
        long long query(int i, int j) {
            return pre(j + 1) - pre(i);
        }
    } tr;
}

using namespace Fenwick; 

using ll = long long;

void solve() {
    int n;
    string s;
    cin >> n >> s;
    
    long long cnt1 = 0, cnt2 = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '-') cnt1++;
        else cnt2++;
    }
    
    cout << (cnt1 / 2) * (cnt1 - cnt1 / 2) * cnt2 << endl;
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
