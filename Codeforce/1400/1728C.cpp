#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include<set>
#include<unordered_set>
#include <string.h>


using namespace std;

//6:54 - 7:07
int to(int n) {
    string s = to_string(n);
    return s.size();
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    priority_queue<int> pq1, pq2;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        pq1.push(a[i]);
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
        pq2.push(b[i]);
    }

    int ans = 0;
    while(pq1.size() && pq2.size()) {
        if(pq1.top() == pq2.top()) {
            pq1.pop();
            pq2.pop();
        } else if(pq1.top() > pq2.top()) {
            ans++;
            int x = pq1.top();
            pq1.pop();
            pq1.push(to(x));
        } else {
            ans++;
            int x = pq2.top();
            pq2.pop();
            pq2.push(to(x));
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
