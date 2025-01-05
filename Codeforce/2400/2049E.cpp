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

int test(int l, int r) {
    int p = 897663;
    int k = 3529833;
    int s = 0;
    if(l <= p && p <= r) {
        s = 1;
    }
    int sz = r - l + 1;
    if(sz < k) return s;
    else return 1 - s;
}

int ask(int l, int r) {
    cout << "? " << l << " " << r << endl; 
    cout.flush();
    int x;
    cin >> x;
    return x;
    //cout << l << "  " << r << " " << test(l, r) << endl;
    //return test(l, r);
}

void output(int ans) {
    cout << "! " << ans << endl;
    cout.flush();
}

int find1(int n, int L, int R) {
    int l = 1, r = R - L + 1;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(ask(L, L + mid - 1) == 0) {
            l = mid + 1;
        } else {
            ans = mid;
            r = mid - 1;
        }
    }
    output(ans);
}

void find2(int n) {
    int l = 1, r = n / 2;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(ask(1, n / 2 + mid) == 0) {
            ans = n / 2 + mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    output(ans);
}

void find3(int n) {
    int l = 1, r = n / 2;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(ask(n / 2 + 1 - mid, n) == 0) {
            ans = n / 2 + mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    output(ans);
}

void solve() {
    int n;  
    cin >> n;
    int x1 = ask(1, n / 4);
    int x2 = ask(1 + n / 4, n / 2);
    if(x1 == x2) { //1 in [n / 2 + 1, n]
        int t1 = ask(n / 2 + 1, n);
        if(t1 == 0) { // k <= n / 2
            find1(n, 1, n / 2);
        } else { // n / 2 < k
            find3(n);
        }
    } else { //1 in [1, n / 2]
        int t1 = ask(1, n / 2);
        if(t1 == 0) { // k <= n / 2
            find1(n, 1 + n / 2, n);
        } else { // n / 2 < k
            find2(n);
        }
    }
}   


int main(){
    int t = 1;
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
