const int N = 1e5 + 10, INF = 1e9;
vector<int> blocks[2 * N];

struct Node {
    int l, r;
    pair<int, int> p; //maintain the 2 smallest
    void init() {
        p = {INF, INF};
    }
} tr[N * 4];

void build(int u) {
    tr[u].init();
    if(tr[u].l == tr[u].r) return;
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    tr[u * 2 + 1] = {l, mid};
    tr[u * 2 + 2] = {mid + 1, r};
    build(u * 2 + 1); build(u * 2 + 2);
}

pair<int, int> merge(pair<int, int> p1, pair<int, int> p2) {
    if(p1.first < p2.first) {
        return {p1.first, min(p1.second, p2.first)};
    } else if(p1.first > p2.first) {
        return {p2.first, min(p2.second, p1.first)};
    } else {
        return {p1.first, p2.first};
    }
}

void pushup(int u) {
    if(tr[u].l == tr[u].r) return;
    tr[u].p = merge(tr[u * 2 + 1].p, tr[u * 2 + 2].p);
}

void update(int u, int index, int val) {
    if(tr[u].l == tr[u].r) {
        auto& p = tr[u].p;
        if(val < p.first) {
            p.second = p.first;
            p.first = val;
        } else if(val < p.second) {
            p.second = val;
        }
        return;
    }
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    if(index <= mid) update(u * 2 + 1, index, val);
    else update(u * 2 + 2, index, val);
    pushup(u);
}

pair<int, int> query(int u, int s, int e) {
    if(tr[u].l == s && tr[u].r == e) {
        return tr[u].p;
    }
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    if(e <= mid) return query(u * 2 + 1, s, e);
    else if(s >= mid + 1) return query(u * 2 + 2, s, e);
    else {
        return merge(query(u * 2 + 1, s, mid), query(u * 2 + 2, mid + 1, e));                 
    }       
}

class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& a) {
        map<int, unordered_set<int>> mp;
        for(int i = 0; i < a.size(); i++) {
            if(a[i][0] > a[i][1]) {
                swap(a[i][0], a[i][1]);
            }
            blocks[i].clear();
        }
        sort(a.begin(), a.end());

        for(int i = 0; i < a.size(); i++) {
            mp[a[i][1]].insert(i);
        }

        long long s = 0;
        int j = 0;
        for(int i = 1; i <= n; i++) {
            while(j < a.size() && a[j][0] < i) {
                mp[a[j][1]].erase(j);
                if(mp[a[j][1]].size() == 0) mp.erase(a[j][1]);
                j++;
            }
            if(mp.size()) {
                auto it = mp.begin();
                int bound = it -> first;
                unordered_set<int>& indexs = it -> second;
                if(indexs.size() == 1) {
                    blocks[*(indexs.begin())].push_back(i);
                }
                s += (bound - i);
            } else {
                s += (n - i + 1);
            }
        }

        tr[0] = {0, n};
        build(0);
        for(int i = 0; i < a.size(); i++) {
            int l = a[i][0], r = a[i][1]; 
            update(0, l, r);
        }

        long long ans = 0;
        for(int i = 0; i < a.size(); i++) {
            auto& vec = blocks[i];
            if(vec.size() == 0) {
                ans = max(ans, s);
                continue;
            }
            long long news = s;
            //delete old contribution
            for(int start : vec) {
                news -= (a[i][1] - start);
            }
            //add new contribution
            for(int start : vec) {
                pair<int, int> p = query(0, start, n - 1);
                if(p.first == a[i][1]) {
                    news += (min(p.second, n + 1) - start);
                } else {
                    news += (min(p.first, n + 1) - start);
                }
            }
            ans = max(ans, news);
        }
        return ans;
    }

};
