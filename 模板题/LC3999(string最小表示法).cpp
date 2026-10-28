class Solution {
public:
    int minimumGroups(vector<string>& a) {
        set<pair<string, string>> se;

        for (string& s : a) {
            string e, o;

            for (int i = 0; i < s.size(); i++) {
                if (i % 2 == 0) e += s[i];
                else o += s[i];
            }

            int t1 = minimalRepresentation(e);
            int t2 = minimalRepresentation(o);

            // 将循环最小表示转换为规范化字符串
            e = e.substr(t1) + e.substr(0, t1);
            o = o.substr(t2) + o.substr(0, t2);

            se.insert({e, o});
        }

        return se.size();
    }

    int minimalRepresentation(string s) {
        int n = s.size();
        if (n == 0) return 0;

        int i = 0, j = 1, k = 0;

        while (i < n && j < n && k < n) {
            int t = s[(i + k) % n] - s[(j + k) % n];

            if (t == 0) {
                k++;
            } else {
                if (t > 0) i += k + 1;
                else j += k + 1;

                if (i == j) j++;
                k = 0;
            }
        }

        return min(i, j);
    }
};
