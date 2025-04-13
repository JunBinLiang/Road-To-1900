long long cal(vector<int>& a) {
    long long s = 1;
    int cur = 1;
    for(int i = 0; i < a.size(); i++) {
        if(!a[i]) continue;
        for(int j = 1; j <= a[i]; j++) {
            s *= cur;
            cur++;
            s /= j;
            if(s >= 2000000) {
                return 2000000;
            }
        }
    }
    return s;
}

class Solution {
public:
    string smallestPalindrome(string s, int k) {
        vector<int> cnt(26);
        for(char c : s) {
            cnt[c - 'a']++;
        }

        string t = "";
        string ans = "";
        int sum = 0;
        for(int i = 0; i < 26; i++) {
            if(cnt[i] % 2 == 1) {
                char c = (char)(i + 'a');
                t += c;
                cnt[i]--;
            }
            cnt[i] /= 2;
            sum += cnt[i];
        }

        if(cal(cnt) < k) return "";
        
        while(k && ans.size() < sum) {
           for(int i = 0; i < 26; i++) {
               if(!cnt[i]) continue;
               cnt[i]--;
               long long w = cal(cnt);
               cnt[i]++;
               if(w >= k) {
                   cnt[i]--;
                   ans += (char)(i + 'a');
                   break;
               } else {
                   k -= w;
               }
           } 
        }

        string rev = ans;
        reverse(rev.begin(), rev.end());
        ans += t;
        ans += rev;
        return ans;
    }
};
