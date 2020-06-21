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

#ifndef _di_f_array_length_printf_
  #define f_array_length_printf       string_format_integer
  #define f_array_length_short_printf string_format_short_integer
  #define f_array_length_long_printf  string_format_long_integer
#endif // _di_f_array_length_printf_

/**
 * define the basic string type.
 */
#ifndef _di_f_string_
  typedef char *f_string;

  #define f_string_initialize 0

  #define f_macro_string_new(status, string, length)     status = f_memory_new((void **) & string, sizeof(f_string), length)
  #define f_macro_string_delete(status, string, length)  status = f_memory_delete((void **) & string, sizeof(f_string), length)
  #define f_macro_string_destroy(status, string, length) status = f_memory_destroy((void **) & string, sizeof(f_string), length)

  #define f_macro_string_delete_simple(string, length)  f_memory_delete((void **) & string, sizeof(f_string), length)
  #define f_macro_string_destroy_simple(string, length) f_memory_destroy((void **) & string, sizeof(f_string), length)

  #define f_macro_string_resize(status, string, old_length, new_length) \
    status = f_memory_resize((void **) & string, sizeof(f_string), old_length, new_length)

  #define f_macro_string_adjust(status, string, old_length, new_length) \
    status = f_memory_adjust((void **) & string, sizeof(f_string), old_length, new_length)
#endif // _di_f_string_

#ifndef _di_f_string_length_
  typedef f_number_unsigned f_string_length;

  // string size is set to (size - 4) to compensate for UTF-8 4-byte character such that it can easily act as a (size - 1) regardless of UTF-8.
  #define f_string_length_size     0xfffffffffffffffb
  #define f_string_length_size_max f_type_number_size_max_unsigned

  #define f_string_length_printf string_format_long_integer
#endif // _di_f_string_length_

/**
 * A structure containing an array of string lengths.
 *
 * array: the array of string lengths.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_lengths_
  typedef struct {
    f_string_length *array;

    f_array_length size;
    f_array_length used;
  } f_string_lengths;

  #define f_string_lengths_initialize { 0, 0, 0 }

  #define f_macro_string_lengths_clear(lengths) f_macro_memory_structure_clear(lengths)

  #define f_macro_string_lengths_new(status, lengths, length) f_macro_memory_structure_new(status, lengths, f_string_length, length)

  #define f_macro_string_lengths_delete(status, lengths)  f_macro_memory_structure_delete(status, lengths, f_string_length)
  #define f_macro_string_lengths_destroy(status, lengths) f_macro_memory_structure_destroy(status, lengths, f_string_length)

  #define f_macro_string_lengths_delete_simple(lengths)  f_macro_memory_structure_delete_simple(lengths, f_string_length)
  #define f_macro_string_lengths_destroy_simple(lengths) f_macro_memory_structure_destroy_simple(lengths, f_string_length)

  #define f_macro_string_lengths_resize(status, lengths, new_length) f_macro_memory_structure_resize(status, lengths, f_string_length, new_length)
  #define f_macro_string_lengths_adjust(status, lengths, new_length) f_macro_memory_structure_adjust(status, lengths, f_string_length, new_length)
#endif // _di_f_string_lengths_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_common_h
