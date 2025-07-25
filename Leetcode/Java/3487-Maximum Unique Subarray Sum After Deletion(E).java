class Solution {
    public int maxSum(int[] nums) {
        Arrays.sort(nums);
        if(nums[nums.length - 1] < 0) {
            return nums[nums.length - 1];
        }
        Set<Integer> set = new HashSet<>();
        int ans = 0;
        for(int x : nums) {
            if(x >= 0) {
                if(!set.contains(x)) {
                    ans += x;
                    set.add(x);
                }
            }
        }
        return ans;
    }
}
