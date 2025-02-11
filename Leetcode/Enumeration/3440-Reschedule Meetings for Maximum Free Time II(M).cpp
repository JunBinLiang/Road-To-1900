class Solution {
public:
    int maxFreeTime(int eventTime, vector<int>& startTime, vector<int>& endTime) {
        int n = startTime.size();
        vector<pair<int, int>> a;
        for(int i = 0; i < n; i++) {
            a.push_back({startTime[i], endTime[i]});
        }
        
        map<int, int> mp;
        int ans = 0;
        for(int i = 1; i < a.size(); i++) {
            ans = max(ans, a[i].first - a[i - 1].second);
            mp[a[i].first - a[i - 1].second]++;
        }
        mp[a[0].first]++;
        mp[eventTime - a.back().second]++;
        ans = max(ans, a[0].first);
        ans = max(ans, eventTime - a.back().second);
        
        /*cout << ans << endl;
        
        for(auto it = mp.begin(); it != mp.end(); it++) cout << it -> first << "  " << it -> second << endl;
        cout << endl;*/
        
        for(int i = 0; i < n; i++) {
            int l = 0, r = eventTime;
            if(i) l = a[i - 1].second;
            if(i + 1 < n) r = a[i + 1].first;
            int len = a[i].second - a[i].first;
            int d = r - l;
            ans = max(ans, d - len);
            
            if(i == 0) {
                del(mp, a[i].first);
                del(mp, a[i + 1].first - a[i].second);
            } else if(i == n - 1) {
                del(mp, eventTime - a[i].second);
                del(mp, a[i].first - a[i - 1].second);
            } else {
                del(mp, a[i + 1].first - a[i].second);
                del(mp, a[i].first - a[i - 1].second);
            }
            
            auto it = mp.end(); it--;
            if(it -> first >= len) {
                ans = max(ans, d);
            }
            
            if(i == 0) {
                add(mp, a[i].first);
                add(mp, a[i + 1].first - a[i].second);
            } else if(i == n - 1) {
                add(mp, eventTime - a[i].second);
                add(mp, a[i].first - a[i - 1].second);
            } else {
                add(mp, a[i + 1].first - a[i].second);
                add(mp, a[i].first - a[i - 1].second);
            }
        }
        
        return ans;
    }
    
    void del(map<int, int>& mp, int k) {
        mp[k]--;
        if(mp[k] == 0) mp.erase(k);
    }
    
    void add(map<int, int>& mp, int k) {
        mp[k]++;
    }
};
