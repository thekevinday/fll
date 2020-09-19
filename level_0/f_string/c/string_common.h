/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_common_h
#define _F_string_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * BUG: for whatever reason strnlen is considered not included with -Wall, even with __USE_GNU defined.
 *      therefore this gets defined here.
 */
#ifdef _en_BUG_strnlen_
  extern size_t strnlen (const char *string, size_t max_length);
#endif // _en_BUG_strnlen_

/**
 * Define the end of line character.
 * FLL forbids '\r' and '\r\n' as end of line characters, \r will be silently ignored.
 */
#ifndef _di_f_string_has_eol_
  #define f_string_eol "\n"
#endif // _di_f_string_has_eol_

#ifndef _di_f_string_has_placeholder_
  #define f_string_placeholder "\0"
#endif // _di_f_string_has_placeholder_

#ifndef _di_string_format_pointers_
  #define string_format_string             "%s"
  #define string_format_character          "%c"
  #define string_format_wide_string        "%ls"
  #define string_format_wide_character     "%lc"
  #define string_format_integer            "%i"
  #define string_format_unsigned           "%u"
  #define string_format_double             "%d"
  #define string_format_float              "%f"
  #define string_format_short_integer      "%hi"
  #define string_format_short_unsigned     "%hu"
  #define string_format_long_integer       "%li"
  #define string_format_long_unsigned      "%lu"
  #define string_format_long_double        "%ld"
  #define string_format_long_long_integer  "%lli"
  #define string_format_long_long_unsigned "%llu"
#endif // _di_string_format_pointers_

#ifndef _di_f_array_t_length_printf_
  #define f_array_length_printf       string_format_integer
  #define f_array_length_short_printf string_format_short_integer
  #define f_array_length_long_printf  string_format_long_integer
#endif // _di_f_array_t_length_printf_

/**
 * Define the basic string type.
 *
 * Dynamic allocation macros are provided, but it is recommended to utilize the f_string_dynamic_t for dynamic allocation.
 */
#ifndef _di_f_string_t_
  typedef char *f_string_t;

  #define f_string_t_initialize 0

  #define f_macro_string_t_new(status, string, length)     status = f_memory_new((void **) & string, sizeof(f_string_t), length)
  #define f_macro_string_t_delete(status, string, length)  status = f_memory_delete((void **) & string, sizeof(f_string_t), length)
  #define f_macro_string_t_destroy(status, string, length) status = f_memory_destroy((void **) & string, sizeof(f_string_t), length)

  #define f_macro_string_t_delete_simple(string, length)  f_memory_delete((void **) & string, sizeof(f_string_t), length)
  #define f_macro_string_t_destroy_simple(string, length) f_memory_destroy((void **) & string, sizeof(f_string_t), length)

  #define f_macro_string_t_resize(status, string, old_length, new_length) \
    status = f_memory_resize((void **) & string, sizeof(f_string_t), old_length, new_length)

  #define f_macro_string_t_adjust(status, string, old_length, new_length) \
    status = f_memory_adjust((void **) & string, sizeof(f_string_t), old_length, new_length)
#endif // _di_f_string_t_

#ifndef _di_f_string_length_t_
  typedef f_number_unsigned_t f_string_length_t;

  // string size is set to (size - 4) to compensate for UTF-8 4-byte character such that it can easily act as a (size - 1) regardless of UTF-8.
  #define f_string_length_t_size     0xfffffffffffffffb
  #define f_string_length_t_size_max f_number_t_size_max_unsigned

  #define f_string_length_t_printf string_format_long_integer
#endif // _di_f_string_length_t_

/**
 * A structure containing an array of string lengths.
 *
 * array: the array of string lengths.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_lengths_t_
  typedef struct {
    f_string_length_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_lengths_t;

  #define f_string_lengths_t_initialize { 0, 0, 0 }

  #define f_macro_string_lengths_t_clear(lengths) f_macro_memory_structure_t_clear(lengths)

  #define f_macro_string_lengths_t_new(status, lengths, length) f_macro_memory_structure_t_new(status, lengths, f_string_length_t, length)

  #define f_macro_string_lengths_t_delete(status, lengths)  f_macro_memory_structure_t_delete(status, lengths, f_string_length_t)
  #define f_macro_string_lengths_t_destroy(status, lengths) f_macro_memory_structure_t_destroy(status, lengths, f_string_length_t)

  #define f_macro_string_lengths_t_delete_simple(lengths)  f_macro_memory_structure_t_delete_simple(lengths, f_string_length_t)
  #define f_macro_string_lengths_t_destroy_simple(lengths) f_macro_memory_structure_t_destroy_simple(lengths, f_string_length_t)

  #define f_macro_string_lengths_t_resize(status, lengths, new_length) f_macro_memory_structure_t_resize(status, lengths, f_string_length_t, new_length)
  #define f_macro_string_lengths_t_adjust(status, lengths, new_length) f_macro_memory_structure_t_adjust(status, lengths, f_string_length_t, new_length)
#endif // _di_f_string_lengths_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_common_h
