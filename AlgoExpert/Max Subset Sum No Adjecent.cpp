#include <vector>
using namespace std;

int maxSubsetSumNoAdjacent(vector<int> a) {
  // Write your code here.
  if(a.size() == 0) {
    return 0;
  }
  vector<int> dp(a.size());
  dp[0] = a[0];
  for(int i = 1; i < a.size(); i++) {
    dp[i] = a[i];
    if(i - 2 >= 0) dp[i] = max(dp[i], a[i] + dp[i - 2]);
    dp[i] = max(dp[i], dp[i - 1]);
  }
  return dp.back();
}
