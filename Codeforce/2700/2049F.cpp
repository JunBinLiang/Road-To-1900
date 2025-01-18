#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    

using namespace std;

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

using ll = long long;
const int N = 1e5 + 10;
long long a[N];

int p[N * 21], t[30], lens[N * 21];
unordered_map<long long, int> mps[N * 21];
set<pair<int, int>> s[21];

int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
}

void merge(int ith, int r1, int r2) { //r2 -> r1
    if(mps[r1].size() < mps[r2].size()) {
        merge(ith, r2, r1);
        return;
    }
    for(auto it = mps[r2].begin(); it != mps[r2].end(); it++) {
        long long k = it -> first;
        int v = it -> second;
        mps[r1][k] += v;
    }
    
    s[ith].erase({lens[r2], r2});
    s[ith].erase({lens[r1], r1});
    p[r2] = r1;
    lens[r1] += lens[r2];
    if(mps[r1].size() == (1 << ith)) {
        s[ith].insert({lens[r1], r1});
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    memset(t, 0, sizeof t);
    for(int i = 0; i < n * 21; i++) {
        p[i] = i;
        mps[i].clear();
    }
    for(int i = 0; i < 21; i++) {
        s[i].clear();
    }

    //update
    vector<pair<int, int>> q;
    for(int i = 0; i < m; i++) {
        int j, x;
        cin >> j >> x;
        j--;
        q.push_back({j, x});
        a[j] += x;
    }
    
    //Printing and find out MEX must be : 1 2 4 8 16 ...
    vector<int> MEX;
    for(int i = 0; ((1 << i)) <= n + 10; i++) {
        if((1 << i) > n + 2) continue;
        MEX.push_back(1 << i);
    }
    
    /*for(int i = 0; i < n; i++) {
       cout << a[i] << "  ";
    }
    cout << endl << endl;*/

    for(int i = 0; i < MEX.size(); i++) {
        int mex = MEX[i];
        for(int j = 0; j < n; j++) {
            int r = find((n * i) + j);
            if(a[j] < mex) {
                mps[r][a[j]] = 1;
                lens[r] = 1;
                if(mps[r].size() == mex) s[i].insert({1, r});
            }
        }
        //cout << "mex " << mex << endl;
        for(int j = 1; j < n; j++) {
            if(a[j] < mex && a[j - 1] < mex) {
                int r1 = find((i * n) + j), r2 = find((i * n) + (j - 1));
                merge(i, r1, r2);
            }
        }
    }
    
    //do it reversely
    vector<int> ans;
    reverse(q.begin(), q.end());
    for(int k = 0; k < q.size(); k++) {
        auto& p = q[k];
        int mx = 0;
        for(int i = 0; i < MEX.size(); i++) {
            while(s[i].size()) {
                auto it = s[i].end(); it--;
                int r = it -> second;
                if(it -> first != lens[r]) {
                    s[i].erase(it);
                } else {
                    break;
                }
            }
            if(s[i].size() == 0) continue;
            auto it = s[i].end(); it--;
            mx = max(mx, it -> first);
        }
        ans.push_back(mx);
        int j = p.first, x = p.second;
        for(int i = 0; i < MEX.size(); i++) {
            int mex = MEX[i];
            if(a[j] < mex) {
                int r = find((i * n) + j);
                mps[r][a[j]]--;
                if(mps[r][a[j]] == 0) {
                    if(mps[r].size() == (1 << i)) {
                        s[i].erase({lens[r], r});
                    }
                    mps[r].erase(a[j]);
                }
                mps[r][a[j] - x]++;
                if(mps[r].size() == (1 << i)) s[i].insert({lens[r], r});
                continue;
            }

            if(a[j] >= mex && a[j] - x < mex) { //we can merge
                //unlock
                int r = find((i * n) + j);
                mps[r][a[j] - x] = 1;
                lens[r] = 1;
                
                if(mps[r].size() == (1 << i)) {
                    s[i].insert({lens[r], r});
                }

                if(j > 0 && a[j - 1] < mex) {
                    merge(i, find(i * n + j - 1), find(i * n + j));
                }
                if(j + 1 < n && a[j + 1] < mex) {
                    merge(i, find(i * n + j), find(i * n + j + 1));
                }
            }
        }
        a[j] -= x;
    }
    reverse(ans.begin(), ans.end());
    for(int x : ans) cout << x << endl;
}   


int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
