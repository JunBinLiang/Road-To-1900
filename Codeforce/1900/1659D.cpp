#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

template <typename T>
ostream &operator<<(ostream &out, const set<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

//6:35 - 7:35
const int N = 2e5 + 10;

void output(vector<int>& ans) {
    for(int i = 1; i < ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
}

void solve() {
    int n;
    scanf("%d", &n);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> ans(n + 1); 
    //if(a[1] == 0) ans[1] = 0;
    //else ans[1] = 1;
    int j = 1;
    while(j <= n && a[j] == 0) {
        ans[j] = 0;
        j++;
    }
    if(j <= n)
        ans[j] = 1;
    int one = 0;
    for(int i = j; i <= n; i++) {
        if(ans[i] == 1) {
            a[i] -= (i - 1);
            while(j <= min(n, i + a[i] - 1)) {
                ans[j++] = 1;
                one++;
            }
            if(j <= n) {
                ans[j++] = 0;
            }
        } else {
            a[i] -= one;
            int r = j + a[i];
            while(j <= min(n, r - 1)) {
                ans[j++] = 1;
                one++;
            }
            if(j <= n) {
                ans[j++] = 0;
            }
        }
    }
    output(ans);
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
