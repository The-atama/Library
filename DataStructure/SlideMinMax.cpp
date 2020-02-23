template <class T> struct SlideMin {
  vector<T> v;
  deque<int> deq;
  SlideMin(vector<T> &v) : v(v) {}
  void add(int id) { // add v[id]
    while (!deq.empty() && v[deq.back()] >= v[id])
      deq.pop_back();
    deq.push_back(id);
  }
  T get(int id) { // [id,added]
    while (!deq.empty() && deq.front() < id)
      deq.pop_front();
    assert(!deq.empty());
    return v[deq.front()];
  }
};

template <class T> struct SlideMax {
  vector<T> v;
  deque<int> deq;
  SlideMax(vector<T> &v) : v(v) {}
  void add(int id) {
    while (!deq.empty() && v[deq.back()] <= v[id])
      deq.pop_back();
    deq.push_back(id);
  }
  T get(int id) { // [id,added]
    while (!deq.empty() && deq.front() < id)
      deq.pop_front();
    assert(!deq.empty());
    return v[deq.front()];
  }
};
