long long getp(vector<long long>& p, int l, int r) {
    return l == 0 ? p[r] : p[r] - p[l - 1];
}

const int MOD = 1e9 + 7;
const int N = 1e5 + 100;

long long h1[N], h2[N], p[N];
int b = 101;
int n;
long long geth1(long long h[], int l, int r) {
    if(l == 0) {
        return h[r];
    }
    return (h[r] - (h[l - 1] * p[r - l + 1] % MOD ) + MOD) % MOD;
}

long long geth2(long long h[], int l, int r) {
    if(r == n - 1) {
        return h[l];
    }
    return (h[l] - (h[r + 1] * p[r - l + 1] % MOD ) + MOD) % MOD;
}

class Solution {
public:
    long long getSum(vector<int>& a) {
        n = a.size();
        vector<long long> ps;
        long long s = 0;
        for(int x : a) {
            s += x;
            ps.push_back(s);
        }

        p[0] = 1;
        for(int i = 1; i <= n; i++) {
            p[i] = p[i - 1] * b;
            p[i] %= MOD;
        }

        long long h = 0;
        for(int i = 0; i < n; i++) {
            h = h * b + a[i];
            h %= MOD;
            h1[i] = h;
        }

        h = 0;
        for(int i = n - 1; i >= 0; i--) {
            h = h * b + a[i];
            h %= MOD;
            h2[i] = h;
        }

        long long ans = 0;
        for(int i = 0; i < n; i++) {
            int l = 0, r = i - 1;
            ans = max(ans, a[i] + 0ll);
            int to = -1;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                int t = i - mid;
                if(i + t < n && geth1(h1, mid, i - 1) == geth2(h2, i + 1, i + t)) {
                    to = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if(to != -1) {
                int t = i - to;
                ans = max(ans, getp(ps, i - t, i + t));
            }
        }

        for(int i = 0; i < n - 1; i++) {
            if(a[i] != a[i + 1]) continue;
            ans = max(ans, a[i] * 2ll);
            int l = 0, r = i - 1;
            int to = -1;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                int t = i - mid;
                if(i + 1 + t < n && geth1(h1, mid, i - 1) == geth2(h2, i + 2, i + 1 + t)) {
                    to = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if(to != -1) {
                int t = i - to;
                ans = max(ans, getp(ps, i - t, i + 1 + t));
            }
        }
        return ans;
    }
};
