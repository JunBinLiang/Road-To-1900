const int N = 2e5 + 100;
int nxt[N], pre[N], vals[N], keys[N];
class LRUCache {
public:
    int cap, sz;
    int id;
    map<int, int> mp;
    LRUCache(int capacity) {
        cap = capacity;
        sz = 0;
        pre[0] = -1;
        nxt[0] = 1;
        nxt[1] = -1;
        pre[1] = 0;
        id = 2;
    }
    
    void addNew(int key, int value) {
        sz++;
        int node = id++;
        mp[key] = node;
        keys[node] = key;
        vals[node] = value;
        pre[node] = pre[1];
        nxt[pre[1]] = node;
        pre[1] = node;
        nxt[node] = 1;
    }

    void addLast(int node) {
        sz++;
        int pnode = pre[1];
        nxt[pnode] = node;
        pre[node] = pnode;
        nxt[node] = 1;
        pre[1] = node;
        mp[keys[node]] = node;
    }

    

    void del(int node) {
        sz--;
        int pnode = pre[node];
        int nnode = nxt[node];
        nxt[pnode] = nnode;
        pre[nnode] = pnode;
        mp.erase(keys[node]);
    }
    
    int get(int key) {
        if(mp.find(key) == mp.end()) {
            return -1;
        }
        int node = mp[key];
        int ans = vals[node];
        del(node);
        addLast(node);
        return ans;
    }
    
    void put(int key, int value) {
        if(mp.find(key) != mp.end()) {
            int node = mp[key];
            vals[node] = value;
            del(node);
            addLast(node);
        } else {
            addNew(key, value);
        }

        if(sz > cap) {
            del(nxt[0]);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
