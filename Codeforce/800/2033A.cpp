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
    int x = 0;
    int i = 1;
    while(abs(x) <= n) {
        if(i % 2 == 1) {
            x = x - (2 * i - 1);
        } else {
            x = x + (2 * i - 1);
        }
        i++;
    }

    if(i % 2 == 1) cout << "Kosuke" << endl;
    else cout << "Sakurako" << endl;
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
