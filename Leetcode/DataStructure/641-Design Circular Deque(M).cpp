class MyCircularDeque {
public:
    vector<int> A;
    int i = 0, j = 1;
    int sz = 0;
    MyCircularDeque(int k) {
        A = vector<int>(k);
    }
    
    bool insertFront(int value) {
        if(isFull()) return false;
        A[i] = value;
        i--;
        if(i < 0) {
            i += A.size();
        }
        sz++;
        return true;
    }
    
    bool insertLast(int value) {
        if(isFull()) return false;
        A[j++] = value;
        j %= A.size();
        sz++;
        return true;
    }
    
    bool deleteFront() {
        if(isEmpty()) return false;
        i++;
        i %= A.size();
        sz--;
        return true;
    }
    
    bool deleteLast() {
        if(isEmpty()) return false;
        j--;
        if(j < 0) j += A.size();
        sz--;
        return true;
    }
    
    int getFront() {
        if(isEmpty()) {
            return -1;
        }
        int first = (i + 1) % A.size();
        return A[first];
    }
    
    int getRear() {
        if(isEmpty()) {
            return -1;
        }
        int last = (j - 1 + A.size()) % A.size();
        return A[last];
    }
    
    bool isEmpty() {
        return sz == 0;
    }
    
    bool isFull() {
        return sz == A.size();
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
