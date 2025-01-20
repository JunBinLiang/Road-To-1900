class Solution {
public:
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        unordered_map<int, pair<int, int>> mp;
        for(int i = 0; i < mat.size(); i++) {
            for(int j = 0; j < mat[0].size(); j++) {
                mp[mat[i][j]] = {i, j};
            }
        }
        
        vector<int> rows(mat.size()), cols(mat[0].size());
        
        for(int i = 0; i < arr.size(); i++) {
            pair<int, int> p = mp[arr[i]];
            int r = p.first, c = p.second;
            rows[r]++;
            cols[c]++;
            if(rows[r] == mat[0].size() || cols[c] == mat.size()) {
                return i;
            }
        }
        return -1;
    }
};
