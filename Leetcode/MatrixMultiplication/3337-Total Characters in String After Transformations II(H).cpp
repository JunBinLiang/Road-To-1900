#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

int MOD = 1e9 + 7;
const int N = 26;
ll a[N][N];
ll f1[N];

void mul1() {
  ll temp[N];
  for(int i = 0; i < N; i++) temp[i] = f1[i];
  for(int c = 0; c < N; c++) {
    ll sum = 0;
    for(int r = 0; r < N; r++) {
      sum += (temp[r] * a[r][c]);
      sum %= MOD;
    }
    f1[c] = sum;
  }
}

void mul2() {
  ll temp[N][N];
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      temp[i][j] = a[i][j];
            
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      ll sum = 0;
      for(int k = 0; k < N; k++) {
        sum += temp[i][k] * temp[k][j];
        sum %= MOD;
      }
      a[i][j] = sum;
    }
  } 
}


class Solution {
public:
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        memset(a, 0, sizeof a);
        for(int i = 0; i < N; i++) {
            f1[i] = 1;
        }
        
        for(int d = 0; d < 26; d++) {
            
            for(int j = 1; j <= nums[d]; j++) {
                int nxt = (d + j) % 26;
                a[nxt][d] = 1;
            }
        }
        
        
        while(t) {
            if (t & 1) mul1();  // res = res * a
            mul2();  // a = a * a
            t >>= 1;
        }
        
        /*for(int i = 0; i < 26; i++) {
            cout << f1[i] << "  ";
        } cout << endl;*/
        
        long long ans = 0;
        for(int i = 0; i < s.size(); i++) {
            int d = s[i] - 'a';
            //cout << d << endl;
            ans += f1[d];
            ans %= MOD;
        }
        return ans;
    }
};
