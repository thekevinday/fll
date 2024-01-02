/**
 * FLL - Level 0
 *
 * Project: Random
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project random.
 *
 * This is auto-included by random.h and should not need to be explicitly included.
 */
#ifndef _F_random_common_h
#define _F_random_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Defines associated with random seed flags.
 *
 * F_random_seed_flag_*:
 *   - block_not: Does not block when getting the bits.
 *   - insecure:  Use insecure, aka non-cryptographic, random bytes.
 *   - source:    Random data is taken from the random source, such as /dev/random and not the urandom source.
 */
#ifndef _di_f_random_seed_flag_d_
  #define F_random_seed_flag_block_not_d GRND_NONBLOCK
  #define F_random_seed_flag_source_d    GRND_RANDOM

  #ifdef GRND_INSECURE
    #define F_random_seed_flag_insecure_d GRND_INSECURE
  #else
    #define F_random_seed_flag_insecure_d 0x0004
  #endif // GRND_INSECURE
#endif // _di_f_random_seed_flag_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_random_common_h
