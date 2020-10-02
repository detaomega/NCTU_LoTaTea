vector<pos> convex_hull(vector<pos> P) {
  sort(begin(P), end(P), cmp());
  int sz = P.size();
  vector<pos> up;
  vector<pos> down;
  for (int i=0; i<sz; i++) {
    while(up.size() >= 2) {
      vec v1 = *(up.end()-1) - *(up.end()-2);
      vec v2 = P[i] - *(up.end()-1);
      if ( (v1|v2) > 0)
        break;
      up.pop_back();
    }
    up.push_back(P[i]);
  }
  up.pop_back();
  for (int i=sz-1; i>=0; i--) {
    while(down.size() >= 2) {
      vec v1 = *(down.end()-1) - *(down.end()-2);
      vec v2 = P[i] - *(down.end()-1);
      if ( (v1|v2) > 0)
        break;
      down.pop_back();
    }
    down.push_back(P[i]);
  }
  down.pop_back();

  vector<pos> hull;
  for (auto it: up) {
    hull.push_back(it);
  }
  for (auto it: down) {
    hull.push_back(it);
  }
  return hull;
}
