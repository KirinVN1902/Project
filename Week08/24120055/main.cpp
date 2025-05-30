#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <cstring>
#include <algorithm>
#define inf 10000000000
using namespace std;
bool visited[1001];
int color[1001];
void readFile(ifstream &f1, string fileName)
{
    f1.open(fileName);
    if (!f1.is_open())
    {
        cout << "Error in open file!";
        return;
    }
}
vector<vector<int>> convertMatrixToList(const string &filename)
{
    ifstream f1;
    readFile(f1, filename);
    int cnt;
    f1 >> cnt;
    vector<vector<int>> output(cnt);
    vector<vector<int>> input(cnt);
    for (int i = 0; i < cnt; i++){
        for (int j = 0; j < cnt; j++){
            int x; f1 >> x;
            input[i].push_back(x);
        }
    }
    for (int i = 0; i < cnt; i++){
        for (int j = 0; j < cnt; j++){
            if(input[i][j] == 1){
                output[i].push_back(j);
            }
        }
        output[i].insert(output[i].begin(), output[i].size());
    }
    return output;
}
vector<vector<int>> convertListToMatrix(const string &filename)
{
    ifstream f1;
    readFile(f1, filename);
    int cnt;
    f1 >> cnt;
    vector<vector<int>> input(cnt);
    for (int i = 0; i < cnt; i++)
    {
        int nums;
        f1 >> nums;
        for (int j = 0; j < nums; j++){
            int index;
            f1 >> index;
            input[i].push_back(index);
        }
    }
    vector<vector<int>> output(cnt, vector<int>(cnt, 0));
    for (int i = 0; i < cnt; i++){
        for (int j = 0; j < input[i].size(); j++) {
            output[i][input[i][j]] = 1;
        }
    }
    return output;
}
bool isDirected(const vector<vector<int>> &adjMatrix){
    for (int i = 0; i < adjMatrix.size(); i++){
        for (int j = 0; j < adjMatrix.size(); j++){
            if(adjMatrix[i][j] != adjMatrix[j][i]){
                return true;
            }
        }
    }
    return false;
}
int countVertices(const vector<vector<int>>& adjMatrix){
    return adjMatrix.size();
}
int countEdges(const vector<vector<int>>& adjMatrix){
    int res = 0;
    int cnt = adjMatrix.size();
    for (int i = 0; i < cnt; i++){
        for (int j = 0; j < cnt; j++){
            if(adjMatrix[i][j] == 1){
                res++;
            }
        }
    }
    bool direct = isDirected(adjMatrix);
    if(direct == false){
        return res / 2;
    }
    return res;
}
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix){
    vector<int> res;
    int cnt = adjMatrix.size();
    for (int i = 0; i < cnt; i++){
        bool check = false;
        for (int j = 0; j < cnt; j++){
            if(adjMatrix[i][j] != 0 || adjMatrix[j][i] != 0){
                check = true;
            }
        }
        if (check == false){
            res.push_back(i);
        }
    }
    return res;
}
// Undirected Graph
bool isCompleteGraph(const vector<vector<int>>& adjMatrix){
    int cnt = adjMatrix.size();
    for (int i = 0; i < cnt; i++){
        for (int j = 0; j < cnt; j++){
            if(i == j){
                continue;
            }
            else{
                if(adjMatrix[i][j] == 0){
                    return false;
                }
            }
        }
    }
    return true;
}
bool isBipartite(const vector<vector<int>>& adjMatrix){
    // white = 0; black = 1
    queue<int> q;
    int cnt = adjMatrix.size();
    memset(color, -1, sizeof(color));
    int start = 0;
    q.push(start);
    color[start] = 0;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for (int i = 0; i < cnt; i++){
            if(adjMatrix[u][i] == 1){
                if(color[i] == -1){
                    color[i] = 1 - color[u];
                    q.push(i);
                }
                else if(color[i] == color[u]){
                    return false;
                }
            }
        }        
    }
    return true;
}
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix){
    if(!isBipartite(adjMatrix)){
        return false;
    }
    vector<int> v1, v2;
    for (int i = 0; i < adjMatrix.size(); i++){
        if(color[i] == 0){ // nếu đỉnh màu trắng -> push vào vector 1
            v1.push_back(i);
        }
        else if(color[i] == 1){ // nếu đỉnh màu đen -> push vào vector 0
            v2.push_back(i);
        }
    }
    for (int i = 0; i < v1.size(); i++){
        for (int j = 0; j < v2.size(); j++){
            if(adjMatrix[v1[i]][v2[j]] == 0){
                return false;
            }
        }
    }
    return true;
}
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix){
    int cnt = adjMatrix.size();
    vector<vector<int>> res = adjMatrix;
    for (int i = 0; i < cnt; i++){
        for (int j = 0; j < cnt; j++){
            if(res[i][j] == 1){
                res[j][i] = 1;
            }
        }
    }
    return res;
}
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix){
    vector<vector<int>> res = adjMatrix;
    int cnt = adjMatrix.size();
    for (int i = 0; i < cnt; i++){
        for(int j = 0; j < cnt; j++){
            if(i == j){
                continue;
            }
            else{
                res[i][j] = 1 - res[i][j];
            }
        }
    }
    return res;
}
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix){
    vector<int> EC;
    stack<int> st;
    vector<vector<int>> adj = adjMatrix;
    int cnt = adjMatrix.size();
    vector<int> degree(cnt, 0), inDegree(cnt, 0), outDegree(cnt, 0);
    for (int i = 0; i < cnt; i++){
        for (int j = 0; j < cnt; j++){
            if(adj[i][j] == 1){
                degree[i]++;
                outDegree[i]++;
                inDegree[j]++;
            }
        }
    }
    int start = -1;
    // tìm đỉnh bắt đầu
    for (int i = 0; i < cnt && start == -1; i++){
        for (int j = 0; j < cnt; j++){
            if(adj[i][j] == 1){
                start = i;
                break;
            }
        }
    }
    bool directed = isDirected(adj);
    if(!directed){
        for (int i = 0; i < cnt; i++){
            if(degree[i] % 2 == 1){
                return {};  // không thể là chu trình Euler nếu bậc đỉnh lẻ
            }
        }   
        st.push(start);
        while(!st.empty()){
            int u = st.top();
            bool check = false;
            for (int i = 0; i < cnt; i++){
                if(adj[u][i] == 1){
                    st.push(i);
                    adj[u][i] = 0;
                    adj[i][u] = 0;
                    check = true;
                    break;
                }
            }
            if(check == false){// nếu không còn cạnh kề
                EC.push_back(u);
                st.pop();
            } 
        }
    }
    else if(directed){
        for (int i = 0; i < cnt; i++){
            if(inDegree[i] != outDegree[i]){
                return {}; // không thể là chu trình Euler nếu bán bậc vào khác bán bậc ra
            }
        }
        st.push(start);
        while(!st.empty()){
            int u = st.top();
            bool check = false;
            for (int i = 0; i < cnt; i++){
                if(adj[u][i] == 1){
                    adj[u][i] = 0;
                    st.push(i);
                    check = true;
                    break;
                }
            }
            if(check == false){
                EC.push_back(u);
                st.pop();
            }
        }
    }
    reverse(EC.begin(), EC.end());
    return EC;
}
void dfs(const vector<vector<int>>& adjMatrix, vector<vector<int>> &dfs1, int u){
    visited[u] = true;
    for (int i = 0; i < adjMatrix.size(); i++){
        if(adjMatrix[u][i] == 1 && !visited[i]){
            dfs1[u][i] = 1;
            dfs1[i][u] = 1;
            dfs(adjMatrix, dfs1, i);
        }
    }
}
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start){
    int cnt = adjMatrix.size();
    vector<vector<int>> res(cnt, vector<int>(cnt, 0));
    memset(visited, false, sizeof(visited));
    dfs(adjMatrix, res, start);
    return res;
}
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start){
    int cnt = adjMatrix.size();
    vector<vector<int>> res(cnt, vector<int>(cnt, 0));
    memset(visited, false, sizeof(visited));
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for (int i = 0; i < cnt; i++){
            if(adjMatrix[u][i] == 1 && !visited[i]){
                visited[i] = true;
                res[u][i] = 1;
                res[i][u] = 1;
                q.push(i);
            }
        }
    }
    return res;
}
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix){
    queue<int> q;
    int cnt = adjMatrix.size();
    memset(visited, false, sizeof(visited));
    q.push(u);
    visited[u] = true;
    while(!q.empty()){
        int x = q.front(); q.pop();
        for(int i = 0; i < cnt; i++){
            if(adjMatrix[x][i] == 1 && !visited[i]){
                q.push(i);
                visited[i] = true;
            }
        }
    }
    return visited[v];
}
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix){
    int cnt = adjMatrix.size();
    vector<long long> d(cnt, inf);
    vector<int> parent(cnt, -1);
    d[start] = 0;
    memset(visited, false, sizeof(visited));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    // tạo 1 queue với phần tử đứng trước là nhỏ nhất
    // pair.first: khoảng cách, pair.second: đỉnh
    q.push({0, start}); // đẩy đỉnh start với khoảng cách 0
    while(!q.empty()){
        pair<int, int> x = q.top(); q.pop();
        int dis = x.first;
        int u = x.second;
        if(visited[u]){
            continue;
        }
        visited[u] = true;
        for (int i = 0; i < cnt; i++){
            if(adjMatrix[u][i] != inf && !visited[i]){
                if(d[u] + adjMatrix[u][i] < d[i]){
                    d[i] = d[u] + adjMatrix[u][i];
                    parent[i] = u;
                    q.push({d[i], i});
                }
            }
        }
    }
    vector<int> path;
    if(d[end] == inf){
        return {};
    }
    else{
        while(true){
            path.push_back(end);
            if(end == start){
                break;
            }
            end = parent[end];
        }
    }
    reverse(path.begin(), path.end());
    return path;
}
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix){
    int cnt = adjMatrix.size();
    vector<long long> d(cnt, inf);
    vector<int> parent(cnt, -1);
    d[start] = 0;
    bool check = true;
    for (int i = 0; i < cnt - 1; i++){
        check = false;
        for (int j = 0; j < cnt; j++){
            for (int k = 0; k < cnt; k++){
                if(adjMatrix[j][k] != inf && d[j] != inf){
                    if(d[j] + adjMatrix[j][k] < d[k]){
                        d[k] = d[j] + adjMatrix[j][k];
                        parent[k] = j;
                        check = true;
                    }
                }
            }
        }
        if(!check){
            break;
        }
    }
    vector<int> path;
    if(d[end] == inf){
        return {};
    }
    while(true){
        path.push_back(end);
        if(end == start){
            break;
        }
        end = parent[end];
    }
    return path;
}
int main(){
    ifstream f1;
    string s1 = "input.txt";
    vector<vector<int>> res = convertListToMatrix(s1);
    for (int i = 0; i < res.size(); i++){
        for (int x : res[i]){
            cout << x << " ";
        }
        cout << endl;
    }
    vector<int> res1 = findEulerCycle(res);
    if(res1.empty()){
        cout << "Empty";
    }
    for (int x : res1){
        cout << x << " ";
    }
    cout << endl;
    cout << isConnected(0, 2, res);
    f1.close();
    return 0;
}
