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

bool comp(pair<int, int>& p1, pair<int, int>& p2) {
    if(p1.first == p2.first) {
        return p2.second < p1.second;
    }
    return p1.first < p2.first;
}

void solve() {
    int n; 
    cin >> n;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end(), comp);
    priority_queue<int, vector<int>, greater<int>> pq;
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        int t = a[i].first, val = a[i].second;
        ans += val;
        pq.push(t);
        int sz = pq.size();

        int j = i + 1;
        while(j < n && a[j].first <= pq.size()) {
            j++;
        }
        while(pq.size() > 0 && pq.top() <= sz) pq.pop();
        i = j - 1;
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
