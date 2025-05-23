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

const int N = 2e5 + 10;
vector<int> p[N];

bool vis[N];

long long cal(vector<int>& a, int mid) {
    int n = a.size() - 1;
    priority_queue<int> maxq;
    priority_queue<int, vector<int>, greater<int>> minq;
    for(int i = n; i > mid; i--) {
        for(int pos : p[i]) {
            maxq.push(pos);
            minq.push(pos);
        }
    }

    for(int i = 1; i <= n; i++) vis[i] = false;

    long long ans = 0;
    for(int i = mid; i >= 1; i--) {
        for(int pos : p[i]) {
            maxq.push(pos);
            minq.push(pos);
        }
        while(maxq.size() > 0 && vis[maxq.top()]) maxq.pop();
        while(minq.size() > 0 && vis[minq.top()]) minq.pop();

        if(maxq.size() == 0) {
            return -1; //can not do it
        }
        
        ans += (maxq.top() - minq.top());
        vis[maxq.top()] = vis[minq.top()] = true;
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 0; i <= n; i++) p[i].clear();
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        p[a[i]].push_back(i);
    }

    long long ans = 0;
    int l = 1, r = n / 2;
    while(l <= r) {
        int mid1 = l + (r - l) / 3;
        int mid2 = l + (r - l) / 3 * 2;
        
        long long ans2 = cal(a, mid2);
        if(ans2 == -1) {
            r = mid2 - 1;
            continue;
        }
        long long ans1 = cal(a, mid1);
        ans = max(ans, ans1);
        ans = max(ans, ans2);

        if(ans1 > ans2) {
            r = mid2 - 1;
        } else {
            l = mid1 + 1;
        }
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
