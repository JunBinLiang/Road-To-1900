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

//1:07 - 1:44

void no() {
    printf("NO\n");
}
void yes() {
    printf("YES\n");
}

pair<int, int> get(set<int>& s) {
    auto it1 = s.begin();
    auto it2 = s.end();
    it2--;
    return {*it1, *it2};
}

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    set<int> sets[3];
    for(int i = 1; i <= n; i++) {
        sets[a[i]].insert(i);
    }

    for(int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        if(op == 1) {
            int s;
            scanf("%d", &s);
            int sum = 2 * n - sets[1].size();
            if(sum < s) {
                no();
                continue;
            }

            if(s % 2 == 1) {
                if(sets[1].size() == 0) {
                    no();
                    continue;
                }

                if(sets[1].size() % 2 == 1) {
                    yes();
                } else {
                    pair<int, int> p = get(sets[1]);
                    int sum1 = sum - (2 * (p.first - 1)) - 1;
                    int sum2 = sum - 2 * (n - p.second) - 1;
                    //cout << p.first << "  " << p.second << endl;
                    //cout << sum1 << "  " << sum2 << endl;
                    if(sum1 >= s || sum2 >= s) yes();
                    else no();
                }
            } else {
                if(sets[1].size() % 2 == 0) {
                    yes();
                } else {
                    pair<int, int> p = get(sets[1]);
                    int sum1 = sum - (2 * (p.first - 1)) - 1;
                    int sum2 = sum - 2 * (n - p.second) - 1;
                    if(sum1 >= s || sum2 >= s) yes();
                    else no();
                }
            }

        } else {
            int index, v;
            scanf("%d%d", &index, &v);
            sets[a[index]].erase(index);
            sets[v].insert(index);
            a[index] = v;
        }
    }
    
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
