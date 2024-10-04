#include <bits/stdc++.h>
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

//11:52 - 2:10
void solve() {
    long long b, c, d;
    cin >> b >> c >> d;
    long long a = 0;
    for(int i = 0; i < 61; i++) {
        int bitd = 0;
        if(d & (1ll << i)) bitd = 1;

        int bitb = 0;
        if(b & (1ll << i)) bitb = 1;

        int bitc = 0;
        if(c & (1ll << i)) bitc = 1;

        if(bitd == 0) {
            if(bitb != 0) {
                if(bitc == 0) {
                    cout << -1 << endl;
                    return;
                }
                a += (1ll << i);
            } else {
                a += (0ll << i);
            }
        } else {
            if(bitb == 0) {
                if(bitc == 1) {
                    cout << -1 << endl;
                    return;
                } else {
                    a += (1ll << i);
                }
            } else {
                a += (0ll << i);
            }
        }   
    }

    if((a | b) - (a & c) != d) {
        cout << -1 << endl;
        return;
    }
    
    cout << a << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
