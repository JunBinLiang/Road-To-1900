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
    void init(T s, int N = 1000010) {
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
};
