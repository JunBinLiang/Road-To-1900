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

//5:47 - 6:08
bool comp(pair<int, int>& p1, pair<int, int>& p2) {
    return p1.second < p2.second;
}
void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++) cin >> a[i].first;
    for(int i = 0; i < n; i++) cin >> a[i].second;
    sort(a.begin(), a.end(), comp);

    long long ans = 0;
    vector<long long> ldp(n);
    for(int i = 0; i < a.size(); i++) {
        if(a[i].second > a[i].first) {
            ldp[i] += (a[i].second - a[i].first);
        }
        if(i) {
            ldp[i] += ldp[i - 1];
        }
    }

    if(k == 0) {
        cout << ldp.back() << endl;
        return;
    }

    //smallest k-sum
    priority_queue<int> pq;
    long long s = 0;
    for(int i = n - 1; i >= 0; i--) {
        long long left = 0;
        if(i) left = ldp[i - 1];
        pq.push(a[i].first);
        s += a[i].first;
        while(pq.size() > k) {
            s -= pq.top();
            pq.pop();
        }
        if(pq.size() == k) {
            ans = max(ans, left - s);
        }
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
