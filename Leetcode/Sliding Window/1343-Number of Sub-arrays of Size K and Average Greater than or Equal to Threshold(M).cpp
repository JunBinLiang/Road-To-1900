class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        long long s = 0;
        int ans = 0;
        for(int i = 0; i < arr.size(); i++) {
            s += arr[i];
            if(i + 1 >= k) {
                if((threshold + 0ll) * k <= s) {
                    ans++;
                }
                s -= arr[i - k + 1];
            }
        }
        return ans;
    }
};
