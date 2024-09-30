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

//2:02 - 2:05
void solve() {
    int n;
    scanf("%d", &n);
    vector<int> b(30);
    for(int i = 0; i < n; i++) {
        int op;
        scanf("%d", &op);
        if(op == 1) {
            int x;
            scanf("%d", &x);
            b[x]++;
        } else {
            int w;
            scanf("%d", &w);
            int c = 0;
            for(int j = 29; j >= 0; j--) {
                c = c * 2;
                if(w & (1 << j)) {
                    c++;
                }
                if(b[j] >= c) {
                    c = 0;
                } else {
                    c -= b[j];
                }
            }
            if(c == 0) printf("YES\n");
            else printf("NO\n");
        }
    }
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
