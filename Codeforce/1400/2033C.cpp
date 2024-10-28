#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>


using namespace std;

//7:31 - 7:45
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int ans = 0;
    int l = n / 2, r = n / 2 + 1;
    if(n % 2 == 1) {
        l = r;
    }
    
    if(l != r && a[l] == a[r]) ans++;
    
    while(l >= 2 && r <= n - 1) {
        int nxtl = l - 1, nxtr = r + 1;
        int cnt1 = 0, cnt2 = 0;
        if(a[nxtl] == a[l]) cnt1++;
        if(a[nxtr] == a[r]) cnt1++;

        if(a[nxtr] == a[l]) cnt2++;
        if(a[nxtl] == a[r]) cnt2++;

        if(cnt2 < cnt1) {
            swap(a[nxtl], a[nxtr]);
        }

        ans += min(cnt1, cnt2);
        l--;
        r++;
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
