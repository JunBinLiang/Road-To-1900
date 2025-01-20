using ll = long long;
const int MOD = 1e9 + 7;
const int N = 1e5 + 10;
long long fact[N];

ll fpow(ll x, int y){
    ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  

ll C(int n,int m) {
  return fact[n] * fpow(fact[n - m], MOD - 2) % MOD * fpow(fact[m], MOD - 2) % MOD;
}

class Solution {
public:
    int distanceSum(int n, int m, int k) {
        if(n > m) {
            return distanceSum(m, n, k);
        }
        long long ans = 0;
        fact[0] = 1;
        for(int i = 1; i <= n * m; i++) {
            fact[i] = fact[i - 1] * i;
            fact[i] %= MOD;
        }
        
        map<int, long long> mp;
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= m; j++) {
                int d = i + j;
                long long w1 = (n - i);
                long long w2 = (m - j);
                if(i > 0 && j > 0) {
                    mp[d] += (w1 * w2 * 2);
                } else {
                    mp[d] += (w1 * w2);
                }
                mp[d] %= MOD;
            }
        }
        
        cout << endl;
        
        for(int d = 1; d <= (n + m - 2); d++) {
            //distance
            long long w1 = C(n * m - 2, k - 2);
            long long w2 = mp[d];
            long long s = (((w1 * w2) % MOD) * d) % MOD;
            ans += s;
            ans %= MOD;
        }
        cout << endl;
        return ans;
    }
};
