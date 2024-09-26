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

//4:41 - 5:05
void solve() {
    int k;
    cin >> k;
    vector<int> a;
    for(int i = 0; i < k; i++) {
        int n;
        cin >> n;
        a.push_back(n);
        for(int j = 1; j < n; j++) {
            int pa;
            cin >> pa;
        }
    }

    sort(a.begin(), a.end());
    vector<bool> vis(a.size());
    vis[a.size() - 1] = true;


    int ans = a.back();
    //cout << ans << endl;
    for(int i = 21; i >= 0; i--) {
        int b = 0;
        if(ans & (1 << i)) b = 1;
        if(b == 1) {
            for(int j = 0; j < a.size(); j++) {
                if(vis[j]) continue;
                if(a[j] >= (1 << i)) {
                    ans |= ((1 << i) - 1);
                    break;
                }
            }
        } else { 
            int goodCount = 0;  
            int index = -1; 
            for(int j = 0; j < a.size(); j++) {
                if(vis[j]) continue;
                if(a[j] >= (1 << i)) {
                    goodCount++;
                    index = j;
                }
            }
            if(goodCount == 0) {
                continue;
            }
            if(goodCount > 1) {
                ans |= (1 << i);
                ans |= ((1 << i) - 1);
                break;
            }
            a[index] -= (1 << i);
            ans |= (1 << i);
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
