#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>
#include <deque>

using namespace std;

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int MOD = 1e9 + 7;
const int N = 2005;

const int FENWICK_SIZE = 2000 + 50;
struct Fenwick
{
    long long tree[FENWICK_SIZE];
    int sz;
    void init(int n)
    {
        sz = n;
        for (int i = 0; i <= n + 1; i++) tree[i] = 0;
    }

    void update(int i, int val)
    {
        i++;
        while (i < sz)
        {
            tree[i] += val;
            if(tree[i] >= MOD) tree[i] -= MOD;
            i += (i & -i);
        }
    }

    int pre(int i)
    {
        int sum = 0;
        while (i > 0)
        {
            sum += tree[i];
            if(sum >= MOD) sum -= MOD;
            i -= (i & -i);
        }
        return sum;
    }
    int query(int i, int j)
    {
        return (pre(j + 1) - pre(i) + MOD) % MOD;
    }
} tr1[N], tr2[N];

int lis(vector<int> &a)
{
    int n = a.size();
    vector<int> dp(n);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int mx = 0;
        for (int j = i - 1; j >= 0; j--)
        {
            if (a[i] > a[j])
                mx = max(mx, dp[j]);
        }
        dp[i] = 1 + mx;
        ans = max(ans, dp[i]);
    }
    return ans;
}

int dp[N][N], sdp[N][N];

struct Upd {
    int first, second, v;
};

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<int> p(n + 1);
    p[0] = 1;
    for (int i = 1; i < p.size(); i++)
    {
        p[i] = p[i - 1] * 2;
        p[i] %= MOD;
    }

    reverse(a.begin(), a.end());
    
    /*int ok = 0;
    for(int st = 0; st < (1 << n); st++) {
        vector<int> b;
        for(int i = 0; i < n; i++) {
            if(st & (1 << i)) b.push_back(a[i]);
        }
        int l = lis(b);
        if(l <= 2) {
            ok++;
            if(l == 2)
                cout << l << "  " << b << endl;
        }
    }
    cout << ok << endl << endl;*/
    
    

    for(int i = 0; i <= n + 3; i++) {
        tr1[i].init(n + 3);
        tr2[i].init(n + 3);
    }
    
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            dp[i][j] = sdp[i][j] = 0;
        }
    }

    dp[0][a[0]] = 1;
    sdp[0][a[0]] = 1;
    for(int i = 1; i < n; i++) {
        vector<Upd> upds;
        //put as second
        for(int j = 1; j < a[i]; j++) {
            int upd = tr1[j].query(a[i], n + 1);
            upds.push_back({j, a[i], upd});
        }

        //put as first
        for(int j = a[i] + 1; j <= n; j++) {
            int upd = tr2[j].query(a[i], j);
            upds.push_back({a[i], j, upd});
        }
        

        for(auto& upd : upds) {
            tr1[upd.first].update(upd.second, upd.v);
            tr2[upd.second].update(upd.first, upd.v);
            //cout << "upd " << upd.first << " " << upd.second << " " << upd.v << endl;
        }

        //[second, first]
        for(int j = 0; j < i; j++) {
            if(a[i] > a[j]) {
                tr1[a[j]].update(a[i], dp[j][a[j]]);
                tr2[a[i]].update(a[j], dp[j][a[j]]); 
                //cout << "upd " << a[j] << " " << a[i] << " " << dp[j][a[j]] << endl;
            }
        }
        //cout << endl;
        

        dp[i][a[i]] += 1;
        dp[i][a[i]] %= MOD;
        for(int j = a[i]; j <= n; j++) {
            dp[i][a[i]] += sdp[i - 1][j];
            dp[i][a[i]] %= MOD;
        }
        for(int j = 0; j <= n; j++) {
            sdp[i][j] = sdp[i - 1][j] + dp[i][j];
            sdp[i][j] %= MOD;
        }
    }
    
    /*for(int i = 0; i <= n; i++) {
        for(int j = i + 1; j <= n + 1; j++) {
            cout << i << " " << j << " " << tr1[i].query(j, j) << endl;
        }
    }*/


    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += sdp[n - 1][i];
        ans %= MOD;
        ans += tr1[i].query(i + 1, n + 1);
        ans %= MOD;
        //cout << "gg " << sdp[n - 1][i] << "  " << tr1[i].query(i + 1, n + 1) << endl; 
    }
    cout << ans + 1 << endl;
}

int main()
{
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
