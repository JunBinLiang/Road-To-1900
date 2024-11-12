#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <string.h>

using namespace std;  
//4:56 - 5:05
int get(vector<int>& p, int l, int r) {
    if(l == 0) return p[r];
    return p[r] - p[l - 1];
} 

void solve() {
    int n, k, x;
    cin >> n >> k >> x;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());

    //the maximum k will be -1
    vector<int> p(n);
    for(int i = 0; i < n; i++) {
        p[i] = a[i];
        if(i) p[i] += p[i - 1];
    }
    


    int ans = -2000000000;
    for(int i = 0; i <= min(k, n); i++) {
        //[1 : x]
        int s1 = 0;
        s1 = get(p, i, min(n - 1, i + x - 1));
        int s2 = 0;
        if(i + x < n) {
            s2 = get(p, i + x, n - 1);
        }
        ans = max(ans, s2 - s1);
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
