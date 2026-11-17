class Solution {
public:
    int minLength(string s, int k) {
        int ans = -1;
        int l = 2, r = s.size();
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(ok(s, mid, k)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        int cnt1 = 0, cnt2 = 0;
        for(int i = 0; i < s.size(); i++) {
            if(i % 2 == 0 && s[i] != '0') {
                cnt1++;
            }

            if(i % 2 == 1 && s[i] != '1') {
                cnt1++;
            }

            if(i % 2 == 0 && s[i] != '1') {
                cnt2++;
            }

            if(i % 2 == 1 && s[i] != '0') {
                cnt2++;
            }

        }

        if(min(cnt1, cnt2) <= k) ans = 1;

        return ans;
    }

    bool ok(string& s, int mid, int k) {
        int cnt = 0;
        for(int i = 0; i < s.size(); i++) {
            int j = i;
            while(j < s.size() && s[j] == s[i]) {
                j++;
            }
            int x = j - i;
            cnt += (x / (mid + 1));
            i = j - 1;
        }
        return cnt <= k;
    }
};
