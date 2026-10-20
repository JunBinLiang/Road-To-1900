struct C1 { //min
    bool operator()(const pair<string, int>& a,
                    const pair<string, int>& b) const {
        if(a.second == b.second) {
            return a.first < b.first; 
        }
        return a.second > b.second; //score
    }
};

struct C2 { //max
    bool operator()(const pair<string, int>& a,
                    const pair<string, int>& b) const {
        if(a.second == b.second) {
            return a.first > b.first;
        }
        return a.second < b.second; //score
    }
};

class SORTracker {
public:
    priority_queue<pair<string, int>, vector<pair<string, int>>, C1> lmin;
    priority_queue<pair<string, int>, vector<pair<string, int>>, C2> rmax;
    int t = 1;
    SORTracker() {
        
    }

    bool less(pair<string, int> p1, pair<string, int> p2) {
        if(p1.second == p2.second) {
            return p1.first > p2.first;
        }
        return p1.second < p2.second;
    }
    
    void add(string name, int score) {
        if(lmin.size() == 0 || rmax.size() == 0) {
            lmin.push({name, score});
        } else {
            if(!less({name, score}, lmin.top())) {
                lmin.push({name, score});
            } else {
                rmax.push({name, score});
            }
        }
        adjust();
    }

    void adjust() {
        while(lmin.size() > t) {
            pair<string, int> p = lmin.top();
            lmin.pop();
            rmax.push(p);
        }
        while(lmin.size() < t) {
            if(rmax.size() == 0) break;
            pair<string, int> p = rmax.top();
            rmax.pop();
            lmin.push(p);
        }
    }
    
    string get() {
        string ans = lmin.top().first;
        t++;
        adjust();
        return ans;
    }
};

/**
 * Your SORTracker object will be instantiated and called as such:
 * SORTracker* obj = new SORTracker();
 * obj->add(name,score);
 * string param_2 = obj->get();
 */
