class UnionFind {
 public:
  UnionFind() = delete;
  UnionFind(int n) : count(n) {
    parent.reserve(n);
    for (int i = 0; i < n; i++) {
      parent.emplace_back(i);
    }
  }

  void Union(int p, int q) {
    int rootP = find(p);
    int rootQ = find(q);

    if (rootP == rootQ) return;
    parent[rootQ] = rootP;
    count--;
  }

  bool connected(int p, int q) { return find(p) == find(q); }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  int get_count() const { return count; }

 private:
  int count;
  vector<int> parent;
};