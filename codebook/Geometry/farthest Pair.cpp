pair<pos,pos> farthest_pair(vector<pos> P) { // with rotating caliper
  if (P.size() == 2) {
    return {P[0], P[1]};
  }
  P = convex_hull(P);
  int N = P.size();
  double maxi = 0;
  pair<pos,pos> ans;
  for (int i=0, j=1; i<N; i++) {
    vec v = P[(i+1) % N] - P[i];
    while( abs( v | (P[j] - P[i]) ) < abs( v | (P[(j+1) % N] - P[i]) )) {
      j = (j+1) % N;
    }

    if (abs(P[j] - P[i]) > maxi) {
      maxi = abs(P[j] - P[i]);
      ans = {P[j], P[i]};
    }
    if (abs(P[j] - P[(i+1)%N]) > maxi) {
      maxi = abs(P[j] - P[(i+1)%N]);
      ans = {P[j], P[(i+1)%N]};
    }
  }
  
  return ans;
}
