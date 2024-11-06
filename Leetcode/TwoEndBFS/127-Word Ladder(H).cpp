class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& a) {
        if(find(a.begin(), a.end(), endWord) == a.end()) {
            return 0;
        }
        
        queue<pair<string, int>> q1, q2;
        q1.push({beginWord, 1});
        q2.push({endWord, 1});
        unordered_map<string, int> mp1, mp2;
        unordered_map<string, vector<string>> g;
        mp1[beginWord] = mp2[endWord] = 1;
        
        for(string& s : a) {
            for(int i = 0; i < s.size(); i++) {
                string ana = s.substr(0, i) + "#" + s.substr(i + 1, s.size() - (i + 1));
                g[ana].push_back(s);
            }
        }
        
        while(q1.size() && q2.size()) {
            if(q1.size() > q2.size()) {
                swap(q1, q2);
                swap(mp1, mp2);
            }
            int sz = q1.size();
            for(int j = 0; j < sz; j++) {
                pair<string, int> p = q1.front(); q1.pop();
                string& s = p.first; 
                int& level = p.second;
                for(int i = 0; i < s.size(); i++) {
                    string ana = s.substr(0, i) + "#" + s.substr(i + 1, s.size() - (i + 1));
                    if(g.find(ana) == g.end()) continue;
                    for(string& nxt : g[ana]) {
                        if(mp2.find(nxt) != mp2.end()) {
                            return level + mp2[nxt];
                        }
                        if(mp1.find(nxt) == mp1.end()) {
                            mp1[nxt] = level + 1;
                            q1.push({nxt, level + 1});
                        }
                    }
                }
            }
        }
        return 0;
    }
};
