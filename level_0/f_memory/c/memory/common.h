/**
 * FLL - Level 0
 *
 * Project: Memory
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines memory common data.
 *
 * This is auto-included by memory.h and should not need to be explicitly included.
 */
#ifndef _F_memory_common_h
#define _F_memory_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check to make sure these two macros are not defined at the same time.
 *
 * If _f_memory_FORCE_secure_memory_ is defined, then all to-be deallocated address spaces are set to 0 before freeing or resizing.
 * If _f_memory_FORCE_fast_memory_ is defined, then all to-be deallocated address spaces remain unchanged before freeing or resizing.
 */
#if defined(_f_memory_FORCE_secure_memory_) && defined(_f_memory_FORCE_fast_memory_)
  #error You cannot define both _f_memory_FORCE_fast_memory_ and _f_memory_FORCE_secure_memory_ at the same time.
#endif // _f_memory_FORCE_secure_memory_

/**
 * Default allocation step.
 *
 * Everytime some array needs a single new element, reallocated by this amount.
 *
 * Normally, this should be small, but when a large number of singular allocations are made, the overhead can be reduced by not having to reallocate space as often.
 * The problem then is that the more space allocated beyond what is initially needed will waste precious memory.
 * Change this if you know your application can afford to reduce the allocation overhead at the cost of more memory.
 *
 * Other projects may provide their own values.
 */
#ifndef _di_f_memory_default_d_
  #define F_memory_default_allocation_large_d 64
  #define F_memory_default_allocation_small_d 8
#endif // _di_f_memory_default_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_memory_common_h
