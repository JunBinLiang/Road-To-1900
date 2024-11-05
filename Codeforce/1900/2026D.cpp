#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string.h>


using namespace std;  
//6：00 - 6:35

long long get(vector<long long>& p, int l, int r) {
    return p[r] - p[l - 1];
}

int find1(vector<long long>& a, long long idx) {
    int l = 0, r = a.size() - 1;
    int po = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(idx <= a[mid]) {
            po = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return po;
}


void solve() {
    int n, m;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<long long> p1(n + 1), p2(n + 1), p3(n + 1);
    for(int i = 1; i <= n; i++) {
        p1[i] = p1[i - 1] + a[i];
    }
    for(int i = 1; i <= n; i++) {
        p2[i] = p2[i - 1] + p1[i];
    }

    
    for(int i = 1; i <= n; i++) {
        //p[1 : 1] + p[1 : 2] + p[1 : 3]
        int cnt = (n - i + 1);
        long long s = get(p2, i, n) - (p1[i - 1] + 0ll) * cnt;
        p3[i] = s;
        p3[i] += p3[i - 1];
    }

    //n, n - 1, n - 2, ...
    vector<long long> p(n + 1);
    for(int i = 1; i <= n; i++) {
        p[i] = (n - i + 1);
        p[i] += p[i - 1];
    }
    
    /*for(int i = 0; i <= n; i++) cout << p1[i] << " ";
    cout << endl;
    for(int i = 0; i <= n; i++) cout << p2[i] << " ";
    cout << endl;
    for(int i = 0; i <= n; i++) cout << p3[i] << " ";
    cout << endl;
    for(int i = 0; i <= n; i++) cout << p[i] << " ";
    cout << endl << endl;*/

    cin >> m;
    for(int i = 0; i < m; i++) {
        long long L, R;
        cin >> L >> R;
        L--;
        int b1 = find1(p, L), b2 = find1(p, R);
        long long ans = 0;
        
        long long cnt2 = R - (p[b2 - 1]);
        long long s2 = p3[b2 - 1];
        s2 += (get(p2, b2, b2 + cnt2 - 1) - (cnt2 + 0ll) * p1[b2 - 1]);

        long long cnt1 = L - (b1 > 0 ? p[b1 - 1] : -1);
        long long s1 = (b1 > 0 ? p3[b1 - 1] : 0);
        s1 += (get(p2, b1, b1 + cnt1 - 1) - (cnt1 + 0ll) * (b1 > 0 ? p1[b1 - 1] : 0));
        
        //cout << L << "  " << R << "  " << b1 << " " << b2 << endl;
        //cout << cnt1 << "  " << cnt2 << "   |" << s1 << " "  << s2 << endl;
        //cout << "gg " <<p3[b2 - 1] << "  " << get(p2, b2, b2 + cnt2 - 1) << endl;
        if(L == 0) cout << s2 << endl;
        else cout << s2 - s1 << endl;
    }   
}

int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
