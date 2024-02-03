/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines data to be used for/by type (array) related functionality.
 *
 * This is auto-included by type_array.h and should not need to be explicitly included.
 */
#ifndef _F_type_array_quantity_h
#define _F_type_array_quantity_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide a static empty quantity.
 *
 * This is intended to represent an empty or disabled quantity.
 */
#ifndef _di_f_quantity_empty_c_
  extern const f_quantity_t f_quantity_empty_c;
#endif // _di_f_quantity_empty_c_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_quantity_h
