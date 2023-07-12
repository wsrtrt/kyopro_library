#include <bits/stdc++.h>
using namespace std;
#define ll long long
/* UnionFind：素集合系管理の構造体(union by rank)
    isSame(x, y): x と y が同じ集合にいるか。 計算量はならし O(α(n))
    unite(x, y): x と y を同じ集合にする。計算量はならし O(α(n))
*/
/*
struct UnionFind {  // The range of node number is u 0 v n-1
    vector<int> rank, parents;
    UnionFind() {}
    UnionFind(int n) {  // make n trees.
        rank.resize(n, 0);
        parents.resize(n, 0);
        for (int i = 0; i < n; i++) {
            makeTree(i);
        }
    }
    void makeTree(int x) {
        parents[x] = x;  // the parent of x is x
        rank[x] = 0;
    }
    bool isSame(int x, int y) { return findRoot(x) == findRoot(y); }
    void unite(int x, int y) {
        x = findRoot(x);
        y = findRoot(y);
        if (rank[x] > rank[y]) {
            parents[y] = x;
        } else {
            parents[x] = y;
            if (rank[x] == rank[y]) {
                rank[y]++;
            }
        }
    }
    int findRoot(int x) {
        if (x != parents[x]) parents[x] = findRoot(parents[x]);
        return parents[x];
    }
};
*/

/*
struct Edge {
    long long u;
    long long v;
    long long cost;
};
bool comp_e(const Edge &e1, const Edge &e2) { return e1.cost < e2.cost; } // 辺を直接比較するための関数
*/
/* Kruskal :クラスカル法で minimum spanning tree を求める構造体
    入力: 辺のvector, 頂点数V
    最小全域木の重みの総和: sum
    計算量: O(|E|log|V|)
*/
/*
struct Kruskal {
    UnionFind uft;
    long long sum;  // 最小全域木の重みの総和
    vector<Edge> edges;
    int V;
    Kruskal(const vector<Edge> &edges_, int V_) : edges(edges_), V(V_) { init(); }
    void init() {
        sort(edges.begin(), edges.end(), comp_e); // 辺の重みでソート
        uft = UnionFind(V);
        sum = 0;
        for (auto e : edges) {
            if (!uft.isSame(e.u, e.v)) { // 閉路にならなければ加える
                uft.unite(e.u, e.v);
                sum += e.cost;
            }
        }
    }
};
*/

//Ford-Fulkerson
/*
struct Edge{
    int to,cap,rev;
};
class MaximumFlow{
public:
    int size_=0;
    bool used[409];
    vector<Edge> g[409];
    //頂点数Nの残余グラフを準備
    MaximumFlow(int N){
        size_=N;
        for(int i=0;i<=size_;i++)g[i].clear();
    }
    //頂点aからbにむっかう,上限ｃリットル/秒の辺を追加
    void add_edge(int a,int b,int c){
        int Current_Ga=g[a].size();//現時点でのg[a]の要素数
        int Current_Gb=g[b].size();//現時点でのg[b]の要素数
        g[a].push_back(Edge{b,c,Current_Gb});
        g[b].push_back(Edge{a,0,Current_Ga});
    }

    //深さ優先探索(Fはスタートからposに到達する過程での"残余グラフの辺の容量"の最小値)
    //返り値は流したフローの量(流せない場合は0)
    int dfs(int pos,int goal,int F){
        //ゴールに到着:フローを流せる！
        if(pos==goal)return F;
        used[pos]=true;

        //探索する
        for(int i=0;i<g[pos].size();i++){
            //容量0の辺は使えない すでに訪問した頂点に行っても意味がない
            if(g[pos][i].cap!=0&&used[g[pos][i].to]==false){
                //目的地までのパスを探す
                int flow=dfs(g[pos][i].to,goal,min(F,g[pos][i].cap));

                //フローを流せる場合、残余グラフの容量をflowだけ増加させる
                if(flow>=1){
                    g[pos][i].cap-=flow;
                    g[g[pos][i].to][g[pos][i].rev].cap+=flow;
                    return flow;
                }
            }
        }

        //すべての辺を探索しても見つからなかった
        return 0;
    }

    //頂点sから頂点tまでの最大フローの総流量を返す
    int max_flow(int s,int t){
        int Total_Flow=0;
        while(true){
            for(int i=0;i<=size_;i++)used[i]=false;
            int F=dfs(s,t,1000000000);

            //フローを流せなくなったら操作終了
            if(F==0)break;
            Total_Flow+=F;
        }
        return Total_Flow;
    }

};
*/
/* //最大フロー最小カット問題
int main() { 
    //入力
    int n,m;cin>>n>>m;
    int a[409],b[409],c[409];
    MaximumFlow mf(n);
    rep(i,0,m){
        cin>>a[i]>>b[i]>>c[i];
        mf.add_edge(a[i],b[i],c[i]);
    }

    cout<<mf.max_flow(1,n)<<endl;
    return 0;
}
*/
/* //二部マッチング問題
int main() {
    //入力
    int n;cin>>n;
    char c[159][159];
    rep(i,0,n){
        rep(j,0,n)cin>>c[i][j];
    }

    //グラフを構成する
    MaximumFlow mf(2*n+2);
    rep(i,0,n){
        rep(j,0,n){
            if(c[i][j]=='#')mf.add_edge(i,n+j,1);
        }
    }
    rep(i,0,n){
        mf.add_edge(2*n+1,i,1);//[s→青色]の辺
        mf.add_edge(n+i,2*n+2,1);//[赤色→t]の辺
    }
    cout<<mf.max_flow(2*n+1,2*n+2)<<endl;

    return 0;

}
*/

//Dijkstra
/*
vector<long long> dijkstra(WeightedGraph& G,int N,int POS){
    vector<ll> cur(N,INFL);
    vector<int> seen(N,false);
    min_priority_queue<pair<ll,int>> Q;
    Q.push({0,POS});
    while(!Q.empty()){
        pair<ll,int> tmp=Q.top();Q.pop();
        int in=tmp.ss;
        ll pre=tmp.ff;
        if(seen[in])continue;
        seen[in]=true;
        cur[in]=pre;
        fore(i,G[in]){
            if(!seen[i.ff]){
                Q.push({pre+i.ss,i.ff});
            }
        }
    }
    return cur;
}
*/

//bfs
/*
vector<int> dfs(UnWeightedGraph& G,int N,int POS){
    queue<pii> q;
    vector<int> seen(N,false);
    vector<int> cur(N,-1); 
    q.push({POS,0});
    cur[POS]=0;
    while(!q.empty()){
        pii tmp=q.front();q.pop();
        int in=tmp.ff;
        int pre=tmp.ss;
        if(seen[in])continue;
        seen[in]=true;
        cur[in]=pre;
        fore(i,G[in]){
            if(seen[i]==false){
                q.push({i,pre+1});
            }
        }
    }
    return cur;
}
*/

//grid_bfs
/*
//斜め移動可能な場合able=true
vector<vector<int>> grid_bfs(vector<vector<char>>& g,pii pos,int able){
    int h=g.size();
    int w=g[0].size();
    queue<pair<pii,int>> q;
    vvi seen(h,vi(w,false));
    vvi cur(h,vi(w,INF));
    q.push({pos,0});
    while(!q.empty()){
        pair<pii,int> tmp=q.front();q.pop();
        pii in=tmp.ff;
        int pre=tmp.ss;
        if(seen[in.ff][in.ss])continue;
        seen[in.ff][in.ss]=true;
        cur[in.ff][in.ss]=pre;
        rep(i,0,4+able*4){
            int x=in.ff+dx[i];
            int y=in.ss+dy[i];
            if(0<=x&&x<h&&0<=y&&y<w&&!seen[x][y]&&g[x][y]!='#'){
                q.push({{x,y},pre+1});
            }
        }
    }
    return cur;
}*/

//dfs
/*
int dfs(vector<vector<pii>>& g,int v,int pre,int goal){
    if(v==goal)return 1;
    fore(i,g[v]){
        if(i.ff!=pre){
            if(dfs(g,i.ff,v,goal)){
                cnt[i.ss]++;
                return 1;
            }
        }
    }
    return 0;
}
*/

//巡回セールスマン
/*
const int MAXN=16;
int n;
int d[MAXN][MAXN];
int dp[1<<MAXN][MAXN];

int rec(int S, int v) {
    if(dp[S][v] >= 0) return dp[S][v];
    if(S==(1<<n)-1 && v==0) return dp[S][v]=0;
    int tmp=INF;
    rep(u,0,n) if(!(S>>u & 1)) tmp=min(tmp, rec(S|1<<u,u)+d[v][u]);
    return dp[S][v]=tmp;
}

int main() {
    fastio
    int m;
    cin>>n>>m;
    rep(i,0,n) rep(j,0,n) d[i][j]=d[j][i]=INF;
    rep(i,0,m) {int a,b,c; cin>>a>>b>>c; d[a][b]=c;}
    fill((int *)dp, (int *)(dp+(1<<MAXN)), -1);
    if(rec(0,0)==INF)cout<<"-1"<<endl;
    else cout << rec(0,0) << endl;

    return 0;
}
*/

// 強連結成分分解をします。scc[i]で頂点iが何番目の成分に含まれているかが分かる。
// StronglyConnectedComponents(グラフ);のあと、build(重みなしグラフ);をする。
/*

template <typename G>
 struct StronglyConnectedComponents {
   const G &g;
   UnWeightedGraph ng, rg;          // normal-graphとreversed-graph
   vector<int> compo, order, used;  // compo…頂点がどの成分に属しているか、order…帰りがけ順で何番目か
 
   StronglyConnectedComponents(G &g) : g(g), ng(g.size()), rg(g.size()), compo(g.size(), -1), used(g.size()) {
     for (int i = 0; i < g.size(); i++)
       for (auto t : g[i]) {
         ng[i].emplace_back((int)t);
         rg[(int)t].emplace_back(i);  // 逆辺
       }
   }
 
   // []で聞かれたときは成分番号を返す
   int operator[](int k) { return compo[k]; }
 
   void dfs(int now) {
     if (used[now]) return;
     used[now] = true;
     for (auto to : ng[now]) dfs(to);
     order.emplace_back(now);
   }
 
   void rdfs(int now, int count) {
     // used代わりに結果を入れていく
     if (compo[now] != -1) return;
     compo[now] = count;
     for (auto to : rg[now]) rdfs(to, count);
   }
 
   void build(UnWeightedGraph &ret) {
     // 普通にDFS、辺の向きを変えてもう一度DFS
     for (int i = 0; i < ng.size(); i++) dfs(i);
     reverse(order.begin(), order.end());
     int group = 0;
     for (auto i : order)
       if (compo[i] == -1) rdfs(i, group), group++;
 
     // 縮めたグラフを構築する
     ret.resize(group);
     for (int i = 0; i < g.size(); i++) {  // 全ての辺について
       for (auto &to : g[i]) {
         int s = compo[i], t = compo[to];
         if (s != t) ret[s].emplace_back(t);
       }
     }
   }
 };  
 */

