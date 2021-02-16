struct Trie {
  const static int alphabet_size = 26;
  const int root = 0;
  const char base = 'a';

  Trie() : T(1) {}

  struct Node {
    vector<int> child; // children of this node in Trie
    bool leaf;
    int par;    // parent
    char par_c; // character on the edge from parent to this node
    Node(int par = -1, char par_c = '$') : leaf(false), par(par), par_c(par_c) {
      child.assign(alphabet_size, -1);
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

  Node &operator[](int v) { return T[v]; }
  int size() const { return T.size(); }
};
