const int MOD = 1e9 + 7;
const int N = 1010;
long long C[N][N];
int cur[6][6];
bool INIT = false;
int A[N];
void init() {
    if(INIT) return;
    INIT = true;
    C[0][0] = 1;
    for(int i = 1;i < N; i++) {
      C[i][0]=1;
      for(int j = 1;j <= i;j++) {
        C[i][j] = ( C[i - 1][j] + C[i - 1][j - 1] ) % MOD;
      }
    }
}

class Solution {
public:
    int subsequencesWithMiddleMode(vector<int>& a) {
        init();
        int n = a.size();
        long long ans = 0;
        map<int, int> mp;
        for(int x : a) mp[x]++;
        for(auto it = mp.begin(); it != mp.end(); it++) {
            if(it -> second >= 5) {
                ans += C[it -> second][5];
                ans %= MOD;
            }
        }

        //2
        ans += f(a);
        ans %= MOD;
        reverse(a.begin(), a.end());
        ans += f(a);
        ans %= MOD;
        
        for(int i = 0; i < n; i++) {
            int l1 = 0, l2 = 0, r1 = 0, r2 = 0;
            for(int j = 0; j < i; j++) {
                if(a[j] == a[i]) l1++;
                else l2++;
            }
            for(int j = i + 1; j < n; j++) {
                if(a[j] == a[i]) r1++;
                else r2++;
            }
            //3
            if(l1 >= 2 && r2 >= 2) {
                ans += (C[l1][2] * C[r2][2]);
            }
            if(l2 >= 2 && r1 >= 2) {
                ans += (C[l2][2] * C[r1][2]);
            }
            if(l1 >= 1 && l2 >= 1 && r1 >= 1 && r2 >= 1) {
                long long w1 = l1 * l2;
                long long w2 = r1 * r2;
                w1 *= w2;
                ans += w1;
                ans %= MOD;
            }
            //4
            if(l1 >= 2 && r1 >= 1 && r2 >= 1) {
                long long w1 = C[l1][2];
                long long w2 = r1 * r2;
                w1 *= w2;
                ans += w1;
                ans %= MOD;
            }
            if(l1 >= 1 && l2 >= 1 && r1 >= 2) {
                long long w1 = C[r1][2];
                long long w2 = l1 * l2;
                w1 *= w2;
                ans += w1;
                ans %= MOD;
            }
        }

        return ans;
    }

    long long f(vector<int>& a) {
        long long ans = 0;
        int n = a.size();
        unordered_map<int, int> mp;
        for(int x : a) mp[x]++;
        

        unordered_map<int, int> cnt;
        for(int i = 0; i < n; i++) {
            int sz = n - (i + 1);
            int tot = (sz) * (sz - 1) / 2;
            mp[a[i]]--;
            for(auto it = mp.begin(); it != mp.end(); it++) {
                int x = it -> second;
                tot -= ((x) * (x - 1) / 2);
            }
            
            cnt[a[i]]++;
            int ls = cnt[a[i]] - 1;
            if(ls == 0) continue;

            for(int j = 0; j < i; j++) {
                if(a[j] != a[i]) {
                    int x1 = mp[a[i]], x2 = mp[a[j]];
                    int rs = (x1 * (sz - x1)) + (x2 * (sz - x2));
                    int com = x1 * x2;
                    rs -= com;
                    ans += (ls * (tot - rs));
                    ans %= MOD;
                }
            }
        }
        return ans;
    }
};
