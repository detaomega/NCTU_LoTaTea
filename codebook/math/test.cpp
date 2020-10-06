
const double PI = acos(-1);

void FFT(complex<double> A[], int n, int rev) {
    // rev == -1 -----> IDFT
    // rer == 1  ----->  DFT
    complex<double> step, w, u, v;
    for(int i = 1, j = 0; i < n; i++) {
        for(int k = (n >> 1); k > (j ^= k); k >>= 1);
        if(i < j) swap(A[i], A[j]);
    }
    for(int len = 1; len << 1 <= n; len <<= 1) {
        step = {cos(PI*rev/len), sin(PI*rev/len)};
        for(int i = 0; i < n; i += (len << 1)) {
            w = {1.0, 0.0};
            for(int j = 0; j < len; j++) {
                u = A[i + j];
                v = A[i + len + j];
                A[i + j] = u + w * v;
                A[i + len + j] = u - w * v;
                w = w * step;
            }
        }
    }
}
