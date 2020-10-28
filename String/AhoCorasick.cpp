struct AhoCorasick {
  const static int alphabet_size = 26;
  const int root = 0;
  const char base = 'a';

  AhoCorasick() : T(1) {}
  AhoCorasick(const vector<string> &ss) : T(1) {
    for (const string &s : ss) add_string(s);
    build();
  }

  struct Node {
    vector<int> child; // children of this node in Trie
    bool leaf;
    int par;         // parent
    char par_c;      // character on the edge from parent to this node
    int suf_link;    // suffix link
    int exit_link;   // exit link : direct suffix link to the nearest match
    vector<int> go;  // transition of the automaton
    int match_count; // the number of matches of this state
    Node(int par = -1, char par_c = '$')
        : leaf(false), par(par), par_c(par_c), suf_link(-1), exit_link(-1),
          match_count(-1) {
      child.assign(alphabet_size, -1);
      go.assign(alphabet_size, -1);
    }
  };

  vector<Node> T;

  int add_string(const string &s) {
    int v = root;
    for (char ch : s) {
      int c = ch - base;
      if (T[v].child[c] == -1) {
        T[v].child[c] = T.size();
        T.emplace_back(v, ch);
      }
      v = T[v].child[c];
    }
    T[v].leaf = true;
    return v;
  }

  int suf_link(int v) {
    if (T[v].suf_link == -1) {
      if (v == root || T[v].par == root) {
        T[v].suf_link = root;
      } else {
        int par_suf_link = suf_link(T[v].par);
        T[v].suf_link = go(par_suf_link, T[v].par_c);
      }
    }
    return T[v].suf_link;
  }

  int go(int v, char ch) {
    int c = ch - base;
    if (T[v].go[c] == -1) {
      if (T[v].child[c] != -1)
        T[v].go[c] = T[v].child[c];
      else
        T[v].go[c] = (v == root) ? root : go(suf_link(v), ch);
    }
    return T[v].go[c];
  }

  int match_count(int v) {
    if (T[v].match_count == -1) {
      if (v == root)
        T[v].match_count = 0;
      else {
        T[v].match_count = match_count(suf_link(v)) + (T[v].leaf ? 1 : 0);
      }
    }
    return T[v].match_count;
  }

  int exit_link(int v) {
    if (T[v].exit_link == -1) {
      if (v == root)
        T[v].exit_link = 0;
      else {
        int suf = suf_link(v);
        T[v].exit_link = T[suf].leaf ? suf : exit_link(suf);
      }
    }
    return T[v].exit_link;
  }

  void build() {
    for (int v = 0; v < T.size(); v++) {
      suf_link(v);
      match_count(v);
      exit_link(v);
      for (int i = 0; i < alphabet_size; i++) go(v, base + i);
    }
  }

  Node &operator[](int v) { return T[v]; }
  int size() const { return T.size(); }
};
