const int N = 1e5 + 10;
int p[N];
int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
}

struct E {
    int u, v, w;
    bool operator<(const E& other) {
        return w < other.w;
    }
};

class Solution {
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        for(int i = 0; i < n; i++) p[i] = i;
        int con = 0;
        int mn = 2e9;
        vector<E> a;
        for(int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1], s = edges[i][2], op = edges[i][3];
            if(op == 1) {
                int r1 = find(u), r2 = find(v);
                if(r1 == r2) {
                    return -1;
                }
                con++;
                mn = min(mn, s);
                p[r1] = r2;
            } else {
                a.push_back({u, v, s});
            }
        }
        
        sort(a.begin(), a.end());

        int l = 0, r = mn;
        int ans = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(ok(n, edges, k, mid)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
        
    }

    bool ok(int n, vector<vector<int>>& edges, int k, int mid) {
        for(int i = 0; i < n; i++) p[i] = i;
        int con = 0;
        vector<E> a;
        for(int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1], s = edges[i][2], op = edges[i][3];
            if(op == 1) {
                int r1 = find(u), r2 = find(v);
                if(r1 == r2) {
                    return -1;
                }
                con++;
                p[r1] = r2;
            } else {
                if(s >= mid) {
                    a.push_back({u, v, 0});
                } else if(s * 2 >= mid) {
                    a.push_back({u, v, 1});
                }
            }
        }
        sort(a.begin(), a.end());
        int cost = 0;
        for(int i = 0; i < a.size(); i++) {
            int u = a[i].u, v = a[i].v, w = a[i].w;
            int r1 = find(u), r2 = find(v);
            if(r1 != r2) {
                p[r1] = r2;
                con++;
                cost += w;
            }
        }
        

        return con == n - 1 && cost <= k;
    }
};
