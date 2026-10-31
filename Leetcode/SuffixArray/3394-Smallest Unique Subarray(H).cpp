struct SA {
    vector<int> s; int n, m;
    //vector<int> sa, rk, p, height;
    //vector<int> discrete, second; //first[i] => 第i个后缀按前k个字母排好序后的前k个离散化数值
    int sa[200010], rk[200010], p[200010], height[200010], discrete[200010], second[200010], oldDiscrete[200010];
    void init(vector<int>& a, int m, int N = 1000010) {
        this -> n = a.size();
        this -> m = m;
        for(int i = 0; i <= n + 10; i++) {
            discrete[i] = p[i] = sa[i] = rk[i] = height[i] = second[i] = 0;
        }
        
        vector<int> news(n + 1);
        for(int i = 0; i < n; i++) {
            news[i + 1] = a[i];
        }
        this -> s = news;

        /*
        N = max(N, m + 1); //becare ful if N is too small
        sa = vector<int>(N, 0);
        rk = vector<int>(N, 0);
        p = vector<int>(N, 0);
        discrete = vector<int>(N, 0);
        second = vector<int>(N, 0);
        height = vector<int>(N, 0);*/
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
            
            //离散化
            discrete[sa[1]] = 1, num = 1;
            for (int i = 2; i <= n; i ++ ) {
                //discrete[sa[i]] = (oldDiscrete[sa[i]] == oldDiscrete[sa[i - 1]] && oldDiscrete[sa[i] + k] == oldDiscrete[sa[i - 1] + k]) ? num : ++num;
                discrete[sa[i]] = (second[sa[i]] == second[sa[i - 1]] && second[sa[i] + k] == second[sa[i - 1] + k]) ? num : ++num;
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

class Solution {
public:
    int smallestUniqueSubarray(vector<int>& a) {
        int n = a.size();
        int id = 1;
        map<int, int> mp;
        for(int i = 0; i < n; i++) {
            if(mp.find(a[i]) == mp.end()) {
                mp[a[i]] = id++;
            }
            a[i] = mp[a[i]];
        }

        sa.init(a, id + 1);
        sa.getSA();
        sa.getHeight();
        int ans = n;

        for(int i = 1; i <= n; i++) {
            int lcp = sa.height[i];
            if(i + 1 <= n) {
                lcp = max(lcp, sa.height[i + 1]);
            }

            int len = n - sa.sa[i];
            if(len > lcp) {
                ans = min(ans, lcp + 1);
            }
        }
        return ans;
    }
};
