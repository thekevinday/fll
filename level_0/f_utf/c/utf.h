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
 * Define the UTF-8 BOM.
 *
 * The BOM designates that a string is in UTF-8.
 * The BOM must be checked for when processing strings.
 *
 * In many cases, this should be removed such that only one exists in some string block.
 */
#ifndef _di_f_utf_bom_
  #define f_utf_bom_length 3

  const static char f_utf_bom[f_utf_bom_length] = { 0xef, 0xbb, 0xbf }; // 1110 1111, 1011 1011, 1011 1111
#endif // _di_f_utf_bom_

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
 * A helper function, f_utf_is_big_endian(), is provided to detect system endianness so that character arrays (char []) can be correctly processed.
 *
 * The byte structure is intended to be read left to right.
 *
 * The f_macro_utf_character_mask_byte_* are used to get the entire character set fo a given width.
 *
 * The f_macro_utf_character_mask_char_* are used to get a specific UTF-8 block as a single character range.
 *
 * The f_macro_utf_character_to_char_* are used to convert a f_utf_character into a char, for a given 8-bit block.
 *
 * The f_macro_utf_character_from_char_* are used to convert a char into part of a f_utf_character, for a given 8-bit block.
 *
 * The f_macro_utf_character_width is used to determine the width of the UTF-8 character based on f_macro_utf_byte_width.
 * The f_macro_utf_character_width_is is used to determine the width of the UTF-8 character based on f_macro_utf_byte_width_is.
 *
 * @see f_utf_is_big_endian()
 */
#ifndef _di_f_utf_character_
  typedef uint32_t f_utf_character;

  #define f_utf_character_mask_bom 0xefbbbf00 // 1110 1111, 1011 1011, 1011 1111, 0000 0000

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
  #define f_macro_utf_character_to_char_3(character) (((character) & f_utf_character_mask_char_3) >> 8) // grab third byte.
  #define f_macro_utf_character_to_char_4(character) ((character) & f_utf_character_mask_char_4) // grab fourth byte.

  #define f_macro_utf_character_from_char_1(character) ((character) << 24) // shift the first byte.
  #define f_macro_utf_character_from_char_2(character) ((character) << 16) // shift the second byte.
  #define f_macro_utf_character_from_char_3(character) ((character) << 8) // shift the third byte.
  #define f_macro_utf_character_from_char_4(character) ((character)) // shift the fourth byte.

  #define f_macro_utf_character_width(character) (f_macro_utf_byte_width(f_macro_utf_character_to_char_1(character)))
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

  #define f_utf_string_max_size   f_signed_long_size
  #define f_utf_string_initialize f_utf_character_eos

  #define f_macro_utf_string_new(status, string, length)   status = f_memory_new((void **) & string, sizeof(f_utf_string), length)
  #define f_macro_utf_string_delete(status, string, size)  status = f_memory_delete((void **) & string, sizeof(f_utf_string), size)
  #define f_macro_utf_string_destroy(status, string, size) status = f_memory_destroy((void **) & string, sizeof(f_utf_string), size)

  #define f_macro_utf_string_resize(status, string, old_length, new_length) \
    status = f_memory_resize((void **) & string, sizeof(f_utf_string), old_length, new_length)

  #define f_macro_utf_string_adjust(status, string, old_length, new_length) \
    status = f_memory_adjust((void **) & string, sizeof(f_utf_string), old_length, new_length)
#endif // _di_f_utf_string_

/**
 * Provide a type specifically for UTF-8 strings.
 */
#ifndef _di_f_utf_string_length_
  typedef f_s_long f_utf_string_length;

  #define f_macro_utf_string_length_new(status, string, length)    status = f_memory_new((void **) & string, sizeof(f_utf_string_length), length)
  #define f_macro_utf_string_length_delete(status, string, length) status = f_memory_delete((void **) & string, sizeof(f_utf_string_length), length)
  #define f_macro_utf_string_length_destroy(status, string, size)  status = f_memory_destroy((f_void_P *) & string, sizeof(f_utf_string_length), size)

  #define f_macro_utf_string_length_resize(status, length, old_length, new_length) \
    status = f_memory_resize((void **) & length, sizeof(f_utf_string_length), old_length, new_length)

  #define f_macro_utf_string_length_adjust(status, length, old_length, new_length) \
    status = f_memory_adjust((void **) & length, sizeof(f_utf_string_length), old_length, new_length)
#endif // _di_f_utf_string_length_

/**
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_lengths_
  typedef struct {
    f_utf_string_length *array;
    f_array_length  size;
    f_array_length  used;
  } f_utf_string_lengths;

  #define f_utf_string_lengths_initialize { 0, 0, 0 }

  #define f_macro_utf_string_length_news(status, lengths) \
    f_macro_memory_structure_new(status, lengths, f_utf_string_length)

  #define f_macro_utf_string_length_deletes(status, lengths) \
    f_macro_memory_structure_delete(status, lengths, f_utf_string_length)

  #define f_macro_utf_string_length_destroys(status, lengths) \
    f_macro_memory_structure_destroy(status, lengths, f_utf_string_length)

  #define f_macro_utf_string_length_resizes(status, lengths, new_length) \
    f_macro_memory_structure_resize(status, lengths, f_utf_string_length, new_length)

  #define f_macro_utf_string_length_adjusts(status, lengths, new_length) \
    f_macro_memory_structure_adjust(status, lengths, f_utf_string_length, new_length)
#endif // _di_f_utf_string_lengths_

/**
 * designates a start and stop position that represents a sub-string inside of some parent string.
 * use this to avoid resizing, restructuring, and reallocating the parent string to separate the sub-string.
 */
#ifndef _di_f_utf_string_location_
  typedef struct {
    f_utf_string_length start;
    f_utf_string_length stop;
  } f_utf_string_location;

  #define f_utf_string_location_initialize { 1, 0 }

  #define f_macro_utf_string_location_new(status, utf_string_location, length)   status = f_memory_new((void **) & utf_string_location, sizeof(f_utf_string_location), length)
  #define f_macro_utf_string_location_delete(status, utf_string_location, size)  status = f_memory_delete((void **) & utf_string_location, sizeof(f_utf_string_location), size)
  #define f_macro_utf_string_location_destroy(status, utf_string_location, size) status = f_memory_destroy((void **) & utf_string_location, sizeof(f_utf_string_location), size)

  #define f_macro_utf_string_location_resize(status, utf_string_location, old_length, new_length) \
    status = f_memory_resize((void **) & utf_string_location, sizeof(f_utf_string_location), old_length, new_length)

  #define f_macro_utf_string_location_adjust(status, utf_string_location, old_length, new_length) \
    status = f_memory_adjust((void **) & utf_string_location, sizeof(f_utf_string_location), old_length, new_length)
#endif // _di_f_utf_string_location_

/**
 * an array of string locations.
 *
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_locations_
  typedef struct {
    f_utf_string_location *array;
    f_array_length    size;
    f_array_length    used;
  } f_utf_string_locations;

  #define f_utf_string_locations_initialize {0, 0, 0}

  #define f_clear_utf_string_locations(locations) \
    f_macro_memory_structure_clear(locations)

  #define f_macro_utf_string_location_news(status, locations, length) \
    f_macro_memory_structure_new(status, locations, f_utf_string_location, length)

  #define f_macro_utf_string_location_deletes(status, locations) \
    f_macro_memory_structure_delete(status, locations, f_utf_string_location)

  #define f_macro_utf_string_location_destroys(status, locations) \
    f_macro_memory_structure_destroy(status, locations, f_utf_string_location)

  #define f_macro_utf_string_location_resizes(status, locations, new_length) \
    f_macro_memory_structure_resize(status, locations, f_utf_string_location, new_length)

  #define f_macro_utf_string_location_adjusts(status, locations, new_length) \
    f_macro_memory_structure_adjust(status, locations, f_utf_string_location, new_length)
#endif // _di_f_utf_string_locations_

/**
 * a string that supports contains a size attribute to handle dynamic allocations and deallocations.
 * save the string size along with the string, so that strlen(..) commands can be avoided as much as possible.
 *
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_dynamic_
  typedef struct {
    f_utf_string        string;
    f_utf_string_length size;
    f_utf_string_length used;
  } f_utf_string_dynamic;

  #define f_utf_string_dynamic_initialize { f_utf_string_initialize, 0, 0 }

  #define f_clear_utf_string_dynamic(dynamic) \
    dynamic.string = 0; \
    dynamic.size = 0; \
    dynamic.used = 0;

  #define f_macro_utf_string_dynamic_new(status, dynamic, new_length) \
    f_clear_utf_string_dynamic(dynamic) \
    status = f_memory_new((void **) & dynamic.string, sizeof(f_utf_string), new_length); \
    if (status == f_none) { \
      dynamic.size = new_length; \
      dynamic.used = 0; \
    }

  #define f_macro_utf_string_dynamic_delete(status, dynamic) \
    status = f_memory_delete((void **) & dynamic.string, sizeof(f_utf_string), dynamic.size); \
    if (status == f_none) { \
      dynamic.size = 0; \
      dynamic.used = 0; \
    }

  #define f_macro_utf_string_dynamic_destroy(status, dynamic) \
    status = f_memory_destroy((void **) & dynamic.string, sizeof(f_utf_string), dynamic.size); \
    if (status == f_none) { \
      dynamic.size = 0; \
      dynamic.used = 0; \
    }

  #define f_macro_utf_string_dynamic_resize(status, dynamic, new_length) \
    status = f_memory_resize((void **) & dynamic.string, sizeof(f_utf_string), dynamic.size, new_length); \
    if (status == f_none) { \
      dynamic.size = new_length; \
      if (dynamic.used > dynamic.size) dynamic.used = new_length; \
    }

  #define f_macro_utf_string_dynamic_adjust(status, dynamic, new_length) \
    status = f_memory_adjust((void **) & dynamic.string, sizeof(f_utf_string), dynamic.size, new_length); \
    if (status == f_none) { \
      dynamic.size = new_length; \
      if (dynamic.used > dynamic.size) dynamic.used = new_length; \
    }
#endif // _di_f_utf_string_dynamic_

/**
 * an array of dynamic utf_strings.
 *
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_utf_string_dynamics_
  typedef struct {
    f_utf_string_dynamic *array;
    f_utf_string_length  size;
    f_utf_string_length  used;
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
    if (status == f_none) { \
      dynamics.size = length; \
      dynamics.used = 0; \
    }

  #define f_macro_utf_string_dynamics_delete(status, dynamics) \
    status = f_none; \
    while (dynamics.size > 0) { \
      --dynamics.size; \
      f_macro_utf_string_dynamic_destroy(status, dynamics.array[dynamics.size]); \
      if (status != f_none) break; \
    } \
    if (status == f_none) status = f_memory_delete((void **) & dynamics.array, sizeof(f_utf_string_dynamic), dynamics.size); \
    if (status == f_none) dynamics.used = 0;

  #define f_macro_utf_string_dynamics_destroy(status, dynamics) \
    status = f_none; \
    while (dynamics.size > 0) { \
      --dynamics.size; \
      f_macro_utf_string_dynamic_destroy(status, dynamics.array[dynamics.size]); \
      if (status != f_none) break; \
    } \
    if (status == f_none) status = f_memory_destroy((void **) & dynamics.array, sizeof(f_utf_string_dynamic), dynamics.size); \
    if (status == f_none) dynamics.used = 0;

  #define f_macro_utf_string_dynamics_resize(status, dynamics, new_length) \
    status = f_none; \
    if (new_length < dynamics.size) { \
      f_utf_string_length i = dynamics.size - new_length; \
      for (; i < dynamics.size; ++i) { \
        f_macro_utf_string_dynamic_destroy(status, dynamics.array[i]); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_memory_resize((void **) & dynamics.array, sizeof(f_utf_string_dynamic), dynamics.size, new_length); \
    if (status == f_none) { \
      if (new_length > dynamics.size) { \
        f_utf_string_length i = dynamics.size; \
        for (; i < new_length; ++i) { \
          memset(&dynamics.array[i], 0, sizeof(f_utf_string_dynamic)); \
        } \
      } \
      dynamics.size = new_length; \
      if (dynamics.used > dynamics.size) dynamics.used = new_length; \
    }

  #define f_macro_utf_string_dynamics_adjust(status, dynamics, new_length) \
    status = f_none; \
    if (new_length < dynamics.size) { \
      f_utf_string_length i = dynamics.size - new_length; \
      for (; i < dynamics.size; ++i) { \
        f_macro_utf_string_dynamic_destroy(status, dynamics.array[i], f_utf_string_dynamic); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_memory_adjust((void **) & dynamics.array, sizeof(f_utf_string_dynamic), dynamics.size, new_length); \
    if (status == f_none) { \
      if (new_length > dynamics.size) { \
        f_utf_string_length i = dynamics.size; \
        for (; i < new_length; ++i) { \
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

  const static char f_utf_space_em[f_utf_space_em_length]                     = { 0xe2, 0x80, 0x83 };
  const static char f_utf_space_em_quad[f_utf_space_em_quad_length]           = { 0xe2, 0x80, 0x81 };
  const static char f_utf_space_em_per_three[f_utf_space_em_per_three_length] = { 0xe2, 0x80, 0x84 };
  const static char f_utf_space_em_per_four[f_utf_space_em_per_four_length]   = { 0xe2, 0x80, 0x85 };
  const static char f_utf_space_em_per_six[f_utf_space_em_per_six_length]     = { 0xe2, 0x80, 0x86 };

  const static char f_utf_space_en[f_utf_space_en_length]           = { 0xe2, 0x80, 0x82 };
  const static char f_utf_space_en_quad[f_utf_space_en_quad_length] = { 0xe2, 0x80, 0x80 };

  const static char f_utf_space_line_feed_reverse[f_utf_space_line_feed_reverse_length] = { 0xc2, 0x8d };
  const static char f_utf_space_line_next[f_utf_space_line_next_length]                 = { 0xc2, 0x85 };

  const static char f_utf_space_medium_mathematical[f_utf_space_medium_mathematical_length] = { 0xe2, 0x81, 0x9f };

  const static char f_utf_space_no_break[f_utf_space_no_break_length]               = { 0xc2, 0xa0 };
  const static char f_utf_space_no_break_narrow[f_utf_space_no_break_narrow_length] = { 0xe2, 0x80, 0xaf };

  const static char f_utf_space_ogham[f_utf_space_ogham_length]             = { 0xe1, 0x9a, 0x80 };
  const static char f_utf_space_figure[f_utf_space_figure_length]           = { 0xe2, 0x80, 0x87 };
  const static char f_utf_space_punctuation[f_utf_space_punctuation_length] = { 0xe2, 0x80, 0x88 };
  const static char f_utf_space_thin[f_utf_space_thin_length]               = { 0xe2, 0x80, 0x89 };
  const static char f_utf_space_hair[f_utf_space_hair_length]               = { 0xe2, 0x80, 0x8a };
  const static char f_utf_space_ideographic[f_utf_space_ideographic_length] = { 0xe3, 0x80, 0x80 };

  const static char f_utf_space_separator_line[f_utf_space_separator_line_length]           = { 0xe2, 0x80, 0xa8 };
  const static char f_utf_space_separator_paragraph[f_utf_space_separator_paragraph_length] = { 0xe2, 0x80, 0xa8 };
#endif // _di_f_utf_space_

/**
 * Define the UTF-8 general substitute whitespace codes.
 *
 * These are integers representing character codes that represent types of substitute spaces.
 *
 * This does not provide substitute whitespace codes for standard ascii whitespaces, such as '\t' or '\r'.
 */
#ifndef _di_f_utf_substitute_
  #define f_utf_substitute_symbol_blank_length 3
  #define f_utf_substitute_symbol_space_length 3

  #define f_utf_substitute_middle_dot_length 2

  #define f_utf_substitute_open_box_length            3
  #define f_utf_substitute_open_box_shouldered_length 3

  const static char f_utf_substitute_symbol_blank[f_utf_substitute_symbol_blank_length] = { 0xe2, 0x90, 0xa2 };
  const static char f_utf_substitute_symbol_space[f_utf_substitute_symbol_space_length] = { 0xe2, 0x90, 0xa0 };

  const static char f_utf_substitute_middle_dot[f_utf_substitute_middle_dot_length] = { 0xc2, 0xb7 };

  const static char f_utf_substitute_open_box[f_utf_substitute_open_box_length]                       = { 0xe2, 0x90, 0xa3 };
  const static char f_utf_substitute_open_box_shouldered[f_utf_substitute_open_box_shouldered_length] = { 0xe2, 0x8d, 0xbd };
#endif // _di_f_utf_substitute_

/**
 * Helper function for UTF-8 processing code to determine endianess of the system.
 *
 *
 * @return
 *   f_true if the system is big-endian.
 *   f_false if the system is little-endian.
 */
#ifndef _di_f_utf_is_big_endian_
  extern f_return_status f_utf_is_big_endian();
#endif // _di_f_utf_is_big_endian_

/**
 * Check to see if the entire byte block of the character is a UTF-8 character.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by max_width.
 * @param max_width
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   f_true if a UTF-8 character.
 *   f_false if not a UTF-8 character.
 *   f_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_
  extern f_return_status f_utf_is(const f_string character, const f_u_short max_width);
#endif // _di_f_utf_is_

/**
 * Check to see if the entire byte block of the character is a UTF-8 BOM.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by max_width.
 * @param max_width
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   f_true if a UTF-8 whitespace or substitute.
 *   f_false if not a UTF-8 whitespace or substitute.
 *   f_maybe (with error bit) if this could be a whitespace or substitute but width is not long enough.
 *   f_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_bom_
  extern f_return_status f_utf_is_bom(const f_string character, const f_u_short max_width);
#endif // _di_f_utf_is_bom_

/**
 * Check to see if the entire byte block of the character is a UTF-8 character.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   f_true if a UTF-8 character.
 *   f_false if not a UTF-8 character.
 *   f_invalid_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_
  extern f_return_status f_utf_is_character(const f_utf_character character);
#endif // _di_f_utf_is_

/**
 * Check to see if the entire byte block of the character is a UTF-8 printable character.
 *
 * This does not check non-UTF-8 graph.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by max_width.
 * @param max_width
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   f_true if a UTF-8 graph.
 *   f_false if not a UTF-8 graph.
 *   f_maybe (with error bit) if this could be a graph but width is not long enough.
 *   f_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_graph_
  extern f_return_status f_utf_is_graph(const f_string character, const f_u_short max_width);
#endif // _di_f_utf_is_graph_

/**
 * Check to see if the entire byte block of the character is a UTF-8 whitespace or substitute character.
 *
 * This does not check non-UTF-8 whitespace.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by max_width.
 * @param max_width
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   f_true if a UTF-8 whitespace or substitute.
 *   f_false if not a UTF-8 whitespace or substitute.
 *   f_maybe (with error bit) if this could be a whitespace or substitute but width is not long enough.
 *   f_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_space_
  extern f_return_status f_utf_is_space(const f_string character, const f_u_short max_width);
#endif // _di_f_utf_is_space_

/**
 * Check to see if the entire byte block of the character is a UTF-8 whitespace substitute character.
 *
 * This does not check non-UTF-8 whitespace.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by max_width.
 * @param max_width
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   f_true if a UTF-8 substitute.
 *   f_false if not a UTF-8 substitute.
 *   f_maybe (with error bit) if this could be a substitute but width is not long enough.
 *   f_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_substitute_
  extern f_return_status f_utf_is_substitute(const f_string character, const f_u_short max_width);
#endif // _di_f_utf_is_substitute_

/**
 * Check to see if the entire byte block of the character is a UTF-8 general whitespace character.
 *
 * This does not check non-UTF-8 whitespace.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by max_width.
 * @param max_width
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   f_true if a UTF-8 whitespace.
 *   f_false if not a UTF-8 whitespace.
 *   f_maybe (with error bit) if this could be a whitespace but width is not long enough.
 *   f_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_whitespace_
  extern f_return_status f_utf_is_whitespace(const f_string character, const f_u_short max_width);
#endif // _di_f_utf_is_whitespace_

/**
 * Check to see if the entire byte block of the character is a UTF-8 BOM.
 *
 * @param character
 *   The UTF-8 character to validate.
 *
 * @return
 *   f_true if a UTF-8 whitespace or substitute.
 *   f_false if not a UTF-8 whitespace or substitute.
 *   f_maybe (with error bit) if this could be a whitespace or substitute but width is not long enough.
 *   f_invalid_utf (with error bit) if character is an invalid UTF-8 character.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_bom_character_
  extern f_return_status f_utf_is_bom_character(const f_utf_character character);
#endif // _di_f_utf_is_bom_character_

/**
 * Check to see if the entire byte block of the character is a UTF-8 printable character.
 *
 * This does not check non-UTF-8 graph.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   f_true if a UTF-8 graph.
 *   f_false if not a UTF-8 graph.
 *   f_invalid_utf (with error bit) if character is an invalid UTF-8 character.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_graph_character_
  extern f_return_status f_utf_is_graph_character(const f_utf_character character);
#endif // _di_f_utf_is_graph_character_

/**
 * Check to see if the entire byte block of the character is a UTF-8 whitespace or substitute character.
 *
 * This does not check non-UTF-8 whitespace.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   f_true if a UTF-8 whitespace or substitute.
 *   f_false if not a UTF-8 whitespace or substitute.
 *   f_invalid_utf (with error bit) if character is an invalid UTF-8 character.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_space_character_
  extern f_return_status f_utf_is_space_character(const f_utf_character character);
#endif // _di_f_utf_is_space_character_

/**
 * Check to see if the entire byte block of the character is a UTF-8 whitespace substitute character.
 *
 * This does not check non-UTF-8 whitespace.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   f_true if a UTF-8 substitute.
 *   f_false if not a UTF-8 substitute.
 *   f_invalid_utf (with error bit) if character is an invalid UTF-8 character.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_substitute_character_
  extern f_return_status f_utf_is_substitute_character(const f_utf_character character);
#endif // _di_f_utf_is_substitute_character_

/**
 * Check to see if the entire byte block of the character is a UTF-8 general whitespace character.
 *
 * This does not check non-UTF-8 whitespace.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   f_true if a UTF-8 whitespace.
 *   f_false if not a UTF-8 whitespace.
 *   f_invalid_utf (with error bit) if character is an invalid UTF-8 character.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_whitespace_character_
  extern f_return_status f_utf_is_whitespace_character(const f_utf_character character);
#endif // _di_f_utf_is_whitespace_character_

/**
 * Convert a UTF-8 character, stored as a string (character buffer), to the specialized f_utf_character type.
 *
 * This will also convert ASCII characters.
 *
 * @param character
 *   The character string to be converted to the f_utf_character type.
 *   There must be enough space allocated to convert against, as limited by max_width.
 * @param max_width
 *   The maximum width available for converting.
 *   Can be anything greater than 0.
 * @param utf_character
 *   The generated character of type f_utf_character.
 *   This value may be cleared, even on error.
 *
 * @return
 *   f_none if conversion was successful.
 *   f_failure (with error bit) if width is not long enough to convert.
 *   f_invalid_utf (with error bit) if character is an invalid UTF-8 character.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_char_to_character_
  extern f_return_status f_utf_char_to_character(const f_string character, const f_u_short max_width, f_utf_character *utf_character);
#endif // _di_f_utf_char_to_character_

/**
 * Convert a specialized f_utf_character type to a char, stored as a string (character buffer).
 *
 * This will also convert ASCII characters stored in the utf_character array.
 *
 * @param utf_character
 *   The UTF-8 characterr to convert from.
 * @param character
 *   A char representation of the UTF-8 character, stored as a string of width bytes.
 *   If max_width is 0, then this should not be allocated (set the pointer address to 0).
 * @param max_width
 *   The number of bytes the generated character represents.
 *   If this is set to 0, then the character will be allocated and this will be set to the width of the utf_character.
 *   If this is set to some value greater than 0 (up to 4), then this represents the size of the character array (no allocations are performed).
 *   If this is greater than 0, and the utf_character width is larger than this size, then an error is returned.
 *
 * @return
 *   f_none if conversion was successful.
 *   f_failure (with error bit) if width is not long enough to convert.
 *   f_invalid_utf (with error bit) if character is an invalid UTF-8 character.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_allocation_error (with error bit) on memory allocation error.
 *   f_failure (with error bit) if width is not long enough to convert.
 */
#ifndef _di_f_utf_character_to_char_
  extern f_return_status f_utf_character_to_char(const f_utf_character utf_character, f_string *character, f_u_short *max_width);
#endif // _di_f_utf_character_to_char_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_h
