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
long long sum = 0;
vector<pair<int, int>> divide(vector<int>& p, int l, int r) {
    if(l == r) {
        return {{p[l], l}};
    }
    int mid = l + (r - l) / 2;
    vector<pair<int, int>> a = divide(p, l, mid);
    vector<pair<int, int>> b = divide(p, mid + 1, r);
    vector<pair<int, int>> c;
    int i = 0, j = 0;
    long long s1 = 0, s2 = 0;
    while(i < a.size() && j < b.size()) {
        if(a[i].first < b[j].first) {
            s1 += a[i].first; // (p[i] - p[j])
            s2 += a[i].second; //(i - j)
            c.push_back(a[i]);
            i++;
        } else {
            int sz = i;
            long long x = (b[j].first + 0ll) * sz - s1;
            long long y = (b[j].second + 0ll) * sz - s2;
            sum += x;
            sum += ((y - x) / 2);
            c.push_back(b[j]);
            j++;
        }
    }

    while(i < a.size()) {
        c.push_back(a[i]);
        i++;
    }

    while(j < b.size()) {
        int sz = i;
        long long x = (b[j].first + 0ll) * sz - s1;
        long long y = (b[j].second + 0ll) * sz - s2;
        sum += x;
        sum += ((y - x) / 2);
        c.push_back(b[j]);
        j++;
    }

    return c;
}
bool first = false;
long long cal(vector<int>& a) {
    int n = a.size();
    int s = 0;
    sum = 0;
    vector<int> p;
    for(int i = 0; i < n; i++) {
        s += a[i];
        p.push_back(s);
        if(s > 0) {
            int sz = i + 1;
            sum += ((sz - s) / 2 + s);
            //cout << "addgg " << ((sz - s) / 2 + s) << endl;
        }
    }

    //handle segment sum with 0
    if(first) {
        first = false;
        map<int, int> mp1;
        map<int, long long> mp2;
        s = 0;
        for(int i = 0; i < n; i++) {
            s += a[i];
            if(s == 0) {
                sum += (1 + i) / 2;
            }
            if(mp1.find(s) != mp1.end()) {
                int cnt = mp1[s];
                long long s1 = (cnt + 0ll) * (i) - mp2[s];
                sum += (s1 / 2);
                //cout << "add " << s1 / 2 << endl;
            }
            mp1[s]++;
            mp2[s] += (i);
        }
    }
    
    divide(p, 0, n - 1);
    int o = 0;
    for(int x = 0; x < p.size(); x++) {
        for(int y = x - 1; y >= 0; y--) {
            int t = p[x] - p[y];
            if(t >= 0) {
                int sz = x - y;
                o += ((sz - t) / 2 + t);
            }
        }
        if(p[x] >= 0) {
            int sz = x + 1;
            o += ((sz - p[x]) / 2 + p[x]);
        }
    }
    return sum;
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a, b;
    for(char c : s) {
        if(c == '1') {
            a.push_back(1);
            b.push_back(-1);
        } else {
            a.push_back(-1);
            b.push_back(1);
        }
    }
    first = true;
    long long s1 = cal(a), s2 = cal(b);
    cout << s1 + s2 << endl;
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
