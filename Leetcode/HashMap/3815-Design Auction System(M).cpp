class AuctionSystem {
public:
    map<pair<int, int>, int> record;
    map<int, set<pair<int, int>>> rk;
    AuctionSystem() {
        
    }
    
    void addBid(int userId, int itemId, int bidAmount) {
        if(record.find({itemId, userId}) != record.end()) {
            int oldAmount = record[{itemId, userId}];
            record[{itemId, userId}] = bidAmount;
            rk[itemId].erase({oldAmount, userId});
            rk[itemId].insert({bidAmount, userId});
        } else {
            record[{itemId, userId}] = bidAmount;
            rk[itemId].insert({bidAmount, userId});
        }
    }
    
    void updateBid(int userId, int itemId, int newAmount) {
        int oldAmount = record[{itemId, userId}];
        record[{itemId, userId}] = newAmount;
        rk[itemId].erase({oldAmount, userId});
        rk[itemId].insert({newAmount, userId});
    }
    
    void removeBid(int userId, int itemId) {
        if(record.find({itemId, userId}) != record.end()) {
            int oldAmount = record[{itemId, userId}];
            record.erase({itemId, userId});
            rk[itemId].erase({oldAmount, userId});
        }
    }
    
    int getHighestBidder(int itemId) {
        auto& s = rk[itemId];
        if(s.size() == 0) {
            return -1;
        }
        auto it = s.end();
        it--;
        return it -> second;
    }
};

/**
 * Your AuctionSystem object will be instantiated and called as such:
 * AuctionSystem* obj = new AuctionSystem();
 * obj->addBid(userId,itemId,bidAmount);
 * obj->updateBid(userId,itemId,newAmount);
 * obj->removeBid(userId,itemId);
 * int param_4 = obj->getHighestBidder(itemId);
 */
