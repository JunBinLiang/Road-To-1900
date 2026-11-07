template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

class Solution {
public:
    vector<int> largestPower(vector<int>& nums) {
        vector<int> ans;
        vector<vector<int>> a = {nums};
        for(int j = 0; j < 15; j++) {
            vector<vector<int>> cur;
            int ith = 14 - j;
            bool ok = true;
            int cnt = 0;
            for(vector<int>& vec : a) {
                vector<vector<int>> split = process(vec, ith);
                if(ok) {
                    for(vector<int>& vec : split) {
                        for(int x : vec) {
                            if(x & (1 << ith)) {
                                if(ok) cnt++;
                            } else {
                                ok = false;
                            }
                        }
                    }
                    for(vector<int>& vec : split) {
                        cur.push_back(vec);
                    }
                } else {
                    vector<vector<int>> m = merge(split);
                    for(vector<int>& vec : m) {
                        cur.push_back(vec);
                    }
                }
            }

    
            a = cur;            
            ans.push_back(cnt);
        }
        return ans;
    }

    vector<vector<int>> process(vector<int>& vec, int i) {
        vector<int> a, b;
        for(int x : vec) {
            if(x & (1 << i)) a.push_back(x);
            else b.push_back(x);
        }
        if(a.size() == 0) {
            return {vec};
        }
        if(b.size() == 0) {
            return {a};
        }
        return {a, b};
    }

    vector<vector<int>> merge(vector<vector<int>>& a) {
        if(a.size() == 1) {
            return a;
        }
        vector<int> ans;
        for(vector<int>& vec : a) {
            for(int x : vec) {
                ans.push_back(x);
            }
        }

        return {ans};
    }
};
