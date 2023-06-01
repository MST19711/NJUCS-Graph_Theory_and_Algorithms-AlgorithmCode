#include<iostream>
#include<string.h>
#include<queue>
#define INF 0x3FFFFFFF
using namespace std;
long long int G[205][205] = {}, s, t, n, m, a, b, cab, pre[205] = {};
bool visited[205] = {};
bool find_path(){
    queue<long long int> Q;
    Q.push(s);
    visited[s] = 1, pre[s] = s;
    while(!Q.empty()){
        for(int i = 1; i <= n; i++){
            if(G[Q.front()][i] != 0 && visited[i] == 0){
                pre[i] = Q.front();
                visited[i] = 1;
                Q.push(i);
                if(i == t){
                    return 1;
                }
            }
        }
        Q.pop();
    }
    return 0;
}
long long int F_F(){
    long long int ans = 0;
    while(find_path()){
        long long int ptr = t, r = INF;
        while(pre[ptr] != ptr)  r = min(r, G[pre[ptr]][ptr]), ptr = pre[ptr];
        ptr = t;
        while(pre[ptr] != ptr){
            G[pre[ptr]][ptr] -= r;
            G[ptr][pre[ptr]] += r;
            ptr = pre[ptr];
        }
        ans += r;
        memset(visited, 0, sizeof(visited));
        memset(pre, 0, sizeof(pre));
    }
    return ans;
}
int main(){
    cin>>n>>m>>s>>t;
    for(int i = 0; i < m ; i++){
        cin>>a>>b>>cab;
        G[a][b] += cab;
    }
    cout<<F_F()<<endl;
    return 0;
}