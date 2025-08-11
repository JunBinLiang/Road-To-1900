#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll

int t,mod=998244353;
int dp[200005];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
    cin >> t;
    for(int test=1;test<=t;test++){
        int n,x;
        cin >> n >> x;
        if(n*(n-1)/2 + n - 1 > x){ // maxQ >= n*(n-1)/2 + n - 1
            cout << 0 << "\n";
            continue;
        }
        for(int i=0;i<=x;i++){
            dp[i] = 0;
        }
        dp[n*(n-1)/2 + n - 1] = 1;
        for(int i=1;i<=n-1;i++){
            for(int j=i;j<=x;j++){
                dp[j] += dp[j-i];
                dp[j] %= mod;
            }
        }
        for(int i=1;i<=x;i++){
            dp[i] += dp[i-1];
            dp[i] %= mod;
        }
        int ans=0;
        for(int i=1;i<=x;i++){
            ans += dp[i];
            ans %= mod;
        }
        cout << ans << "\n";
    }
	return 0;
}
