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

//12:24 - 12:53

const int MAX = 300000 + 100;

struct Node {
  int l, r;
  int mn;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 2000000000};
  tree[id * 2 + 2] = {mid + 1, r, 2000000000};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mn = min(tree[id].mn, val);  
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  tree[id].mn = min(tree[left].mn, tree[right].mn);
}

int query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mn;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return min(query(left, s, mid), query(right, mid + 1, e));
  }
}

void print(vector<int>& ans) {
    for(int x : ans) cout << x << " ";
    cout << endl;
}

void update(int& ans, int val) {
    if(ans == -1) ans = val;
    else ans = min(ans, val);
}

long long get(vector<long long>& p, int l, int r) {
    return l == 0 ? p[r] : p[r] - p[l - 1];
}

int find1(vector<int>& a, vector<long long>& p, int index) {
    int l = 0, r = index - 1;
    int po = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        long long s = get(p, mid, index - 1);
        if(s <= a[index]) {
            r = mid - 1;
        } else {
            int cnt = (index - mid);
            int mn = query(0, mid, index - 1);
            long long t = ((mn + 0ll) * cnt);
            if(t == s && cnt != 1) { //all maximum
                r = mid - 1;
            } else {
                po = mid;
                l = mid + 1;
            }
        }
    }
    return po;
}

int find2(vector<int>& a, vector<long long>& p, int index) {
    int l = index + 1, r = a.size() - 1;
    int po = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        long long s = get(p, index + 1, mid);
        int mn = query(0, index + 1, mid);
        if(s <= a[index]) {
            l = mid + 1;
        } else {
            int cnt = mid - index;
            if((mn + 0ll) * cnt == s && cnt != 1) {
                l = mid + 1;
            } else {
                po = mid;
                r = mid - 1;
            }
        }
    }
    return po;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> ans(n, -1);
    vector<long long> p(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    p[0] = a[0];
    for(int i = 1; i < n; i++) {
        p[i] = a[i];
        if(i) p[i] += p[i - 1];
    }
    
    tree[0] = {0, n, 2000000000};
    build(0);
    for(int i = 0; i < n; i++) update(0, i, a[i]);
    

    //find1(a, p, 4);
    //return;
    for(int i = 0; i < n; i++) {
        int p1 = find1(a, p, i), p2 = find2(a, p, i);
        if(p1 != -1) {
            update(ans[i], i - p1);
        }
        if(p2 != -1) {
            update(ans[i], p2 - i);
        }
        //cout << i << " " << p1 << " " << p2 << endl;
    }
    
    for(int i = 0; i < n; i++) {
        if(i + 1 < n && a[i + 1] > a[i]) ans[i] = 1;
        if(i > 0 && a[i - 1] > a[i]) ans[i] = 1;
    }
    
    print(ans);
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
