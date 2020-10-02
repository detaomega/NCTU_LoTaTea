pos find_O(pos A, pos B, pos C) {
  pos m1 = (A+B) / 2.0;
  pos m2 = (A+C) / 2.0;
  vec v1 = B - A;
  vec v2 = C - A;
  double c1 = m1.x * v1.x + m1.y * v1.y;
  double c2 = m2.x * v2.x + m2.y * v2.y;
  double d  = v1.x * v2.y - v2.x * v1.y;
  double dx = c1   * v2.y - c2   * v1.y;
  double dy = v1.x * c2   - v2.x * c1;
  return {dx/d, dy/d};
}

pair<pos, double> min_EnclosinCircle(vector<pos> P) {
  int N = P.size();
  random_shuffle(begin(P), end(P));
  pos C = pos(0,0);
  double r = 0;
  for (int i=0; i<N; i++) {
    if (abs(C - P[i]) <= r)
      continue;

    C = P[i];
    r = 0;
    for (int j=0; j<i; j++) {
      if (abs(C - P[j]) <= r)
        continue;

      C = ( P[i] + P[j] ) / 2.0;
      r = abs(C - P[i]);
      for (int k=0; k<j; k++) {
        if (abs(C - P[k]) <= r)
          continue;

        C = find_O(P[i], P[j], P[k]);
        r = abs(C - P[i]);
      }
    }
  }
  return {C, r};
}
