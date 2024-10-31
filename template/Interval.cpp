namespace Interval {
    int sz = 0;
    map<int, int> mp;
    
    void init() {
        mp.clear();
        sz = 0;
    }
    
    void add(int l, int r) {
        while(true) {
            auto it = mp.upper_bound(l);
            if(it != mp.end()) {
                if(it -> first > r) break;
                else {
                    r = max(r, it -> second);
                    sz -= (it -> second - it -> first + 1);
                    mp.erase(it -> first);
                }
            } else {
                break;
            }
        }
        
        while(true) {
            auto it = mp.upper_bound(l);
            if(it == mp.begin()) break;
            else {
                it--;
                if(it -> second < l) break;
                else {
                    l = min(l, it -> first);
                    r = max(r, it -> second);
                    sz -= (it -> second - it -> first + 1);
                    mp.erase(it -> first);
                }
            }
        }
        
        
        mp[l] = r;
        sz += (r - l + 1);
    }
    
    int getSize() {
        return sz;
    }
};
