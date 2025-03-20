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

int ask(int val) {
    cout << val << endl;
    //int x = 1, y = 2;
    //return (x | val) + (y | val);
    int n;
    cin >> n;
    return n;
}

int getbit(int n, int i) {
    int b = 0;
    if(n & (1 << i)) b = 1;
    return b;
}

void solve() {
    int x1 = 0, x2 = 0;
    for(int i = 0; i < 30; i++) {
        if(i % 2 == 1) x1 |= (1 << i);
        else x2 |= (1 << i);
    }

    int n1 = ask(x1);
    int n2 = ask(x2);

    vector<int> cnt(30);
    int car = 0;
    for(int i = 0; i < 30; i++) {
        int b1 = getbit(n1, i);
        int b2 = getbit(n2, i);
       
        if(i == 0) {
            if(b1 == 0) {
                //0 1
                //0 0
                if(getbit(n1, 1) == 0) {
                    cnt[0] = 0;
                } else {
                    cnt[0] = 2;
                }
            } else {
                cnt[0] = 1;
            }
        } else {
            int usen = -1;
            int other = -1;
            if(i % 2 == 0) {
                usen = n1;
                other = n2;
            } else {
                usen = n2;
                other = n1;
            }
            
            //previous has carry over
            int b = getbit(usen, i);
            if(b == 1) { //1 1 : has carry to next  0 0 : no carry to next
                if(i == 29) {
                    if(getbit(usen, i + 1) == 1) cnt[i] = 2;
                    else cnt[i] = 0;
                } else {
                    if(getbit(usen, i + 1) == 1) cnt[i] = 2;
                    else cnt[i] = 0;
                }
            } else { //0 1
                cnt[i] = 1;
            }
        }
    }
    
    int m;
    cout << "!" << endl;
    cin >> m;
    int ans = 0;
    car = 0;
    for(int i = 0; i < 30; i++) {
        int b = 0;
        if(m & (1 << i)) b = 1;
        ans += ((1 << i) * cnt[i]);
        if(b == 0) {

        } else {
            ans += ((1 << i) * (2 - cnt[i]));
        }
    }
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
