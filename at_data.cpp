#include <bits/stdc++.h>
using namespace std;
const int INF = INT_MAX / 2; const long long INFL = 1LL << 60;
//文字列のハッシュ
/*
class StringHush{
    string s;
    int s_SIZE=0;
    private:
    long long modh=2147483647;
    vector<long long> t,h,power100;
    public:
    StringHush(string s_){
        modh=2147483647;
        s=s_;
        s_SIZE=s.size();
        //文字列を数値に変換
        t.push_back(-1);
        for(int i=1;i<=s_SIZE;i++)t.push_back((s[i-1]-'a')+1);
        //100のｎ乗を計算
        power100.push_back(1);
        for(int i=1;i<=s_SIZE;i++)power100.push_back(100LL*power100[i-1]%modh);
        //文字ごとにハッシュ化
        h.push_back(0);
        for(int i=1;i<=s_SIZE;i++)h.push_back((100LL*h[i-1]+t[i])%modh);
    }
    StringHush(string s_,long long m){
        modh=m;
        s=s_;
        s_SIZE=s.size();
        //文字列を数値に変換
        t.push_back(-1);
        for(int i=1;i<=s_SIZE;i++)t.push_back((s[i-1]-'a')+1);
        //100のｎ乗を計算
        power100.push_back(1);
        for(int i=1;i<=s_SIZE;i++)power100.push_back(100LL*power100[i-1]%modh);
        //文字ごとにハッシュ化
        h.push_back(0);
        for(int i=1;i<=s_SIZE;i++)h.push_back((100LL*h[i-1]+t[i])%modh);
    }
    //s[l,r]のハッシュ値を返す
    long long Hash_Value(int l,int r){
        long long val=h[r]-(h[l-1]*power100[r-l+1]%modh);
        if(val<0)val+=modh;
        return val;
    }
};
*/

//セグメント木
/*
class SegmentTree{
    public:
    int dat[300000],siz=1;

    //要素datの初期化
    void init(int N){
        siz=1;
        while(siz<N)siz*=2;
        for(int i=1;i<siz*2;i++)dat[i]=0;
    }

    //要素の更新
    void update(int pos,int x){
        pos=pos+siz-1;
        dat[pos]=x;
        //最大値の更新
        while(pos>=2){
            pos/=2;
            dat[pos]=max(dat[pos*2],dat[pos*2+1]);
        }
    }
    
    //クエリ処理
    //uは現在のセル,{a,b}はセルに対応する半開区画,{l,r}は求めたい半開区画
    //完全に含まれる範囲を見つけるまで枝分かれ的に探索
    int query(int l,int r,int a,int b,int u){
        if(r<=a||b<=l)return -INF;//一切含まれない場合
        if(l<=a&&b<=r)return dat[u];//完全に含まれる場合
        //一部含まれる場合
        int m=(a+b)/2;
        int AnswerL=query(l,r,a,m,u*2);
        int AnswerR=query(l,r,m,b,u*2+1);
        return max(AnswerL,AnswerR);
    }
};
*/

//Priority-Sum-Structure
//query O(1)
//insert erase O(log n)(ならし)
//set_k O((それ以前のkとの差)log n)
/*
template< typename T, typename Compare = less< T >, typename RCompare = greater< T > >
struct PrioritySumStructure {

  size_t k;
  T sum;

  priority_queue< T, vector< T >, Compare > in, d_in;
  priority_queue< T, vector< T >, RCompare > out, d_out;

  PrioritySumStructure(int k) : k(k), sum(0) {}

  void modify() {
    while(in.size() - d_in.size() < k && !out.empty()) {
      auto p = out.top();
      out.pop();
      if(!d_out.empty() && p == d_out.top()) {
        d_out.pop();
      } else {
        sum += p;
        in.emplace(p);
      }
    }
    while(in.size() - d_in.size() > k) {
      auto p = in.top();
      in.pop();
      if(!d_in.empty() && p == d_in.top()) {
        d_in.pop();
      } else {
        sum -= p;
        out.emplace(p);
      }
    }
    while(!d_in.empty() && in.top() == d_in.top()) {
      in.pop();
      d_in.pop();
    }
  }

  //上位 k 個の和（要素数がk個未満の場合すべての要素の和）
  T query() const {
    return sum;
  }

  //要素 x を追加する
  void insert(T x) {
    in.emplace(x);
    sum += x;
    modify();
  }

  //要素 x を削除する
  void erase(T x) {
    assert(size());
    if(!in.empty() && in.top() == x) {
      sum -= x;
      in.pop();
    } else if(!in.empty() && RCompare()(in.top(), x)) {
      sum -= x;
      d_in.emplace(x);
    } else {
      d_out.emplace(x);
    }
    modify();
  }

  //k を指定しなおす
  void set_k(size_t kk) {
    k = kk;
    modify();
  }
  
  //k を返す
  size_t get_k() const {
    return k;
  }

  //全体の要素数を返す
  size_t size() const {
    return in.size() + out.size() - d_in.size() - d_out.size();
  }
};

//降順 k 個に指定
template< typename T >
using MaximumSum = PrioritySumStructure< T, greater< T >, less< T > >;

//昇順 k 個に指定
template< typename T >
using MinimumSum = PrioritySumStructure< T, less< T >, greater< T > >;
*/

//セグメントツリー(modint区間和)
/*
struct SegmentTree{
private:
    int n;
    vector<mint> node;
public:
    //元配列 v をセグメント木で構築する
    SegmentTree(vector<mint> v){
        //最下段のノード数は元配列のサイズ以上になる最小の２冪
        int sz=v.size();
        n=1;while(n<sz)n*=2;
        node.resize(2*n-1,0);
        // 最下段に値を入れたあとに、下の段から順番に値を入れる
        // 値を入れるには、自分の子の 2 値を参照すれば良い
        for(int i=0; i<sz; i++) node[i+n-1] = v[i];
        for(int i=n-2; i>=0; i--) node[i] = node[2*i+1]+ node[2*i+2];
    }
    void update(int x, mint val) {
        // 最下段のノードにアクセスする
        x += (n - 1);
        // 最下段のノードを更新したら、あとは親に上って更新していく
        node[x] = val;
        while(x > 0) {
            x = (x - 1) / 2;
            node[x] = node[2*x+1]+node[2*x+2];
        }
    }
    // 要求区間 [a, b) 中の要素の区間和を答える
    // k := 自分がいるノードのインデックス
    // 対象区間は [l, r) にあたる

    mint getsum(int a, int b, int k=0, int l=0, int r=-1) {
        // 最初に呼び出されたときの対象区間は [0, n)
        if(r < 0) r = n;

        // 要求区間と対象区間が交わらない -> 適当に返す
        if(r <= a || b <= l) return 0;

        // 要求区間が対象区間を完全に被覆 -> 対象区間を答えの計算に使う
        if(a <= l && r <= b) return node[k];

        // 要求区間が対象区間の一部を被覆 -> 子について探索を行う
        // 左側の子を vl ・ 右側の子を vr としている
        // 新しい対象区間は、現在の対象区間を半分に割ったもの
        mint AnswerL = getsum(a, b, 2*k+1, l, (l+r)/2);
        mint AnswerR = getsum(a, b, 2*k+2, (l+r)/2, r);
        return AnswerL+AnswerR;
    }
};
*/

//RMQ（区間最小値セグ木）
/*
// set(i, x), build(): i番目の要素をxにセットし、buildでまとめてセグ木を構築する
// update(a,b,x): 区間 [a,b) の要素を x に更新
// query(a,b): 区間 [a,b) での最小の要素を取得
// find_rightest(a,b,x): [a,b) で x以下の要素を持つ最右位置を求める
// find_leftest(a,b,x): [a,b) で x以下の要素を持つ最左位置を求める
*/
/*
template <typename T>
struct RMQ {
    const T e = numeric_limits<T>::max();
    function<T(T, T)> fx = [](T x1, T x2) -> T { return min(x1, x2); };
    int n;
    vector<T> dat;
    RMQ(int n_) : n(), dat(n_ * 4, e) {
        int x = 1;
        while (n_ > x) {
            x *= 2;
        }
        n = x;
    }
    void set(int i, T x) { dat[i + n - 1] = x; }
    void build() {
        for (int k = n - 2; k >= 0; k--) dat[k] = fx(dat[2 * k + 1], dat[2 * k + 2]);
    }
    void update(int i, T x) {
        i += n - 1;
        dat[i] = x;
        while (i > 0) {
            i = (i - 1) / 2;  // parent
            dat[i] = fx(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }
    // the minimum element of [a,b)
    T query(int a, int b) { return query_sub(a, b, 0, 0, n); }
    T query_sub(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) {
            return e;
        } else if (a <= l && r <= b) {
            return dat[k];
        } else {
            T vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return fx(vl, vr);
        }
    }
    int find_rightest(int a, int b, T x) { return find_rightest_sub(a, b, x, 0, 0, n); }
    int find_leftest(int a, int b, T x) { return find_leftest_sub(a, b, x, 0, 0, n); }
    int find_rightest_sub(int a, int b, T x, int k, int l, int r) {
        if (dat[k] > x || r <= a || b <= l) {  // 自分の値がxより大きい or [a,b)が[l,r)の範囲外ならreturn a-1
            return a - 1;
        } else if (k >= n - 1) {  // 自分が葉ならその位置をreturn
            return (k - (n - 1));
        } else {
            int vr = find_rightest_sub(a, b, x, 2 * k + 2, (l + r) / 2, r);
            if (vr != a - 1) {  // 右の部分木を見て a-1 以外ならreturn
                return vr;
            } else {  // 左の部分木を見て値をreturn
                return find_rightest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2);
            }
        }
    }
    int find_leftest_sub(int a, int b, T x, int k, int l, int r) {
        if (dat[k] > x || r <= a || b <= l) {  // 自分の値がxより大きい or [a,b)が[l,r)の範囲外ならreturn b
            return b;
        } else if (k >= n - 1) {  // 自分が葉ならその位置をreturn
            return (k - (n - 1));
        } else {
            int vl = find_leftest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2);
            if (vl != b) {  // 左の部分木を見て b 以外ならreturn
                return vl;
            } else {  // 右の部分木を見て値をreturn
                return find_leftest_sub(a, b, x, 2 * k + 2, (l + r) / 2, r);
            }
        }
    }
};
*/


