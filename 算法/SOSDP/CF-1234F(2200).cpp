/*
思路：
1. 找两个互不相交的substring 并且他们没有共同的character
2. 可以暴力找出所有的substring 只有unique character 然后存起来，O(20n) 最多
3. SOSDP，然后找出两个互补state 里长度最大的加起来。他们因为没有共同character，所以也一定是不相交的
*/

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
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

int complement(int st) {
    int ans = 0;
    for(int i = 0; i < 20; i++) {
        if(st & (1 << i)) {

        } else {
            ans |= (1 << i);
        }
    }
    return ans;
}


void solve() {
    int n;
    string s;
    cin >> s;
    n = s.size();

    //find two non overlapping substring such that no repeat characters
    vector<int> f((1 << 20) + 5);
    for(int i = 0; i < n; i++) {
        int st = 0;
        int cnt = 0;
        for(int j = i; j < n; j++) {
            int c = s[j] - 'a';
            if(st & (1 << c)) break;
            st |= (1 << c);
            cnt++;
            f[st] = cnt; 
        }
    }

    //SOS
    for(int i = 0; i < 20; i++) {
        for(int st = (1 << 20) - 1; st >= 0; st--) {
            if(st & (1 << i)) {
                f[st] = max(f[st], f[st ^ (1 << i)]);
            }
        }
    }

    int ans = 0;
    for(int st = 0; st < (1 << 20); st++) {
        int cst = complement(st);
        ans = max(ans, f[st] + f[cst]);
    }
    cout << ans << endl;

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
