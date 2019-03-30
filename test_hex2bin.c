#include "hex2bin.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

int TEST_hex2bin(void) {

  char buf[32];
  uint8_t data[32];

  struct test_vector_s {
    char *hex;
    unsigned int n;
    unsigned int m;
    unsigned int p;
    int e0;
    unsigned int e1;

  } test_vector[] = {
      /*  0 */ {.hex = "0123456789abcdef",
                .n = 0,
                .m = 8,
                .p = 17,
                .e0 = 8,
                .e1 = 16},
      /*  1 */ {.hex = "0123456789abcdef",
                .n = 0,
                .m = 8,
                .p = 16,
                .e0 = 8,
                .e1 = 16},
      /*  2 */ {.hex = "0123456789abcdef",
                .n = 0,
                .m = 7,
                .p = 17,
                .e0 = 8,
                .e1 = 16},
      /*  3 */ {.hex = "0123456789abcdef",
                .n = 0,
                .m = 9,
                .p = 16,
                .e0 = 8,
                .e1 = 16},
      /*  4 */ {.hex = "0123456789abcdef",
                .n = 10,
                .m = 5,
                .p = 11,
                .e0 = 5,
                .e1 = 10},
      /*  5 */ {.hex = "0x0123456789abcdef",
                .n = 0,
                .m = 8,
                .p = 17,
                .e0 = 8,
                .e1 = 16},
      /*  6 */ {.hex = "0x0123456789abcdef",
                .n = 10,
                .m = 5,
                .p = 17,
                .e0 = 4,
                .e1 = 8},
      /*  7 */ {.hex = "0x0123456789abcdef",
                .n = 10,
                .m = 4,
                .p = 17,
                .e0 = 4,
                .e1 = 8},
      /*  8 */ {.hex = "", .n = 0, .m = 8, .p = 17, .e0 = 0, .e1 = 0},
      /*  9 */ {.hex = "", .n = 0, .m = 0, .p = 17, .e0 = 0, .e1 = 0},
      /* 10 */ {.hex = "0x", .n = 0, .m = 0, .p = 17, .e0 = 0, .e1 = 0},
      /* 11 */ {.hex = "0x", .n = 0, .m = 8, .p = 17, .e0 = 0, .e1 = 0},
      /* 12 */ {.hex = "0xf", .n = 0, .m = 8, .p = 17, .e0 = -1, .e1 = 0},
      /* 13 */ {.hex = "0x*", .n = 0, .m = 8, .p = 17, .e0 = -1, .e1 = 0},
      /* 14 */ {.hex = "0", .n = 0, .m = 8, .p = 17, .e0 = -1, .e1 = 0},
      /* 15 */ {.hex = "x", .n = 0, .m = 8, .p = 17, .e0 = -1, .e1 = 0},
      /* 16 */ {.hex = "zz", .n = 0, .m = 8, .p = 17, .e0 = -1, .e1 = 0},
      /* 17 */ {.hex = "z", .n = 0, .m = 8, .p = 17, .e0 = -1, .e1 = 0},
      /* 18 */ {.hex = "f", .n = 0, .m = 8, .p = 17, .e0 = -1, .e1 = 0},
      /* 19 */ {.hex = "123", .n = 0, .m = 8, .p = 17, .e0 = -1, .e1 = 0},

  };

  setbuf(stdout, NULL);
  for (unsigned int i = 0;
       i < sizeof(test_vector) / sizeof(struct test_vector_s); i++) {
    char *hex = test_vector[i].hex;
    unsigned int n = test_vector[i].n;
    unsigned int m = test_vector[i].m;
    unsigned int p = test_vector[i].p;
    int e0 = test_vector[i].e0;
    unsigned int e1 = test_vector[i].e1;
    fprintf(stdout, "test [%i]---------------:\n", i);
    fprintf(stdout, "In:  `%s`\n", hex);

    int len0 = hex2bin(hex, n, data, m);

    if (e0 != len0) {
      fprintf(stderr, "Expected len0 = %d got %d\n", e0, len0);
      assert(0);
    }

    if (len0 < 0) {
      fprintf(stderr, "ERROR: malformed hex\n");
      continue;
    }
    if (len0 > m) {
      fprintf(stderr, "ERROR: data not big enough\n");
      continue;
    }

    unsigned int len1 = bin2hex(data, len0, buf, p);

    if (e1 != len1) {
      fprintf(stderr, "Expected len1 = %u got %u\n", e1, len1);
      assert(0);
    }

    if (len1 > p) {
      fprintf(stderr, "ERROR: buf not big enough\n");
    }

    fprintf(stdout, "Out: `%s`\n", buf);
    char *ptr = memcmp(hex, "0x", 2) ? hex : hex + 2;
    if (strcmp(ptr, buf) != 0) {
      fprintf(stderr, "ERROR: Hex strings do not match\n");
    }
  }
  return 0;
}
