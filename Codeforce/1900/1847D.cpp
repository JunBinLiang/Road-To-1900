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

const int SIZE = 200000 + 100;
struct Fenwick {
  int tree[SIZE];
  void init(int n) {
    for(int i = 0; i <= n + 1; i++) tree[i] = 0;
  }

  void update(int i, int val) {
    i++;
    while(i < SIZE){
      tree[i] += val;
      i += (i & -i);
    }
  }

  int pre(int i) {
    int sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
} tr, tr1;

//12:28 - 2:06
void add(vector<pair<int, int>>& vec, vector<int>& line) {
    for(int i = 0; i < line.size(); i++) {
        int j = i + 1;
        while(j < line.size() && line[j] == line[j - 1] + 1) {
            j++;
        }
        vec.push_back({line[i], line[j - 1]});
        i = j - 1;
    }
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    string s;
    cin >> s;

    vector<pair<int, int>> a;
    for(int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        a.push_back({l, r});
    }

    set<int> notSet;
    for(int i = 0; i < n; i++) {
        notSet.insert(i);
    }

    set<pair<int, int>> se;
    vector<pair<int, int>> vec;
    for(int i = 0; i < m; i++) {
        //cout << i << endl;
        int l = a[i].first, r = a[i].second;
        int curl = l;
        vector<pair<int, int>> temp;
        while(true) {
            auto it = se.upper_bound({curl - 1, 1000000});
            if(it == se.end()) {
                //cout << "yes " << i << endl;
                break;
            } else {
                int L = it -> second, R = it -> first;
                if(L > r) break;
                temp.push_back({L, R});
                curl = R + 1;
            }
            //cout << "tt " << it -> second << " " << it -> first << " " << curl << endl;
            /*if(i == 2 && c <= 2) {
                cout << "tt " << it -> second << " " << it -> first << " " << curl << endl;
                if(c == 2)return;
            }*/
        }
        
        int newl = l, newr = r;
        
        if(temp.size() > 0) {
            newl = min(newl, temp[0].first);
            newr = max(newr, temp.back().second);
        } else {
            
        }
        
        for(pair<int, int>& p : temp) se.erase({p.second, p.first});
        se.insert({newr, newl});
        
        
        //for(auto it : se) {
            //cout << "[ " << it.second << ", " << it.first << "] ";
        //}
        //cout << endl << endl;
        
        vector<int> line;
        while(true) {
            auto it = notSet.upper_bound(newl - 1);
            if(it == notSet.end()) break;
            if(*it <= newr) {
                line.push_back(*it);
                notSet.erase(*it);
            } else {
                break;
            }
        }
        //cout << "line " << line << endl;
        add(vec, line);
        //cout << "vec  " << endl;
        //for(auto it : vec) cout << "[ " << it.first << ", " << it.second << "] ";
        //cout << endl;
        //cout << endl;
    }
    
    tr.init(n + 1);
    tr1.init(n + 1);
    vector<int> pos(n + 1, -1);
    vector<int> prefix;
    for(int i = 0; i < vec.size(); i++) {
        int l = vec[i].first, r = vec[i].second;
        int one = 0;
        for(int j = l; j <= r; j++) {
            if(s[j] == '1') {
                tr1.update(j, 1);
                one++;
            }
            pos[j] = i;
        }
        tr.update(i, one);
        prefix.push_back(r - l + 1);
        if(i) prefix[i] += prefix[i - 1];
    }
    
    int one = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '1') one++;
    }
    
    //cout << endl;
    for(int i = 0; i < q; i++) {
        int index;
        cin >> index;
        index--;
        //pos[index], update that interval
        if(s[index] == '1') {
            if(pos[index] != -1)
              tr.update(pos[index], -1);
            tr1.update(index, -1);
            s[index] = '0';
            one--;
        } else {
            if(pos[index] != -1)
              tr.update(pos[index], 1);
            tr1.update(index, 1);
            s[index] = '1';
            one++;
        }

        int l = 0, r = vec.size() - 1;
        int p = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(prefix[mid] >= one) {
                p = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        
        if(p == -1) {
            cout << (prefix.back() - tr.query(0, vec.size() - 1)) << endl;
            continue;
        }

        int count = 0;
        if(p > 0) {
            count += tr.query(0, p - 1);
        }
        
       
        
        int more = one;
        if(p > 0) more -= prefix[p - 1];
        
        //cout << "query " << i << "   " << p << " " << one << endl;
        //cout << s <<"  " << more <<"  " << tr1.query(vec[p].first, vec[p].first + more - 1) << endl;
        //cout << count << "   " << tr.query(0, p - 1) << endl;
        
        count += tr1.query(vec[p].first, vec[p].first + more - 1);
        cout << (one - count) << endl;
        
        //cout << endl;
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
