#include <bits/stdc++.h>
using namespace std;
 
int mod(int a, int m){
    return (a % m + m) % m;
}
 
void solve(){
    int n, m, q, op, i, x, k;
    cin >> n >> m >> q;
    vector<int> a(n+1);
    for(int i=1; i<=n; i++)
        cin >> a[i];
    map<int, long long> ans;
    for(int i=1; i*i<=m; i++)
        if(!(m % i)){
            ans[i] = 0;
            ans[m/i] = 0;
        }
    for(pair<int, int> p : ans)
        for(int i=1; i<=n; i++)
            ans[p.first] += mod(a[i] - a[i-1], p.first);
    while(q--){
        cin >> op;
        if(op == 1){
            cin >> i >> x;
            for(pair<int, int> p : ans){
                ans[p.first] += mod(x - a[i-1], p.first) - mod(a[i] - a[i-1], p.first);
                if(i != n)
                    ans[p.first] += mod(a[i+1] - x, p.first) - mod(a[i+1] - a[i], p.first);
            }
            a[i] = x;
        }
        else{
            cin >> k;
            cout << (ans[__gcd(k, m)] < m ? "YES" : "NO") << '\n';
        }
    }
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) solve();
}
