class MyCalendar {
public:
    map<int, int> f;
    MyCalendar() {
        
    }
    
    bool book(int start, int end) {
        end--;
        auto it = f.upper_bound(end);
        if(it == f.begin()) {
            f[start] = end;
            return true;
        }
        it--;
        if(it -> second >= start) return false;
        f[start] = end;
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
