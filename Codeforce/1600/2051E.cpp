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

int find1(vector<int>& a, int x) {
    int l = 0, r = a.size() - 1;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(a[mid] >= x) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans + 1;
}

int find2(vector<int>& a, int x) {
    int l = 0, r = a.size() - 1;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(a[mid] < x) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans + 1;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(n);
    vector<int> b1, b2;
    for(int i = 0; i < n; i++) cin >> a[i].first;
    for(int i = 0; i < n; i++) {
        cin >> a[i].second;
    }

    for(int i = 0; i < n; i++) {
        b1.push_back(a[i].first);
        b2.push_back(a[i].second);
    }

    sort(b1.begin(), b1.end());
    sort(b2.begin(), b2.end());

    map<int, int> mp;
    mp[1] = 0;
    for(auto& p : a) {
        int l = p.first, r = p.second;
        mp[l + 1]++;
        mp[r + 1]--;    
    }

    int s = 0;
    vector<pair<int, int>> c;
    for(auto it = mp.begin(); it != mp.end(); it++) {
        s += (it -> second);
        c.push_back({it -> first, s});
    }


    long long ans = 0;
    int j = 0;
    sort(a.begin(), a.end());
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i = 0; i < c.size(); i++) {
        int price = c[i].first, cnt = c[i].second;
        if(cnt <= k) {
            if(i + 1 < c.size()) {
                int best = max(price, c[i + 1].first - 1);
                while(j < a.size() && a[j].first <= best) {
                    pq.push(a[j].second);
                    j++;
                }
                
                while(pq.size() > 0 && pq.top() < best) pq.pop();
                ans = max(ans, (best + 0ll) * (pq.size() + (n - j)));            
            }
        }
    }
    cout << ans << endl;
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

