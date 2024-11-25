//4:20 - 4:30
const int N = 1e5 + 10;
const int MOD = 1e9 + 7, base = 101;
long long h1[N], h2[N];
long long p[N];
long long get(long long h[N], long l, long r) {
    if(l == 0) return h[r];
    return (h[r] - (h[l - 1] * p[r - l + 1] % MOD) + MOD) % MOD;
}

class Solution {
public:
    int minStartingIndex(string s, string t) {
        if(s.size() < t.size()) {
            return -1;
        }
        p[0] = 1;
        for(int i = 1; i <= max(s.size(), t.size()); i++) {
            p[i] = p[i - 1] * base;
            p[i] %= MOD;
        }
        
        long long h = 0;
        for(int i = 0; i < s.size(); i++) {
            h = h * base + (s[i] - 'a' + 1);
            h %= MOD;
            h1[i] = h;
        }
        
        h = 0;
        for(int i = 0; i < t.size(); i++) {
            h = h * base + (t[i] - 'a' + 1);
            h %= MOD;
            h2[i] = h;
        }
        
        for(int i = 0; i < s.size(); i++) {
            if(i + t.size() - 1 >= s.size()) {
                break;
            }
            int l = i, r = min(s.size() - 1, i + t.size() - 1);
            int common = 0;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                int sz = mid - i + 1;
                if(get(h1, i, mid) == get(h2, 0, sz - 1)) {
                    common = sz;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            if(common == t.size() || common == t.size() - 1) return i;
            if(get(h1, i + common + 1, i + t.size() - 1) == get(h2, common + 1, t.size() - 1)) {
                return i;
            }
        }
        return -1;
    }
};
