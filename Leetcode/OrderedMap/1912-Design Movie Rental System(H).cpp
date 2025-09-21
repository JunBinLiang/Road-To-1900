class MovieRentingSystem {
public:
    map<int, set<pair<int, int>>> mp1; //movie : [(price, shop)]
    map<pair<int, int>, int> mp2; //(shop, movie) : price
    map<int, set<pair<int, int>>> rmp; //price : (shop movie)
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for(vector<int>& entry : entries) {
            int shop = entry[0], movie = entry[1], price = entry[2];
            mp1[movie].insert({price, shop});
            mp2[{shop, movie}] = price;
        }
    }
    
    vector<int> search(int movie) {
        vector<int> ans;
        auto it = mp1[movie].begin();
        while(ans.size() < 5 && it != mp1[movie].end()) {
            ans.push_back(it -> second);
            it++;
        }
        return ans;
    }
    
    void rent(int shop, int movie) {
        int price = mp2[{shop, movie}];
        mp1[movie].erase({price, shop});
        rmp[price].insert({shop, movie});
    }
    
    void drop(int shop, int movie) {
        int price = mp2[{shop, movie}];
        mp1[movie].insert({price, shop});
        rmp[price].erase({shop, movie});
        if(rmp[price].size() == 0) {
            rmp.erase(price);
        }
    }
    
    vector<vector<int>> report() {
        vector<vector<int>> ans;
        auto it = rmp.begin();
        while(ans.size() < 5 && it != rmp.end()) {
            auto sit = (it -> second).begin();
            while(ans.size() < 5 && sit != (it -> second).end()) {
                ans.push_back({sit -> first, sit -> second});
                sit++;
            }
            it++;
        }
        return ans;
    }
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */
