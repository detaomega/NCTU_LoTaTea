vector<int> linear_sieve(int Up_bound) {
  vector<int> primes, last_prime(Up_bound, 0);
  for (int p = 2; p < Up_bound; p++) {
    if (!last_prime[p]) {
	  primes.push_back(p);
	  last_prime[p] = p;
    }
    for (int j = 0; primes[j] * p < Up_bound; j++) {
      last_prime[primes[j] * p] = primes[j];
      if (p % primes[j] == 0) break;
    }
  }
  return last_prime;
}
