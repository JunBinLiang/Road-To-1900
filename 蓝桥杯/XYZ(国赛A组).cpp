//https://www.lanqiao.cn/problems/17097/learning/?page=1&first_category_id=1&name=XYZ
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

void check(int L, int R) {
    int ans = 0;
    for(int i = L; i <= R; i++) {
        for(int j = L; j <= R; j++) {
            if(i + j <= R) ans++;
        }
    }
    cout << ans << endl;
}

void solve() {
    int L, R;
    cin >> L >> R;
    if(L == R) {
        cout << 0 << endl;
        return;
    }

    if(L + L > R) {
        cout << 0 << endl;
        return;
    }
    
    //check(L, R);

    //3 4 5 6 7 8 9 10 11 12 13
    //3 : 6 7 8 9 10 11 12 13
    //4 :     8 9 10 11 12 13
    //5 :         10 11 12 13
    //6 :               12 13
    long long ans = 0;
    long long l = L, r = R / 2;
    if(r * 2 > R) r--;

    long long sz = (r - l) + 1;
    long long first = (R - (L + L) + 1);
    long long last = ((first % 2 == 0) ? 2 : 1);
    ans = (first + last) * sz / 2;
    ans *= 2;
    long long dup = R / 2;
    if(dup * 2 > R) dup--;
    ans -= (dup - L + 1);
    cout << ans << endl;
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
