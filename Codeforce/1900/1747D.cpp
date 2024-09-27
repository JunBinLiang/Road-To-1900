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
//4:56 - : 6:07

int find1(vector<int>& vec, int L, int R) {
    int l = 0, r = vec.size() - 1;
    int p = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(vec[mid] <= R) {
            p = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    if(p == -1) return p;
    return vec[p];
}

int find2(vector<int>& vec, int L, int R) {
    int l = 0, r = vec.size() - 1;
    int p = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(vec[mid] >= L) {
            p = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    if(p == -1) return p;
    return vec[p];
}

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    //cout << a << endl;

    int xo = 0;
    map<int, vector<int>> mp[2];
    mp[0][0].push_back(0);

    vector<int> prefix;
    vector<int> sums;
    int s = 0;
    sums.push_back(s);
    prefix.push_back(0);
    for(int i = 1; i <= n; i++) {
        xo ^= a[i];
        prefix.push_back(xo);
        mp[i % 2][xo].push_back(i);
        s += a[i];
        sums.push_back(s);
    }
    
    //cout << prefix << endl;


    for(int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        if(sums[r] - sums[l - 1] == 0) {
            printf("0\n");
            continue;
        }
        
        if((prefix[r] ^ prefix[l - 1]) != 0) {
            printf("-1\n");
            continue;
        }

        int sz = r - l + 1;
        if(sz % 2 == 1) {
            printf("1\n");
            continue;
        }
        
        int index1 = -1;

        if(mp[l % 2].find(prefix[l - 1]) != mp[l % 2].end()) {
            index1 = find1(mp[l % 2][prefix[l - 1]], l, r);
        }

        if(index1 == -1 || index1 < l) {
            printf("-1\n");
            continue;
        }

        if(a[l] == 0 || a[r] == 0 ) {
            printf("1\n");
            continue;
        }

        printf("2\n");
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
