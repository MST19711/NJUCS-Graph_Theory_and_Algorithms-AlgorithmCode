#include<iostream>
#include<vector>
using namespace std;
vector<int> nodes[10005];
bool visited[10005] = {};
void dfs(int node){
	visited[node] = 1;
	for(int i=0;i<nodes[node].size();i++){
		if(visited[nodes[node][i]] == 0){
			dfs(nodes[node][i]);
		}
	}
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int a,b;
		cin>>a>>b;
		nodes[a].push_back(b);
		nodes[b].push_back(a);
	}
	long long int ans = 0;
	for(int i=1;i<=n;i++){
		if(visited[i] == 0){
			ans ++;
			dfs(i);
		}
	}
	cout<<ans<<endl;
	return 0;
}
