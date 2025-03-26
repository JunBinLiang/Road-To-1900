#include <bits/stdc++.h>
using namespace std;

long long ans = 1e18; // 初始化一个较大的数作为初始答案
int n, prime[16] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53}; // 前16个质数

// 深度优先搜索函数
// k: 当前考虑的质数在 prime 数组中的索引
// cur: 当前的乘积
// fact: 当前的因子个数
void dfs(int k, long long cur, long long fact) {
  if (fact > n) return; // 当前的因子个数已经超过 n，直接返回
  if (fact == n && cur < ans) ans = cur; // 更新答案，如果当前因子个数等于 n 且当前乘积小于当前答案
  for (int i  = 1; i <= 61; i++) {
    if (cur * prime[k] >= ans) return; // 如果当前乘积乘以下一个质数大于等于当前答案，直接返回
    dfs(k + 1, cur *= prime[k], fact * (i + 1)); // 递归调用，考虑下一个质数，更新乘积和因子个数
  }
}

int main() {
  cin >> n; // 从输入读取 n
  dfs(0, 1, 1); // 从质数数组的第一个质数开始深度优先搜索
  cout << ans << endl; // 输出最终答案
  return 0;
}
