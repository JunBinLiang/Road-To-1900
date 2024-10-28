struct Node {
    Node* next;
    Node* pre;
    int expire = 0;
    string tokenId;
    Node() {
        
    }
    Node(string s, int e) {
        tokenId = s;
        expire = e;
    }
};


class AuthenticationManager {
public:
    int t;
    Node* head;
    Node* tail;
    unordered_map<string, Node*> mp;
    AuthenticationManager(int timeToLive) {
        t = timeToLive;
        head = new Node();
        tail = new Node();
        head -> next = tail;
        tail -> pre = head;
    }
    
    void generate(string tokenId, int currentTime) {
        adjust(currentTime);
        append(tokenId, currentTime + t);
    }
    
    void renew(string tokenId, int currentTime) {
        adjust(currentTime);
        if(mp.find(tokenId) == mp.end()) {
            return;
        }    
        
        Node* node = mp[tokenId];
        remove(node);
        append(tokenId, currentTime + t);
        
    }
    
    int countUnexpiredTokens(int currentTime) {
        adjust(currentTime);
        return mp.size();
    }
    
    void adjust(int currentTime) {
        while(head -> next != tail && head -> next -> expire <= currentTime) {
            remove(head -> next);
        }
    }
    
    void remove(Node* node) {
        Node* pre = node -> pre;
        Node* nxt = node -> next;
        nxt -> pre = pre;
        pre -> next = nxt;
        mp.erase(node -> tokenId);
    }
    
    void append(string tokenId, int expire) { //
        Node* node = new Node(tokenId, expire);
        Node* pre = tail -> pre;
        pre -> next = node;
        node -> pre = pre;
        node -> next = tail;
        tail -> pre = node;
        mp[tokenId] = node;
    }
};

/**
 * Your AuthenticationManager object will be instantiated and called as such:
 * AuthenticationManager* obj = new AuthenticationManager(timeToLive);
 * obj->generate(tokenId,currentTime);
 * obj->renew(tokenId,currentTime);
 * int param_3 = obj->countUnexpiredTokens(currentTime);
 */
