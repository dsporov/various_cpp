#include <vector>
#include <chrono>
#include <bitset>

#include <iostream>

bool isPrime(size_t value, std::vector<size_t> &primes) {
	for (auto prime : primes) {
		if (value % prime == 0)
			return false;
	}

	return true;
}

void fillNonPrimesForPrimeMultipliers(size_t val, std::vector<bool> &primeMarkers) {
	size_t valSqrt = val*val;
	size_t bound = primeMarkers.size();
	for (size_t i = 0; i < bound; ++i) {
		size_t idx = valSqrt + i*val;
		if (idx >= bound)
			break;
		primeMarkers[idx] = false;
	}
}

void fillNonPrimes(size_t bound, std::vector<bool> &primeMarkers) {
	size_t boundSqrt = static_cast<size_t>(std::sqrt(bound));

	for (size_t i = 2; i < boundSqrt; ++i) {
		if (!primeMarkers[i])
			continue;

		fillNonPrimesForPrimeMultipliers(i, primeMarkers);
	}
}

void primeNumbers(size_t bound, std::vector<size_t> &primes) {
	std::vector<bool> primeMarkers(bound, true);
	fillNonPrimes(bound, primeMarkers);

	for (size_t i = 2; i < bound; ++i) {
		if (primeMarkers[i])
			primes.push_back(i);
	}
}

void test_primeNumbers() {
	auto started = std::chrono::high_resolution_clock::now();

	std::vector<size_t> primes;
	primeNumbers(100000, primes);

	auto done = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();

	if (primes.size() != 9592
		|| primes.front() != 2
		|| primes[33] != 139
		|| primes[157] != 929
		|| primes[1927] != 16661
		|| primes[5142] != 50093
		|| primes.back() != 99991
		)
	{
		throw std::logic_error("Incorrect result");
	}
}

