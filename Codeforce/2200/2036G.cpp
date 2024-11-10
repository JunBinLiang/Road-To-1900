#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string.h>

using namespace std;  
const int N = 3e5 + 10;

void output(vector<long long>& vec) {
    cout << "ans " << vec[0] << " " << vec[1] << " " << vec[2] << endl;
}

long long ask(long long l, long long r) {
    long long ans = 0;
    /*vector<int> a(1001);
    a[1] = a[2] = a[3] = 1;
    for(long long i = l; i <= r; i++) {
        if(a[i] % 2 == 1) {
            ans ^= i;
        }
    }*/
    cout << "xor " << l << " " << r << endl;
    cin >> ans; 
    return ans;
}

void solve() {
    long long n;
    cin >> n;

    vector<long long> vec;
    long long l = -1, r = -1, xo = -1;
    long long L = 1;
    for(int i = 0; i < 61 && L <= n; i++) {
        long long R = L + (1ll << i) - 1;
        long long q = ask(L, min(R, n)); //never be zero if there is such number
        if(q != 0) {
            if(L <= q && q <= min(R, n) && ask(q, q) != 0) {
              vec.push_back(q);
            } else {
                l = L;
                r = min(R, n);
                xo = q;
            }
        }
        L += (1ll << i);
    }
    
    //cout << " "  << l << " " << r  << "  " << xo << endl;
 
    if(l != -1) {
        if(vec.size() > 0) { //only 2 in the range
            while(l <= r) {
                long long mid = l + (r - l) / 2;
                long long q = ask(l, mid);
                if(q == 0) {
                    l = mid + 1;
                } else if(q == xo) {
                    r = mid - 1;
                } else {
                    vec.push_back(q);
                    vec.push_back(xo ^ q);
                    break;
                }
            }
        } else {
            long long lrange = l, range = r;
            while(l <= r) {
                long long mid = l + (r - l) / 2;
                long long q1 = ask(l, mid);
                if(q1 == 0) {
                    l = mid + 1;
                } else if(q1 == xo) {
                    r = mid - 1;
                } else {
                    if(q1 >= lrange && q1 <= range) {
                        vec.push_back(q1);
                        xo ^= q1;
                        l = mid + 1;
                        break;
                    } else {
                        vec.push_back(xo ^ q1);
                        r = mid - 1;
                        xo = q1;
                        break;
                    }
                }
            }

            //only 2 in the range
            while(l <= r) {
                long long mid = l + (r - l) / 2;
                long long q = ask(l, mid);
                if(q == 0) {
                    l = mid + 1;
                } else if(q == xo) {
                    r = mid - 1;
                } else {
                    vec.push_back(q);
                    vec.push_back(xo ^ q);
                    break;
                }
            }
        }
    }

    output(vec);
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
