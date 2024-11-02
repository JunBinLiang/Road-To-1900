class RandomizedSet {
public:
    unordered_map<int, int> mp;
    vector<int> vec;
    RandomizedSet() {
        
    }
    
    bool insert(int val) {
        if(mp.find(val) != mp.end()) return false;
        mp[val] = vec.size();
        vec.push_back(val);
        return true;
    }
    
    bool remove(int val) {
        if(mp.find(val) == mp.end()) return false;
        int pos = mp[val]; mp.erase(val);
        if(vec.back() != val) {
            swap(vec[pos], vec[vec.size() - 1]);
            mp[vec[pos]] = pos;
            vec.pop_back();
        } else {
            vec.pop_back();
        }
        return true;
    }
    
    int getRandom() {
        return vec[rand() % vec.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
