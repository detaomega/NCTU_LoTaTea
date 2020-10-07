#include<bits/stdc++.h>

using namespace std;

struct frc {
  int u;
  int d;

  frc norm() {
    int gcd = __gcd( abs(u), abs(d));
    u /= gcd;
    d /= gcd;
    return {u, d};
  }

  bool operator==(frc b) {
    return (u == b.u && d == b.d);
  }
  bool operator>=(frc b) {
    return u * b.d >= b.d * d;
  }
  bool operator<=(frc b) {
    return u * b.d <= b.d * d;
  }
  frc operator-(frc b) {
    frc ret = (frc) { u*b.d - d*b.u, d*b.d};
    ret.norm();
    return ret;
  }
};

int main() {

  int p,q,r;

  cin >> p >> q >> r;
  frc x1 = {3*p-q, 4*q};
  frc x2 = {3*p-r, 4*p+4*r};
  frc x3 = {3*q-3*r, 4*q};

  x1.norm();
  x2.norm();
  x3.norm();
  printf("%d/%d\n", x1.u, x1.d);
  printf("%d/%d\n", x2.u, x2.d);
  printf("%d/%d\n", x3.u, x3.d);
  if (x1 == x2 &&  x1 == x3 && x2 == x3 && x1 >= (frc){0,1} && x1 <= (frc){1,2}) {
    frc y = (frc){1,2} - x1;
    printf("%d/%d %d/%d", x1.u, x1.d, y.u, y.d);
  } else {
    printf("-1\n");
  }

  return 0;
}
