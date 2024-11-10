#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string.h>

using namespace std;  

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    set<int> st;
    for(int i = 0; i < n; i++) {
        if(i + 3 >= n) continue;
        if(s[i] == '1' && s[i + 1] == '1' && s[i + 2] == '0' && s[i + 3] == '0') {
            st.insert(i);
        }
    }

    int m;
    cin >> m;
    while(m--) {
        int p; char c;
        cin >> p >> c;
        p--;
        s[p] = c;
        for(int i = p - 3; i <= p; i++) {
            if(i + 3 >= n) continue;
            if(s[i] == '1' && s[i + 1] == '1' && s[i + 2] == '0' && s[i + 3] == '0') {
                st.insert(i);
            } else {
                st.erase(i);
            }
        }
        if(st.size() > 0) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
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
