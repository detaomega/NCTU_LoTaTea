struct HK{
    struct Edge{
        int to, pre;
    };
    vector<Edge> edge;
    vector<int> mx, my, dx, dy, head;
    int n,m;
    HK(int n,int m): n(n), m(m), mx(n+1,-1), my(m+1,-1), dx(n+1), dy(m+1), head(n+1,-1){}
    void add(int u,int v){
        edge.push_back({v,head[u]});
        head[u] = edge.size()-1;
    }
    bool bfs(){
        bool flag = false;
        queue<int> Q;
        fill(dy.begin(),dy.end(),0);
        fill(dx.begin(),dx.end(),0);
        for(int i=1;i<=n;i++){
            if(mx[i] == -1)
                Q.push(i), dx[i] = 1;
        }
        while(!Q.empty()){
            int x = Q.front();
            Q.pop();
            for(int i=head[x];i!=-1;i=edge[i].pre){
                int y = edge[i].to;
                if(!dy[y]){
                    dy[y] = dx[x]+1;
                    if(my[y] == -1) flag = true;
                    else {
                        dx[my[y]] = dy[y]+1;
                        Q.push(my[y]);
                    }
                }
            }
        }
        return flag;
    }
    bool dfs(int x){
        for(int i=head[x];i!=-1;i=edge[i].pre){
            int y = edge[i].to;
            if(dy[y] == dx[x]+1){
                dy[y] = 0;
                if(my[y] == -1 || dfs(my[y])){
                    mx[x] = y;
                    my[y] = x;
                    return true;
                }
            }
        }
        return false;
    }
    int cal(){
        int ans = 0;
        while(bfs()){
            for(int i=1;i<=n;i++)
                if(mx[i] == -1 && dfs(i)) ans++;
        }
        return ans;
    }
};
