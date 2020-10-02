pair<pos,pos> nearest_pair(vector<pos> P) {
  int N = P.size();
  sort(begin(P), end(P),cmp());
  pair<pos,pos> ans;
  double mini = INF;

  multiset<pos,cmp2> st;
  for (int i=0, j=0; i<N; i++) {
    st.insert(P[i]);
    while(P[i].x - P[j].x > mini) {
      st.erase(st.find(P[j++]));
    }
    for (auto it=begin(st); it!=end(st); it++) {
      for (auto it2=next(it); it2!=end(st); it2++) {
        if ( (*it2).y - (*it).y > mini)
          break;
        if (abs(*it2 - *it) < mini) {
          mini = abs(*it2 - *it);
          ans = {*it2, *it};
        }
      }
    }
  }

  return ans;
}
