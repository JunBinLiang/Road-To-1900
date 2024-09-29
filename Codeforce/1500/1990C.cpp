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

//5:38 - 6:05
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    long long s = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        s += a[i];
    }

    vector<int> b(n);
    map<int, int> f;
    priority_queue<int> pq;
    for(int i = 0; i < n; i++) {
        f[a[i]]++;
        if(f[a[i]] == 2) {
            pq.push(a[i]);
        }
        if(pq.size() > 0) {
            b[i] = pq.top();
        }
    }

    long long ans = s;
    

    s = 0;
    for(int i = 0; i < n; i++) s += b[i];
    ans += s;

    f.clear();
    while(pq.size() > 0) pq.pop();
    vector<int> c(n);
    for(int i = 0; i < n; i++) {
        f[b[i]]++;
        if(f[b[i]] == 2) {
            pq.push(b[i]);
        }
        if(pq.size() > 0) {
            c[i] = pq.top();
        }
    }
    
    s = 0;
    for(int i = 0; i < c.size(); i++) s += c[i];
    while(c.back() != 0) {
        ans += s;
        s -= c.back();
        c.pop_back();
    }
    
    cout << ans << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
