const int MOD = 1e9 + 7;
namespace Fenwick {
    const int FENWICK_SIZE = 100000 + 100;
    struct Fenwick {
        int tree[FENWICK_SIZE];
        int sz;
        void init(int n) {
            sz = n;
            for(int i = 0; i <= n + 1; i++) tree[i] = 0;
        }

        void update(int i, int val) {
            i++;
            while(i < sz){
                tree[i] += val;
                tree[i] %= MOD;
                i += (i & -i);
            }
        }

        int pre(int i) {
            int sum = 0;
            while(i > 0){
                sum += tree[i];
                sum %= MOD;
                i -= ( i & -i);
            }
            return sum;
        }
        int query(int i, int j) {
            return (pre(j + 1) - pre(i) + MOD) % MOD;
        }
    } tr;
}

using namespace Fenwick;


class Solution {
public:
    int totalBeauty(vector<int>& a) {
        int n = a.size();
        unordered_map<int, vector<int>> mp; //the map has n log n number at most
        for(int i = 0; i < a.size(); i++) { 
            for(int j = 1; j * j <= a[i]; j++) {
                if(a[i] % j == 0) {
                    int x = j;
                    mp[x].push_back(a[i]);
                    if(a[i] / j != j) {
                        int y = a[i] / j;
                        mp[y].push_back(a[i]);
                    }
                }
            }
        }

        int mx = *max_element(a.begin(), a.end());
        tr.init(mx + 10);
        vector<int> dp(mx + 1);

        for(auto it = mp.begin(); it != mp.end(); it++) {
            int g = it -> first;
            vector<int> vec = it -> second;
            for(int i = 0; i < vec.size(); i++) {
                int x = vec[i];
                int count = tr.query(0, x - 1);
                count++;
                count %= MOD;
                tr.update(x, count);
                dp[g] += count;
                dp[g] %= MOD;
            }

            //reset the tree
            for(int i = 0; i < vec.size(); i++) {
                int x = vec[i];
                int val = tr.query(x, x);
                tr.update(x, -val);
            }
        }

        for(int i = mx; i >= 1; i--) {
            for(int j = i + i; j <= mx; j += i) {
                dp[i] -= dp[j];
                if(dp[i] < 0) dp[i] += MOD;
            }
        }

        long long ans = 0;
        for(int g = 1; g <= mx; g++) {
            ans += ((dp[g] + 0ll) * g);
            ans %= MOD;
        }
        return ans;
    }
};
