#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include<set>
#include<unordered_map>
#include <string.h>


using namespace std;

/*
后缀数组
sa[i] : 排名第i的是第几个后缀
rank[i] : 第i个后缀的排名
height[i] : sa[i] 和 sa[i - 1] 的最长公共前缀

height[i] = lcp(i, i - 1)
h[i] = height[rk[i]] : 第i个后缀和排名在他前面一个后缀的最长公共前缀 
性质 : h[i] >= h[i - 1] - 1
*/


/*
后缀数组
sa[i] : 排名第i的是第几个后缀
rank[i] : 第i个后缀的排名
height[i] : sa[i] 和 sa[i - 1] 的最长公共前缀

height[i] = lcp(i, i - 1)
h[i] = height[rk[i]] : 第i个后缀和排名在他前面一个后缀的最长公共前缀 
性质 : h[i] >= h[i - 1] - 1
*/

template <typename T> 
struct SA {
    T s; int n, m;
    vector<int> sa, rk, p, height;
    vector<int> discrete, second; //first[i] => 第i个后缀按前k个字母排好序后的前k个离散化数值
    //int sa[1000010], rk[1000010], p[1000010], height[1000010], discrete[1000010], second[1000010], oldDiscrete[1000010];
    void init(T s, int N, int m) {
        this -> n = s.size() - 1;
        this -> m = m;
        this -> s = s;
        N = max(N, m + 1);

        sa = vector<int>(N, 0);
        rk = vector<int>(N, 0);
        p = vector<int>(N, 0);
        discrete = vector<int>(N, 0);
        second = vector<int>(N, 0);
        height = vector<int>(N, 0);
    }

    void getSA() {
        for(int i = 1; i <= n; i++) {
            discrete[i] = s[i];
            p[discrete[i]] ++ ;
        }
        
        for (int i = 2; i <= m; i ++ ) p[i] += p[i - 1];
        for (int i = n; i >= 1; i -- ) {
            sa[p[discrete[i]]] = i;
            p[discrete[i]]--;
        }
        
        for(int k = 1; k <= n; k *= 2) {
            //没有第二关键字
            int num = 0; 
            for (int i = n - k + 1; i <= n; i++ ) second[++num] = i;
            for (int i = 1; i <= n; i ++ ) { 
                if (sa[i] > k) { //sa[i] 是 sa[i] - k的第二关键字
                    second[++num] = sa[i] - k;
                }
            } //已经按第二关键字排好序, second[i] => 排名第i的是第几个后缀, 这里是根据第二关键字
                
            //按第一关键字基数排序, 相同的会保证第二关键字的in place order 不变
            for (int i = 1; i <= m; i++ ) p[i] = 0;
            for (int i = 1; i <= n; i++ ) p[discrete[i]]++ ;
            for (int i = 2; i <= m; i++ ) p[i] += p[i - 1];
            for (int i = n; i >= 1; i-- ) {
                sa[p[discrete[second[i]]]--] = second[i];
                second[i] = 0;
            }

            swap(discrete, second);  //这里的second 现在保存的是老的离散化指
            vector<int> oldDiscrete = second;
            //离散化
            discrete[sa[1]] = 1, num = 1;
            for (int i = 2; i <= n; i ++ ) {
                discrete[sa[i]] = (oldDiscrete[sa[i]] == oldDiscrete[sa[i - 1]] && oldDiscrete[sa[i] + k] == oldDiscrete[sa[i - 1] + k]) ? num : ++num;
                //discrete[sa[i]] = (second[sa[i]] == second[sa[i - 1]] && second[sa[i] + k] == second[sa[i - 1] + k]) ? num : ++num;
            }
            if (num == n) break; //完全分离，可提前break
            m = num;  
        }
    }

    void getHeight() {
        for (int i = 1; i <= n; i ++ ) rk[sa[i]] = i;
        for (int i = 1, k = 0; i <= n; i ++ ) {
            if (rk[i] == 1) continue;
            if (k) k -- ;
            int j = sa[rk[i] - 1];
            while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k ++ ;
            height[rk[i]] = k;
        }
    }
};

/*
for 1 <= i <= n，
求 s[1 : i] 有多少个不同(distinct)的子数组
*/
const int N = 1e5 + 10;
long long tot = 0;
int Nxt[N], Pre[N];
SA<vector<int>> sa;
void del(int n, int i) {
    int pre = Pre[i], nxt = Nxt[i];
    tot -= ((n - sa.sa[i] + 1) - sa.height[i]);
    tot -= ((n - sa.sa[nxt] + 1) - sa.height[nxt]);
    sa.height[nxt] = min(sa.height[i], sa.height[nxt]);
    Pre[nxt] = pre;
    Nxt[pre] = nxt;
    tot += (n - sa.sa[nxt] + 1 - sa.height[nxt]);
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    unordered_map<int, int> mp;
    int id = 1;
    for(int i = n; i >= 1; i--) {
        cin >> a[i];
        //离散化
        if(mp.find(a[i]) == mp.end()) mp[a[i]] = id++;
        a[i] = mp[a[i]];
    }

    sa.init(a, n + 10, id + 1);
    sa.getSA();
    sa.getHeight();
    
    /*for(int i = 1; i <= n; i++) cout << sa.sa[i] << " ";
    cout << endl;
    for(int i = 1; i <= n; i++) cout << sa.height[i] << " ";
    cout << endl;*/

    
    for(int i = 1; i <= n; i++) {
        int len = n - sa.sa[i] + 1;
        if(i > 1) {
            tot += (len - sa.height[i]);
        } else {
            tot += len;
        }
    }

    for(int i = 1; i <= n; i++) {
        Nxt[i] = i + 1;
        Pre[i] = i - 1;
    }
    Nxt[0] = 1;
    Pre[n + 1] = n;
    sa.height[0] = sa.height[n + 1] = 0;

    vector<long long> ans;
    for(int i = 1; i <= n; i++) {
        ans.push_back(tot);
        del(n, sa.rk[i]);
    }
    
    reverse(ans.begin(), ans.end());
    for(long long x : ans) cout << x << endl;
}

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
