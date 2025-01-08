class Solution {
public:
    int countPrefixSuffixPairs(vector<string>& a) {
        int ans = 0;
        for(int i = 0; i < a.size(); i++) {
            for(int j = i + 1; j < a.size(); j++) {
                if(ok(a[i], a[j])) {
                    ans++;
                }
            }
        }
        return ans;
    }
    
    bool ok(string& s, string& t) {
        if(s.size() > t.size()) return false;
        string sub1 = t.substr(0, s.size());
        string sub2 = t.substr(t.size() - s.size(), s.size());
        return sub1 == s && sub2 == s;
    }
};
