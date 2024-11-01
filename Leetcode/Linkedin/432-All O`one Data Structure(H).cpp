struct Node {
    Node* next;
    Node* pre;
    unordered_set<string> keys;
    int freq;
    Node(int freq) {
        this -> freq = freq;
    }
};

class AllOne {
public:
    Node* head;
    Node* tail;
    unordered_map<string, int> freq;
    unordered_map<int, Node*> mp;
    AllOne() {
        head = new Node(0);
        tail = new Node(0);
        head -> next = tail;
        tail -> pre = head;
    }
    
    void inc(string key) {
        freq[key]++;
        if(freq[key] == 1) {
            if(head -> next != tail && head -> next -> freq == 1) {
                head -> next -> keys.insert(key);
            } else {
                Node* newnode = new Node(freq[key]);
                newnode -> keys.insert(key);
                add(head, newnode);
            } 
        } else {
            Node* node = mp[freq[key] - 1];
            node -> keys.erase(key);
            if(node -> next != tail && node -> next -> freq == freq[key]) {
                node -> next -> keys.insert(key);
            } else {
                Node* newnode = new Node(freq[key]);
                newnode -> keys.insert(key);
                add(node, newnode);
            }
            //remove the bucket once no key left
            if(node -> keys.size() == 0) remove(node);
        }
    }
    
    void dec(string key) {
        freq[key]--;
        Node* node = mp[freq[key] + 1];
        node -> keys.erase(key);
        if(freq[key] > 0) {
            if(node -> pre != head && node -> pre -> freq == freq[key]) {
                node -> pre -> keys.insert(key);
            } else {
                Node* newnode = new Node(freq[key]);
                newnode -> keys.insert(key);
                add(node -> pre, newnode);
            }
        }
        if(node -> keys.size() == 0) remove(node);
    }
    
    string getMaxKey() {
        if(tail -> pre == head) {
            return "";
        }
        return *(tail -> pre -> keys.begin());
    }
    
    string getMinKey() {
        if(head -> next == tail) {
            return "";
        }
        return *(head -> next -> keys.begin());
    }
    
    void remove(Node* node) {
        Node* pre = node -> pre;
        Node* next = node -> next;
        pre -> next = next;
        next -> pre = pre;
        mp.erase(node -> freq);
    }
    
    void add(Node* node, Node* newnode) {
        Node* next = node -> next;
        next -> pre = newnode;
        newnode -> next = next;
        node -> next = newnode;
        newnode -> pre = node;
        mp[newnode -> freq] = newnode;
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
