#include<bits/stdc++.h>
using namespace std;
bool dfs(vector<vector<int>>& rGraph, int s, int t,vector<int>& parent,int V)
{
    vector<bool> visited(V,false);
    stack<int> st;
    st.push(s);
    parent[s]=-1;
    visited[s]=true;
    while(!st.empty())
    {
    	int u=st.top(); st.pop();
    	for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                st.push(v);
                parent[v] = u;
                visited[v] = true;
            }

		}
	}


    return false;
}

int fordFulkerson(vector<vector<int>> graph, int s, int t,int V)
{
    int u, v;

    vector<vector<int>> rGraph(V,vector<int>(V,0));
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    vector<int> parent(V,0);

    int max_flow = 0;
    while (dfs(rGraph, s, t, parent,V)) {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

    max_flow += path_flow;
    }
     for(int i=0;i<V;i++)
    {
    	for(int j=0;j<V;j++)
    	{
    		cout<<rGraph[i][j]<<" ";
		}
		cout<<endl;
	}
    return (max_flow);
}

int main()
{
	fstream file;
    string line, filename;
    filename = "program3data.txt";
    file.open(filename.c_str());
    if(!file.is_open()){
    	cout<<"file doesn't exists";
    	return -1;
	}
    int n;
    int i=1;
    vector<pair<int,string>> names;
    getline (file, line);
    n=stoi(line);
   // cout<<n<<endl;
    while (file)
    {
    	getline (file, line);
        if(i<=n)
        {
        	names.push_back(make_pair(i,line));
		}
		else
		{
			break;
		}
        i++;
    }
    i=1;
    n=stoi(line);
    vector<vector<int>> graph(n+2,vector<int>(n+2,0));
    //cout<<n<<endl;
    vector<int> start(n,0),end(n,0);
    while (file)
    {
    	getline (file, line);
        if(i<=n)
        {
        	int t1[2],k=0;
        	string word;
        	stringstream ss(line);
        	while(ss>>word)
        	{
        		t1[k++]=stoi(word);
			}
			start[t1[0]]=1;
			end[t1[1]]=1;
        	graph[t1[0]][t1[1]]=1;
		}
        i++;
    }
	for(i=1;i<=n;i++)
	{
		if(start[i])
			graph[0][i]=1;
	}
	for(i=1;i<=n;i++){
		if(end[i])
			graph[i][n+1]=1;
	}
	 for(int i=0;i<n+2;i++)
    {
    	for(int j=0;j<n+2;j++)
    	{
    		cout<<graph[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	cout<<fordFulkerson(graph,0,n+1,n+2);
	return 0;
}
