namespace Combination {
    const int MOD = 1e9 + 7;
    int C[2010][2010];
    bool isInit = false;
    
    long long fpow(long long x, int y){
    	long long res = 1;
    	while(y){
    		if(y & 1) res = (res * x) % MOD;
    		x = (x * x) % MOD;
    		y >>= 1;
    	}
	    return res;
    } 
    
    void init() {
        if(isInit) return;
        isInit = true;
        C[0][0] = 1;
        for(int i = 1;i <= 2000; i++) {
          C[i][0]=1;
          for(int j = 1; j <= i;j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
          }
        }
    }
}
