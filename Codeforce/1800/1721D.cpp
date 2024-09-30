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


//8:33 - 9:00
int ans = 0;

void off(int i) {
  if(ans & (1 << i)) {
      ans ^= (1 << i);
  }
}

bool check(vector<int>& A, vector<int>& B, int i) {
    vector<int> vec1(2), vec2(2);
    for(int x : A) {
        if(x & (1 << i)) vec1[1]++;
        else vec1[0]++;
    }

    for(int x : B) {
        if(x & (1 << i)) vec2[1]++;
        else vec2[0]++;
    }
    if((vec1[0] != vec2[1]) || (vec1[1] != vec2[0])) { //can not divide this group
        return false;
    }
    return true;
}

void solve() {
    int n;
    scanf("%d", &n);
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    for(int i = 0; i < n; i++) scanf("%d", &b[i]);
    ans = 0;
    for(int i = 0; i <= 30; i++) {
        ans |= (1 << i);
    }
    
    
    vector<vector<int>> g = {a, b};
    for(int i = 30; i >= 0; i-- ) {
        bool success = true;

        for(int j = 0; j < g.size() && success; j += 2) {
            vector<int>& A = g[j];
            vector<int>& B = g[j + 1];
            if(!check(A, B, i)) success = false;
        }

        if(success) {
            vector<vector<int>> newg;
            for(int j = 0; j < g.size(); j += 2) {
                vector<int>& A = g[j];
                vector<int>& B = g[j + 1];
                vector<int> vec1, vec2;
                vector<int> vec3, vec4;
                for(int x : A) {
                    if(x & (1 << i)) vec1.push_back(x);
                    else vec2.push_back(x);
                }

                for(int x : B) {
                    if(x & (1 << i)) vec3.push_back(x);
                    else vec4.push_back(x);
                }
                if(vec1.size() > 0) {
                    newg.push_back(vec1);
                    newg.push_back(vec4);
                }
                if(vec2.size() > 0) {
                    newg.push_back(vec2);
                    newg.push_back(vec3);
                }
            }
            g = newg;
        } else {
            off(i);
        }
    }

    printf("%d\n", ans);
    
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
