#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>

using namespace std;
const int MOD = 998244353;
const int N = 2e5 + 10;

const int FENWICK_SIZE = (200000 + 10) * 30;
struct Fenwick {
    int tree[FENWICK_SIZE];
    int sz;
    void init(int n) {
        sz = n;
        for(int i = 0; i <= n + 1; i++) tree[i] = 0;
    }

    void update(int i, int val) {
        i++;
        while(i < sz) {
            tree[i] += val;
            if(tree[i] >= MOD) tree[i] -= MOD;
            i += (i & -i);
        }
    }

    int pre(int i) {
        int sum = 0;
        while(i > 0){
            sum += tree[i];
            if(sum >= MOD) sum -= MOD;
            i -= ( i & -i);
        }
        return sum;
    }

    int query(int i, int j) {
        return (pre(j + 1) - pre(i) + MOD) % MOD;
    }
} tr;

struct Tuple {
    int l, r, o; 
};
struct Q {
    int y1, y2, si, i;
};
vector<Q> q[N];

unordered_map<int, int> mp;
vector<pair<int, int>> vec[N];
int a[N], cnt[N * 30], dp[N * 30], oval[N * 30];

void solve() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    //Calculate distinct or
    unordered_set<int> pre;
    pre.insert(0);
    set<int> all;
    for(int i = 1; i <= n; i++) {
        int o = a[i];
        unordered_set<int> cur;
        cur.insert(o);
        for(auto x : pre) {
            cur.insert(o | x);
        }
        for(auto x : cur) {
            all.insert(x);
        }
        pre = cur;
    }
    
    int id = 2;
    for(auto x : all) {
        mp[x] = id++;
    }

    memset(cnt, 0, sizeof cnt);
    memset(dp, 0, sizeof dp);

    vector<Tuple> pseg;
    int si = 0, lsi = 1e9, rsi = -1;
    for(int i = 1; i <= n; i++) {
        vector<Tuple> cseg;
        int o = a[i];
        int j = pseg.size() - 1;
        int L = i, R = i;
        while(j >= 0) {
            if((o | pseg[j].o) == o) {
                L = pseg[j].l;
                j--;
            } else {
                cseg.push_back({L, R, o});
                //Update for next round
                R = L - 1;
                L = pseg[j].l;
                o |= pseg[j].o;
                j--;
            }
        }

        //update 1 more time
        cseg.push_back({L, R, o});
        reverse(cseg.begin(), cseg.end());
        //用二维偏序

        for(auto& seg : cseg) {
            int x1 = seg.l - 1, x2 = seg.r - 1;
            int y1 = 1, y2 = mp[seg.o];
            if(x1 - 1 >= 0) {
                q[x1 - 1].push_back({y1 - 1, y2, si, i});
                cnt[si] += 2;
            }
            q[x2].push_back({y2, y1 - 1, si, i});
            cnt[si] += 2;
            if(i == n) {
                lsi = min(lsi, si);
                rsi = max(rsi, si);
            }
            oval[si] = y2;
            si++;
            /*
            q[qi++] = {x1 - 1, y1 - 1, 1, i, o};
            q[qi++] = {x1 - 1, y2, -1, i, o};
            
            q[qi++] = {x2, y1 - 1, -1, i, o};
            q[qi++] = {x2, y2, 1, i, o};
            */
        }
        pseg = cseg;
    }

    tr.init(id + 10);
    vec[0].push_back({1, 1});
    int j = 0;
    int ans = 0;
    for(int x = 0; x <= n; x++) {
        auto& v = q[x];
        while (j <= x) {
            for(auto& p : vec[j]) {
                tr.update(p.first, p.second); 
            }
            j++;
        }

        for(auto& v : q[x]) {
            int y1 = v.y1, y2 = v.y2, si = v.si;
            cnt[si] -= 2;
            int val1 = (tr.query(0, y1));
            int val2 = (-tr.query(0, y2));
            if(val2 < 0) val2 += MOD;
            dp[si] += val1;
            dp[si] %= MOD;
            dp[si] += val2;
            dp[si] %= MOD;
            if(cnt[si] == 0) {
                vec[v.i].push_back({oval[si], dp[si]});
            }
        }
    }

    for(int i = lsi; i <= rsi; i++) {
        ans += dp[i];
        ans %= MOD;
    }
    cout << ans << endl;
}

/*
7
9 5 5 4 3 1 1

8
896 795 705 493 485 439 335 299

3
3 1 4
*/

int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
