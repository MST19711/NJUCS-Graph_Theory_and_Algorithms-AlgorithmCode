#include<iostream>
#include<string.h>
using namespace std;
static int N, M, E;
static int p[1005] = {};
static bool G[1005][1005] = {};
static bool visited[1005] = {};
bool is_matched(int n){
    for(int i = 1; i <= M; i++){
        if(G[n][i] == 1 && visited[i] == 0){
            visited[i] = 1;
            if(p[i] == 0 || is_matched(p[i])){
                p[i] = n;
                return 1;
            }
        }
    }
    return 0;
}
int Hungarian(){
    int ans = 0;
    for(int i = 1; i <= N; i++){
        memset(visited, 0 ,sizeof(visited));
        ans += is_matched(i);
    }
    return ans;
}
int main(){
    cin>>N>>M>>E;
    for(int i = 0; i < E; i++){
        int a,b;
        cin>>a>>b;
        G[a][b] = 1;
    }
    cout<<Hungarian()<<endl;
    return 0;
}