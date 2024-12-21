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

const int N = 4e5 + 100;
bool vis[N], isp[N];
vector<int> di[N], indexs[N];

void init() {
    memset(vis, 0, sizeof vis);
    memset(isp, 0, sizeof isp);
    for(int i = 2; i < N; i++) {
        if(vis[i]) continue;
        isp[i] = true;
        for(int j = i; j < N; j += i) {
            vis[j] = true;
            di[j].push_back(i);
        }
    }
}

void clean(vector<int>& a) {
    for(int i = 1; i < a.size(); i++) {
        for(int d : di[a[i]]) {
            if(indexs[d].size() > 0) {
                indexs[d].clear();
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if(n == 1) {
        cout << a[0] << endl;
        return;
    }
    
    /*sort(a.begin(), a.end());
    for(int i = 1; i < n; i++) {
        for(int d : di[a[i]]) {
            indexs[d].push_back(i);
        }
    }*/

    sort(a.begin(), a.end());

    set<int> p;
    for(int i = 0; i < n; i++) {
        if(isp[a[i]]) {
            p.insert(a[i]);
        }
    }

    if(p.size() > 1) {
        cout << -1 << endl;
    } else if(p.size() == 1) {
        int x = *(p.begin());
        if(a[0] != x || a[1] < x * 2) {
            cout << -1 << endl;
            return;
        }
        
        x += x;
        
        for(int i = 1; i < n; i++) {
            if(a[i] % 2 == 0) continue;
            int val = a[i];
            bool ok = false;
            for(int j = 2; j * j <= val && !ok; j++) {
                if(val % j == 0) {
                    while(val % j == 0) val /= j;
                    int t = j * 2;
                    int first = (x / t) * t;
                    if(first < x) first += t;
                    if(first <= a[i]) {
                        ok = true;
                    }
                }
            }

            if(val > 1) {
                int j = val;
                int t = j * 2;
                int first = (x / t) * t;
                if(first < x) first += t;
                if(first <= a[i]) {
                    ok = true;
                }
            }


            if(!ok) {
                cout << -1 << endl;
                return;
            }
        }
        int ans = *(p.begin());
        cout << ans << endl;
    } else {
        cout << 2 << endl;
    }

}   


int main(){
    int t = 1;
    init();
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
