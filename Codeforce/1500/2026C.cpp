#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string.h>


using namespace std;  
//3：55 - 4:22
void solve() {
    int n;
    string s;
    cin >> n >> s;

    if(s.size() == 1) {
        cout << 1 << endl;
        return;
    }

    long long tot = 0;
    for(int i = 1; i <= s.size(); i++) tot += i;

    set<int> one, zero;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '0') zero.insert(i);
        else one.insert(i);
    }
    
    for(int i = s.size() - 1; i >= 0; i--) {
        if(s[i] == '1') { //can kill
            if(one.find(i) != one.end()) {
                one.erase(i);
                if(zero.size() > 0) {
                    auto it = zero.end(); it--;
                    zero.erase(*it);
                    tot -= (i + 1);
                } else if(one.size() > 0) {
                    auto it = one.begin();
                    one.erase(*it);
                    tot -= (i + 1);
                }
            }
        } else {
            zero.erase(i);
        }
    }

    cout << tot << endl;
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
