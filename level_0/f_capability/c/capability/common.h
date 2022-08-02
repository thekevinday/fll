/**
 * FLL - Level 0
 *
 * Project: Capability
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by capability related functionality.
 *
 * This is auto-included by capability.h and should not need to be explicitly included.
 */
#ifndef _F_capability_common_h
#define _F_capability_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide a typedef of cap_t such that if _di_libcap_ is defined then a stub is used in its place.
 *
 * f_capability_value_type_*:
 *   - effective:   Specify "effective" capability.
 *   - permitted:   Specify "permitted" capability.
 *   - inheritable: Specify "inheritable" capability.
 *
 * f_capability_flag_type_*:
 *   - clear: Clear (remove) the capability.
 *   - set:   Set the capability.
 */
#ifndef _di_f_capability_t_

  enum {
    f_capability_value_type_effective_e = 0,
    f_capability_value_type_permitted_e,
    f_capability_value_type_inheritable_e,
  };

  enum {
    f_capability_flag_type_clear_e = 0,
    f_capability_flag_type_set_e,
  };

  // provide stubs in the event that libcap is disabled.
  #ifdef _di_libcap_
    typedef void * cap_t;
    typedef int cap_flag_t;
    typedef int cap_flag_value_t;
    typedef unsigned int cap_mode_t;
    typedef int cap_value_t;
  #elif defined(_libcap_legacy_only_)
    typedef unsigned int cap_mode_t;
  #endif // _di_libcap_

  typedef cap_t f_capability_t;
  typedef unsigned int f_capability_bits_t;
  typedef cap_flag_t f_capability_flag_t;
  typedef cap_flag_value_t f_capability_flag_value_t;
  typedef cap_mode_t f_capability_mode_t;
  typedef cap_value_t f_capability_value_t;

  #define f_capability_t_initialize 0
  #define f_capability_bits_t_initialize 0
  #define f_capability_flag_t_initialize 0
  #define f_capability_flag_value_t_initialize 0
  #define f_capability_mode_t_initialize 0
  #define f_capability_value_t_initialize 0
#endif // _di_f_capability_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_capability_common_h
