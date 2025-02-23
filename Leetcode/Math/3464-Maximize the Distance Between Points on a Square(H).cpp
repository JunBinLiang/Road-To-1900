bool comp1(pair<int, int>& p1, pair<int, int>& p2) {
    return p1.second < p2.second;
}

bool comp2(pair<int, int>& p1, pair<int, int>& p2) {
    return p1.first < p2.first;
}

bool comp3(pair<int, int>& p1, pair<int, int>& p2) {
    return p1.second > p2.second;
}

bool comp4(pair<int, int>& p1, pair<int, int>& p2) {
    return p1.first > p2.first;
}

long long dis(pair<int, int>& p1, pair<int, int>& p2) {
    long long dis = abs(p1.first - p2.first) + abs(p1.second - p2.second);
    return dis;
}

class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& p, int k) {
        
        //(0, 0), (0, side), (side, side), (side, 0)
        vector<pair<int, int>> a, b, c, d;
        
        for(int i = 0; i < p.size(); i++) {
            int x = p[i][0], y = p[i][1];
            if(x == 0) a.push_back({x, y});
        }
        
        for(int i = 0; i < p.size(); i++) {
            int x = p[i][0], y = p[i][1];
            if(y == side) b.push_back({x, y});
        }
        
        for(int i = 0; i < p.size(); i++) {
            int x = p[i][0], y = p[i][1];
            if(x == side) c.push_back({x, y});
        }
        
        for(int i = 0; i < p.size(); i++) {
            int x = p[i][0], y = p[i][1];
            if(y == 0) d.push_back({x, y});
        }
        
        sort(a.begin(), a.end(), comp1);
        sort(b.begin(), b.end(), comp2);
        sort(c.begin(), c.end(), comp3);
        sort(d.begin(), d.end(), comp4);
        vector<pair<int, int>> vec;
        for(int i = 0; i < a.size(); i++) {
            vec.push_back(a[i]);
        }
        for(int i = 0; i < b.size(); i++) {
            vec.push_back(b[i]);
        }
        for(int i = 0; i < c.size(); i++) {
            vec.push_back(c[i]);
        }
        for(int i = 0; i < d.size(); i++) {
            vec.push_back(d[i]);
        }
        if(vec[0].first == vec.back().first && vec[0].second == vec.back().second) vec.pop_back();
        
        
        
        /*for(int i = 0; i < vec.size() * 2; i++) {
            cout << vec[i % vec.size()].first << "   " << vec[i % vec.size()].second << endl;
        }
        cout << endl << endl;
        
        bool t = ok(vec, 66, k);
        cout << "final " << t << endl;*/

        int l = 1, r = 2e9;
        int ans = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(ok(vec, mid, k)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
    
    bool ok(vector<pair<int, int>>& a, int mid, int k) {
        int n = a.size();
        vector<int> nxt(2 * n, -1);
        for(int r = 0, l = 0; r < 2 * n; r++) {
            while(l <= r && dis(a[r % n], a[l % n]) >= mid) {
                nxt[l] = r;
                l++;
            }
        }

        for(int i = 0; i < n; i++) {
            int j = i;
            vector<int> b;
            while(j < i + n && j != -1) {
                b.push_back(j);
                j = nxt[j];
                if(b.size() == k) break;
            }
            
            if(b.size() < k) continue;
            if(dis(a[b[0]], a[b.back() % n]) >= mid) {                
                return true;
            }
        }
        return false;
    }
};
