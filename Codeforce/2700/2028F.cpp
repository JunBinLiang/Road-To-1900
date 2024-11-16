#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <string.h>
#include <bitset>

using namespace std;  

const int N = 2e5 + 10;
const int M = 10000 + 100;
//const int M = 15;
bitset<M> dp[20];
bitset<M> all, zero;
int t = 0;
void solve() {
    //clean
    for(int i = 0; i < 20; i++) {
        dp[i] &= 0;
    }
    all &= 0;
    zero &= 0;
    t++;
    int n, k;
    cin >> n >> k;
    
    int index = 0;
    deque<int> dq;
    int one = 0;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        index = i;
        if(x == 0) {
            dq.push_back(0);           
            for(int j = 0; j <= min(one, k); j++) {
                all.flip(j);
            }
            dp[0] |= all;
            zero |= all;
            break;
        } else if(x == 1) {
            one++;
        } else {
            for(int j = 0; j <= min(one, k); j++) {
                if(j > 0) all.flip(j);
                if(x + j <= k) {
                    dp[0].flip(x + j); //[x : x + one]
                }
            }
            all |= dp[0];
            dq.push_back(x);
            break;
        }
    }
    
    
    for(int i = index + 1; i < n; i++) {
        int x;
        cin >> x;

        if(x == 0) {
            for(int j = 0; j < dq.size(); j++) {
                dp[j] &= 0;
            }
            dq.clear();
            dq.push_back(0);
            dp[0] |= all;
            dp[0] |= 1;
            zero &= 0;
            zero |= all;
            zero |= 1;
            all |= dp[0];
            //cout << i << ":  " << dp[dq.size() - 1].to_string() <<"  " << zero.to_string() << endl;
        } else if(x == 1) {
            dp[dq.size() - 1] |= (dp[dq.size() - 1] << 1);
            all |= dp[dq.size() - 1];
            //cout << i << ":  " << dp[dq.size() - 1].to_string() <<"  " << zero.to_string() << endl;
        } else {
            vector<int> a;
            for(auto& p : dq) a.push_back(p);
            int temp = x;
            for(int j = a.size() - 1; j >= 0 && temp <= k && temp != 0; j--) {
                dp[dq.size()] |= (dp[j] << temp);
                temp *= a[j];
            }
            if(temp == 0 || (a[0] == 0)) {
                dp[dq.size()] |= zero;
            } else if(temp <= k) {
                for(int j = 0; j <= min(one, k); j++) {
                    if(j + temp <= k) dp[dq.size()][j + temp] = 1;
                }
            }
            all |= dp[dq.size()];
            dq.push_back(x);
            
            //cout << i << ":  " << dp[dq.size() - 1].to_string() <<"  " << zero.to_string() << endl;
        }

        //adjust
        if(dq.size() > 18) {
            if(dq.front() == 0) {
                vector<int> a;
                for(auto& p : dq) a.push_back(p);
                dq.clear();

                for(int i = 1; i < a.size() - 1; i++) {
                    dp[i] &= 0;
                    dp[i] |= dp[i + 1];
                }
                dp[a.size() - 1] &= 0;
                dq.push_back(0);
                for(int i = 2; i < a.size(); i++) dq.push_back(a[i]);
            } else {
                dq.pop_front();
                for(int j = 0; j < dq.size(); j++) {
                    dp[j] &= 0;
                    dp[j] |= dp[j + 1];
                }
                dp[dq.size()] &= 0;
            }
        }
    }
    
    /*cout << endl;
    for(int i = 0; i <= dq.size(); i++) {
        cout << dp[i].to_string() << endl;
    }*/
    if(dq.size() == 0) {
        if(n >= k) cout << "YES" << endl;
        else cout << "NO" << endl;
        return;
    }
    
    if(dp[dq.size() - 1][k]) cout << "YES" << endl;
    else cout << "NO" << endl;
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

/*
2
1 1 1 2 2

1
1 1 1 2 1

1
0 0 0 1 2

2
0 0 0 1 2

2
1 1 1 1 2
*/
