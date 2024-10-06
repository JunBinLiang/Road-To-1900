//https://vjudge.net/problem/POJ-2976
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string.h>

using namespace std;  

/**
 * Approach: Greedy + BinarySearch
 * 题意：有N个考试，每个考试有ai和bi两个值，最后成绩由上面的公式求得。幸运的是，可以放弃K个科目，求最大化最后的成绩。
 * 思路：该题实质上就是一个 最大化平均值 的问题
 * 最大化平均值：有n个物品的重量和价值分别为 wi 和 vi，从中选择 k 个物品使得单位重量的价值最大。
 * 
 * 那么首先本题需要确定一个贪心策略，来去掉那些对正确率贡献小的考试。
 * 那么如何确定某个考试[ai, bi]对总体准确率x的贡献呢？
 * ai / bi肯定是不行的，不然例子里的[0,1]会首当其冲被刷掉。
 * 因此这里需要使用到 01分数规划 的一个技巧：
 * 题目求的是 max(∑a[i] / ∑b[i])，其中a,b都是一一对应的。
 * 那么可以转化一下：
 *   令 r = ∑a[i] / ∑b[i]，则有 ∑a[i] - ∑b[i] * r = 0；
 * 然后我们就可以 二分枚举 r 的值即可。
 * 对于每一个 r, 求出每个 a[i] - b[i] * r; 然后排序，去除 k 个最小值。
 * 然后相加得到结果 Q(r)，
 * 如果 Q(r) > 0 说明 r 的值偏小，因为可能存在 r 使得 Q(r) = 0；
 * 如果 Q(r) < 0 说明选取的 r 值过大；
 * 
 * 时间复杂度：O(nlogn)
 */

double eps = 1e-5;

bool ok(vector<double>& a, vector<double>& b, int k, double mid) {
    vector<double> c;
    for(int i = 0; i < a.size(); i++) {
        c.push_back((a[i] + 0.0) - mid * b[i]);
    }
    sort(c.begin(), c.end());

    double s = 0;
    for(int i = k; i < a.size(); i++) {
        s += c[i];
    }
    return s >= 0;
}

bool solve() {
    int n, k;
    cin >> n >> k;
    if(n == 0 && k == 0) {
        return false;
    }

    vector<double> a(n), b(n);
    for(int i = 0; i < n; i++) scanf("%lf", &a[i]);
    for(int i = 0; i < n; i++) scanf("%lf", &b[i]);
    
    double l = 0, r = 1e6;
    while(r - l > eps) {
        double mid = (l + r) / 2;
        if(ok(a, b, k, mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    //printf("%.0f\n", 100.0 * ans);
    cout << (int)(100 * l + 0.5) << endl; 
    return true;
}

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(solve()) {
        
    }
    return 0;
}
