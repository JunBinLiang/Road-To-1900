namespace Combination {
  int mod = 1000000007;
  ll fact[1000000 + 100];
  ll inv[1000000 + 100];
  int c[505][505];
  
ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  
  
long long modInverse(long long a, long long m) {
    long long m0 = m;
    long long y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
          // q is quotient
        long long q = a / m;
        long long t = m;
        // m is remainder now, process
        // same as Euclid's algo
        m = a % m;
        a = t;
        t = y;
        // Update x and y
        y = x - q * y;
        x = t;
    }
    // Make x positive
    if (x < 0)
        x += m0;
    return x;
}




ll C(int n,int m) {
  return fact[n] * fpow(fact[n - m], MOD - 2) % MOD * fpow(fact[m], MOD - 2) % MOD;
}

  void init() {
    fact[0] = 1;
    FOR(i, 1, 1000000 + 50) {
      fact[i] = fact[i - 1] * i;
      fact[i] %= mod;
    }

    inv[0] = inv[1]=1;
    for (int i=2;i < 1000000 + 50;i++){
        inv[i] = modInverse(i,mod);
        inv[i] %= mod;
    }

    c[0][0] = 1;
    for(int i = 1;i <= 500; i++) {
      c[i][0]=1;
      for(int j = 1;j <= i;j++) {
        c[i][j] = ( c[i-1][j] + c[i-1][j-1] ) % mod;
      }
    }
  }
}
