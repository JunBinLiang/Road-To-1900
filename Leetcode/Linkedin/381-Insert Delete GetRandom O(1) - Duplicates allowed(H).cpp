class RandomizedCollection {
public:
    unordered_map<int, unordered_set<int>> mp;
    vector<int> vec;
    RandomizedCollection() {
        
    }
    
    bool insert(int val) {
        mp[val].insert(vec.size());
        vec.push_back(val);
        if(mp[val].size() == 1) return true;
        else return false;
    }
    
    bool remove(int val) {
        if(mp.find(val) == mp.end()) {
            return false;
        }
        
        int pos = *(mp[val].begin());
        mp[val].erase(pos);
        if(mp[val].size() == 0) mp.erase(val);
        if(pos == vec.size() - 1) vec.pop_back();
        else {
            int lastval = vec.back(); 
            mp[lastval].erase(vec.size() - 1);
            vec.pop_back();
            vec[pos] = lastval;
            mp[lastval].insert(pos);
        }
        return true;
    }
    
    int getRandom() {
        return vec[rand() % vec.size()];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
