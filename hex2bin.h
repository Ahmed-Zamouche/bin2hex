#ifndef HEX2BIN_H
#define HEX2BIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
/**
 * Converts an array of bytes to a null terminated hex string.
 * @param: [in] bin pointer to the array of bytes
 * @param: [in] n length in bytes of bin
 * @param: [out] hex pointer to the buffer used for writing the result
 * @param: [out] m length in bytes of the output buffer hex. Must be at least
 * 2*n+1
 * @return: the number of characters written (excluding the null byte). if m is
 * not enough return the number of characters that would have been
 * written(excluding the null byte).
 */
size_t bin2hex(const uint8_t *bin, size_t n, char *hex, size_t m);
/**
 * Convert a hex string  to an array of bytes.
 * @param: [in] hex pointer to hex string
 * @param: [in] n length in bytes of hex string. n can be zero for null
 terminated strings.
 * @param: [out] bin pointer to the buffer used for writing the result
 * @param: [out] m length in byte of the output buffer. Must be at least 2*n.
 * @return: the number of bytes written. if m is not enough return the number
 * of characters that would have been written. a negative value indicates that
 * hex is a malformat hex string.
 */
ssize_t hex2bin(const char *hex, size_t n, uint8_t *bin, size_t m);

#ifdef __cplusplus
}
#endif

#endif
