#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    
#include <deque>  

using namespace std;

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

set<int> s;
int cal1(vector<int>& a, vector<int>& b, int n, int cnt, int sz) {
    if(a.size() == 0) {
        return cnt + b.size();
    }

    //for(int x : a) cout << x << " ";
    //cout << endl;

    //for(int x : b) cout << x << " ";
    //cout << endl << endl;
    
    int mn = 1000000000;
    vector<int> p1, p2;
    for(int i = 0; i < a.size(); i++) {
        mn = min(mn, a[i]);
        p1.push_back(mn);
    }

    mn = 1000000000;
    p2.push_back(mn);
    for(int i = 1; i < b.size(); i++) {
        mn = min(mn, b[i]);
        p2.push_back(mn);
    }
    
    int ans = 0;
    for(int i = 1; i < b.size(); i++) {
        //swap b[0] and b[i]
        int l = 0, r = b.size() - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(sz + mid + 1 > n) {
                r = mid - 1;
                continue;
            }
            int mn1 = p2[mid];
            mn1 = min(mn1, b[i]);
            if(mid >= i) {
                mn1 = min(mn1, b[0]);
            }
            
            //cout << "mid " << mid << " " << mn1 << endl;

            int sz1 = mid + 1, sz2 = n - sz - sz1;
            //cout << sz1 << "  " << sz2 << endl;
            if(a.size() <= sz2) { //ok
                l = mid + 1;
                ans = max(ans, cnt + sz1);
                continue;
            }

            if(mn1 > p1[sz2]) {
                l = mid + 1;
                ans = max(ans, cnt + sz1);
            } else {
                r = mid - 1;
            }
        }
    }
    return ans;
}

int cal2(vector<int>& a, vector<int>& b, int n, int cnt, int sz) {
    if(a.size() == 0) {
        return cnt + b.size();
    }

    //for(int x : a) cout << x << " ";
    //cout << endl;

    //for(int x : b) cout << x << " ";
    //cout << endl << endl;
    
    int mn = 1000000000;
    vector<int> p1, p2;
    for(int i = 0; i < a.size(); i++) {
        mn = min(mn, a[i]);
        p1.push_back(mn);
    }

    mn = 1000000000;
    p2.push_back(mn);
    for(int i = 1; i < b.size(); i++) {
        mn = min(mn, b[i]);
        p2.push_back(mn);
    }

    if(s.size() == 0) return 0;
    auto it = s.end(); it--;
    int mx = *it;
    
    int ans = 0;
    int l = 0, r = b.size() - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(sz + mid + 1 > n) {
            r = mid - 1;
            continue;
        }
        int mn1 = p2[mid];
        mn1 = min(mn1, mx);

        int sz1 = mid + 1, sz2 = n - sz - sz1;
        if(a.size() <= sz2) { //ok
            l = mid + 1;
            ans = max(ans, cnt + sz1);
            continue;
        }
        if(mn1 > p1[sz2]) {
            l = mid + 1;
            ans = max(ans, cnt + sz1);
        } else {
            r = mid - 1;
        }
    }
    return ans;
}


int te = 0;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    s.clear();
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        s.insert(a[i]);
    }
    for(int i = 0; i < n; i++) cin >> b[i];

    vector<pair<int, int>> c;
    int x = 0, y = 0;
    while(x < n && y < n) {
        if(a[x] > b[y]) {
            c.push_back({a[x], 1});
            x++;
        } else {
            c.push_back({b[y], 0});
            y++;
        }
    }

    while(x < n) c.push_back({a[x++], 1});
    while(y < n) c.push_back({a[y++], 0});

    int ans = 0;
    for(int i = 0; i < n; i++) {
        ans += c[i].second;
    }
    
    int cnt = 0;
    vector<int> p;
    int tot = 0;
    for(int i = 0; i < c.size(); i++) {
        int j = i;
        vector<int> d;
        while(j < c.size() && c[i].second == c[j].second) {
            d.push_back(c[j].first);
            s.erase(c[j].first);
            j++;
        }
        int type = c[i].second;
        i = j - 1;

        if(type == 0) {
            p = d;
        } else {
            int sz = tot - p.size();
            if(sz > n) break;
            if(tot + d.size() <= n) {
                tot += d.size();
                cnt += d.size();
                continue;
            }
            ans = max(ans, cal1(p, d, n, cnt, sz));
            ans = max(ans, cal2(p, d, n, cnt, sz));
            cnt += d.size();
        }
        tot += d.size();
    }
    cout << ans << endl;
}


int main() {
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
