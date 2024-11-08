#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string.h>


using namespace std;  

void out(vector<int>& ans) {
    for(int i = 1; i < ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
}

int cal(vector<int>& ans) {
    int k = 0;
    for(int i = 1; i < ans.size(); i++) {
        if(i % 2 == 1) k = (k & ans[i]);
        else k = (k | ans[i]);
        //cout << ans[i] << "  " << k << endl;
    }
    return k;
}

void solve() {
    int n;
    cin >> n;
    vector<int> ans(n + 1);

    set<int> all, p;
    for(int i = 1; i < 25; i++) {
        all.insert((1 << i) - 1);
        p.insert(1 << i);
    }

    //find the highest bit
    int bit = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 25; j++) {
            if(i & (1 << j)) {
                bit = max(bit, j);
            }
        }
    }

    vector<bool> used(n + 1);
    if(n % 2 == 0 && p.find(n) == p.end()) { // last is or
        ans[n] = n;
        int com = 0;
        int mask = 0;
        for(int i = 0; i < bit; i++) {
            mask |= (1 << i);
            if(n & (1 << i)) {
            } else {
                com |= (1 << i);
            }
        }

        ans[n - 1] = com;
        ans[n - 2] = mask;
        used[n] = used[com] = used[mask] = true;


        int j = 1;
        for(int i = 1; i <= n; i++) {
            if(!used[i]) ans[j++] = i;
        }
        cout << cal(ans) << endl;
        out(ans);
    } else { 
        if(n % 2 == 0) { //power of 2
            ans[n] = n;
            n--;
        }
        ans[n] = n;
        ans[n - 1] = n - 1; //or
        ans[n - 3] = 3;
        ans[n - 2] = 1;
        used[1] = used[3] = used[n] = used[n - 1] = true;
        int j = 1;
        for(int i = 1; i <= n; i++) {
            if(!used[i]) ans[j++] = i;
        }
        cout << cal(ans) << endl;
        out(ans);
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
