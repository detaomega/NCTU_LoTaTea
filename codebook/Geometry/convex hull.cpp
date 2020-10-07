vector<pos> convex_hull(vector<pos> P) {
  sort(begin(P), end(P), cmp());
  for (int i=P.size()-2; i>=0; i--) {
    P.push_back(P[i]);
  }
  vector<pos> keep;
  for (auto now: P) {
    while (keep.size() >= 2) {
      vec v1 = *(keep.end()-1) - *(keep.end()-2);
      vec v2 = now - *(keep.end()-1);
      if ( (v1 | v2) > 0 || (v1 | v2) == 0 && ( v1 & v2) < 0) {
        break;
      }
      keep.pop_back();
    }
    keep.push_back(now);
  }
  keep.pop_back();
  return keep;
}
