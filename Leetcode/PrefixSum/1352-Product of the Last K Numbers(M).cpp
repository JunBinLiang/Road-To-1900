class ProductOfNumbers {
public:
    vector<int> p;
    int product = 1;
    ProductOfNumbers() {
        
    }
    
    void add(int num) {
        if(num == 0) {
            product = 1;
            p.clear();
        } else {
            product *= num;
            p.push_back(product);
        }
    }
    
    int getProduct(int k) {
        if(k > p.size()) {
            return 0;
        } else {
            if(k == p.size()) {
                return p.back();
            }
            else {
                return p.back() / p[p.size() - k - 1];
            }
        }
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
