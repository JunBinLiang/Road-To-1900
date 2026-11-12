const int N = 40000 * 17;
int tr[N][2];
int mxIndex[N];
bool done = false;
int id = 1;
void init() {
    if(done) {
        return;
    }
    id = 1;
    done = true;
    memset(tr, -1, sizeof tr);
}

void clean(int u) {
    if(tr[u][0] != -1) {
        int v = tr[u][0];
        tr[u][0] = -1;
        clean(v);
    }
    if(tr[u][1] != -1) {
        int v = tr[u][1];
        tr[u][1] = -1;
        clean(v);
    }
}

void add(int index, int x) {
    int u = 0;
    for(int i = 16; i >= 0; i--) {
        if(x & (1 << i)) {
            if(tr[u][1] == -1) {
                tr[u][1] = id++;
            }
            u = tr[u][1];
        } else {
            if(tr[u][0] == -1) {
                tr[u][0] = id++;
            }
            u = tr[u][0];
        }
        mxIndex[u] = max(mxIndex[u], index);
    }
}

int query(int x, int bound) {
    int u = 0;
    int ans = 0;
    for(int i = 16; i >= 0; i--) {
        int bit = 0;
        if(x & (1 << i)) bit = 1;
        if(bit == 1) { //to 0 first
            if(tr[u][0] != -1 && mxIndex[tr[u][0]] >= bound - 1 ) {
                u = tr[u][0];
                ans += (1 << i);
            } else {
                u = tr[u][1];
            }
        } else {
            if(tr[u][1] != -1 && mxIndex[tr[u][1]] >= bound - 1 ) {
                u = tr[u][1];
                ans += (1 << i);
            } else {
                u = tr[u][0];
            }
        }
    }
    return ans;
}

class Solution {
public:
    int maxXor(vector<int>& a, int k) {
        init();
        int n = a.size();

        //find the maximum it can extend
        vector<int> to(n);
        deque<pair<int, int>> mnq, mxq;
        int j = 0;
        for(int i = 0; i < n; i++) {
            while(mnq.size() > 0 && a[i] < mnq.back().first) mnq.pop_back();
            mnq.push_back({a[i], i});   
            while(mxq.size() > 0 && a[i] > mxq.back().first) mxq.pop_back();
            mxq.push_back({a[i], i});    

            //adjust
            while(mxq.front().first - mnq.front().first > k) {
                j++; //remove an element
                if(mxq.front().second < j) mxq.pop_front();
                if(mnq.front().second < j) mnq.pop_front();
            }
            to[i] = j;
        }

        int xo = 0;
        int mn = 1e9, mx = -1e9;
        int ans = 0;
        for(int i = 0; i < n; i++) {
            xo ^= a[i];
            mn = min(mn, a[i]);
            mx = max(mx, a[i]);
            if(mx - mn <= k) {
                ans = max(ans, xo);
            }

            add(i, xo);
            int best = query(xo, to[i]);
            ans = max(ans, best);         
        }

        clean(0);
        for(int i = 0; i <= id; i++) mxIndex[i] = -1;
        id = 1;

        return ans;
    }
};
