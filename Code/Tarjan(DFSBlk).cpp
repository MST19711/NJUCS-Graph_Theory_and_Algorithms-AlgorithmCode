#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
struct node{
    node(){
        visited = isCutVertex = 0;
        d = low = children = parent = 0;
    }
    bool visited,isCutVertex;
    int d,low,children,parent;
    vector<int> to;
}graph[10005];
struct edge{
    edge(int A,int B){
        a=A,b=B;
    }
    int a,b;
};
stack<edge> S;
priority_queue<int> ans;
int Time = 0;
int DFSBlk(int u){
    Time ++;
    graph[u].d = Time;
    graph[u].low = graph[u].d;
    graph[u].visited = 1;
    for(int i=0;i<graph[u].to.size();i++){
        if(graph[graph[u].to[i]].visited == 0){
            S.push(edge(u,graph[u].to[i]));
            graph[graph[u].to[i]].parent = u;
            graph[u].children ++;
            DFSBlk(graph[u].to[i]);
            graph[u].low = min(graph[u].low,graph[graph[u].to[i]].low);
            if((graph[u].parent == 0 && graph[u].children >= 2) ||
              (graph[u].parent != 0 && graph[graph[u].to[i]].low >= graph[u].d)){
                int tans = 0;
                int A,B;
                do{
                    A = S.top().a,B = S.top().b;
                    tans++;
                    S.pop();
                }while(A != u && B != graph[u].to[i]);
                ans.push(tans);
            }
        }
        else if(graph[u].parent != graph[u].to[i]){
            if(graph[u].d > graph[graph[u].to[i]].d)    S.push(edge(u,graph[u].to[i]));
            graph[u].low = min(graph[u].low,graph[graph[u].to[i]].d);
        }
    }
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i = 1;i <= m;i++){
        int a,b;
        cin>>a>>b;
        graph[a].to.push_back(b),graph[b].to.push_back(a);
    }
    for(int i = 1;i <= n;i++){
        while(!S.empty())   S.pop();
        if(graph[i].to.empty()) ans.push(0);
        else if(graph[i].visited == 0)    DFSBlk(i);
        int tans = 0;
        if(!S.empty()){
            while(!S.empty())   S.pop(),tans++;
            ans.push(tans);
        }
    }
    cout<<ans.size()<<endl;
    stack<int> output;
    while(!ans.empty()){
        output.push(ans.top());
        ans.pop();
    }
    while(!output.empty()){
        cout<<output.top()<<" ";
        output.pop();
    }
    return 0;
}