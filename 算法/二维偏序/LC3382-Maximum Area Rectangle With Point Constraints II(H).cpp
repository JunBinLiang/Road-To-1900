const int N = 2e5 + 100;
int add[N];
long long area[N];

const int FENWICK_SIZE = (400000 + 10);
struct Fenwick {
    int tree[FENWICK_SIZE];
    int sz;
    void init(int n) {
        sz = n;
        for(int i = 0; i <= n + 1; i++) tree[i] = 0;
    }

    void update(int i, int val) {
        i++;
        while(i < sz) {
            tree[i] += val;
            i += (i & -i);
        }
    }

    int pre(int i) {
        int sum = 0;
        while(i > 0){
            sum += tree[i];
            i -= ( i & -i);
        }
        return sum;
    }

    int query(int i, int j) {
        return pre(j + 1) - pre(i);
    }
} tr;

//使用二维偏序
class Solution {
public:
    long long maxRectangleArea(vector<int>& a, vector<int>& b) {
        vector<vector<int>> q;
        vector<pair<int, int>> cur;
        vector<int> allpoint;
        for(int x : a) allpoint.push_back(x);
        for(int y : b) allpoint.push_back(y);
        
        long long ans = -1;
        map<int, vector<int>> mp;
        map<pair<int, int>, vector<int>> mp1;
        int n = a.size();
        for(int i = 0; i < n; i++) {
            int x = a[i], y = b[i];
            mp[x].push_back(y);
            cur.push_back({x, y});
        }
        
        for(auto it = mp.begin(); it != mp.end(); it++) {
            int x = it -> first;
            vector<int>& ycor = it -> second;
            sort(ycor.begin(), ycor.end());
            for(int i = 1; i < ycor.size(); i++) {
                pair<int, int> p = {ycor[i - 1], ycor[i]};
                mp1[p].push_back(it -> first);
            }
        }
        
        int o = 0;
        for(auto it = mp1.begin(); it != mp1.end(); it++) {
            pair<int, int> p = it -> first;
            vector<int>& xcor = it -> second;
            if(xcor.size() == 1) continue;
            int y1 = p.first, y2 = p.second;
            for(int i = 1; i < xcor.size(); i++) {
                int x1 = xcor[i - 1], x2 = xcor[i];
                
                q.push_back({x1 - 1, y1 - 1, 1, o});
                q.push_back({x1 - 1, y2, -1, o});
                q.push_back({x2, y1 - 1, -1, o});
                q.push_back({x2, y2, 1, o});
                allpoint.push_back(x1 - 1);
                allpoint.push_back(y1 - 1);
                area[o] = (x2 - x1 + 0ll) * (y2 - y1);
                add[o] = 0;
                o++;
            }
        }
        
        sort(cur.begin(), cur.end());
        sort(allpoint.begin(), allpoint.end());
        unordered_map<int, int> f;
        int id = 1;
        for(int x : allpoint) {
            if(f.find(x) == f.end()) {
                f[x] = id++;
            }
        }
        tr.init(id + 10);
        sort(q.begin(), q.end());
        int j = 0;
        for(auto& v : q) {
            int x = v[0], y = v[1], c = v[2], index = v[3];
            while(j < cur.size() && cur[j].first <= x) {
                tr.update(f[cur[j].second], 1);
                j++;
            }
            add[index] += (c * tr.pre(f[y] + 1));
        }
        
        for(int i = 0; i < o; i++) {
            if(add[i] == 4) { //exclude itself
                ans = max(ans, area[i]);
            }
        }
        return ans;
    }
};
