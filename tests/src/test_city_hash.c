#include "test_city_hash.h"

// Initialize data to pseudorandom values.
void setup_data() {
  uint64 a = 9;
  uint64 b = 777;
	int i;
  for (i = 0; i < k_data_size; i++) {
    a = (a ^ (a >> 41)) * k_0 + b;
    b = (b ^ (b >> 41)) * k_0 + i;
    uint8 u = b >> 37;
    memcpy(data + i, &u, 1);  // uint8 -> char
  }
}

void test_city_hash_64(test *t) {
  setup_data();
  int i;
  for (i = 0; i < k_test_size; i++) {
    uint64 expected = city_hash_testdata[i][0];
    int last = i == k_test_size - 1;
    uint64 actual = city_hash_64(
        last ? data : data + i * i,
        last ? k_data_size : i
    );

    test_assert(
        expected == actual,
        "expected %llx to equal %llx",
        actual,
        expected
    );
  }
}

void test_city_hash_64_with_seed(test *t) {
}
void test_city_hash_64_with_two_seeds(test *t) {
}
void test_city_hash_128(test *t) {
}
void test_city_hash_128_with_seed(test *t) {
}
