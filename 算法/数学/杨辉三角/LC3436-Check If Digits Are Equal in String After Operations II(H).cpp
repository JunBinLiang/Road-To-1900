const int N = 1e5 + 10, MOD1 = 2, MOD2 = 5;
long long p1[N], p2[N], fact[N];

long long fpow(long long x, int y, int MOD){
	long long res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  

int C(int n,int m) {
  return fact[n] * fpow(fact[n - m], 5 - 2, 5) % 5 * fpow(fact[m], 5 - 2, 5) % 5;
}

int C2(int n,int m) {
    int cnt = p1[n] - p1[n - m] - p1[m];
    if(cnt > 0) return 0;
    else return 1;
}

int C5(int n,int m) {
    int cnt = p2[n] - p2[n - m] - p2[m];
    if(cnt > 0) return 0;
    return C(n, m);
}

class Solution {
public:
    bool hasSameDigits(string s) {
        int n = s.size();
        p1[0] = p2[0] = 0;
        fact[0] = 1;
        for(int i = 1; i <= n; i++) {
            int x = i;
            p1[i] = p2[i] = 0;
            while(x % 2 == 0) {
                p1[i]++;
                x /= 2;
            }
            
            x = i;
            while(x % 5 == 0) {
                p2[i]++;
                x /= 5;
            }
            
            p1[i] += p1[i - 1];
            p2[i] += p2[i - 1];
            fact[i] = x;
            fact[i] *= fact[i - 1];
            fact[i] %= 5;
        }
        
        vector<vector<int>> mp(2, vector<int>(5));
        mp[0][0] = 0;
        mp[0][1] = 6;
        mp[0][2] = 2;
        mp[0][3] = 8;
        mp[0][4] = 4;
        
        mp[1][0] = 5;
        mp[1][1] = 1;
        mp[1][2] = 7;
        mp[1][3] = 3;
        mp[1][4] = 9;
        
        
        int s1 = 0, s2 = 0;
        for(int i = 0; i < n - 1; i++) {
            int t1 = C2(n - 2, i);
            int t2 = C5(n - 2, i);
            int t = mp[t1][t2];
            
            s1 += (t * (s[i] - '0'));
            s1 %= 10;
        }
        
        for(int i = 1; i < n; i++) {
            int t1 = C2(n - 2, i - 1);
            int t2 = C5(n - 2, i - 1);
            int t = mp[t1][t2];
            
            s2 += (t * (s[i] - '0'));
            s2 %= 10;
        }
        return s1 == s2;
    }
};
