struct F2 {
  int x;
  F2() : x(0) {}
  F2(int v) : x(v & 1) {}
  F2 operator+(const F2 &a) const { return F2(x + a.x); }
  F2 operator-() const { return F2(-x); }
  bool operator==(const F2 &a) const { return val() == a.val(); }
  int val() const { return x; }
};

// #include <atcoder/modint>
// using F2 = atcoder::static_modint<2>;

// -------- Linear System Incidence ----------
//
// 接続行列を係数行列とする連立方程式を解く(Bx = vs)
// 各頂点vに対してsum_{vに入るe}x(e) - sum_{vから出るe}x(e) = vs(v)となるような
// (sum...は相対流入量と考えると混乱しにくい)
// 辺へのコストの割り当てc : E -> Tを求める
// (内部的に接続行列は辺の始点ならば-1, 終点ならば+1)
//
// Note: class Tに必要な演算は2項+,単項-,等号==のみ(等式の場合)
//       コンストラクタは0から零元を生成することが期待される
//       不等式の場合は<も必要
//       F2を使用する問題が多い
//
// Complexity: O(|V| + |E|)
//
// Reference:
// https://drive.google.com/file/d/1GYxjvoEIn_j9i9AEWP5zQ4yyCQCLysrn/view
//
// Verify: https://atcoder.jp/contests/agc035/submissions/17884800
template <class T>
struct LinearSystemIncidence {
  struct edge {
    int to;
    bool rev;
    int id;
    edge() {}
    edge(int to, bool rev, int id) : to(to), rev(rev), id(id) {}
  };

  vector<vector<edge>> G;
  int E;

  LinearSystemIncidence(int N) : G(N), E(0) {}

  // from -> toの辺をidをつけて追加
  void add_edge(int from, int to, int id) {
    G[from].emplace_back(to, false, id);
    G[to].emplace_back(from, true, id);
    E = max(E, id + 1);
  }

  // vs : 各頂点vの相対流入量
  // ineq : 不等式かどうか(trueならBx <= vsを解く
  // 解が存在しない場合、空配列を返す
  vector<T> solve(vector<T> vs, bool ineq = false) {
    vector<bool> used(vs.size(), false);
    vector<T> es(E, T(0));

    auto dfs = [&](auto &&f, int v) -> T {
      used[v] = true;
      T r = vs[v];
      for (edge e : G[v]) {
        if (used[e.to]) continue;
        T y = f(f, e.to);
        if (!e.rev)
          es[e.id] = y;
        else
          es[e.id] = -y;
        r = r + y;
      }
      return r;
    };

    for (int i = 0; i < vs.size(); i++) {
      if (!used[i]) {
        T rem = dfs(dfs, i);
        if (!ineq && !(rem == T(0))) return vector<T>();
        // if (ineq && rem < T(0)) return vector<T>();
      }
    }
    return es;
  }
};
