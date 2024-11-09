class Solution {
public:
    string smallestNumber(string s, long long val) {
        vector<int> vec = get(val);
        if(vec.size() == 0) return "-1";
        vector<int> prefix(4);
        
        for(int i = 0; i < s.size(); i++) {
            vector<int> temp = get(s[i] - '0');
            add(prefix, temp);
        }
        
        int zeroIndex = -1;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '0') {
                zeroIndex = i;
                break;
            }
        }
        
        
        if(ok(prefix, vec) && zeroIndex == -1) {
            return s;
        }
        
        //can I make it the same length
        int postlen = 0;
        for(int i = s.size() - 1; i >= 0; i--) {
            int d = s[i] - '0';
            vector<int> temp = get(d);
            remove(prefix, temp);
            if(zeroIndex != -1 && i > zeroIndex) {
                postlen++;
                continue;
            }
            

            for(int j = d + 1; j <= 9; j++) {
               // cout << i << " " << j << endl;
                temp = get(j);
                add(prefix, temp);
                remove(vec, prefix); //how much needed
                
                vector<int> t = construct(vec);
                int cnt = 0;
                for(int k = 2; k < 10; k++) cnt += t[k];
                
                if(cnt <= postlen) {
                    vector<int> temp = add1(prefix, t);
                    if(ok(temp, vec)) {
                        string ans = s.substr(0, i);
                        ans += ((char)(j + '0'));
                        while(cnt != postlen) { //fill empty with 1
                            cnt++;
                            ans += '1';
                        }
                        for(int k = 1; k < 10; k++) {
                            while(t[k]--) ans += ((char)(k + '0'));
                        }
                        return ans;
                    }
                }
                
                
                add(vec, prefix);
                remove(prefix, temp);
            }
            postlen++;
        }
        
        //can not make with the same length
        string ans = "";
        vector<int> t = construct(vec);
        for(int i = 1; i < 10; i++) {
            while(t[i]--) {
                ans += ((char)(i + '0'));
            }
        }
        string one = "";
        while(one.size() + ans.size() <= s.size()) one += "1";
    
        return one + ans;
    }
    
    vector<int> construct(vector<int>& vec) {
        vector<int> ans(10);
        if(vec[2] > 0) ans[5] = vec[2]; //5
        if(vec[3] > 0) ans[7] = vec[3]; //5
        int two = vec[0], three = vec[1];
        two = max(two, 0);
        three = max(three, 0);
        while(two >= 3) {
            two -= 3;
            ans[8]++;
        }
        
        while(three >= 2) {
            three -= 2;
            ans[9]++;
        }
        
        if(two == 1 && three == 0) {
            ans[2]++;
        } else if(two == 2 && three == 1) {
            ans[2]++;
            ans[6]++;
        } else if(two == 1 && three == 1) {
            ans[6]++;
        } else if(two == 2 && three == 0) {
            ans[4]++;
        } else if(two == 0 && three == 1) {
            ans[3]++;
        }
        return ans;
    }
    
    bool ok(vector<int>& vec1, vector<int>& vec2) {
        for(int i = 0; i < 4; i++) {
            if(vec1[i] < vec2[i]) {
                return false;
            }
        }
        return true;
    }
    
    vector<int> get(long long n) {
        vector<int> vec(4);
        if(n == 0) return vec;
        while(n % 2 == 0) n /= 2, vec[0]++;
        while(n % 3 == 0) n /= 3, vec[1]++;
        while(n % 5 == 0) n /= 5, vec[2]++;
        while(n % 7 == 0) n /= 7, vec[3]++;
        if(n != 1) return {};
        return vec;
    }
    
    void add(vector<int>& vec1, vector<int>& vec2) {
        for(int i = 0; i < 4; i++) {
            vec1[i] += vec2[i];
        }
    }
    
    vector<int> add1(vector<int>& vec1, vector<int>& vec10) {
        vector<int> temp(vec1.begin(), vec1.end());
        temp[0] += (vec10[2] + vec10[6]);
        temp[0] += (2 * vec10[4]);
        temp[0] += (3 * vec10[8]);
        
        temp[1] += vec10[3];
        temp[1] += vec10[6];
        temp[1] += (2 * vec10[9]);
        
        temp[2] += (vec10[5]);
        temp[3] += (vec10[7]);
        return temp;
    }
    
    void remove(vector<int>& vec1, vector<int>& vec2) {
        for(int i = 0; i < 4; i++) {
            vec1[i] -= vec2[i];
        }
    }
};
