struct Node {
    long long first, second; int index1, index2;
    long long sum;
    void init(long f, long s, int i, int j) {
        first = f;
        second = s;
        index1 = i;
        index2 = j;
        sum = f + s;
    }
};

struct Compare {
    bool operator()(const Node& a, const Node& b) const {
        if(a.sum == b.sum) {
            return a.index1 < b.index1;
        }
        return a.sum < b.sum;
    }
};

const int N = 1e5 + 100;
int pre[N], nxt[N];
long long val[N];

class Solution {
public:
    int minimumPairRemoval(vector<int>& a) {
        int n = a.size();
        int cnt = 0;
        for(int i = 1; i < n; i++) {
            if(a[i] >= a[i - 1]) {
                cnt++;
            }
        }

        for(int i = 0; i < n; i++) {
            val[i] = a[i];
        }

        pre[0] = -1;
        nxt[n - 1] = -1;
        for(int i = 1; i < n; i++) {
            pre[i] = i - 1;
            nxt[i - 1] = i;
        }

        set<Node, Compare> s;
        for(int i = 0; i < n - 1; i++) {
            Node node;
            node.init(a[i], a[i + 1], i, i + 1);
            s.insert(node);
        }

        int ans = 0;
        while(cnt != s.size()) {
            ans++;
            auto it = s.begin();
            Node node = *it;
            s.erase(node);
            int index1 = node.index1, index2 = node.index2;
            int nextNode = nxt[index2];
            int preNode = pre[index1];
            val[index1] += val[index2];
            nxt[index1] = nextNode;

            if(node.second >= node.first) {
                cnt--;
            }
            
            if(preNode != -1) {
                if(val[index1] >= val[preNode]) {
                    cnt++;
                }
                if(node.first >= val[preNode]) {
                    cnt--;
                }

                Node pnode;
                pnode.init(val[preNode], node.first, preNode, index1);
                auto it1 = s.find(pnode);
                if(it1 != s.end()) {
                    s.erase(it1);
                }

                Node newPnode;
                newPnode.init(val[preNode], val[index1], preNode, index1);
                s.insert(newPnode);
            }

            if(nextNode != -1) {
                pre[nextNode] = index1;
                if(val[nextNode] >= node.second) {
                    cnt--;
                }
                if(val[nextNode] >= val[index1]) {
                    cnt++;
                }
                pre[nextNode] = index1;

                Node nnode;
                nnode.init(node.second, val[nextNode], index2, nextNode);
                auto it1 = s.find(nnode);
                if(it1 != s.end()) {
                    s.erase(it1);
                }
                
                Node newNextNode;
                newNextNode.init(val[index1], val[nextNode], index1, nextNode);
                s.insert(newNextNode);
            }
        }
        return ans;
    }


};
