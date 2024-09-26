//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P4735
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

//7:51 - 8:24
int c(int a, int n) {
    if(n % 2 == 0) return -a;
    else return a;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, int> f;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        f[a[i]]++;
    }

    cout << f.size() << endl;
    vector<int> stk;
    set<int> cur;
    for(int i = 0; i < n; i++) {
        f[a[i]]--;
        if(cur.find(a[i]) != cur.end()) {
            continue;
        }
        
        /*if(i == 3) {
          cout << "gg " << endl;
          cout << c(a[i], stk.size() - 1) << "  " << c(stk.back(), stk.size() - 1) << endl;
        }*/

        while(stk.size() > 0) {
            int sz = stk.size();
            if(sz == 1) {
                if(c(a[i], stk.size() - 1) < c(stk.back(), stk.size() - 1) && f[stk.back()] > 0) {
                    int v = stk.back();
                    cur.erase(v);
                    stk.pop_back();
                } else {
                    break;
                }
            } else {
                if(f[stk[sz - 1]] > 0 && f[stk[sz - 2]] > 0 && c(a[i], sz - 2) < c(stk[sz - 2], sz - 2)) {
                      int v1 = stk.back(); stk.pop_back();
                      cur.erase(v1);
                      int v2 = stk.back(); stk.pop_back();
                      cur.erase(v2);
                }  else if(c(a[i], stk.size() - 1) < c(stk.back(), stk.size() - 1) && f[stk.back()] > 0) {
                      int v = stk.back();
                      cur.erase(v);
                      stk.pop_back();
                } else {
                    break;
                }
            }
        }
        cur.insert(a[i]);
        stk.push_back(a[i]);
        //cout << stk << endl;
    }

    for(int i : stk) cout << i << " ";
    cout << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
