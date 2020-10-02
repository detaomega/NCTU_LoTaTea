bool intersect(pos p1, pos q1, pos p2, pos q2) {
  if (max(p1.x, q1.x) < min(p2.x, q2.x) ||
      max(p2.x, q2.x) < min(p1.x, q1.x) ||
      max(p1.y, q1.y) < min(p2.y, q2.y) ||
      max(p2.y, q2.y) < min(p1.y, q1.y) ){
    return 0;
  }
  double d1 = ( (q1-p1) | (p2-p1) ) * ( (q1-p1) | (q2-p1) );
  double d2 = ( (q2-p2) | (p1-p2) ) * ( (q2-p2) | (q1-p2) );

  return (d1 <= 0 && d2 <= 0);
}

bool in_polygon(vector<pos> P, pos a) {
  int N = P.size();
  int cnt = 0;
  for (int i=0; i<N; i++) {
    if ( intersect( P[i], P[(i+1)%N], a, pos(1e9,0)) ) {
      cnt++;
    }
  }
  return (cnt % 2 == 1);
}
