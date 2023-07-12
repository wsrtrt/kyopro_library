#include <bits/stdc++.h>
using namespace std;
//素数判定
bool IsPrime(int X){
    for(int i=2;i*i<=X;i++){
        if(X%i==0)return false;
    }
    return true;
}

//GCD
long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}
 
//LCM
long long lcm(long long a, long long b) {
    long long d = gcd(a, b);
    return a / d * b;
}

//Aのb乗をmで割ったあまり
int power(int n, long long p, int mod) {
	if (p == 0) {
		return 1;
	}
	if (p % 2 == 0) {
		long long int t = power(n, p / 2, mod);
		return (int)(t * t % mod);
	}
	return (int)(((long long int)n * power(n, p - 1, mod))% mod);
}

//A÷Bをmで割ったあまり
long long Division(long long A,long long B,long long M){
    return (A*power(B,M-2,M))%M;
}

// 1 以上 N 以下の整数が素数かどうかを返す
vector<bool> Eratosthenes(int N) {
    // テーブル
    vector<bool> isprime(N+1, true);

    // 0, 1 は予めふるい落としておく
    isprime[0] = isprime[1] = false;

    // ふるい
    for (int p = 2; p <= N; ++p) {
        // すでに合成数であるものはスキップする
        if (!isprime[p]) continue;

        // p 以外の p の倍数から素数ラベルを剥奪
        for (int q = p * 2; q <= N; q += p) {
            isprime[q] = false;
        }
    }

    // 1 以上 N 以下の整数が素数かどうか
    return isprime;
}

//(1LL<<64)を超えそうな場合はdouble型を通して判定
long long f(long long p,long long q){
  double est=1;
  est=(q*q*q);
  est*=p;
  if(est>4e18){return 4e18;}
  return p*q*q*q;
}

//modint
template <std::uint_fast64_t Modulus> class modint {
  using u64 = std::uint_fast64_t;

public:
  u64 a;

  constexpr modint(const u64 x = 0) noexcept : a(x % Modulus) {}
  constexpr u64 &val() noexcept { return a; }
  constexpr const u64 &val() const noexcept { return a; }
  constexpr modint operator+(const modint rhs) const noexcept {
    return modint(*this) += rhs;
  }
  constexpr modint operator-(const modint rhs) const noexcept {
    return modint(*this) -= rhs;
  }
  constexpr modint operator*(const modint rhs) const noexcept {
    return modint(*this) *= rhs;
  }
  constexpr modint operator/(const modint rhs) const noexcept {
    return modint(*this) /= rhs;
  }
  constexpr modint &operator+=(const modint rhs) noexcept {
    a += rhs.a;
    if (a >= Modulus) {
      a -= Modulus;
    }
    return *this;
  }
  constexpr modint &operator-=(const modint rhs) noexcept {
    if (a < rhs.a) {
      a += Modulus;
    }
    a -= rhs.a;
    return *this;
  }
  constexpr modint &operator*=(const modint rhs) noexcept {
    a = a * rhs.a % Modulus;
    return *this;
  }
  constexpr modint &operator/=(modint rhs) noexcept {
    u64 exp = Modulus - 2;
    while (exp) {
      if (exp % 2) {
        *this *= rhs;
      }
      rhs *= rhs;
      exp /= 2;
    }
    return *this;
  }
};
using mint=modint<998244353>;
//using mint=modint<1000000007>;

//log2
int logN(long long n){
    int ret=1;
    while((1LL<<ret)<n)ret++;
    return ret;
}

/*  PrimeFact
    init(N): 初期化。O(N log log N)
    get(n): クエリ。素因数分解を求める。O(log n)
 */
template <typename T>
struct PrimeFact {
    vector<T> spf;
    PrimeFact(T N) { init(N); }
    void init(T N) { // 前処理。spf を求める
        spf.assign(N + 1, 0);
        for (T i = 0; i <= N; i++) spf[i] = i;
        for (T i = 2; i * i <= N; i++) {
            if (spf[i] == i) {
                for (T j = i * i; j <= N; j += i) {
                    if (spf[j] == j) {
                        spf[j] = i;
                    }
                }
            }
        }
    }
    map<T, T> get(T n) { // nの素因数分解を求める
        map<T, T> m;
        while (n != 1) {
            m[spf[n]]++;
            n /= spf[n];
        }
        return m;
    }
};

//素因数分解
/*
vector<pair<long long, long long> > prime_factorize(long long N) {
    vector<pair<long long, long long> > res;
    for (long long a = 2; a * a <= N; ++a) {
        if (N % a != 0) continue;
        long long ex = 0; // 指数

        // 割れる限り割り続ける
        while (N % a == 0) {
            ++ex;
            N /= a;
        }

        // その結果を push
        res.push_back({a, ex});
    }

    // 最後に残った数について
    if (N != 1) res.push_back({N, 1});
    return res;
}
*/


long long sqrtll(long long x) {
    assert(x >= 0);
    long long rev = sqrt(x);
    while(rev * rev > x) --rev;
    while((rev+1) * (rev+1)<=x) ++rev;
    return rev;
}

/*
DP
LIS
耳DP
数え上げDP
木DP
全方位木DP

二分探索
決めうち二分探索
単調性を見つけるのがうまくなった

貪欲
区間スケジューリング問題
解法の一部に含まれる貪欲要素に気を配れるようになった(DPのときとか)

数え上げ
主客転倒
包除原理
期待値の線形性(というかだいたい数え上げだと思って解いてる)
マスターオブ場合の数を読んだのがよかった

データ構造
BIT
セグ木
遅延伝播セグ木

整数関連
中国剰余定理
拡張ユークリッドの互除法
エラトステネスの篩
高速素因数分解

文字列
Suffix Array(使ったことない)
Z-algorithm(使ったことない)
manachar(使ったことない)

ゲーム
Nim(XORが大事)
真似するやつ
過半数が大事
min-max法?

グラフ
LCA

フロー
最大流
最小費用流(使ったことない)
二部グラフのマッチング(使ったことない)

その他テクニック
座標圧縮
鳩の巣原理
拡張ダイクストラ
真ん中を固定する
2変数を1変数に変えるやつ
計算量が調和級数になるやつ
操作回数が実は多くない
半分全列挙
マンハッタン距離は45°回転
添字ガチャ
set, multisetガチャガチャ
*/
