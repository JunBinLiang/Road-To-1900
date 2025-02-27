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
#include <deque>  

using namespace std;
using ll = long long;

void solve() {
    string s;
    cin >> s;
    int a, b, ab, ba;
    cin >> a >> b >> ab >> ba;
    int n = s.size();
    int extra = 0;
    vector<int> vec1, vec2;
    for(int i = 0; i < n; i++) {
        int j = i + 1;
        while(j < n && s[j] != s[j - 1]) {
            j++;
        }

        int cnt = j - i;
        if(cnt % 2 == 0) {
            if(s[i] == 'A') {
                vec1.push_back(cnt / 2);
            } else {
                vec2.push_back(cnt / 2);
            }
        } else {
            if(s[i] == 'A') a--;
            else b--;
            extra += ((cnt - 1) / 2);
        }
        //cout << i << "  " << j - 1 << " " << cnt <<"  " << a << " " << b << endl;
        i = j - 1;
    }

    if(a < 0 || b < 0) {
        cout << "NO" << endl;
        return;
    }

    sort(vec1.begin(), vec1.end());
    sort(vec2.begin(), vec2.end());
    reverse(vec1.begin(), vec1.end());
    reverse(vec2.begin(), vec2.end());

    while(vec1.size() > 0 && ab >= vec1.back()) {
        ab -= vec1.back();
        vec1.pop_back();
    }
    while(vec2.size() > 0 && ba >= vec2.back()) {
        ba -= vec2.back();
        vec2.pop_back();
    }

    a -= (vec1.size() + vec2.size());
    b -= (vec1.size() + vec2.size());

    if(a < 0 || b < 0) {
        cout << "NO" << endl;
        return;
    }
    
    //cout << extra <<"  " << a << " " << b << endl;

    for(int x : vec1) extra += (x - 1);
    for(int x : vec2) extra += (x - 1);
    extra -= (ab + ba);
    extra = max(extra, 0);

    if(extra <= min(a, b)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
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

