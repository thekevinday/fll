/**
 * FLL - Level 0
 *
 * Project: Random
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides basic string random capabilities.
 */
#ifndef _F_random_h
#define _F_random_h

// Libc includes.
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>

// FLL-0 includes.
#include <fll/level_0/status.h>
#include <fll/level_0/type.h>
#include <fll/level_0/string.h>

// FLL-0 random includes.
#include <fll/level_0/random/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Set the destination string by reading from the random or urandom entropy source directly.
 *
 * The standard behavior of this is to call random().
 *
 * The random seed should be set by either calling f_random_seed(), f_random_seed_set(), or directly calling random().
 * Calling f_random_seed() or f_random_seed_set() to set the seed is generally safer from a library implementation perspective for situations where the implementation of f_random_seed() or f_random_seed_set() and therefore f_random() is changed from the standard behavior.
 *
 * @param destination
 *   The destination long to write to.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_random_get_
  extern f_status_t f_random_get(long * const destination);
#endif // _di_f_random_get_

/**
 * Set the destination string by reading from the random or urandom entropy source directly.
 *
 * The standard behavior of this is to call getrandom().
 *
 * The behavior of this function might also be replaced with calls to other libraries that are highly security specialized.
 * If this is done, the meaning behind the flags passed should not be changed.
 *
 * This calls the Linux-specific getrandom() by default.
 * If this is not available or pure POSIX is desired, then the implementation must handle accessing the /dev/random and /dev/urandom themselves (or something equivalent).
 *
 * @param flag
 *   The flags to be passed to getrandom().
 *
 *   Flag bits:
 *     - F_random_seed_flag_block_not_d: Does not block when getting the bits.
 *     - F_random_seed_flag_source_d:    Random data is taken from the random source, such as /dev/random and not the urandom source.
 * @param length
 *   The size within the destination string to copy.
 *   The standard max size is 255.
 *   This length must not exceed the size allocated in destination or buffer overrun or other security problems may occur.
 * @param destination
 *   The destination string to write to.
 *   The size of this is not dynamically allocated.
 *   The caller must assure that the size allocated is not smaller than the size specified in the length parameter.
 *
 *   Must not be NULL.
 * @param total
 *   (optional) The total number of bytes actually read.
 *   This value is not changed on error.
 *
 *   Set to NULL to not use.
 *
 * @return
 *   F_okay on success.
 *
 *   F_again (with error bit) when in non-blocking mode but reading entropy source would block (such as when the entropy source is busy).
 *   F_buffer (with error bit) if the address represented by the buffer is outside accessible address space.
 *   F_interrupt (with error bit) if stopping due to an interrupt.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_support_not (with error bit) if the running kernel does not support the getrandom() call.
 */
#ifndef _di_f_random_read_
  extern f_status_t f_random_read(const unsigned int flag, const f_number_unsigned_t length, f_string_t * const destination, ssize_t * const total);
#endif // _di_f_random_read_

/**
 * Set the random seed from random entropy, generally for the standard POSIX random() use cases.
 *
 * The standard behavior of this is to call getrandom().
 *
 * The behavior of this function might also be replaced with calls to other libraries that are highly security specialized.
 * If this is done, the meaning behind the flags passed should not be changed.
 *
 * This calls the Linux-specific getrandom() by default.
 * If this is not available or pure POSIX is desired, then the implementation must handle accessing the /dev/random and /dev/urandom themselves (or something equivalent).
 *
 * @param flag
 *   The flags to be passed to getrandom().
 *
 *   Flag bits:
 *     - F_random_seed_flag_block_not_d: Does not block when getting the bits.
 *     - F_random_seed_flag_source_d:    Random data is taken from the random source, such as /dev/random and not the urandom source.
 *
 * @return
 *   F_okay on success.
 *
 *   F_again (with error bit) when in non-blocking mode but reading entropy source would block (such as when the entropy source is busy).
 *   F_buffer (with error bit) if the address represented by the buffer is outside accessible address space.
 *   F_interrupt (with error bit) if stopping due to an interrupt.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_support_not (with error bit) if the running kernel does not support the getrandom() call.
 *
 * @see getrandom()
 * @see srandom()
 */
#ifndef _di_f_random_seed_
  extern f_status_t f_random_seed(const unsigned int flag);
#endif // _di_f_random_seed_

/**
 * Set the random seed manually using the given seed value, generally for the standard POSIX random() use cases.
 *
 * The standard behavior of this is to call srandom().
 *
 * The behavior of this function might also be replaced with calls to other libraries that are highly security specialized.
 *
 * @param seed
 *   The seed value to assign.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_random_seed_set_
  extern f_status_t f_random_seed_set(unsigned int seed);
#endif // _di_f_random_seed_set_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_random_h
