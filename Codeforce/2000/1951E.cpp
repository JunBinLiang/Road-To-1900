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

bool isp(string s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    return rev == s;
}

bool same(string s) {
    for(int i = 1; i < s.size(); i++) {
        if(s[i] != s[i - 1]) {
            return false;
        }
    }
    return true;
}

void solve() {
    string s;
    cin >> s;
    
    if(!isp(s)) {
        cout << "YES" << endl;
        cout << 1 << endl;
        cout << s << endl;
        return;
    }
    
    int l = 0, r = s.size() - 1;
    bool ok = false;
    while(l <= r) {
        if(s[l] == s[0]) {
            l++;
            r--;
        } else {
            ok = true;
            break;
        }
    }
    

    if(!ok || l == r) { //all same
        cout << "NO" << endl;
        return;
    }

    
    string a = s.substr(0, l + 1);
    string b = s.substr(l + 1, s.size() - a.size() * 2); //middle
    string c = s.substr(r, a.size());
    
    //cout << a << " " << b << " " << c << endl;
    if(a.size() == 2 && b.size() == 1 && b[0] == a[0]) {
      cout << "NO" << endl;
      return;
    }

    if(same(b)) {
        if(b[0] != a[0]) {
            cout << "YES" << endl;
            cout << 2 << endl;
            cout << a + b << " " << c << endl;
        } else {
            cout << "YES" << endl;
            cout << 2 << endl;
            int len = a.size() - 1;
            for(int i = 0; i < b.size(); i++) {
                if(i + 1 != len && b.size() - (i + 1) != len) {
                    cout << a + b.substr(0, i + 1) << " " << b.substr(i + 1, b.size() - (i + 1)) + c << endl;
                    break;
                }
            }
        }
    } else {
        string p = b + c;
        if(a.size() == 2 && isp(p)) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
            cout << 2 << endl;
            if(!isp(p))
                cout << a << " " << b + c << endl;
            else 
                cout << a + b[0] + " " + b.substr(1) + c << endl;
        }
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
