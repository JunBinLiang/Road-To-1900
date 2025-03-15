//https://www.lanqiao.cn/problems/501/learning/?page=1&first_category_id=1&name=%E5%AD%97%E4%B8%B2%E6%8E%92%E5%BA%8F
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

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;
int len = -1; //at most 145

int cal(int n, int k) {
    int chunk = n / k;
    int m = n % k;
    vector<int> a;
    for(int i = 0; i < k; i++) {
        a.push_back(chunk + (m > 0));
        if(m) m--;
    }
    int tot = n;
    int inv = 0;
    for(int i = 0; i < k; i++) {
        tot -= a[i];
        inv += (a[i] * tot);
    }
    return inv;
}

void check(string s) {
    int ans = 0;
    for(int i = 0; i <s.size(); i++) {
        for(int j = i + 1; j < s.size(); j++) {
            if(s[j] < s[i]) ans++;
        }
    }
    cout << ans << endl;
}

int get(vector<int>& p, int l, int r) {
    if(l > r) return 0;
    return l == 0 ? p[r] : p[r] - p[l - 1];
}

int getMost(vector<int>& cnt1, int n) { //贪心放就可以
    if(n == 0) {
        return 0;
    }
    vector<int> cnt2(26);
    int tot = 0;
    for(int i = 1; i <= n; i++) {
        int pos = -1, mx = -1, s = 0;
        for(int j = 25; j >= 0; j--) {
            if( i - 1 - cnt2[j] + s  >= mx) {
                pos = j;
                mx = i - 1 - cnt2[j] + s ;
            }
            s += cnt1[j];
        }
        tot += mx; 
        cnt2[pos]++;
    }
    return tot;
}

void solve() {
    int n;
    cin >> n;
    //先找最短长度，那第一个肯定是放最大字母
    for(int i = 1; i <= n; i++) {
        int m = i % 26, chunk = i / 26;
        int s = 0;
        vector<int> a;
        for(int j = 0; j < 26; j++) {
            a.push_back(chunk + (m > 0));
            if(m) {
                m--;
            }
        }
        int tot = i;
        for(int j = 0; j < a.size(); j++) {
            int cnt = a[j];
            tot -= cnt;
            s += (cnt * (tot));
        }
        if(s >= n) {
            len = i;
            break;
        }
    }
    
    string ans = "";
    int inv = 0;
    vector<int> cnt(26);
    for(int i = 0; i < len; i++) {
        for(int c = 0; c < 26; c++) {
            //try c
            vector<int> p(26);
            for(int j = 0; j < 26; j++) {
                p[j] = cnt[j];
                if(j) p[j] += p[j - 1];
            }
            
            int cCon = get(p, c + 1, 25);
            vector<int> cnt1(cnt.begin(), cnt.end());
            cnt1[c]++;

            int most = getMost(cnt1, len - i - 1);
            
            //for(int x : cnt1) cout << x << " ";
            //cout << endl;
            //cout << i << " " << c << "   " << ans << "   |" << inv << "   " << cCon << "  " << most << endl; 

            if(inv + cCon + most >= n) {
                ans += (char)(c + 'a');
                cnt[c]++;
                inv += cCon;
                break;
            }
        }
    }

    //check(ans);
    cout << ans << endl;
}

int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
