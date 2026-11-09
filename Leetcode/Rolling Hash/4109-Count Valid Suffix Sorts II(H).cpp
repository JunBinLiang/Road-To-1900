//Some predefined templates
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 1e5 + 100;
const int MOD = 1e9 + 7, base = 101;
long long h1[N], h2[N], p[N];

long long geth(long long h[], int l, int r) {
    if(l == 0) {
        return h[r];
    }
    return (h[r] - (h[l - 1] * p[r - l + 1] % MOD ) + MOD) % MOD;
}


class Solution {
public:
    vector<int> countSuffix(vector<int>& a, vector<int>& b) {
        //decreasing order
        int n = a.size(), m = b.size();

        p[0] = 1;
        for(int i = 1; i <= m; i++) {
            p[i] = p[i - 1] * base;
            p[i] %= MOD;
        }

        long long h = 0;
        for(int i = 0; i < n; i++) {
            h = h * base + a[i];
            h %= MOD;
            h1[i] = h;
        }

        h = 0;
        for(int i = 0; i < m; i++) {
            h = h * base + b[i];
            h %= MOD;
            h2[i] = h;
        }

        map<int, int> mp1, mp2;
        for(int x : a) mp1[x]++;

        vector<bool> can(m);
        int same = 0;
        for(int i = 0; i < m; i++) {
            int x = b[i];
            mp2[x]++;
            if(mp1.find(x) != mp1.end() && mp1[x] == mp2[x]) {
                same++;
            }
            if(mp1.find(x) != mp1.end() && mp1[x] == mp2[x] - 1) {
                same--;
            }

            if(same == mp1.size()) {
                can[i - n + 1] = true;
            }

            if(i + 1 >= n) {
                int L = i - n + 1;
                x = b[L];
                if(mp1.find(x) != mp1.end() && mp1[x] == mp2[x]) {
                    same--;
                }
                mp2[x]--;
                if(mp1.find(x) != mp1.end() && mp1[x] == mp2[x]) {
                    same++;
                }
            }
        }

        

        vector<int> extend(m);
        for(int i = m - 1; i >= 0; i--) {
            int j = i - 1;
            int cnt = 1;
            while(j >= 0 && b[j] >= b[j + 1]) {
                cnt++;
                j--;
            }

            int index = i;
            while(cnt >= 1) {
                extend[index] = cnt;
                index--;
                cnt--;
            }
            i = j + 1;
        }

        vector<int> ans;
        for(int i = 0; i < m; i++) {
            int L = i, R = i + n - 1;
            if(R >= m) break;
            // b[L : R]
            int l = 0, r = n - 1;
            int commonPrefix = 0;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                if(geth(h1, 0, mid) == geth(h2, i, i + mid)) {
                    commonPrefix = mid + 1;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }

            if(can[i]) {
                int to = min(extend[i + n - 1], n);
                if(commonPrefix == n) {
                    ans.push_back(to);
                } else {
                    int suffixcnt = n - commonPrefix;
                    if(to >= suffixcnt) ans.push_back(to - suffixcnt + 1);
                    else ans.push_back(0);
                }
            } else {
                ans.push_back(0);
            }
        }
        return ans;
    }
};
