#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    
#include <deque>  

using namespace std;
using ll = long long;

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int MOD = 998244353;
const int N = 2e5 + 100;
struct Node {
    int l, r;
    int cnt[4], s[4];
    void init() {
        for(int i = 0; i < 4; i++) {
            cnt[i] = s[i] = 0;
        }
    }
} tr[N * 4];

string s;

void pushup(int u) {
    int left = u * 2 + 1, right = u * 2 + 2;
    for(int i = 0; i < 4; i++) {
        tr[u].cnt[i] = (tr[left].cnt[i] + tr[right].cnt[i]);
        tr[u].cnt[i] %= MOD;
        tr[u].s[i] = (tr[left].s[i] + tr[right].s[i]);
        tr[u].s[i] %= MOD;
    }

    //00 01 10 11
    vector<int> vec1, vec2;
    for(int b1 = 0; b1 < 4; b1++) {
        vec1 = {b1 / 2, b1 % 2};
        for(int b2 = 0; b2 < 4; b2++) {
            vec2 = {b2 / 2, b2 % 2};
            int b = vec1[0] * 2 + vec2[1];
            if(vec1[1] == vec2[0]) { //same
                tr[u].s[b] += (((tr[left].s[b1] + 0ll) * tr[right].cnt[b2]) % MOD);
                tr[u].s[b] %= MOD;
                tr[u].s[b] -= (((tr[left].cnt[b1] + 0ll) * tr[right].cnt[b2]) % MOD);
                if(tr[u].s[b] < 0) tr[u].s[b] += MOD;
                tr[u].s[b] += (((tr[left].cnt[b1] + 0ll) * tr[right].s[b2]) % MOD); 
                tr[u].s[b] %= MOD;
            } else { //different
                tr[u].s[b] += (((tr[left].s[b1] + 0ll) * tr[right].cnt[b2]) % MOD);
                tr[u].s[b] %= MOD;
                tr[u].s[b] += (((tr[left].cnt[b1] + 0ll) * tr[right].s[b2]) % MOD); 
                tr[u].s[b] %= MOD;
            }
            tr[u].cnt[b] += (((tr[left].cnt[b1] + 0ll) * tr[right].cnt[b2]) % MOD);
            tr[u].cnt[b] %= MOD;
        }
    }
    
    /*cout << "after " << tr[u].l << "  " << tr[u].r << endl;
    for(int i = 0; i < 4; i++) cout << tr[u].cnt[i] << " ";
    cout << endl;
    for(int i = 0; i < 4; i++) cout << tr[u].s[i] << " ";
    cout << endl;
    cout << endl;*/
}

void build(int u) {
    int l = tr[u].l, r = tr[u].r;
    if(l == r) {
        tr[u].init();
        int val = s[l] - '0';
        if(val == 0) {
            tr[u].cnt[0] = tr[u].s[0] = 1;
            tr[u].cnt[3] = tr[u].s[3] = 0;
        } else {
            tr[u].cnt[0] = tr[u].s[0] = 0;
            tr[u].cnt[3] = tr[u].s[3] = 1;
        }
        return;
    }
    
    int left = u * 2 + 1, right = u * 2 + 2;
    int mid = l + (r - l) / 2;
    tr[left] = {l, mid};
    tr[right] = {mid + 1, r};
    build(left);
    build(right);
    tr[u].init();
    pushup(u);
}

void update(int u, int index, int val) {
    int l = tr[u].l, r = tr[u].r;
    if(l == r) {
        if(val == 0) {
            tr[u].cnt[0] = tr[u].s[0] = 1;
            tr[u].cnt[3] = tr[u].s[3] = 0;
        } else {
            tr[u].cnt[0] = tr[u].s[0] = 0;
            tr[u].cnt[3] = tr[u].s[3] = 1;
        }
        return;
    }
    int mid = l + (r - l) / 2;
    int left = u * 2 + 1, right = u * 2 + 2;
    if(index <= mid) {
        update(left, index, val);
    } else {
        update(right, index, val);
    }
    pushup(u);
}

void solve() {
    int n, m;
    cin >> s >> m;
    n = s.size();
    tr[0] = {0, n - 1};
    tr[0].init();
    build(0);
    
    for(int i = 0; i < m; i++) {
        int j;
        cin >> j;
        j--;
        if(s[j] == '0') s[j] = '1';
        else s[j] = '0';
        update(0, j, s[j] - '0');
        long long ans = (tr[0].s[0] + 0ll) + tr[0].s[1] + tr[0].s[2] + tr[0].s[3];
        ans %= MOD;
        cout << ans << " ";
    }
    cout << endl;
}    


int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

