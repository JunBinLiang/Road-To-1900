bool comp(vector<int>& p1, vector<int>& p2) {
    return (-p1[0] + p1[1]) < (-p2[0] + p2[1]);
}
class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& a) {
        int s = 0;
        for(int i = 0; i < a.size(); i++) {
            s += a[i][0];
        }
        
        sort(a.begin(), a.end(), comp);
        for(int i = 0; i < a.size() / 2; i++) {
            s -= a[i][0];
            s += a[i][1];
        }
        
        return s;
    }
};
