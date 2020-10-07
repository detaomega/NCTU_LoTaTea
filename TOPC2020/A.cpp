#include<bits/stdc++.h>

using namespace std;



int main() {
  int r,c;

  cin >> r >> c;
  printf("%d %d\n", r, c);
  while(r > 0) {
    printf("%d %d\n", --r, c);
  }
  while(c > 0) {
    printf("%d %d\n", r, --c);
  }
  for (int i=0; i<=9; i++) {
    for (int j=0; j<=9; j++) {
      if(i == 0 && j == 0)
        continue;
      printf("%d %d\n", i, i % 2 == 0 ? j : 9-j);
    }
  }

  return 0;
}
