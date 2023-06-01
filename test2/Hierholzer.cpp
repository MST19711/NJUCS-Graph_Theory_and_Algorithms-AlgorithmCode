#include<iostream>
#include<stack>
using namespace std;
int graph[105][105]={};
int deg[105]={};
stack<int> ans;
int n,m;
void dfs(int v){
    for(int i=n;i;i--){
        if(graph[v][i]){
            graph[v][i]--,graph[i][v]--;
            dfs(i);
        }
    }
    ans.push(v);
}
int main(){
    cin>>n>>m;
    int start=n,oddnum=0,a,b,i;
    for(i=0;i<m;i++){
        cin>>a>>b;
        graph[a][b]++,graph[b][a]++;
        deg[a]++,deg[b]++;
        start=max(start,max(a,b));
    }
    for(i=1;i<=n;i++)    if(deg[i]%2)   start=i,oddnum++;
    dfs(start);
    if(ans.size()!=m+1||(oddnum!=0&&oddnum!=2))   cout<<0<<endl;
    else{
        cout<<1<<endl;
        while(!ans.empty())    cout<<ans.top()<<" ",ans.pop();
    }
    return 0;
}