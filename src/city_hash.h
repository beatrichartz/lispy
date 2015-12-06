#ifndef LISPY_GRAMMAR
#define LISPY_GRAMMAR

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t uint8;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef struct _uint128 uint128;
struct _uint128 {
  uint64 first;
  uint64 second;
};
#define uint_128_low_64(x) 	(x).first
#define uint_128_high_64(x) (x).second

uint64 city_hash_64(const char *buf, size_t len);

#endif
