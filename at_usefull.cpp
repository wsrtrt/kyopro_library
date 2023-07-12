//bit全探索テンプレ
/*
int n;cin>>n;
    for(int bit=0;bit<(1<<n);bit++){
        vector<int> S;
        for(int i=0;i<n;i++){
            if(bit&(1<<i)){
                S.push_back(i);
            }
        }
        cout << bit << ": {";
        for (int i = 0; i < (int)S.size(); ++i) {
            cout << S[i] << " ";
        }
        cout << "}" << endl;
    }
    
*/

// 汎用的な二分探索のテンプ
/*
vector<int> v = {1, 14, 32, 51, 51, 51, 243, 419, 750, 910};
int binary_search(int key) {
    int left = -1; //「index = 0」が条件を満たすこともあるので、初期値は -1
    int right = (int)v.size(); 
    while (right - left > 1) {
        int mid = left + (right - left) / 2;

        if (v[mid] >= key) right = mid;
        else left = mid;
    }
    return right;
}
*/


//グリッド問題便利きっと
/*
//vector<pair<int,int>> grid_serch={{0,1},{0,-1},{1,0},{-1,0},{1,1},{-1,-1},{1,-1},{-1,1}};
int dx[4] = { 0, 1, 0, -1 }, dy[4] = { -1, 0, 1, 0 };
rep(k,0,4){
    if(0<=x+grid_serch[k].ff&&x+grid_serch[k].ff<n&&0<=y+grid_serch[k].ss&&m>y+grid_serch[k].ss){
    
    }
}
if(0<=a&&a<h&&0<=b&&b<w)
*/

//座標圧縮
/*
template<typename T>
vector<T> coordinate(vector<T>& A){
    vector<T> B=A;
    sort(all(B));
    B.erase(unique(all(B)),B.end());
    vector<ll> ret(A.size());
    rep(i,0,(int)A.size()){
        ret[i]=lower_bound(all(B),A[i])-B.begin();
    }
    return ret;
}
*/

