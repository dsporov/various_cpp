#include <cstdint>
#include <cassert>
#include <limits>

using uchar = unsigned char;

template<uint8_t n>
uint8_t num_of_bits() {
	return (n & 1) + num_of_bits<n - 1>();
}

template<>
uint8_t num_of_bits<0>() {
	return 0;
}

uint8_t num_of_bits_cache(uint8_t n) {
	static uint8_t bits[] = {
		num_of_bits<0>(),
		num_of_bits<1>(),
		num_of_bits<2>(),
		num_of_bits<3>(),
		num_of_bits<4>(),
		num_of_bits<5>(),
		num_of_bits<6>(),
		num_of_bits<7>(),
		num_of_bits<8>(),
		num_of_bits<9>(),
		num_of_bits<10>(),
		num_of_bits<11>(),
		num_of_bits<12>(),
		num_of_bits<13>(),
		num_of_bits<14>(),
		num_of_bits<15>()
	};

	return bits[n & 0x0f] + bits[n >> 4];
}

uint8_t num_of_bits_mask2(uint8_t n) {
	n = n - ((n >> 1) & 0x55);
	n = (n & 0x33) + ((n >> 2) & 0x33);
	return (((n + (n >> 4)) & 0x0F) * 0x01);
}

uint8_t num_of_bits_mask(uint8_t n) {
	uint8_t num = 0;

	if (n & 1) ++num;
	if (n & 2) ++num;
	if (n & 4) ++num;
	if (n & 8) ++num;
	if (n & 16) ++num;
	if (n & 32) ++num;
	if (n & 64) ++num;
	if (n & 128) ++num;

	return num;
}

uint8_t num_of_bits(uint8_t n) {
	int num = 0;

	while (n) {
		if (n & 1)
			++num;

		n >>= 1;
	}

	return num;
}

void test_num_of_bits() {
	assert(num_of_bits(0) == 0);
	assert(num_of_bits(1) == 1);
	assert(num_of_bits(2) == 1);
	assert(num_of_bits(3) == 2);
	assert(num_of_bits(0xf0) == 4);
	assert(num_of_bits(0x0f) == 4);
	assert(num_of_bits(0xff) == 8);
}

