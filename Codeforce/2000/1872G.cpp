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
using ll = long long;
const long long INF = 1e9;

long long get(vector<long long>& p, int l, int r) {
    if(l > r) return 0;
    return l == 0 ? p[r] : p[r] - p[l - 1];
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<int> p;
    for(int i = 1; i <= n; i++) {
        if(a[i] > 1) {
            p.push_back(i);
        }
    }

    if(p.size() == 0) { //all one
        cout << "1 1" << endl; 
        return;
    }

    long long s = 1;
    for(int i = 0; i < p.size(); i++) {
        s = s * a[p[i]];
        if(s > INF) {
            cout << p[0] << " " << p.back() << endl;
            return;
        }
    }

    vector<long long> pref(n + 1);
    for(int i = 1; i <= n; i++) {
        pref[i] = a[i];
        pref[i] += pref[i - 1];
    }

    long long mx = 0, l = -1, r = -1;
    for(int i = 0; i < p.size(); i++) {
        long long pro = 1;
        for(int j = i; j < p.size(); j++) {
            pro *= a[p[j]];
            long long sum = get(pref, 0, p[i] - 1) + get(pref, p[j] + 1, n);
            if(pro + sum > mx) {
                mx = pro + sum;
                l = p[i];
                r = p[j];
            }
        }
    }
    cout << l << " " << r << endl;
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
