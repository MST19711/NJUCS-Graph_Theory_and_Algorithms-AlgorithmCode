#include<iostream>
#include<vector>
using namespace std;
class Node{
    public:
        Node(){
            this->visited = 0;
            this->isCutVertex = 0;
            this->parent = 0;
            this->children = 0;
        }
        vector<int> to;
        bool visited,isCutVertex;
        int d,low,children,parent;
};
Node graph[10005];
int Time;
void DFSVC(int u){
    Time ++;
    graph[u].d = Time;
    graph[u].low = graph[u].d;
    graph[u].visited = 1;
    for(int i=0;i<graph[u].to.size();i++){
        if(graph[graph[u].to[i]].visited == 0){
            graph[graph[u].to[i]].parent = u;
            graph[u].children ++;
            DFSVC(graph[u].to[i]);
            graph[u].low = min(graph[u].low,graph[graph[u].to[i]].low);
            if(graph[u].parent == 0 && graph[u].children >= 2)  graph[u].isCutVertex = 1;
            else if(graph[u].parent != 0 && graph[graph[u].to[i]].low >= graph[u].d) graph[u].isCutVertex = 1;
        }
        else if(graph[u].parent != graph[u].to[i])  graph[u].low = min(graph[u].low,graph[graph[u].to[i]].d);
    }
}
int main(){
    int n,m;
    cin>>n>>m;
    Time = 0;
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        graph[a].to.push_back(b);
        graph[b].to.push_back(a);
    }
    int numOfCUtVertex = 0;
    for(int i=1;i<=n;i++){
        if(graph[i].visited == 0)    DFSVC(i);
        if(graph[i].isCutVertex == 1) numOfCUtVertex ++;
    }
    cout<<numOfCUtVertex<<endl;
    for(int i=1;i<=n;i++){
        if(graph[i].isCutVertex == 1)   cout<<i<<endl;
    }
    return 0;
}
