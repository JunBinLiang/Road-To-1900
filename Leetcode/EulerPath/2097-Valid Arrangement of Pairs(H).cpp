namespace Euler {
/*
欧拉路劲/回路 (边得联通)
路径: 每条边经过一次。
回路：每条边经过一次并回到原点。


无向图
欧拉路劲存在必要条件: 所有度数为奇数的点只能有0 或者 2 个。 (从奇数点开始搜)
欧拉回路存在必要条件: 所有度数为奇数的点只能有0。 (可以从任何点搜)


有向图：
欧拉路劲存在必要条件: 所有点入度等于出度 或者 除两个点所有点入度等于出度，两个点一个满足出度比入度多1一个满足入度比出度多1
欧拉回路存在必要条件: 所有点入度等于出度 (可以从任何点搜)

必要条件: 在充分条件下，是否可以有种方式一定可以构造一个方案。(是的)


注意:我们需要把搜索的边删除掉。如果是无向图，需要删掉反向边

*/  
    const int N = 5e5 + 10, M = (5e5 + 10) * 2; 
    unordered_set<int> usg[N];
    set<int> sg[N];
    int to[M];
    int from[M];
    int ans[N];
    int din[N], dout[N];
    bool used[M];
    int ei = 0, cnte = 0;
    
    void init() {
        memset(din, 0, sizeof din);
        memset(dout, 0, sizeof dout);
        memset(used, 0, sizeof used);
    }

    template <typename G>
    void add(G g[N], int u, int v) {
        g[u].insert(ei);
        to[ei] = v;
        from[ei] = u;
        ei++;

        //count degree
        dout[u]++;
        din[v]++;
    }
    
    template <typename G>
    void dfsNonDirected(G g[N], int u) {
        while(g[u].size() > 0) {
            int eid = (*g[u].begin());
            if(used[eid]) {
                g[u].erase(eid);
                continue;
            }
            used[eid] = true;
            used[eid ^ 1] = true; //删除反向边
            dfsNonDirected(g, to[eid]);
            ans[cnte++] = eid;
        }
    }

    template <typename G>
    void dfsDirected(G g[N], int u) {
        while(g[u].size() > 0) {
            int eid = (*g[u].begin());
            if(used[eid]) {
                g[u].erase(eid);
                continue;
            }
            used[eid] = true;
            dfsDirected(g, to[eid]);
            ans[cnte++] = eid;
        }
    }

    bool check(int type, int n) {
        if(type == 1) { //无向图欧拉路劲
            int cnt = 0;
            for(int i = 1; i <= n; i++) {
                if((din[i] + dout[i]) % 2 == 1) cnt++;
            }
            return cnt == 0 || cnt == 2;
        } else if(type == 2) {//无向图欧拉回路
            int cnt = 0;
            for(int i = 1; i <= n; i++) {
                if((din[i] + dout[i]) % 2 == 1) cnt++;
            }
            return cnt == 0;
        } else if(type == 3) { //有向图欧拉路劲
            int a = 0, b = 0;
            for(int i = 1; i <= n; i++) {
                if(din[i] != dout[i]) {
                    if(din[i] == 1 + dout[i]) {
                        a++;
                    } else if(din[i] + 1 == dout[i]) {
                        b++;
                    } else {
                        return false;
                    }
                }
            }
            return ((a == 0 && b == 0) || (a == 1 && b == 1));
        } else if(type == 4) {
            for(int i = 1; i <= n; i++) {
                if(din[i] != dout[i]) {
                    return false;
                }
            }
            return true;
        }
        cout << "Invalid Type" << endl;
        return false;
    }

    template <typename G>
    void clear(G g[N], int n) {
        for(int i = 0; i <= n; i++) {
            g[i].clear(); //unordered_set graph
            din[i] = 0;
            dout[i] = 0;
        }
        for(int i = 0; i < ei; i++) {
            used[i] = false;
            to[i] = 0;
        }
        cnte = 0;
        ei = 0;
    }

    void printE() {
        //cout << cnte << endl;
        for(int i = cnte - 1; i >= 0; i--) {
            cout << ans[i] << " ";
        }
    }

    void printNonDirectedV() {
        //cout << cnte << endl;
        cout << to[ans[cnte - 1] ^ 1] << " ";
        for(int i = cnte - 1; i >= 0; i--) {
            cout << to[ans[i]] << " ";
        }
        cout << endl;
    }
    
    void printDirectedV(vector<int>& path) {
        path.push_back(from[ans[cnte - 1]]);
        for(int i = cnte - 1; i >= 0; i--) {
            //cout << to[ans[i]] << " ";
            path.push_back(to[ans[i]]);
        }
    }

}

class Solution {
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& a) {
        unordered_map<int, int> mp;
        unordered_map<int, int> pm;
        int id = 0;
        for(int i = 0; i < a.size(); i++) {
            int u = a[i][0], v = a[i][1];
            if(mp.find(u) == mp.end()){
                 mp[u] = id;
                 pm[id] = u;
                 id++;
            }
            if(mp.find(v) == mp.end()) {
                mp[v] = id;
                pm[id] = v;
                id++;
            }
        }
        
        for(int i = 0; i < a.size(); i++) {
            int u = mp[a[i][0]], v = mp[a[i][1]];
            //u -> v 
            Euler :: add(Euler :: usg, u, v);
        }
        
        int start = 0;
        for(int i = 0; i < id; i++) {
            if(Euler :: din[i] + 1 == Euler:: dout[i]) {
                start = i; //start node
                break;
            }    
        }
        
        Euler :: dfsDirected(Euler :: usg, start);
        vector<vector<int>> ans;
        vector<int> path;
        Euler :: printDirectedV(path);
        for(int i = 0; i < path.size() - 1; i++) {
            ans.push_back({pm[path[i]], pm[path[i + 1]]});
        }
        Euler :: clear(Euler :: usg, id + 1);
        return ans;
    }
};
