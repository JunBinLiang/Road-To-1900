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


//4:47 - 4:57
void print(vector<int>& p) {
    for(int i = 1; i < p.size(); i++) cout << p[i] << " ";
    cout << endl;
}
void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> p(n + 1);
    p[n] = 1;
    p[1] = x;

    if(x == n) {
        for(int i = 2; i < n; i++) p[i] = i;
        print(p);
        return;
    }
    
    //minimal

    if(n % x != 0) {
        cout << -1 << endl;
        return;
    }
    
    
    for(int i = 2; i < n; i++) p[i] = i;
    
    while(x != n) {
        for(int j = 2; j <= n; j++) {
            int v = x * j;
            if(n % v == 0) {
                p[x] = v;
                x = v;
                break;
            }
        }
    }
    
    print(p);
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
