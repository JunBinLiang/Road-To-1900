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

const int N = 2e5 + 10;
long long oddp[N], evenp[N];

long long get1(vector<int>& a, vector<long long>& ans, int i) {
    int n = a.size();
    long long x = a[i] + 2 * ans[i];
    int pre = (i - 1 + n) % n;
    int nxt = (i + 1) % n;
    x += ans[pre];
    x += ans[nxt];
    return x;
}

long long get2(vector<int>& a, vector<long long>& ans, int i) {
    int n = a.size();
    long long x = a[i];
    int pre = (i - 1 + n) % n;
    int nxt = (i + 1) % n;
    
    if(i % 2 == 0) x += 2 * evenp[i];
    else x += 2 * oddp[i];

    if(pre % 2 == 0) x += evenp[pre];
    else x += oddp[pre];

    if(nxt % 2 == 0) x += evenp[nxt];
    else x += oddp[nxt];

    x += ans[i] * 2;
    x += ans[pre];
    x += ans[nxt];

    return x;
}

void check(vector<int>& a, vector<long long>& ans) {
    int n = a.size();
    for(int i = 0; i < n; i++) {
        long long x = get1(a, ans, i);
        cout << x << " ";
    }
    cout << endl;
}

void out(vector<long long>& ans) {
    for(long long x : ans) cout << x << " ";
    cout << endl;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if(n == 1) {
        cout << 0 << endl;
        return;
    }

    for(int i = 0; i <= n; i++) {
        oddp[i] = evenp[i] = 0;
    }

    vector<long long> ans(n);

    int l = 0, r = n - 1;
    while(l < r) {
        long long t1 = get2(a, ans, l), t2 = get2(a, ans, r);
        long long dif = abs(t1 - t2);
        if(t1 < t2) {
            /*int o = 0;
            for(int j = l; j >= 0; j--) {
                if(o % 2 == 0) {
                    ans[j] += dif;
                } else {
                    ans[n - j - 1] += dif;
                }
                o++;
            }*/
            if(l % 2 == 0) {
                evenp[l] += dif;
                if(l - 1 >= 0) {
                    oddp[(n - (l - 1) - 1)] += dif;
                }
            } else {
                oddp[l] += dif;
                if(l - 1 >= 0) {
                    evenp[(n - (l - 1) - 1)] += dif;
                }
            }
        } else if(t1 > t2) {
            /*int o = 0;
            for(int j = l; j >= 0; j--) {
                if(o % 2 == 0) {
                    ans[n - j - 1] += dif;
                } else {
                    ans[j] += dif;
                }
                o++;
            }*/

            if(l % 2 == 0) {
                evenp[n - l - 1] += dif;
                if(l - 1 >= 0) {
                    oddp[l - 1] += dif;
                }
            } else {
                oddp[n - l - 1] += dif;
                if(l - 1 >= 0) {
                    evenp[l - 1] += dif;
                }
            }
        }
        l++;
        r--;
    }

    int mid = n / 2;
    long long esum = 0, osum = 0;
    for(int i = mid - 1; i >= 0; i--) {
        if(i % 2 == 0) {
            esum += evenp[i];
            ans[i] = esum;
        } else {
            osum += oddp[i];
            ans[i] = osum;
        }
    }

    esum = 0; osum = 0;
    for(int i = mid - 1; i >= 0; i--) {
        if(i % 2 == 0) {
            esum += evenp[n - i - 1];
            ans[n - i - 1] = esum;
        } else {
            osum += oddp[n - i - 1];
            ans[n - i - 1] = osum;
        }
    }
        
    //check(a, ans);
    
    long long mx = 0;
    for(int i = 0; i < n; i++) mx += get1(a, ans, i);
    ans[0] += 1000000000000ll;
    ans[n - 1] += 1000000000000ll;

    if(n == 3) {
        long long t = get1(a, ans, mid);
        ans[0] += t;
        ans[2] += t;
        ans[1] += abs(get1(a, ans, 0) - get1(a, ans, 1));
        //check(a, ans);
        out(ans);
        return;
    }
    
    if(get1(a, ans, mid) > get1(a, ans, mid - 1)) {
        long long t = get1(a, ans, mid);
        ans[mid - 2] += t;
        ans[mid + 2] += t;
        ans[mid] += abs(get1(a, ans, mid) - get1(a, ans, mid + 1));
    } else if(get1(a, ans, mid) < get1(a, ans, mid - 1)) {
        ans[mid] += abs(get1(a, ans, mid) - get1(a, ans, mid - 1));
    }
    
    //check(a, ans);

    for(int i = 0; i <= n; i++) {
        oddp[i] = evenp[i] = 0;
    }

    //check(a, ans);
    
    l = mid - 2, r = mid + 2;
    while(l >= 0) {
        long long t1 = get2(a, ans, l), t2 = get2(a, ans, l + 1);
        //cout << t1 << " " << t2 << endl;
        if(t1 > t2) {
            if((l + 1) % 2 == 0) {
                evenp[l + 1] += abs(t1 - t2);
                evenp[n - (l + 1) - 1] += abs(t1 - t2);
            } else {
                oddp[l + 1] += abs(t1 - t2);
                oddp[n - (l + 1) - 1] += abs(t1 - t2);
            }
        } else if(t1 < t2) {
            ans[l - 1] += abs(t1 - t2);
            ans[r + 1] += abs(t1 - t2);
        }
        l--;
        r++;
    }
    
    esum = 0;
    osum = 0;
    for(int i = 0; i <= mid; i++) {
        if(i % 2 == 0) {
            esum += evenp[i];
            ans[i] += esum;
            if(n - i - 1 != i) ans[n - i - 1] += esum;
        } else {
            osum += oddp[i];
            ans[i] += osum;
            if(n - i - 1 != i) ans[n - i - 1] += osum;
        }
        
    }

    //check(a, ans);
    out(ans);
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
