#include "city_hash.h"

static const uint64 k_0 = 0xc3a5c85c97cb3127ULL;
static const uint64 k_1 = 0xb492b66fbe98f273ULL;
static const uint64 k_2 = 0x9ae16a3b2f90404fULL;
static const uint64 k_3 = 0xc949d7c7509e6557ULL;

static uint64 UNALIGNED_LOAD_64(const char *p) {
  uint64 result;
  memcpy(&result, p, sizeof(result));
  return result;
}

static uint32 UNALIGNED_LOAD_32(const char *p) {
  uint32 result;
  memcpy(&result, p, sizeof(result));
  return result;
}

#if !defined(WORDS_BIGENDIAN)

#define uint32_in_expected_order(x) (x)
#define uint64_in_expected_order(x) (x)

#else

#ifdef _MSC_VER
#include <stdlib.h>
#define bswap_32(x) _byteswap_ulong(x)
#define bswap_64(x) _byteswap_uint64(x)

#elif defined(__APPLE__)
#include <libkern/OSByteOrder.h>
#define bswap_32(x) OSSwapInt32(x)
#define bswap_64(x) OSSwapInt64(x)

#else
#include <byteswap.h>
#endif

#define uint32_in_expected_order(x) (bswap_32(x))
#define uint64_in_expected_order(x) (bswap_64(x))

#endif

#if !defined(LIKELY)
#if HAVE_BUILTIN_EXPECT
#define LIKELY(x) (__builtin_expect(!!(x), 1))
#else
#define LIKELY(x) (x)
#endif
#endif

static uint64 fetch_64(const char *s) {
  return uint64_in_expected_order(UNALIGNED_LOAD_64(s));
}

static uint32 fetch_32(const char *s) {
  return uint32_in_expected_order(UNALIGNED_LOAD_32(s));
}

static inline uint64 hash_128_to_64(const uint128 x) {
  const uint64 k_mul = 0x9ddfea08eb382d69ULL;
  uint64 a = (uint_128_low_64(x) ^ uint_128_high_64(x)) * k_mul;
  a ^= (a >> 47);
  uint64 b = (uint_128_high_64(x) ^ a) * k_mul;
  b ^= (b >> 47);
  b *= k_mul;

  return b;
}

static uint64 rotate(uint64 val, int shift) {
  return shift == 0 ? val : ((val >> shift) | (val << (64 - shift)));
}

static uint64 rotate_by_at_least_1(uint64 val, int shift) {
  return (val >> shift) | (val << (64 - shift));
}

static uint64 shift_mix(uint64 val) {
  return val ^ (val >> 47);
}

static uint64 hash_len_16(uint64 u, uint64 v) {
  uint128 result;
  result.first = u;
  result.second = v;
  return hash_128_to_64(result);
}

static uint64 hash_len_0_to_16(const char *s, size_t len) {
  if (len > 8) {
    uint64 a = fetch_64(s);
    uint64 b = fetch_64(s + len - 8);
    return hash_len_16(
        a,
        rotate_by_at_least_1(b + len, len)
    ) ^ b;
  }
  if (len >= 4) {
    uint64 a = fetch_32(s);
    return hash_len_16(
        len + (a << 3),
        fetch_32(s + len - 4)
    );
  }
  if (len > 0) {
    uint8 a = s[0];
    uint8 b = s[len >> 1];
    uint8 c = s[len - 1];
    uint32 y = (uint32)(a) + ((uint32)(b) << 8);
    uint32 z = len + ((uint32)(c) << 2);
    return shift_mix(y * k_2 ^ z * k_3) * k_2;
  }

  return k_2;
}

static uint64 hash_len_17_to_32(const char *s, size_t len) {
  uint64 a = fetch_64(s) * k_1;
  uint64 b = fetch_64(s + 8);
  uint64 c = fetch_64(s + len - 8) * k_2;
  uint64 d = fetch_64(s + len - 16) * k_0;

  return hash_len_16(
      rotate(a - b, 43) + rotate(c, 30) + d,
      a + rotate(b ^ k_3, 20) - c + len
  );
}

static uint64 hash_len_33_to_64(const char *s, size_t len) {
  uint64 z = fetch_64(s + 24);
  uint64 a = fetch_64(s) + (len + fetch_64(s + len - 16)) * k_0;
  uint64 b = rotate(a + z, 52);
  uint64 c = rotate(a, 37);

  a += fetch_64(s + 8);
  c += rotate(a, 7);
  a += fetch_64(s + 16);

  uint64 vf = a + z;
  uint64 vs = b + rotate(a, 31) + c;

  a = fetch_64(s + 16) + fetch_64(s + len - 32);
  z = fetch_64(s + len - 8);
  b = rotate(a + z, 52);
  c = rotate(a, 37);

  a += fetch_64(s + len - 24);
  c += rotate(a, 7);
  a += fetch_64(s + len - 16);

  uint64 wf = a + z;
  uint64 ws = b + rotate(a, 31) + c;
  uint64 r = shift_mix((vf + ws) * k_2 + (wf + vs) * k_0);

  return shift_mix(r * k_0 + vs) * k_2;
}

uint128 weak_hash_len_32_with_seeds_6(
    uint64 w, uint64 x, uint64 y, uint64 z, uint64 a, uint64 b
) {
  a += w;

  b = rotate(b + a + z, 21);
  uint64 c = a;

  a += x;
  a += y;

  b += rotate(a, 44);

  uint128 result;
  result.first = (uint64) (a + z);
  result.second = (uint64) (b + c);

  return result;
}

uint128 weak_hash_len_32_with_seeds(
    const char *s, uint64 a, uint64 b
) {
  return weak_hash_len_32_with_seeds_6(
      fetch_64(s),
      fetch_64(s + 8),
      fetch_64(s + 16),
      fetch_64(s + 24),
      a,
      b
  );
}

uint64 city_hash_64(const char *s, size_t len) {
  if (len <= 32) {
    if (len <= 16) {
      return hash_len_0_to_16(s, len);
    } else {
      return hash_len_17_to_32(s, len);
    }
  } else if (len <= 64) {
    return hash_len_33_to_64(s, len);
  }

  uint64 x = fetch_64(s + len - 40);
  uint64 y = fetch_64(s + len - 16) + fetch_64(s + len - 56);
  uint64 z = hash_len_16(
      fetch_64(s + len - 48) + len,
      fetch_64(s + len - 24)
  );

  uint64 temp;
  uint128 v = weak_hash_len_32_with_seeds(s + len - 64, len, z);
  uint128 w = weak_hash_len_32_with_seeds(s + len - 32, y + k_1, x);
  x = x * k_1 + fetch_64(s);

  len = (len - 1) & ~(size_t)(63);
  do {
    x = rotate(x + y + v.first + fetch_64(s + 8), 37) * k_1;
    y = rotate(y + v.second + fetch_64(s + 48), 42) * k_1;

    x ^= w.second;
    y += v.first + fetch_64(s + 40);

    z = rotate(z + w.first, 33) * k_1;

    v = weak_hash_len_32_with_seeds(s, v.second * k_1, x + w.first);
    w = weak_hash_len_32_with_seeds(s + 32, z + w.second, y + fetch_64(s + 16));

    temp = z;
    z = x;
    x = temp;

    s += 64;
    len -= 64;
  } while (len != 0);

  return hash_len_16(
      hash_len_16(v.first, w.first) + shift_mix(y) * k_1 + z,
      hash_len_16(v.second, w.second) + x
  );

  return 0;
}
