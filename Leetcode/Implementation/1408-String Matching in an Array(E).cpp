bool ok(string& s, string& t) {
    for(int i = 0; i < t.size(); i++) {
        if(i + s.size() - 1 < t.size()) {
            string sub = t.substr(i, s.size());
            if(s == sub) {
                return true;
            }
        }
    }
    return false;
}

class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        vector<string> ans;
        for(int i = 0; i < words.size(); i++) {
            for(int j = 0; j < words.size(); j++) {
                if(i == j) continue;
                if(ok(words[i], words[j])) {
                    ans.push_back(words[i]);
                    break;
                }
            }
        }
        return ans;
    }
};
