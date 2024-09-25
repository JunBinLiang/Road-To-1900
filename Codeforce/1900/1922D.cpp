#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
#include<set>
#include<unordered_map>
#include<map>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>
#include <cmath>

using namespace std;

//2:14 - 2 : 38

const int N = 3e5 + 10;
int nxt[N], pre[N];
int a[N], d[N]; //attack, defense
long long receive[N];
int n;
void del(int node, set<int>& pending) {
    int nxtnode = nxt[node];
    int prenode = pre[node];
    nxt[prenode] = nxtnode;
    pre[nxtnode] = prenode;

    if(nxtnode <= n) {
        receive[nxtnode] += a[node];
        receive[nxtnode] -= a[prenode];
    }
        
    if(prenode > 0) {
        receive[prenode] += a[node];
        receive[prenode] -= a[nxtnode];
    }
    
    if(prenode > 0 && receive[prenode] < 0) {
        pending.insert(prenode);
    }

    if(nxtnode <= n && receive[nxtnode] < 0) {
        pending.insert(nxtnode);
    }
    
    if(prenode > 0 && receive[prenode] >= 0) {
        pending.erase(prenode);
    }
    
    if(nxtnode <= n && receive[nxtnode] >= 0) {
        pending.erase(nxtnode);
    }
}

void solve() {
    scanf("%d", &n);
    a[0] = d[0] = a[n + 1] = d[n + 1] = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n; i++) {
        scanf("%d", &d[i]);
    }
    for(int i = 0; i <= n + 1; i++) {
        pre[i] = nxt[i] = -1;
    }

    for(int i = 1; i <= n; i++) {
        pre[i] = i - 1;
        nxt[i] = i + 1;
        receive[i] =  d[i] - (a[i - 1] + a[i + 1]);
    }

    vector<int> pending;
    for(int i = 1; i <= n; i++) {
        if(receive[i] < 0) {
            pending.push_back(i);
        }
    }

    for(int i = 0; i < n; i++) {
        printf("%d ", (int)(pending.size()));
        set<int> nextpending;
        for(int node : pending) {
            //remove pending
            del(node, nextpending);
        }
        for(int node : pending) {
            nextpending.erase(node);
        }
        pending = vector<int>(nextpending.begin(), nextpending.end());
    }

    printf("\n");
}   

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
