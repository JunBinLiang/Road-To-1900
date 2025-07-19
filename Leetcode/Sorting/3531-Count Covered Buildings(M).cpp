struct P {
    int x, y, t = 0;
};

bool comp1(P& p1, P& p2) {
    if(p1.x == p2.x) return p1.y < p2.y;
    return p1.x < p2.x;
}

bool comp2(P& p1, P& p2) {
    if(p1.y == p2.y) return p1.x < p2.x;
    return p1.y < p2.y;
}

class Solution {
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        vector<P> a;
        for(int i = 0; i < buildings.size(); i++) {
            int x = buildings[i][0], y = buildings[i][1];
            a.push_back({x, y, 0});
        }

        sort(a.begin(), a.end(), comp1);
        for(int i = 0; i < a.size(); i++) {
            int j = i;
            while(j < a.size() && a[i].x == a[j].x) {
                j++;
            }

            for(int k = i + 1; k < j - 1; k++) {
                a[k].t += 2;
            }
            i = j - 1;
        }

        sort(a.begin(), a.end(), comp2);
        for(int i = 0; i < a.size(); i++) {
            int j = i;
            while(j < a.size() && a[i].y == a[j].y) {
                j++;
            }
            for(int k = i + 1; k < j - 1; k++) {
                a[k].t += 2;
            }
            i = j - 1;
        }

        int ans = 0;
        for(int i = 0; i < a.size(); i++) {
            if(a[i].t == 4) ans++;
        }
        return ans;
    }
};
