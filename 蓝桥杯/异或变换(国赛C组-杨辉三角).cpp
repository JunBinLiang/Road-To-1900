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

string gen(string s) {
    string ans = "";
    for(int i = 0; i < s.size(); i++) {
        if(i == 0) ans += s[i];
        else {
            int d1 = s[i - 1] - '0', d2 = s[i] - '0';
            ans += to_string(d1 ^ d2);
        }
    }
    return ans;
}

int get(long long n) {
    int cnt = 0;
    while(n % 2 == 0) {
        n /= 2;
        cnt++;
    }
    return cnt;
}

const int N = 20000 + 10;
long long f1[N], f2[N];

bool C(long long n, int r) { //return true if is double 
    if(r == 0 || r == n) {
        return false;
    }
    //C(10, 3)
    //(10 * 9 * 8) / (1 * 2 * 3)
    int up = f2[r];
    int down = f1[r];
    return up > down; 
}

void solve() {
    string s; int n; long long k;
    cin >> n >> k >> s;

    vector<int> a;
    for(int i = 0; i < s.size(); i++) {
        a.push_back(s[i] - '0');
    }

    memset(f1, 0, sizeof f1);
    memset(f2, 0, sizeof f2);
    for(int i = 1; i <= n; i++) {
        f1[i] = get(i);
        f1[i] += f1[i - 1];
    }
    
    for(int i = 1; i <= n; i++) {
        if(i > k) break;
        f2[i] = get(k - i + 1);
        f2[i] += f2[i - 1];
    }
    
    
    
    //do the answer
    vector<bool> bit;
    for(int i = 0; i < n; i++) {
        if(i <= k) {
            bool b = C(k, i);
            bit.push_back(b);
        }

        int o = 0;
        for(int j = 0; j < bit.size(); j++) {
            int index = i - j;
            if(!bit[j] && (s[index] == '1')) { //
                o++;
            }   
        }
        cout << o % 2;
    }
    
    cout << endl;
    
    /*cout << endl << endl;
    for(bool b : bit) {
        if(b) cout << 0 << " ";
        else cout << 1 << " ";
    }
    cout << endl;*/
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
