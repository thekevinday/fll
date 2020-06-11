/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides UTF-8 capabilities.
 *
 * Identifiers:
 * - UTF_8-1: 1000 0000
 * - UTF_8-2: 1100 0000
 * - UTF_8-3: 1110 0000
 * - UTF_8-4: 1111 0000
 *
 * Values:
 * - UTF_8-1: 1011 1111
 * - UTF_8-2: 1101 1111
 * - UTF_8-3: 1110 1111
 * - UTF_8-4: 1111 0111
 *
 * Identifier Structure:
 * - UTF_8-1: 1000 0000
 * - UTF_8-2: 1100 0000 1000 0000
 * - UTF_8-3: 1110 0000 1000 0000 1000 0000
 * - UTF_8-4: 1111 0000 1000 0000 1000 0000 1000 0000
 *
 * Value Structure:
 * - UTF_8-1: 10xx xxxx
 * - UTF_8-2: 110x xxxx, 10xx xxxx
 * - UTF_8-3: 1110 xxxx, 10xx xxxx, 10xx xxxx
 * - UTF_8-4: 1111 0xxx, 10xx xxxx, 10xx xxxx, 10xx xxxx
 */
#ifndef _F_utf_h
#define _F_utf_h

// libc includes
#include <ctype.h>
#include <string.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/type.h>
#include <level_0/string.h>

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
 * The f_macro_utf_character_mask_byte_* are used to get the entire character set fo a given width.
 *
 * The f_macro_utf_character_mask_char_* are used to get a specific UTF-8 block as a single character range.
 *
 * The f_macro_utf_character_to_char_* are used to convert a f_utf_character into a int8_t, for a given 8-bit block.
 *
 * The f_macro_utf_character_from_char_* are used to convert a int8_t into part of a f_utf_character, for a given 8-bit block.
 *
 * The f_macro_utf_character_width is used to determine the width of the UTF-8 character based on f_macro_utf_byte_width.
 * The f_macro_utf_character_width_is is used to determine the width of the UTF-8 character based on f_macro_utf_byte_width_is.
 *
 * @see f_utf_is_big_endian()
 */
#ifndef _di_f_utf_character_
  typedef uint32_t f_utf_character;

  #define f_utf_character_mask_byte_1 0xff000000 // 1111 1111, 0000 0000, 0000 0000, 0000 0000
  #define f_utf_character_mask_byte_2 0xffff0000 // 1111 1111, 1111 1111, 0000 0000, 0000 0000
  #define f_utf_character_mask_byte_3 0xffffff00 // 1111 1111, 1111 1111, 1111 1111, 0000 0000
  #define f_utf_character_mask_byte_4 0xffffffff // 1111 1111, 1111 1111, 1111 1111, 1111 1111

  #define f_utf_character_mask_char_1 0xff000000 // 1111 1111, 0000 0000, 0000 0000, 0000 0000
  #define f_utf_character_mask_char_2 0x00ff0000 // 0000 0000, 1111 1111, 0000 0000, 0000 0000
  #define f_utf_character_mask_char_3 0x0000ff00 // 0000 0000, 0000 0000, 1111 1111, 0000 0000
  #define f_utf_character_mask_char_4 0x000000ff // 0000 0000, 0000 0000, 0000 0000, 1111 1111

  #define f_macro_utf_character_to_char_1(character) (((character) & f_utf_character_mask_char_1) >> 24) // grab first byte.
  #define f_macro_utf_character_to_char_2(character) (((character) & f_utf_character_mask_char_2) >> 16) // grab second byte.
  #define f_macro_utf_character_to_char_3(character) (((character) & f_utf_character_mask_char_3) >> 8)  // grab third byte.
  #define f_macro_utf_character_to_char_4(character) ((character) & f_utf_character_mask_char_4)         // grab fourth byte.

  #define f_macro_utf_character_from_char_1(character) (((character) << 24) & f_utf_character_mask_char_1) // shift to first byte.
  #define f_macro_utf_character_from_char_2(character) (((character) << 16) & f_utf_character_mask_char_2) // shift to second byte.
  #define f_macro_utf_character_from_char_3(character) (((character) << 8) & f_utf_character_mask_char_3)  // shift to third byte.
  #define f_macro_utf_character_from_char_4(character) ((character) & f_utf_character_mask_char_4)         // shift to fourth byte.

  #define f_macro_utf_character_width(character)    (f_macro_utf_byte_width(f_macro_utf_character_to_char_1(character)))
  #define f_macro_utf_character_width_is(character) (f_macro_utf_byte_width_is(f_macro_utf_character_to_char_1(character)))
#endif // _di_f_utf_character_

#ifndef _di_f_utf_character_have_eol_
  #define f_utf_character_eol 0x0a000000 // 0000 1010, 0000 0000, 0000 0000, 0000 0000
#endif // _di_f_utf_character_have_eol_

#ifndef _di_f_utf_character_have_eos_
  #define f_utf_character_eos 0x00000000 // 0000 0000, 0000 0000, 0000 0000, 0000 0000
#endif // _di_f_utf_character_have_eos_

#ifndef _di_f_utf_character_have_placeholder_
  #define f_utf_character_placeholder 0x00000000 // 0000 0000, 0000 0000, 0000 0000, 0000 0000
#endif // _di_f_utf_character_have_placeholder_

/**
 * Provide a UTF-8 characters set to 4-bits wide as a string.
 */
#ifndef _di_f_utf_string_
  typedef f_utf_character *f_utf_string;

  #define f_utf_string_max_size   f_type_number_size_unsigned
  #define f_utf_string_initialize f_utf_character_eos

  #define f_macro_utf_string_new(status, string, length)   status = f_memory_new((void **) & string, sizeof(f_utf_string), length)

  #define f_macro_utf_string_delete(status, string, size)  status = f_memory_delete((void **) & string, sizeof(f_utf_string), size)
  #define f_macro_utf_string_destroy(status, string, size) status = f_memory_destroy((void **) & string, sizeof(f_utf_string), size)

  #define f_macro_utf_string_resize(status, string, old_length, new_length) status = f_memory_resize((void **) & string, sizeof(f_utf_string), old_length, new_length)
  #define f_macro_utf_string_adjust(status, string, old_length, new_length) status = f_memory_adjust((void **) & string, sizeof(f_utf_string), old_length, new_length)
#endif // _di_f_utf_string_

/**
 * Provide a type specifically for UTF-8 strings.
 */
#ifndef _di_f_utf_string_length_
  typedef f_number_unsigned f_utf_string_length;

  #define f_utf_string_length_size     0xfffffffffffffffe
  #define f_utf_string_length_size_max f_type_number_size_max_unsigned

  #define f_macro_utf_string_length_new(status, string, length)    status = f_memory_new((void **) & string, sizeof(f_utf_string_length), length)

  #define f_macro_utf_string_length_delete(status, string, length) status = f_memory_delete((void **) & string, sizeof(f_utf_string_length), length)
  #define f_macro_utf_string_length_destroy(status, string, size)  status = f_memory_destroy((f_void_P *) & string, sizeof(f_utf_string_length), size)

  #define f_macro_utf_string_length_resize(status, length, old_length, new_length) status = f_memory_resize((void **) & length, sizeof(f_utf_string_length), old_length, new_length)
  #define f_macro_utf_string_length_adjust(status, length, old_length, new_length) status = f_memory_adjust((void **) & length, sizeof(f_utf_string_length), old_length, new_length)
#endif // _di_f_utf_string_length_

/**
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_lengths_
  typedef struct {
    f_utf_string_length *array;

    f_array_length size;
    f_array_length used;
  } f_utf_string_lengths;

  #define f_utf_string_lengths_initialize { 0, 0, 0 }

  #define f_macro_utf_string_lengths_clear(lengths) f_macro_memory_structure_clear(lengths)

  #define f_macro_utf_string_lengths_new(status, lengths, length) f_macro_memory_structure_new(status, lengths, f_utf_string_length, length)

  #define f_macro_utf_string_lengths_delete(status, lengths) f_macro_memory_structure_delete(status, lengths, f_utf_string_length)
  #define f_macro_utf_string_lengths_destroy(status, lengths) f_macro_memory_structure_destroy(status, lengths, f_utf_string_length)

  #define f_macro_utf_string_lengths_resize(status, lengths, new_length) f_macro_memory_structure_resize(status, lengths, f_utf_string_length, new_length)
  #define f_macro_utf_string_lengths_adjust(status, lengths, new_length) f_macro_memory_structure_adjust(status, lengths, f_utf_string_length, new_length)
#endif // _di_f_utf_string_lengths_

/**
 * Designates a start and stop position that represents a sub-string inside of some parent string.
 * use this to avoid resizing, restructuring, and reallocating the parent string to separate the sub-string.
 */
#ifndef _di_f_utf_string_range_
  typedef struct {
    f_utf_string_length start;
    f_utf_string_length stop;
  } f_utf_string_range;

  #define f_utf_string_range_initialize { 1, 0 }

  #define f_macro_utf_string_range_new(status, utf_string_range, length)   status = f_memory_new((void **) & utf_string_range, sizeof(f_utf_string_range), length)
  #define f_macro_utf_string_range_delete(status, utf_string_range, size)  status = f_memory_delete((void **) & utf_string_range, sizeof(f_utf_string_range), size)
  #define f_macro_utf_string_range_destroy(status, utf_string_range, size) status = f_memory_destroy((void **) & utf_string_range, sizeof(f_utf_string_range), size)

  #define f_macro_utf_string_range_resize(status, utf_string_range, old_length, new_length) \
    status = f_memory_resize((void **) & utf_string_range, sizeof(f_utf_string_range), old_length, new_length)

  #define f_macro_utf_string_range_adjust(status, utf_string_range, old_length, new_length) \
    status = f_memory_adjust((void **) & utf_string_range, sizeof(f_utf_string_range), old_length, new_length)
#endif // _di_f_utf_string_range_

/**
 * An array of string ranges.
 *
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_ranges_
  typedef struct {
    f_utf_string_range *array;

    f_array_length size;
    f_array_length used;
  } f_utf_string_ranges;

  #define f_utf_string_ranges_initialize {0, 0, 0}

  #define f_clear_utf_string_ranges(ranges) f_macro_memory_structure_clear(ranges)

  #define f_macro_utf_string_range_news(status, ranges, length) f_macro_memory_structure_new(status, ranges, f_utf_string_range, length)

  #define f_macro_utf_string_range_deletes(status, ranges) f_macro_memory_structure_delete(status, ranges, f_utf_string_range)
  #define f_macro_utf_string_range_destroys(status, ranges) f_macro_memory_structure_destroy(status, ranges, f_utf_string_range)

  #define f_macro_utf_string_range_resizes(status, ranges, new_length) f_macro_memory_structure_resize(status, ranges, f_utf_string_range, new_length)
  #define f_macro_utf_string_range_adjusts(status, ranges, new_length) f_macro_memory_structure_adjust(status, ranges, f_utf_string_range, new_length)
#endif // _di_f_utf_string_ranges_

/**
 * Store string quantity.
 *
 * Similar to f_utf_string_range, except total is relative to start and is not an absolute stop position.
 *
 * Two common uses for when total is 0 is:
 * 1) Exactly that, process a total of 0 strings bytes.
 * 2) Process with no limit, aka infinite.
 *
 * start: The position where the string starts (based on some string/buffer).
 * total: The total number of elements within that string/buffer the quantity represents.
 */
#ifndef _di_f_utf_string_quantity_
  typedef struct {
    f_utf_string_length start;
    f_utf_string_length total;
  } f_utf_string_quantity;

  #define f_utf_string_quantity_initialize { 0, 0 }
#endif // _di_f_utf_string_quantity_

/**
 * An array of string quantities.
 *
 * array: the array of string quantities.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_quantitys_
  typedef struct {
    f_utf_string_quantity *array;

    f_array_length size;
    f_array_length used;
  } f_utf_string_quantitys;

  #define f_utf_string_quantitys_initialize {0, 0, 0}

  #define f_macro_utf_string_quantitys_clear(quantitys) f_macro_memory_structure_clear(quantitys)

  #define f_macro_utf_string_quantitys_new(status, quantitys, length) f_macro_memory_structure_new(status, quantitys, f_utf_string_quantity, length)

  #define f_macro_utf_string_quantitys_delete(status, quantitys)  f_macro_memory_structure_delete(status, quantitys, f_utf_string_quantity)
  #define f_macro_utf_string_quantitys_destroy(status, quantitys) f_macro_memory_structure_destroy(status, quantitys, f_utf_string_quantity)

  #define f_macro_utf_string_quantitys_delete_simple(quantitys)  f_macro_memory_structure_delete_simple(quantitys, f_utf_string_quantity)
  #define f_macro_utf_string_quantitys_destroy_simple(quantitys) f_macro_memory_structure_destroy_simple(quantitys, f_utf_string_quantity)

  #define f_macro_utf_string_quantitys_resize(status, quantitys, new_length) f_macro_memory_structure_resize(status, quantitys, f_utf_string_quantity, new_length)
  #define f_macro_utf_string_quantitys_adjust(status, quantitys, new_length) f_macro_memory_structure_adjust(status, quantitys, f_utf_string_quantity, new_length)
#endif // _di_f_utf_string_quantitys_


/**
 * A string that is analogous to f_utf_string_dynamic but intended for static-only uses.
 *
 * The f_utf_string_static type should never be directly allocated or deallocated.
 *
 * string: the string.
 * size: total amount of space available.
 * used: total number of space used.
 */
#ifndef _di_f_utf_string_static_
  typedef struct {
    f_utf_string string;

    f_utf_string_length size;
    f_utf_string_length used;
  } f_utf_string_static;

  #define f_utf_string_static_initialize { f_utf_string_initialize, 0, 0 }

  #define f_macro_utf_string_static_clear(string_static) \
    string_static.string = 0; \
    string_static.size = 0; \
    string_static.used = 0;
#endif // _di_f_string_static_

/**
 * A string that supports contains a size attribute to handle dynamic allocations and deallocations.
 * save the string size along with the string, so that strlen(..) commands can be avoided as much as possible.
 *
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_dynamic_
  typedef f_utf_string_static f_utf_string_dynamic;

  #define f_utf_string_dynamic_initialize f_utf_string_static_initialize

  #define f_clear_utf_string_dynamic(dynamic) f_macro_utf_string_static_clear(dynamic)

  #define f_macro_utf_string_dynamic_new(status, dynamic, new_length) \
    f_clear_utf_string_dynamic(dynamic) \
    status = f_memory_new((void **) & dynamic.string, sizeof(f_utf_string), new_length); \
    if (status == F_none) { \
      dynamic.size = new_length; \
      dynamic.used = 0; \
    }

  #define f_macro_utf_string_dynamic_delete(status, dynamic) \
    status = f_memory_delete((void **) & dynamic.string, sizeof(f_utf_string), dynamic.size); \
    if (status == F_none) { \
      dynamic.size = 0; \
      dynamic.used = 0; \
    }

  #define f_macro_utf_string_dynamic_destroy(status, dynamic) \
    status = f_memory_destroy((void **) & dynamic.string, sizeof(f_utf_string), dynamic.size); \
    if (status == F_none) { \
      dynamic.size = 0; \
      dynamic.used = 0; \
    }

  #define f_macro_utf_string_dynamic_delete_simple(dynamic) \
    f_memory_delete((void **) & dynamic.string, sizeof(f_utf_string), dynamic.size); \
    dynamic.size = 0; \
    dynamic.used = 0;

  #define f_macro_utf_string_dynamic_destroy_simple(dynamic) \
    f_memory_destroy((void **) & dynamic.string, sizeof(f_utf_string), dynamic.size); \
    dynamic.size = 0; \
    dynamic.used = 0;

  #define f_macro_utf_string_dynamic_resize(status, dynamic, new_length) \
    status = f_memory_resize((void **) & dynamic.string, sizeof(f_utf_string), dynamic.size, new_length); \
    if (status == F_none) { \
      dynamic.size = new_length; \
      if (dynamic.used > dynamic.size) dynamic.used = new_length; \
    }

  #define f_macro_utf_string_dynamic_adjust(status, dynamic, new_length) \
    status = f_memory_adjust((void **) & dynamic.string, sizeof(f_utf_string), dynamic.size, new_length); \
    if (status == F_none) { \
      dynamic.size = new_length; \
      if (dynamic.used > dynamic.size) dynamic.used = new_length; \
    }
#endif // _di_f_utf_string_dynamic_

/**
 * An array of dynamic utf_strings.
 *
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_dynamics_
  typedef struct {
    f_utf_string_dynamic *array;

    f_utf_string_length size;
    f_utf_string_length used;
  } f_utf_string_dynamics;

  #define f_utf_string_dynamics_initialize { 0, 0, 0 }

  #define f_clear_utf_string_dynamics(dynamics) \
    dynamics.array = 0; \
    dynamics.size = 0; \
    dynamics.used = 0;

  #define f_macro_utf_string_dynamics_new(status, dynamics, length) \
    dynamics.array = 0; \
    dynamics.size = 0; \
    dynamics.used = 0; \
    status = f_memory_new((void **) & dynamics.array, sizeof(f_utf_string_dynamic), length); \
    if (status == F_none) { \
      dynamics.size = length; \
      dynamics.used = 0; \
    }

  #define f_macro_utf_string_dynamics_delete(status, dynamics) \
    status = F_none; \
    while (dynamics.size > 0) { \
      --dynamics.size; \
      f_macro_utf_string_dynamic_destroy(status, dynamics.array[dynamics.size]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & dynamics.array, sizeof(f_utf_string_dynamic), dynamics.size); \
    if (status == F_none) dynamics.used = 0;

  #define f_macro_utf_string_dynamics_destroy(status, dynamics) \
    status = F_none; \
    while (dynamics.size > 0) { \
      --dynamics.size; \
      f_macro_utf_string_dynamic_destroy(status, dynamics.array[dynamics.size]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & dynamics.array, sizeof(f_utf_string_dynamic), dynamics.size); \
    if (status == F_none) dynamics.used = 0;

  #define f_macro_utf_string_dynamics_delete_simple(dynamics) \
    dynamics.used = dynamics.size; \
    while (dynamics.used > 0) { \
      dynamics.used--; \
      f_macro_string_dynamic_delete_simple(dynamics.array[dynamics.used]); \
      if (dynamics.used == 0) { \
        if (f_memory_delete((void **) & dynamics.array, sizeof(f_utf_string_dynamic), dynamics.size)) { \
          dynamics.size = 0; \
        } \
      } \
    }

  #define f_macro_utf_string_dynamics_destroy_simple(dynamics) \
    dynamics.used = dynamics.size; \
    while (dynamics.used > 0) { \
      dynamics.used--; \
      f_macro_string_dynamic_destroy_simple(dynamics.array[dynamics.used]); \
      if (dynamics.used == 0) { \
        if (f_memory_destroy((void **) & dynamics.array, sizeof(f_utf_string_dynamic), dynamics.size)) { \
          dynamics.size = 0; \
        } \
      } \
    }

  #define f_macro_utf_string_dynamics_resize(status, dynamics, new_length) \
    status = F_none; \
    if (new_length < dynamics.size) { \
      f_utf_string_length i = dynamics.size - new_length; \
      for (; i < dynamics.size; i++) { \
        f_macro_utf_string_dynamic_destroy(status, dynamics.array[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & dynamics.array, sizeof(f_utf_string_dynamic), dynamics.size, new_length); \
    if (status == F_none) { \
      if (new_length > dynamics.size) { \
        f_utf_string_length i = dynamics.size; \
        for (; i < new_length; i++) { \
          memset(&dynamics.array[i], 0, sizeof(f_utf_string_dynamic)); \
        } \
      } \
      dynamics.size = new_length; \
      if (dynamics.used > dynamics.size) dynamics.used = new_length; \
    }

  #define f_macro_utf_string_dynamics_adjust(status, dynamics, new_length) \
    status = F_none; \
    if (new_length < dynamics.size) { \
      f_utf_string_length i = dynamics.size - new_length; \
      for (; i < dynamics.size; i++) { \
        f_macro_utf_string_dynamic_destroy(status, dynamics.array[i], f_utf_string_dynamic); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & dynamics.array, sizeof(f_utf_string_dynamic), dynamics.size, new_length); \
    if (status == F_none) { \
      if (new_length > dynamics.size) { \
        f_utf_string_length i = dynamics.size; \
        for (; i < new_length; i++) { \
          memset(&dynamics.array[i], 0, sizeof(f_utf_string_dynamic)); \
        } \
      } \
      dynamics.size = new_length; \
      if (dynamics.used > dynamics.size) dynamics.used = new_length; \
    }
#endif // _di_f_utf_string_dynamic_

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

/**
 * Check to see if the entire byte block of the character is a UTF-8 character.
 *
 * This does not validate if the UTF-8 character is a valid UTF-8 character, for that use f_utf_character_is_valid().
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_false if not a UTF-8 character.
 *   F_true if a UTF-8 character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_valid()
 * @see f_utf_is()
 */
#ifndef _di_f_utf_character_is_
  extern f_return_status f_utf_character_is(const f_utf_character character);
#endif // _di_f_utf_character_is_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 alphabet character.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_false if not a UTF-8 alphabet character.
 *   F_true if a UTF-8 alphabet character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see iscntrl()
 * @see f_utf_is_alpha()
 */
#ifndef _di_f_utf_character_is_alpha_
  extern f_return_status f_utf_character_is_alpha(const f_utf_character character);
#endif // _di_f_utf_character_is_alpha_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 alphabetic or numeric character.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_false if not a UTF-8 alpha-numeric character.
 *   F_true if a UTF-8 alpha-numeric character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see iscntrl()
 * @see f_utf_is_alphanumeric()
 */
#ifndef _di_f_utf_character_is_alpha_numeric_
  extern f_return_status f_utf_character_is_alpha_numeric(const f_utf_character character);
#endif // _di_f_utf_character_is_alpha_numeric_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 control character.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_false if not a UTF-8 control character.
 *   F_true if a UTF-8 control character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see iscntrl()
 * @see f_utf_is_control()
 */
#ifndef _di_f_utf_character_is_control_
  extern f_return_status f_utf_character_is_control(const f_utf_character character);
#endif // _di_f_utf_character_is_control_

/**
 * Check to see if the entire byte block of the character is a UTF-8 control picture character.
 *
 * Control Picture characters are placeholders for special ASCII characters and therefore there are no ASCII Control Picture characters.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_false if not a UTF-8 control picture character.
 *   F_true if a UTF-8 control picture character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_is_control_picture()
 */
#ifndef _di_f_utf_character_is_control_picture_
  extern f_return_status f_utf_character_is_control_picture(const f_utf_character character);
#endif // _di_f_utf_character_is_control_picture_

/**
 * Check to see if the entire byte block of the character is a 1-width UTF-8 character fragment.
 *
 * Characters whose width is 1-byte are invalid.
 * However, the character could have been cut-off, so whether or not this is actually valid should be determined by the caller.
 *
 * For normal validation functions, try using f_utf_character_is() or f_utf_character_is_valid().
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_false if not a UTF-8 character.
 *   F_true if a UTF-8 character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is()
 * @see f_utf_character_is_valid()
 * @see f_utf_is_fragment()
 */
#ifndef _di_f_utf_character_is_fragment_
  extern f_return_status f_utf_character_is_fragment(const f_utf_character character);
#endif // _di_f_utf_character_is_fragment_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 printable character.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_false if not a UTF-8 graph.
 *   F_true if a UTF-8 graph.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see isgraph()
 * @see f_utf_is_graph()
 */
#ifndef _di_f_utf_character_is_graph_
  extern f_return_status f_utf_character_is_graph(const f_utf_character character);
#endif // _di_f_utf_character_is_graph_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 numeric character.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_false if not a UTF-8 numeric character.
 *   F_true if a UTF-8 numeric character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see iscntrl()
 * @see f_utf_is_numeric()
 */
#ifndef _di_f_utf_character_is_numeric_
  extern f_return_status f_utf_character_is_numeric(const f_utf_character character);
#endif // _di_f_utf_character_is_numeric_

/**
 * Check to see if the entire byte block of the character is a valid UTF-8 character.
 *
 * This does validate if the UTF-8 character is a valid UTF-8 character.
 * To not do this, use f_utf_character_is().
 *
 * This function can be expensive due to how Unicode has invalid codes spread randomly through it.
 * For simpler error checking, try f_utf_is_fragment(), to just check that the width is valid or not.
 * (First characters should not have a width of 1, and all other characters should have a width of 1.)
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_false if not a UTF-8 character.
 *   F_true if a UTF-8 character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is()
 * @see f_utf_character_is_fragment()
 * @see f_utf_is_valid()
 */
#ifndef _di_f_utf_character_is_valid_
  extern f_return_status f_utf_character_is_valid(const f_utf_character character);
#endif // _di_f_utf_character_is_value_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 general space character.
 *
 * Non-printing or zero-width characters are not considered whitespace.
 * This does include line separators like '\n'.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_false if not a UTF-8 whitespace.
 *   F_true if a UTF-8 whitespace.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_f_utf_character_is_whitespace_
  extern f_return_status f_utf_character_is_whitespace(const f_utf_character character);
#endif // _di_f_utf_character_is_whitespace_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word character.
 *
 * A word character is alpha-numeric or an underscore '_'.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_false if not a UTF-8 word character.
 *   F_true if a UTF-8 word character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see iscntrl()
 * @see f_utf_is_word()
 */
#ifndef _di_f_utf_character_is_word_
  extern f_return_status f_utf_character_is_word(const f_utf_character character);
#endif // _di_f_utf_character_is_word_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word or dash character.
 *
 * A word dash character is alpha-numeric, an underscore '_' or a dash '-'.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_false if not a UTF-8 word or dash character.
 *   F_true if a UTF-8 word or dash character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see iscntrl()
 * @see f_utf_is_word_dash()
 */
#ifndef _di_f_utf_character_is_word_dash_
  extern f_return_status f_utf_character_is_word_dash(const f_utf_character character);
#endif // _di_f_utf_character_is_word_dash_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word, dash, or plus character.
 *
 * A word dash character is alpha-numeric, an underscore '_', a dash '-', or a plus '+'.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_false if not a UTF-8 word or dash character.
 *   F_true if a UTF-8 word or dash character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see iscntrl()
 * @see f_utf_is_word_dash()
 */
#ifndef _di_f_utf_character_is_word_dash_plus_
  extern f_return_status f_utf_character_is_word_dash_plus(const f_utf_character character);
#endif // _di_f_utf_character_is_word_dash_plus_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 general non-printing character.
 *
 * Only characters that do not print, which are generally called zero-width.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_false if not a UTF-8 non-printing or zero-width character.
 *   F_true if a UTF-8 non-printing or zero-width character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_is_zero_width()
 */
#ifndef _di_f_utf_character_is_zero_width_
  extern f_return_status f_utf_character_is_zero_width(const f_utf_character character);
#endif // _di_f_utf_character_is_zero_width_

/**
 * Check to see if the entire byte block of the character is an word character.
 *
 * A word character is alphanumeric or underscore '_'.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_false if not a UTF-8 alpha character.
 *   F_true if a UTF-8 alpha character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see iscntrl()
 * @see f_utf_is_word()
 */
#ifndef _di_f_utf_character_is_word_
  extern f_return_status f_utf_character_is_word(const f_utf_character character);
#endif // _di_f_utf_character_is_word_

/**
 * Convert a specialized f_utf_character type to a int8_t, stored as a string (character buffer).
 *
 * This will also convert ASCII characters stored in the utf_character array.
 *
 * @param utf_character
 *   The UTF-8 characterr to convert from.
 * @param character
 *   A int8_t representation of the UTF-8 character, stored as a string of width bytes.
 *   If width_max is 0, then this should not be allocated (set the pointer address to 0).
 * @param width_max
 *   The number of bytes the generated character represents.
 *   If this is set to 0, then the character will be allocated and this will be set to the width of the utf_character.
 *   If this is set to some value greater than 0 (up to 4), then this represents the size of the character array (no allocations are performed).
 *   If this is greater than 0, and the utf_character width is larger than this size, then an error is returned.
 *
 * @return
 *   F_none if conversion was successful.
 *   F_failure (with error bit) if width is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *   F_failure (with error bit) if width is not long enough to convert.
 */
#ifndef _di_f_utf_character_to_char_
  extern f_return_status f_utf_character_to_char(const f_utf_character utf_character, f_string *character, f_string_length *width_max);
#endif // _di_f_utf_character_to_char_

/**
 * Helper function for UTF-8 processing code to determine endianess of the system.
 *
 * @todo relocate this outside of f_utf into a more general path, perhaps f_memory (f_memory_is_big_endian).
 *
 * @return
 *   F_false if the system is little-endian.
 *   F_true if the system is big-endian.
 */
#ifndef _di_f_utf_is_big_endian_
  extern f_return_status f_utf_is_big_endian();
#endif // _di_f_utf_is_big_endian_

/**
 * Check to see if the entire byte block of the character is a UTF-8 character.
 *
 * This does not check the validity of the character, for that instead use f_utf_is_valid().
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_false if not a UTF-8 character.
 *   F_true if a UTF-8 character.
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_utf_is_valid()
 * @see f_utf_character_is()
 */
#ifndef _di_f_utf_is_
  extern f_return_status f_utf_is(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 alphabet character.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_false if not a UTF-8 alphabet character.
 *   F_true if a UTF-8 alphabet character.
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see iscntrl()
 * @see f_utf_character_is_alpha()
 */
#ifndef _di_f_utf_is_alpha_
  extern f_return_status f_utf_is_alpha(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_alpha_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 alphabet or numeric character.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_false if not a UTF-8 alpha-numeric character.
 *   F_true if a UTF-8 alpha-numeric character.
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see iscntrl()
 * @see f_utf_character_is_alpha_numeric()
 */
#ifndef _di_f_utf_is_alpha_numeric_
  extern f_return_status f_utf_is_alpha_numeric(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_alpha_numeric_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 control character.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_false if not a UTF-8 control character.
 *   F_true if a UTF-8 control character.
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see iscntrl()
 * @see f_utf_character_is_control()
 */
#ifndef _di_f_utf_is_control_
  extern f_return_status f_utf_is_control(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_control_

/**
 * Check to see if the entire byte block of the character is a UTF-8 control picture character.
 *
 * Control Picture characters are placeholders for special ASCII characters and therefore there are no ASCII Control Picture characters.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_false if not a UTF-8 control picture character.
 *   F_true if a UTF-8 control picture character.
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see f_utf_character_is_control_picture()
 */
#ifndef _di_f_utf_is_control_picture_
  extern f_return_status f_utf_is_control_picture(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_control_picture_

/**
 * Check to see if the entire byte block of the character is a 1-width UTF-8 character fragment.
 *
 * Characters whose width is 1-byte are invalid.
 * However, the character could have been cut-off, so whether or not this is actually valid should be determined by the caller.
 *
 * For normal validation functions, try using f_utf_character_is() or f_utf_character_is_valid().
 *
 * According to rfc3629, the valid octect sequences for UTF-8 are:
 *   UTF8-octets = *( UTF8-char )
 *   UTF8-char   = UTF8-1 / UTF8-2 / UTF8-3 / UTF8-4
 *   UTF8-1      = %x00-7F
 *   UTF8-2      = %xC2-DF UTF8-tail
 *   UTF8-3      = %xE0 %xA0-BF UTF8-tail / %xE1-EC 2( UTF8-tail ) /
 *                 %xED %x80-9F UTF8-tail / %xEE-EF 2( UTF8-tail )
 *   UTF8-4      = %xF0 %x90-BF 2( UTF8-tail ) / %xF1-F3 3( UTF8-tail ) /
 *                 %xF4 %x80-8F 2( UTF8-tail )
 *   UTF8-tail   = %x80-BF
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_false if not a UTF-8 character.
 *   F_true if a UTF-8 character.
 *
 * @see f_utf_character_is()
 * @see f_utf_character_is_valid()
 * @see f_utf_character_is_fragment()
 */
#ifndef _di_f_utf_is_fragment_
  extern f_return_status f_utf_is_fragment(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_fragment_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 printable character.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_false if not a UTF-8 graph.
 *   F_true if a UTF-8 graph.
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_maybe (with error bit) if this could be a graph but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see isgraph()
 * @see iscntrl()
 * @see f_utf_character_is_graph()
 */
#ifndef _di_f_utf_is_graph_
  extern f_return_status f_utf_is_graph(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_graph_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 numeric character.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_false if not a UTF-8 numeric character.
 *   F_true if a UTF-8 numeric character.
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see iscntrl()
 * @see f_utf_character_is_numeric()
 */
#ifndef _di_f_utf_is_numeric_
  extern f_return_status f_utf_is_numeric(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_numeric_

/**
 * Check to see if the entire byte block of the character is a UTF-8 character and if that character is a valid UTF-8.
 *
 * This does check the validity of the character, to not do this use f_utf_is().
 *
 * This function can be expensive due to how Unicode has invalid codes spread randomly through it.
 * For simpler error checking, try f_utf_is_fragment(), to just check that the width is valid or not.
 * (First characters should have a width of not 1, and all other characters should not have a width of 1.)
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_false if not a valid UTF-8 character.
 *   F_true if a valid UTF-8 character.
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_utf_is()
 * @see f_utf_is_fragment()
 * @see f_utf_character_is_valid()
 */
#ifndef _di_f_utf_is_valid_
  extern f_return_status f_utf_is_valid(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_valid_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 general space character.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_false if not a UTF-8 whitespace.
 *   F_true if a UTF-8 whitespace.
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_maybe (with error bit) if this could be a whitespace but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see isspace()
 * @see iscntrl()
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_utf_is_whitespace_
  extern f_return_status f_utf_is_whitespace(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_whitespace_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word character.
 *
 * A word character is alpha-numeric or an underscore '_'.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_false if not a UTF-8 word character.
 *   F_true if a UTF-8 word character.
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see iscntrl()
 * @see f_utf_character_is_word()
 */
#ifndef _di_f_utf_is_word_
  extern f_return_status f_utf_is_word(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_word_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word or dash character.
 *
 * A word dash character is alpha-numeric, an underscore '_' or a dash '-'.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_false if not a UTF-8 word or dash character.
 *   F_true if a UTF-8 word or dash character.
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see iscntrl()
 * @see f_utf_character_is_word_dash()
 */
#ifndef _di_f_utf_is_word_dash_
  extern f_return_status f_utf_is_word_dash(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_word_dash_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word, dash, or plus character.
 *
 * A word dash character is alpha-numeric, an underscore '_', a dash '-', or a plus '+'.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_false if not a UTF-8 word or dash character.
 *   F_true if a UTF-8 word or dash character.
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see iscntrl()
 * @see f_utf_character_is_word_dash_plus()
 */
#ifndef _di_f_utf_is_word_dash_plus_
  extern f_return_status f_utf_is_word_dash_plus(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_word_dash_plus_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 general non-printing character.
 *
 * Only characters that do not print, which are generally called zero-width.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_false if not a UTF-8 whitespace.
 *   F_true if a UTF-8 whitespace.
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_maybe (with error bit) if this could be a whitespace but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see isspace()
 * @see iscntrl()
 * @see f_utf_character_is_zero_width()
 */
#ifndef _di_f_utf_is_zero_width_
  extern f_return_status f_utf_is_zero_width(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_zero_width_

/**
 * Convert an ASCII or UTF-8 character, stored as a string (character buffer), to the specialized f_utf_character type.
 *
 * @param character
 *   The character string to be converted to the f_utf_character type.
 *   There must be enough space allocated to convert against, as limited by width_max.
 * @param width_max
 *   The maximum width available for converting.
 *   Can be anything greater than 0.
 * @param character_utf
 *   The generated character of type f_utf_character.
 *   This value may be cleared, even on error.
 *
 * @return
 *   F_none if conversion was successful.
 *   F_failure (with error bit) if width is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 */
#ifndef _di_f_utf_char_to_character_
  extern f_return_status f_utf_char_to_character(const f_string character, const f_string_length width_max, f_utf_character *character_utf);
#endif // _di_f_utf_char_to_character_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_h
