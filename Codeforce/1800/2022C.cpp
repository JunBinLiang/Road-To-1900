#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <string.h>

using namespace std;  

const int N = 1e5 + 100;
int dp[N][4];
int get(vector<string>& a, int r1, int c1, int r2, int c2, int r3, int c3) {
    int cnt = 0;
    if(a[r1][c1] == 'A') cnt++;
    if(a[r2][c2] == 'A') cnt++;
    if(a[r3][c3] == 'A') cnt++;
    if(cnt > 1) return 1;
    return 0;
}

void solve() {
    int n;
    cin >> n;
    vector<string> a(2);
    for(int i = 0; i < 2; i++) {
        cin >> a[i];
    }

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j < 4; j++) {
            dp[i][j] = -10000000;
        }
    }

    dp[1][2] = get(a, 0, 0, 0, 1, 1, 0);
    dp[1][1] = get(a, 0, 0, 1, 0, 1, 1);
    dp[0][3] = 0;
    for(int i = 1; i < n; i++) {
        dp[i][1] = max(dp[i][1], dp[i - 1][3] + get(a, 0, i - 1, 1, i - 1, 1, i));
        dp[i][2] = max(dp[i][2], dp[i - 1][3] + get(a, 0, i - 1, 1, i - 1, 0, i));

        dp[i][3] = max(dp[i][3], dp[i - 1][0]);

        dp[i][0] = max(dp[i][0], dp[i - 1][1] + get(a, 0, i - 1, 0, i, 1, i));
        dp[i][0] = max(dp[i][0], dp[i - 1][2] + get(a, 0, i, 1, i, 1, i - 1));

        if(i >= 2) {
            int p = 0;
            if(i - 3 >= 0) {
                p = dp[i - 3][0];
            }
            dp[i][0] = max(dp[i][0], p + get(a, 0, i, 0, i - 1, 0, i - 2) + get(a, 1, i, 1, i - 1, 1, i - 2));
        }

        if(i >= 3) {
            dp[i][1] = max(dp[i][1], dp[i - 3][1] + get(a, 0, i - 1, 0, i - 2, 0, i - 3) + get(a, 1, i, 1, i - 1, 1, i - 2));
            dp[i][2] = max(dp[i][2], dp[i - 3][2] + get(a, 0, i, 0, i - 1, 0, i - 2) + get(a, 1, i - 1, 1, i - 2, 1, i - 3));
        }
    }


    cout << dp[n - 1][0] << endl;

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
