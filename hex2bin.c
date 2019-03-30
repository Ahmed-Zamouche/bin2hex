#include "hex2bin.h"

#include <stdio.h>
#include <string.h>

#define _T(a) L##a
//#define _T(a) a

static inline int hex2byte(char c) {
  return (c >= _T('0') && c <= _T('9'))
             ? (c)-_T('0')
             : (c >= _T('A') && c <= _T('F'))
                   ? (c)-_T('A') + 10
                   : (c >= _T('a') && c <= _T('f')) ? (c)-_T('a') + 10 : 0;
}

static inline int byte2hex(char c) {
  return ((c < 10) ? (c) + _T('0') : (c)-10 + _T('a'));
}

static inline int is_hex(char c) {
  return ((c >= _T('0') && c <= _T('9')) || (((c >= _T('a') && c <= _T('f'))) ||
                                             ((c >= _T('A') && c <= _T('F')))));
}

size_t bin2hex(const uint8_t *bin, size_t n, char *hex, size_t m) {

  size_t olen = (n << 1);

  if (m < (olen + 1)) {
    return olen;
  }

  for (size_t i = 0; i < n; i++) {
    size_t j = (i << 1);
    uint8_t byte = bin[i];

    uint8_t hbyte = (byte & 0xf0) >> 4;
    uint8_t lbyte = byte & 0xf;

    hex[j] = byte2hex(hbyte);
    hex[j + 1] = byte2hex(lbyte);
  }

  hex[olen] = '\0';

  return olen;
}

ssize_t hex2bin(const char *hex, size_t n, uint8_t *bin, size_t m) {

  n = (n == 0) ? strlen(hex) : n;

  if (n % 2 != 0) { /*hex string not multiple of 2*/
    return -1;
  }

  if (memcmp(hex, "0x", 2) == 0 && n >= 2) { /* hex string has 0x prefix */
    hex += 2;
    n -= 2;
  }

  size_t olen = (n >> 1);

  if (olen > m) { /*bin not large enough*/
    return olen;
  }

  for (size_t i = 0; i < n; i += 2) {
    char hbyte = hex[i];
    char lbyte = hex[i + 1];

    if (!is_hex(hbyte) || !is_hex(lbyte)) {
      /* invalid character */
      return -1;
    }
    bin[(i >> 1)] = (uint8_t)(hex2byte(hbyte) << 4 | hex2byte(lbyte));
  }

  return olen;
}
