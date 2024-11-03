#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include<set>
#include<unordered_set>
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


struct SA {
    string s; int n, m;
    vector<int> sa, rk, p, height;
    vector<int> discrete, second; //first[i] => 第i个后缀按前k个字母排好序后的前k个离散化数值
    //int sa[1000010], rk[1000010], p[1000010], height[1000010], discrete[1000010], second[1000010], oldDiscrete[1000010];
    void init(string s, int N = 1000010) {
        this -> n = s.size();
        this -> m = 256;
        this -> s = " " + s;
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
} sa;

/*
给出一个字符串s 和数组a

求从 0 到 n - 1(每个都要输出), r
有多少个后缀对(2个)拥有至少r个相同的前缀，并且求出这些对中 a[i] * a[j] 的最大值
*/

const int N = 3e5 + 10, INF = 2e9;
int p[N], sz[N];
vector<int> h[N];
int max1[N], max2[N], min1[N], min2[N];

long long cnt = 0, maxv = -2000000000000000000ll;;

int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
} 

long long get(int n) {
    return (n - 1ll) * n / 2;
}

pair<long long, long long> cal(vector<int>& a, int i) {
    for(int index : h[i]) {
        int r1 = find(index - 1), r2 = find(index); 
        vector<int> a = {max1[r1], max2[r1]};
        sort(a.begin(), a.end());
        cnt -= get(sz[r1]); cnt -= get(sz[r2]);
        p[r1] = r2;
        sz[r2] += sz[r1];
        cnt += get(sz[r2]);
        
        for(int x = 0; x < 2; x++) {
            int val = a[x];
            if(abs(val) == INF) continue;
            if(val >= max1[r2]) {
                max2[r2] = max1[r2];
                max1[r2] = val;
            } else if(val >= max2[r2]) {
                max2[r2] = val;
            }
        }

        a = {min1[r1], min2[r1]};
        for(int x = 0; x < 2; x++) {
            int val = a[x];
            if(abs(val) == INF) continue;
            if(val <= min1[r2]) {
                min2[r2] = min1[r2];
                min1[r2] = val;
            } else if(val <= min2[r2]) {
                min2[r2] = val;
            }
        }
        
        if(abs(max2[r2]) != INF) maxv = max(maxv, (max1[r2] + 0ll) * max2[r2]);
        if(abs(min2[r2]) != INF) maxv = max(maxv, (min1[r2] + 0ll) * min2[r2]);
    }
    if(cnt == 0) return {0, 0};
    return {cnt, maxv};
}

void solve() {
    int n;
    string s;
    cin >> n >> s;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    
    sa.init(s, n + 10);
    sa.getSA();
    sa.getHeight();
    
    /*for(int i = 1; i <= n; i++) cout << sa.sa[i] << " ";
    cout << endl;
    for(int i = 1; i <= n; i++) cout << sa.height[i] << " ";
    cout << endl;*/
    
    for(int i = 2; i <= n; i++) {
        h[sa.height[i]].push_back(i);
    }
    

    for(int i = 1; i <= n; i++) {
        p[i] = i;
        sz[i] = 1;
        max1[i] = a[sa.sa[i]];
        max2[i] = -INF;
        
        min1[i] = a[sa.sa[i]];
        min2[i] = INF;
    }

    vector<pair<long long, long long>> ans;
    for(int i = n - 1; i >= 0; i--) {
        ans.push_back(cal(a, i));
    }
    for(int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
    
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
