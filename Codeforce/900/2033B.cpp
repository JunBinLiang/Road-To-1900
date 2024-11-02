#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include<set>
#include<unordered_set>
#include <string.h>


using namespace std;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}


void solve() {
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }   

    map<int, int> mp;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int r = i, c = j;
            if(mp.find(c - r) == mp.end()) mp[c - r] = a[i][j];
            else mp[c - r] = min(mp[c - r], a[i][j]);
            //cout << c - r << " " << a[i][j] << endl;
        }
    }

    int ans = 0;
    for(auto it = mp.begin(); it != mp.end(); it++) {
        if(it -> second < 0) ans += abs(it -> second);
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
