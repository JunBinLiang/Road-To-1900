#include <vector>
using namespace std;

int q(vector<int>& nums, int k) {
  int pivot = nums[rand() % nums.size()];
  vector<int> left;
  vector<int> mid;
  vector<int> right;
        
  for (int num: nums) {
    if (num < pivot) {
      left.push_back(num);
    } else if (num > pivot) {
        right.push_back(num);
    } else {
      mid.push_back(num);
    }
  }
        
  if (k <= left.size()) {
    return q(left, k);
  }
  if (left.size() + mid.size() < k) {
    return q(right, k - left.size() - mid.size());
  }
  return pivot;
}

int quickselect(vector<int> array, int k) {
  // Write your code here.
  return q(array, k);
}
