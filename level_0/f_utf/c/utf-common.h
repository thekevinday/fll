/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by project utf.
 *
 * This is auto-included by utf.h and should not need to be explicitly included.
 */
#ifndef _F_utf_common_h
#define _F_utf_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Define the UTF-8 bytes.
 *
 * The bytes are for checking a single 8-bit character value (specifically, checking the first bits).
 *
 * The byte offs are used for determining the character width of a UTF-8 character.
 *
 * The f_utf_byte_is method will return non-zero if the character is a UTF-8 character of any width.
 *
 * The f_utf_byte_1 is specifically used only on UTF-8 fragments.
 * For example, with the 2-byte-wide UTF-8 character '1100x xxxx 10yy yyyy', the 8-byte block '10yy yyyy' would be a fragment.
 *
 * The f_macro_utf_byte_is_* macros are used to determine a width of the character (either 1, 2, 3, or 4, respectively).
 *
 * The f_macro_utf_byte_width macro determines a width of the character.
 * The f_macro_utf_byte_width_is is identical to f_macro_utf_byte_width, except it returns 0 when character is not UTF-8.
 */
#ifndef _di_f_utf_byte_
  #define f_utf_byte_1 0x80 // 1000 0000
  #define f_utf_byte_2 0xc0 // 1100 0000
  #define f_utf_byte_3 0xe0 // 1110 0000
  #define f_utf_byte_4 0xf0 // 1111 0000

  #define f_utf_byte_off_1 0xc0 // 1100 0000
  #define f_utf_byte_off_2 0xe0 // 1110 0000
  #define f_utf_byte_off_3 0xf0 // 1111 0000
  #define f_utf_byte_off_4 0xf8 // 1111 1000

  #define f_macro_utf_byte_is(character) ((character) & f_utf_byte_1)

  #define f_macro_utf_byte_is_1(character) (((character) & f_utf_byte_off_1) == f_utf_byte_1) // (10xx xxxx & 1100 0000) == 1000 0000
  #define f_macro_utf_byte_is_2(character) (((character) & f_utf_byte_off_2) == f_utf_byte_2) // (110x xxxx & 1110 0000) == 1100 0000
  #define f_macro_utf_byte_is_3(character) (((character) & f_utf_byte_off_3) == f_utf_byte_3) // (1110 xxxx & 1111 0000) == 1110 0000
  #define f_macro_utf_byte_is_4(character) (((character) & f_utf_byte_off_4) == f_utf_byte_4) // (1111 0xxx & 1111 1000) == 1111 0000

  #define f_macro_utf_byte_width(character)    ((!f_macro_utf_byte_is(character) || f_macro_utf_byte_is_1(character)) ? 1 : (f_macro_utf_byte_is_2(character) ? 2 : (f_macro_utf_byte_is_3(character) ? 3 : 4)))
  #define f_macro_utf_byte_width_is(character) (f_macro_utf_byte_is(character) ? (f_macro_utf_byte_is_1(character) ? 1 : (f_macro_utf_byte_is_2(character) ? 2 : (f_macro_utf_byte_is_3(character) ? 3 : 4))) : 0)
#endif // _di_f_utf_byte_

/**
 * Provide a basic UTF-8 character as a single 4-byte variable.
 *
 * This is intended to be used when a single variable is desired to represent a 1-byte, 2-byte, 3-byte, or even 4-byte character.
 *
 * This "character" type is stored as a big-endian 4-byte integer (32-bits).
 * A helper function, f_utf_is_big_endian(), is provided to detect system endianness so that character arrays (int8_t []) can be correctly processed.
 *
 * The byte structure is intended to be read left to right.
 *
 * The f_macro_utf_character_t_mask_byte_* are used to get the entire character set fo a given width.
 *
 * The f_macro_utf_character_t_mask_char_* are used to get a specific UTF-8 block as a single character range.
 *
 * The f_macro_utf_character_t_to_char_* are used to convert a f_utf_character_t into a int8_t, for a given 8-bit block.
 *
 * The f_macro_utf_character_t_from_char_* are used to convert a int8_t into part of a f_utf_character_t, for a given 8-bit block.
 *
 * The f_macro_utf_character_t_width is used to determine the width of the UTF-8 character based on f_macro_utf_byte_width.
 * The f_macro_utf_character_t_width_is is used to determine the width of the UTF-8 character based on f_macro_utf_byte_width_is.
 *
 * @see f_utf_is_big_endian()
 */
#ifndef _di_f_utf_character_t_
  typedef uint32_t f_utf_character_t;

  #define f_utf_character_mask_byte_1 0xff000000 // 1111 1111, 0000 0000, 0000 0000, 0000 0000
  #define f_utf_character_mask_byte_2 0xffff0000 // 1111 1111, 1111 1111, 0000 0000, 0000 0000
  #define f_utf_character_mask_byte_3 0xffffff00 // 1111 1111, 1111 1111, 1111 1111, 0000 0000
  #define f_utf_character_mask_byte_4 0xffffffff // 1111 1111, 1111 1111, 1111 1111, 1111 1111

  #define f_utf_character_mask_char_1 0xff000000 // 1111 1111, 0000 0000, 0000 0000, 0000 0000
  #define f_utf_character_mask_char_2 0x00ff0000 // 0000 0000, 1111 1111, 0000 0000, 0000 0000
  #define f_utf_character_mask_char_3 0x0000ff00 // 0000 0000, 0000 0000, 1111 1111, 0000 0000
  #define f_utf_character_mask_char_4 0x000000ff // 0000 0000, 0000 0000, 0000 0000, 1111 1111

  #define f_macro_utf_character_t_to_char_1(character) (((character) & f_utf_character_mask_char_1) >> 24) // grab first byte.
  #define f_macro_utf_character_t_to_char_2(character) (((character) & f_utf_character_mask_char_2) >> 16) // grab second byte.
  #define f_macro_utf_character_t_to_char_3(character) (((character) & f_utf_character_mask_char_3) >> 8)  // grab third byte.
  #define f_macro_utf_character_t_to_char_4(character) ((character) & f_utf_character_mask_char_4)         // grab fourth byte.

  #define f_macro_utf_character_t_from_char_1(character) (((character) << 24) & f_utf_character_mask_char_1) // shift to first byte.
  #define f_macro_utf_character_t_from_char_2(character) (((character) << 16) & f_utf_character_mask_char_2) // shift to second byte.
  #define f_macro_utf_character_t_from_char_3(character) (((character) << 8) & f_utf_character_mask_char_3)  // shift to third byte.
  #define f_macro_utf_character_t_from_char_4(character) ((character) & f_utf_character_mask_char_4)         // shift to fourth byte.

  #define f_macro_utf_character_t_width(character)    (f_macro_utf_byte_width(f_macro_utf_character_t_to_char_1(character)))
  #define f_macro_utf_character_t_width_is(character) (f_macro_utf_byte_width_is(f_macro_utf_character_t_to_char_1(character)))
#endif // _di_f_utf_character_t_

#ifndef _di_f_utf_character_t_codes_
  #define f_utf_character_t_eol         0x0a000000 // 0000 1010, 0000 0000, 0000 0000, 0000 0000
  #define f_utf_character_t_eos         0x00000000 // 0000 0000, 0000 0000, 0000 0000, 0000 0000
  #define f_utf_character_t_placeholder 0x00000000 // 0000 0000, 0000 0000, 0000 0000, 0000 0000
#endif // _di_f_utf_character_t_codes_

/**
 * Provide a UTF-8 characters set to 4-bits wide as a string.
 */
#ifndef _di_f_utf_string_t_
  typedef f_utf_character_t *f_utf_string_t;

  #define f_utf_string_t_size_max   f_number_t_size_unsigned
  #define f_utf_string_t_initialize f_utf_character_t_eos

  #define f_macro_utf_string_t_new(status, string, length)   status = f_memory_new((void **) & string, sizeof(f_utf_string_t), length)

  #define f_macro_utf_string_t_delete(status, string, size)  status = f_memory_delete((void **) & string, sizeof(f_utf_string_t), size)
  #define f_macro_utf_string_t_destroy(status, string, size) status = f_memory_destroy((void **) & string, sizeof(f_utf_string_t), size)

  #define f_macro_utf_string_t_resize(status, string, old_length, new_length) status = f_memory_resize((void **) & string, sizeof(f_utf_string_t), old_length, new_length)
  #define f_macro_utf_string_t_adjust(status, string, old_length, new_length) status = f_memory_adjust((void **) & string, sizeof(f_utf_string_t), old_length, new_length)
#endif // _di_f_utf_string_t_

/**
 * Provide a type specifically for UTF-8 strings.
 */
#ifndef _di_f_utf_string_length_t_
  typedef f_number_unsigned_t f_utf_string_length_t;

  #define f_utf_string_length_t_size     0xfffffffffffffffe
  #define f_utf_string_length_t_size_max f_number_t_size_max_unsigned

  #define f_macro_utf_string_length_t_new(status, string, length)    status = f_memory_new((void **) & string, sizeof(f_utf_string_length_t), length)

  #define f_macro_utf_string_length_t_delete(status, string, length) status = f_memory_delete((void **) & string, sizeof(f_utf_string_length_t), length)
  #define f_macro_utf_string_length_t_destroy(status, string, size)  status = f_memory_destroy((f_void_P *) & string, sizeof(f_utf_string_length_t), size)

  #define f_macro_utf_string_length_t_resize(status, length, old_length, new_length) status = f_memory_resize((void **) & length, sizeof(f_utf_string_length_t), old_length, new_length)
  #define f_macro_utf_string_length_t_adjust(status, length, old_length, new_length) status = f_memory_adjust((void **) & length, sizeof(f_utf_string_length_t), old_length, new_length)
#endif // _di_f_utf_string_length_t_

/**
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_lengths_t_
  typedef struct {
    f_utf_string_length_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_utf_string_lengths_t;

  #define f_utf_string_lengths_t_initialize { 0, 0, 0 }

  #define f_macro_utf_string_lengths_t_clear(lengths) f_macro_memory_structure_t_clear(lengths)

  #define f_macro_utf_string_lengths_t_new(status, lengths, length) f_macro_memory_structure_t_new(status, lengths, f_utf_string_length_t, length)

  #define f_macro_utf_string_lengths_t_delete(status, lengths) f_macro_memory_structure_t_delete(status, lengths, f_utf_string_length_t)
  #define f_macro_utf_string_lengths_t_destroy(status, lengths) f_macro_memory_structure_t_destroy(status, lengths, f_utf_string_length_t)

  #define f_macro_utf_string_lengths_t_resize(status, lengths, new_length) f_macro_memory_structure_t_resize(status, lengths, f_utf_string_length_t, new_length)
  #define f_macro_utf_string_lengths_t_adjust(status, lengths, new_length) f_macro_memory_structure_t_adjust(status, lengths, f_utf_string_length_t, new_length)
#endif // _di_f_utf_string_lengths_t_

/**
 * Designates a start and stop position that represents a sub-string inside of some parent string.
 * use this to avoid resizing, restructuring, and reallocating the parent string to separate the sub-string.
 *
 * A special f_macro_utf_string_range_t_initialize() is provided for the special purpose of easily initialize a static string range.
 */
#ifndef _di_f_utf_string_range_t_
  typedef struct {
    f_utf_string_length_t start;
    f_utf_string_length_t stop;
  } f_utf_string_range_t;

  #define f_utf_string_range_t_initialize { 1, 0 }

  #define f_macro_utf_string_range_t_initialize(length) { length ? 0 : 1, length ? length - 1 : 0 }

  #define f_macro_utf_string_range_t_new(status, utf_string_range, length)   status = f_memory_new((void **) & utf_string_range, sizeof(f_utf_string_range_t), length)
  #define f_macro_utf_string_range_t_delete(status, utf_string_range, size)  status = f_memory_delete((void **) & utf_string_range, sizeof(f_utf_string_range_t), size)
  #define f_macro_utf_string_range_t_destroy(status, utf_string_range, size) status = f_memory_destroy((void **) & utf_string_range, sizeof(f_utf_string_range_t), size)

  #define f_macro_utf_string_range_t_resize(status, utf_string_range, old_length, new_length) \
    status = f_memory_resize((void **) & utf_string_range, sizeof(f_utf_string_range_t), old_length, new_length)

  #define f_macro_utf_string_range_t_adjust(status, utf_string_range, old_length, new_length) \
    status = f_memory_adjust((void **) & utf_string_range, sizeof(f_utf_string_range_t), old_length, new_length)
#endif // _di_f_utf_string_range_t_

/**
 * An array of string ranges.
 *
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_ranges_t_
  typedef struct {
    f_utf_string_range_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_utf_string_ranges_t;

  #define f_utf_string_ranges_t_initialize {0, 0, 0}

  #define f_clear_utf_string_t_ranges(ranges) f_macro_memory_structure_t_clear(ranges)

  #define f_macro_utf_string_range_t_news(status, ranges, length) f_macro_memory_structure_t_new(status, ranges, f_utf_string_range_t, length)

  #define f_macro_utf_string_range_t_deletes(status, ranges) f_macro_memory_structure_t_delete(status, ranges, f_utf_string_range_t)
  #define f_macro_utf_string_range_t_destroys(status, ranges) f_macro_memory_structure_t_destroy(status, ranges, f_utf_string_range_t)

  #define f_macro_utf_string_range_t_resizes(status, ranges, new_length) f_macro_memory_structure_t_resize(status, ranges, f_utf_string_range_t, new_length)
  #define f_macro_utf_string_range_t_adjusts(status, ranges, new_length) f_macro_memory_structure_t_adjust(status, ranges, f_utf_string_range_t, new_length)
#endif // _di_f_utf_string_ranges_t_

/**
 * Store string quantity.
 *
 * Similar to f_utf_string_range_t, except total is relative to start and is not an absolute stop position.
 *
 * Two common uses for when total is 0 is:
 * 1) Exactly that, process a total of 0 strings bytes.
 * 2) Process with no limit, aka infinite.
 *
 * start: The position where the string starts (based on some string/buffer).
 * total: The total number of elements within that string/buffer the quantity represents.
 */
#ifndef _di_f_utf_string_quantity_t_
  typedef struct {
    f_utf_string_length_t start;
    f_utf_string_length_t total;
  } f_utf_string_quantity_t;

  #define f_utf_string_quantity_t_initialize { 0, 0 }
#endif // _di_f_utf_string_quantity_t_

/**
 * An array of string quantities.
 *
 * array: the array of string quantities.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_quantitys_t_
  typedef struct {
    f_utf_string_quantity_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_utf_string_quantitys_t;

  #define f_utf_string_quantitys_t_initialize {0, 0, 0}

  #define f_macro_utf_string_quantitys_t_clear(quantitys) f_macro_memory_structure_t_clear(quantitys)

  #define f_macro_utf_string_quantitys_t_new(status, quantitys, length) f_macro_memory_structure_t_new(status, quantitys, f_utf_string_quantity_t, length)

  #define f_macro_utf_string_quantitys_t_delete(status, quantitys)  f_macro_memory_structure_t_delete(status, quantitys, f_utf_string_quantity_t)
  #define f_macro_utf_string_quantitys_t_destroy(status, quantitys) f_macro_memory_structure_t_destroy(status, quantitys, f_utf_string_quantity_t)

  #define f_macro_utf_string_quantitys_t_delete_simple(quantitys)  f_macro_memory_structure_t_delete_simple(quantitys, f_utf_string_quantity_t)
  #define f_macro_utf_string_quantitys_t_destroy_simple(quantitys) f_macro_memory_structure_t_destroy_simple(quantitys, f_utf_string_quantity_t)

  #define f_macro_utf_string_quantitys_t_resize(status, quantitys, new_length) f_macro_memory_structure_t_resize(status, quantitys, f_utf_string_quantity_t, new_length)
  #define f_macro_utf_string_quantitys_t_adjust(status, quantitys, new_length) f_macro_memory_structure_t_adjust(status, quantitys, f_utf_string_quantity_t, new_length)
#endif // _di_f_utf_string_quantitys_t_


/**
 * A string that is analogous to f_utf_string_dynamic_t but intended for static-only uses.
 *
 * The f_utf_string_static_t type should never be directly allocated or deallocated.
 *
 * A special f_macro_utf_string_static_t_initialize() is provided for the special purpose of easily initialize a static string.
 *
 * string: the string.
 * size: total amount of space available.
 * used: total number of space used.
 */
#ifndef _di_f_utf_string_static_t_
  typedef struct {
    f_utf_string_t string;

    f_utf_string_length_t size;
    f_utf_string_length_t used;
  } f_utf_string_static_t;

  #define f_utf_string_static_t_initialize { f_utf_string_t_initialize, 0, 0 }

  #define f_macro_utf_string_static_t_clear(string_static) \
    string_static.string = 0; \
    string_static.size = 0; \
    string_static.used = 0;

  #define f_macro_utf_string_static_t_initialize(string, length) { string, length, length }
#endif // _di_f_string_static_t_

/**
 * A string that supports contains a size attribute to handle dynamic allocations and deallocations.
 * save the string size along with the string, so that strlen(..) commands can be avoided as much as possible.
 *
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_dynamic_t_
  typedef f_utf_string_static_t f_utf_string_dynamic_t;

  #define f_utf_string_dynamic_t_initialize f_utf_string_static_t_initialize

  #define f_clear_utf_string_dynamic_t(dynamic) f_macro_utf_string_static_t_clear(dynamic)

  #define f_macro_utf_string_dynamic_t_new(status, dynamic, new_length) \
    f_clear_utf_string_dynamic_t(dynamic) \
    status = f_memory_new((void **) & dynamic.string, sizeof(f_utf_string_t), new_length); \
    if (status == F_none) { \
      dynamic.size = new_length; \
      dynamic.used = 0; \
    }

  #define f_macro_utf_string_dynamic_t_delete(status, dynamic) \
    status = f_memory_delete((void **) & dynamic.string, sizeof(f_utf_string_t), dynamic.size); \
    if (status == F_none) { \
      dynamic.size = 0; \
      dynamic.used = 0; \
    }

  #define f_macro_utf_string_dynamic_t_destroy(status, dynamic) \
    status = f_memory_destroy((void **) & dynamic.string, sizeof(f_utf_string_t), dynamic.size); \
    if (status == F_none) { \
      dynamic.size = 0; \
      dynamic.used = 0; \
    }

  #define f_macro_utf_string_dynamic_t_delete_simple(dynamic) \
    f_memory_delete((void **) & dynamic.string, sizeof(f_utf_string_t), dynamic.size); \
    dynamic.size = 0; \
    dynamic.used = 0;

  #define f_macro_utf_string_dynamic_t_destroy_simple(dynamic) \
    f_memory_destroy((void **) & dynamic.string, sizeof(f_utf_string_t), dynamic.size); \
    dynamic.size = 0; \
    dynamic.used = 0;

  #define f_macro_utf_string_dynamic_t_resize(status, dynamic, new_length) \
    status = f_memory_resize((void **) & dynamic.string, sizeof(f_utf_string_t), dynamic.size, new_length); \
    if (status == F_none) { \
      dynamic.size = new_length; \
      if (dynamic.used > dynamic.size) dynamic.used = new_length; \
    }

  #define f_macro_utf_string_dynamic_t_adjust(status, dynamic, new_length) \
    status = f_memory_adjust((void **) & dynamic.string, sizeof(f_utf_string_t), dynamic.size, new_length); \
    if (status == F_none) { \
      dynamic.size = new_length; \
      if (dynamic.used > dynamic.size) dynamic.used = new_length; \
    }
#endif // _di_f_utf_string_dynamic_t_

/**
 * An array of dynamic utf_strings.
 *
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_dynamics_t_
  typedef struct {
    f_utf_string_dynamic_t *array;

    f_utf_string_length_t size;
    f_utf_string_length_t used;
  } f_utf_string_dynamics_t;

  #define f_utf_string_dynamics_t_initialize { 0, 0, 0 }

  #define f_clear_utf_string_dynamics_t(dynamics) \
    dynamics.array = 0; \
    dynamics.size = 0; \
    dynamics.used = 0;

  #define f_macro_utf_string_dynamics_t_new(status, dynamics, length) \
    dynamics.array = 0; \
    dynamics.size = 0; \
    dynamics.used = 0; \
    status = f_memory_new((void **) & dynamics.array, sizeof(f_utf_string_dynamic_t), length); \
    if (status == F_none) { \
      dynamics.size = length; \
      dynamics.used = 0; \
    }

  #define f_macro_utf_string_dynamics_t_delete(status, dynamics) \
    status = F_none; \
    while (dynamics.size > 0) { \
      --dynamics.size; \
      f_macro_utf_string_dynamic_t_destroy(status, dynamics.array[dynamics.size]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & dynamics.array, sizeof(f_utf_string_dynamic_t), dynamics.size); \
    if (status == F_none) dynamics.used = 0;

  #define f_macro_utf_string_dynamics_t_destroy(status, dynamics) \
    status = F_none; \
    while (dynamics.size > 0) { \
      --dynamics.size; \
      f_macro_utf_string_dynamic_t_destroy(status, dynamics.array[dynamics.size]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & dynamics.array, sizeof(f_utf_string_dynamic_t), dynamics.size); \
    if (status == F_none) dynamics.used = 0;

  #define f_macro_utf_string_dynamics_t_delete_simple(dynamics) \
    dynamics.used = dynamics.size; \
    while (dynamics.used > 0) { \
      dynamics.used--; \
      f_macro_string_dynamic_t_delete_simple(dynamics.array[dynamics.used]); \
      if (!dynamics.used) { \
        if (f_memory_delete((void **) & dynamics.array, sizeof(f_utf_string_dynamic_t), dynamics.size)) { \
          dynamics.size = 0; \
        } \
      } \
    }

  #define f_macro_utf_string_dynamics_t_destroy_simple(dynamics) \
    dynamics.used = dynamics.size; \
    while (dynamics.used > 0) { \
      dynamics.used--; \
      f_macro_string_dynamic_t_destroy_simple(dynamics.array[dynamics.used]); \
      if (!dynamics.used) { \
        if (f_memory_destroy((void **) & dynamics.array, sizeof(f_utf_string_dynamic_t), dynamics.size)) { \
          dynamics.size = 0; \
        } \
      } \
    }

  #define f_macro_utf_string_dynamics_t_resize(status, dynamics, new_length) \
    status = F_none; \
    if (new_length < dynamics.size) { \
      for (f_utf_string_length_t _macro__i = dynamics.size - new_length; _macro__i < dynamics.size; _macro__i++) { \
        f_macro_utf_string_dynamic_t_destroy(status, dynamics.array[_macro__i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & dynamics.array, sizeof(f_utf_string_dynamic_t), dynamics.size, new_length); \
    if (status == F_none) { \
      if (new_length > dynamics.size) { \
        for (f_utf_string_length_t _macro__i = dynamics.size; _macro__i < new_length; _macro__i++) { \
          memset(&dynamics.array[_macro__i], 0, sizeof(f_utf_string_dynamic_t)); \
        } \
      } \
      dynamics.size = new_length; \
      if (dynamics.used > dynamics.size) dynamics.used = new_length; \
    }

  #define f_macro_utf_string_dynamics_t_adjust(status, dynamics, new_length) \
    status = F_none; \
    if (new_length < dynamics.size) { \
      for (f_utf_string_length_t _macro__i = dynamics.size - new_length; _macro__i < dynamics.size; _macro__i++) { \
        f_macro_utf_string_dynamic_t_destroy(status, dynamics.array[_macro__i], f_utf_string_dynamic_t); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & dynamics.array, sizeof(f_utf_string_dynamic_t), dynamics.size, new_length); \
    if (status == F_none) { \
      if (new_length > dynamics.size) { \
        for (f_utf_string_length_t _macro__i = dynamics.size; _macro__i < new_length; _macro__i++) { \
          memset(&dynamics.array[_macro__i], 0, sizeof(f_utf_string_dynamic_t)); \
        } \
      } \
      dynamics.size = new_length; \
      if (dynamics.used > dynamics.size) dynamics.used = new_length; \
    }
#endif // _di_f_utf_string_dynamic_t_

/**
 * Define the UTF-8 general whitespace codes.
 *
 * These are integers representing character codes that represent types of spaces.
 *
 * This does not provide whitespace codes for standard ascii whitespaces, such as '\t' or '\r'.
 */
#ifndef _di_f_utf_space_
  #define f_utf_space_em_length           3
  #define f_utf_space_em_quad_length      3
  #define f_utf_space_em_per_three_length 3
  #define f_utf_space_em_per_four_length  3
  #define f_utf_space_em_per_six_length   3

  #define f_utf_space_en_length      3
  #define f_utf_space_en_quad_length 3

  #define f_utf_space_line_feed_reverse_length 2
  #define f_utf_space_line_next_length         2

  #define f_utf_space_medium_mathematical_length 3

  #define f_utf_space_no_break_length        2
  #define f_utf_space_no_break_narrow_length 3

  #define f_utf_space_ogham_length       3
  #define f_utf_space_figure_length      3
  #define f_utf_space_punctuation_length 3
  #define f_utf_space_thin_length        3
  #define f_utf_space_hair_length        3
  #define f_utf_space_ideographic_length 3

  #define f_utf_space_separator_line_length      3
  #define f_utf_space_separator_paragraph_length 3

  const static int8_t f_utf_space_em[f_utf_space_em_length]                     = { 0xe2, 0x80, 0x83 };
  const static int8_t f_utf_space_em_quad[f_utf_space_em_quad_length]           = { 0xe2, 0x80, 0x81 };
  const static int8_t f_utf_space_em_per_three[f_utf_space_em_per_three_length] = { 0xe2, 0x80, 0x84 };
  const static int8_t f_utf_space_em_per_four[f_utf_space_em_per_four_length]   = { 0xe2, 0x80, 0x85 };
  const static int8_t f_utf_space_em_per_six[f_utf_space_em_per_six_length]     = { 0xe2, 0x80, 0x86 };

  const static int8_t f_utf_space_en[f_utf_space_en_length]           = { 0xe2, 0x80, 0x82 };
  const static int8_t f_utf_space_en_quad[f_utf_space_en_quad_length] = { 0xe2, 0x80, 0x80 };

  const static int8_t f_utf_space_line_feed_reverse[f_utf_space_line_feed_reverse_length] = { 0xc2, 0x8d };
  const static int8_t f_utf_space_line_next[f_utf_space_line_next_length]                 = { 0xc2, 0x85 };

  const static int8_t f_utf_space_medium_mathematical[f_utf_space_medium_mathematical_length] = { 0xe2, 0x81, 0x9f };

  const static int8_t f_utf_space_no_break[f_utf_space_no_break_length]               = { 0xc2, 0xa0 };
  const static int8_t f_utf_space_no_break_narrow[f_utf_space_no_break_narrow_length] = { 0xe2, 0x80, 0xaf };

  const static int8_t f_utf_space_ogham[f_utf_space_ogham_length]             = { 0xe1, 0x9a, 0x80 };
  const static int8_t f_utf_space_figure[f_utf_space_figure_length]           = { 0xe2, 0x80, 0x87 };
  const static int8_t f_utf_space_punctuation[f_utf_space_punctuation_length] = { 0xe2, 0x80, 0x88 };
  const static int8_t f_utf_space_thin[f_utf_space_thin_length]               = { 0xe2, 0x80, 0x89 };
  const static int8_t f_utf_space_hair[f_utf_space_hair_length]               = { 0xe2, 0x80, 0x8a };
  const static int8_t f_utf_space_ideographic[f_utf_space_ideographic_length] = { 0xe3, 0x80, 0x80 };

  const static int8_t f_utf_space_separator_line[f_utf_space_separator_line_length]           = { 0xe2, 0x80, 0xa8 };
  const static int8_t f_utf_space_separator_paragraph[f_utf_space_separator_paragraph_length] = { 0xe2, 0x80, 0xa8 };
#endif // _di_f_utf_space_

/**
 * Define the UTF-8 general substitute whitespace codes.
 *
 * These are integers representing character codes that represent types of substitute spaces.
 *
 * Substitute codes are not actual codes and are actually prints of the codes so they should not be treated as the actual codes.
 *
 * This does not provide substitute whitespace codes for standard ascii whitespaces, such as '\t' or '\r'.
 */
#ifndef _di_f_utf_substitute_
  #define f_utf_substitute_symbol_blank_length 3
  #define f_utf_substitute_symbol_space_length 3

  #define f_utf_substitute_middle_dot_length 2

  #define f_utf_substitute_open_box_length            3
  #define f_utf_substitute_open_box_shouldered_length 3

  const static int8_t f_utf_substitute_symbol_blank[f_utf_substitute_symbol_blank_length] = { 0xe2, 0x90, 0xa2 };
  const static int8_t f_utf_substitute_symbol_space[f_utf_substitute_symbol_space_length] = { 0xe2, 0x90, 0xa0 };

  const static int8_t f_utf_substitute_middle_dot[f_utf_substitute_middle_dot_length] = { 0xc2, 0xb7 };

  const static int8_t f_utf_substitute_open_box[f_utf_substitute_open_box_length]                       = { 0xe2, 0x90, 0xa3 };
  const static int8_t f_utf_substitute_open_box_shouldered[f_utf_substitute_open_box_shouldered_length] = { 0xe2, 0x8d, 0xbd };
#endif // _di_f_utf_substitute_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_common_h
