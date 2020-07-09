/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines set data to be used for/by project fss.
 *
 * This is auto-included by fss.h and should not need to be explicitly included.
 */
#ifndef _F_fss_quoted_h
#define _F_fss_quoted_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Types for FSS quoted.
 */
#ifndef _di_f_fss_quoted_type_
  enum {
    f_fss_quoted_type_single = 1,
    f_fss_quoted_type_double,
  };
#endif // _di_f_fss_quoted_type_

/**
 * Designate an fss quoted.
 */
#ifndef _di_f_fss_quoted_
  typedef uint8_t f_fss_quoted;
#endif // _di_f_fss_quoted_

/**
 * An array of f_fss_quoted.
 *
 * array: the array of fss quoted.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_fss_quoteds_
  typedef struct {
    f_fss_quoted *array;

    f_array_length size;
    f_array_length used;
  } f_fss_quoteds;

  #define f_fss_quoteds_initialize {0, 0, 0}

  #define f_macro_fss_quoteds_clear(quoteds) f_macro_memory_structure_clear(quoteds)

  #define f_macro_fss_quoteds_new(status, quoteds, length) f_macro_memory_structure_new(status, quoteds, f_fss_quoted, length)

  #define f_macro_fss_quoteds_delete(status, quoteds)  f_macro_memory_structure_delete(status, quoteds, f_fss_quoted)
  #define f_macro_fss_quoteds_destroy(status, quoteds) f_macro_memory_structure_destroy(status, quoteds, f_fss_quoted)

  #define f_macro_fss_quoteds_delete_simple(quoteds)  f_macro_memory_structure_delete_simple(quoteds, f_fss_quoted)
  #define f_macro_fss_quoteds_destroy_simple(quoteds) f_macro_memory_structure_destroy_simple(quoteds, f_fss_quoted)

  #define f_macro_fss_quoteds_resize(status, quoteds, new_length) f_macro_memory_structure_resize(status, quoteds, f_fss_quoted, new_length)
  #define f_macro_fss_quoteds_adjust(status, quoteds, new_length) f_macro_memory_structure_adjust(status, quoteds, f_fss_quoted, new_length)
#endif // _di_f_fss_quoteds_

/**
 * An array of f_fss_quoteds.
 *
 * array: the array of fss quoteds.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_fss_quotedss_
  typedef struct {
    f_fss_quoteds *array;

    f_array_length size;
    f_array_length used;
  } f_fss_quotedss;

  #define f_fss_quotedss_initialize {0, 0, 0}

  #define f_macro_fss_quotedss_clear(quotedss) f_macro_memory_structures_clear(quotedss)

  #define f_macro_fss_quotedss_new(status, quotedss, length) f_macro_memory_structures_new(status, quotedss, f_fss_quoteds, length)

  #define f_macro_fss_quotedss_delete(status, quotedss)  f_macro_memory_structures_delete(status, quotedss, f_fss_quoted, f_fss_quoteds)
  #define f_macro_fss_quotedss_destroy(status, quotedss) f_macro_memory_structures_destroy(status, quotedss, f_fss_quoted, f_fss_quoteds)

  #define f_macro_fss_quotedss_delete_simple(quotedss)  f_macro_memory_structures_delete_simple(quotedss, f_fss_quoted, f_fss_quoteds)
  #define f_macro_fss_quotedss_destroy_simple(quotedss) f_macro_memory_structures_destroy_simple(quotedss, f_fss_quoted, f_fss_quoteds)

  #define f_macro_fss_quotedss_resize(status, quotedss, new_length) f_macro_memory_structures_resize(status, quotedss, f_fss_quoted, f_fss_quoteds, new_length, f_array_length)
  #define f_macro_fss_quotedss_adjust(status, quotedss, new_length) f_macro_memory_structures_adjust(status, quotedss, f_fss_quoted, f_fss_quoteds, new_length, f_array_length)
#endif // _di_f_fss_quotedss_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_quoted_h
