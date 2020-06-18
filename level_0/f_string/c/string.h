/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides string capabilities.
 *
 * It is highly recommended that all string arrays are set to a max size of f_string_length_size.
 * Any calculations against the length (aka: string.used) can always perform (A < B) operators such that the B is f_string_length_size + 1 without integer overflow.
 */
#ifndef _F_string_h
#define _F_string_h

// libc includes
#include <string.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/type.h>

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

/**
 * A structure designating a start and stop range for some string.
 *
 * In general, this project uses the start and stop position inclusively, meaning that a range of 0 to 1 would include positions 0 and position 1.
 * Therefore, a range from 0 to 0 would be include position 0.
 * Set start to some value larger than stop to designate that there is no range (such as start = 1, stop = 0).
 *
 * A special f_macro_string_range_initialize() is provided for the special purpose of easily initialize a static string range.
 *
 * start: the start position.
 * stop: the stop position.
 */
#ifndef _di_f_string_range_
  typedef struct {
    f_string_length start;
    f_string_length stop;
  } f_string_range;

  #define f_string_range_initialize { 1, 0 }

  #define f_macro_string_range_initialize(length) { 0, length - 1 }

  #define f_macro_string_range_clear(range) \
    range.start = 1; \
    range.stop = 0;
#endif // _di_f_string_range_

/**
 * An array of string ranges.
 *
 * array: the array of string ranges.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_ranges_
  typedef struct {
    f_string_range *array;

    f_array_length size;
    f_array_length used;
  } f_string_ranges;

  #define f_string_ranges_initialize {0, 0, 0}

  #define f_macro_string_ranges_clear(ranges) f_macro_memory_structure_clear(ranges)

  #define f_macro_string_ranges_new(status, ranges, length) f_macro_memory_structure_new(status, ranges, f_string_range, length)

  #define f_macro_string_ranges_delete(status, ranges)  f_macro_memory_structure_delete(status, ranges, f_string_range)
  #define f_macro_string_ranges_destroy(status, ranges) f_macro_memory_structure_destroy(status, ranges, f_string_range)

  #define f_macro_string_ranges_delete_simple(ranges)  f_macro_memory_structure_delete_simple(ranges, f_string_range)
  #define f_macro_string_ranges_destroy_simple(ranges) f_macro_memory_structure_destroy_simple(ranges, f_string_range)

  #define f_macro_string_ranges_resize(status, ranges, new_length) f_macro_memory_structure_resize(status, ranges, f_string_range, new_length)
  #define f_macro_string_ranges_adjust(status, ranges, new_length) f_macro_memory_structure_adjust(status, ranges, f_string_range, new_length)
#endif // _di_f_string_ranges_

/**
 * Store string quantity.
 *
 * Similar to f_string_range, except total is relative to start and is not an absolute stop position.
 *
 * Two common uses for when total is 0 is:
 * 1) Exactly that, process a total of 0 strings bytes.
 * 2) Process with no limit, aka infinite.
 *
 * start: The position where the string starts (based on some string/buffer).
 * total: The total number of elements within that string/buffer the quantity represents.
 */
#ifndef _di_f_string_quantity_
  typedef struct {
    f_string_length start;
    f_string_length total;
  } f_string_quantity;

  #define f_string_quantity_initialize { 0, 0 }
#endif // _di_f_string_quantity_

/**
 * An array of string quantities.
 *
 * array: the array of string quantities.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_quantitys_
  typedef struct {
    f_string_quantity *array;

    f_array_length size;
    f_array_length used;
  } f_string_quantitys;

  #define f_string_quantitys_initialize {0, 0, 0}

  #define f_macro_string_quantitys_clear(quantitys) f_macro_memory_structure_clear(quantitys)

  #define f_macro_string_quantitys_new(status, quantitys, length) f_macro_memory_structure_new(status, quantitys, f_string_quantity, length)

  #define f_macro_string_quantitys_delete(status, quantitys)  f_macro_memory_structure_delete(status, quantitys, f_string_quantity)
  #define f_macro_string_quantitys_destroy(status, quantitys) f_macro_memory_structure_destroy(status, quantitys, f_string_quantity)

  #define f_macro_string_quantitys_delete_simple(quantitys)  f_macro_memory_structure_delete_simple(quantitys, f_string_quantity)
  #define f_macro_string_quantitys_destroy_simple(quantitys) f_macro_memory_structure_destroy_simple(quantitys, f_string_quantity)

  #define f_macro_string_quantitys_resize(status, quantitys, new_length) f_macro_memory_structure_resize(status, quantitys, f_string_quantity, new_length)
  #define f_macro_string_quantitys_adjust(status, quantitys, new_length) f_macro_memory_structure_adjust(status, quantitys, f_string_quantity, new_length)
#endif // _di_f_string_quantitys_

/**
 * A string that is analogous to f_string_dynamic but intended for static-only uses.
 *
 * The f_string_static type should never be directly allocated or deallocated.
 *
 * A special f_macro_string_static_initialize() is provided for the special purpose of easily initialize a static string.
 *
 * string: the string.
 * size: total amount of space available.
 * used: total number of space used.
 */
#ifndef _di_f_string_static_
  typedef struct {
    f_string string;

    f_string_length size;
    f_string_length used;
  } f_string_static;

  #define f_string_static_initialize { 0, 0, 0 }

  #define f_macro_string_static_clear(string_static) \
    string_static.string = 0; \
    string_static.size = 0; \
    string_static.used = 0;

  #define f_macro_string_static_initialize(string, length) { string, length, length }
#endif // _di_f_string_static_

/**
 * A string that supports contains a size attribute to handle dynamic allocations and deallocations.
 *
 * Save the string size along with the string, so that strlen(..) commands can be avoided as much as possible.
 *
 * This is a sub-type of f_string_static, allowing it to be passed into any f_string_static type.
 * It is recommended that f_string_static are not otherwise casted into f_string_dynamic to avoid potential memory allocation issues.
 *
 * string: the string.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamic_
  typedef f_string_static f_string_dynamic;

  #define f_string_dynamic_initialize f_string_static_initialize

  #define f_macro_string_dynamic_clear(dynamic) f_macro_string_static_clear(dynamic)

  #define f_macro_string_dynamic_new(status, dynamic, new_length) \
    f_macro_string_dynamic_clear(dynamic) \
    status = f_memory_new((void **) & dynamic.string, sizeof(f_string), new_length); \
    if (status == F_none) { \
      dynamic.size = new_length; \
      dynamic.used = 0; \
    }

  #define f_macro_string_dynamic_delete(status, dynamic) \
    status = f_memory_delete((void **) & dynamic.string, sizeof(f_string), dynamic.size); \
    if (status == F_none) { \
      dynamic.size = 0; \
      dynamic.used = 0; \
    }

  #define f_macro_string_dynamic_destroy(status, dynamic) \
    status = f_memory_destroy((void **) & dynamic.string, sizeof(f_string), dynamic.size); \
    if (status == F_none) { \
      dynamic.size = 0; \
      dynamic.used = 0; \
    }

  #define f_macro_string_dynamic_delete_simple(dynamic) \
    f_memory_delete((void **) & dynamic.string, sizeof(f_string), dynamic.size); \
    dynamic.size = 0; \
    dynamic.used = 0;

  #define f_macro_string_dynamic_destroy_simple(dynamic) \
    f_memory_destroy((void **) & dynamic.string, sizeof(f_string), dynamic.size); \
    dynamic.size = 0; \
    dynamic.used = 0;

  #define f_macro_string_dynamic_resize(status, dynamic, new_length) \
    status = f_memory_resize((void **) & dynamic.string, sizeof(f_string), dynamic.size, new_length); \
    if (status == F_none) { \
      dynamic.size = new_length; \
      if (dynamic.used > dynamic.size) dynamic.used = new_length; \
    }

  #define f_macro_string_dynamic_adjust(status, dynamic, new_length) \
    status = f_memory_adjust((void **) & dynamic.string, sizeof(f_string), dynamic.size, new_length); \
    if (status == F_none) { \
      dynamic.size = new_length; \
      if (dynamic.used > dynamic.size) dynamic.used = new_length; \
    }
#endif // _di_f_string_dynamic_

/**
 * An array of static strings.
 *
 * array: the array of static strings.
 * size: total amount of space available.
 * used: total number of space used.
 */
#ifndef _di_f_string_statics_
  typedef struct {
    f_string_static *array;

    f_array_length size;
    f_array_length used;
  } f_string_statics;

  #define f_string_statics_initialize { 0, 0, 0 }

  #define f_macro_string_statics_clear(statics) \
    statics.array = 0; \
    statics.size = 0; \
    statics.used = 0;
#endif // _di_f_string_statics_

/**
 * An array of dynamic strings.
 *
 * array: the array of dynamic strings.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamics_
  typedef f_string_statics f_string_dynamics;

  #define f_string_dynamics_initialize f_string_statics_initialize

  #define f_macro_string_dynamics_clear(dynamics) f_macro_string_statics_clear(dynamics)

  #define f_macro_string_dynamics_new(status, dynamics, length) \
    f_macro_string_dynamics_clear(dynamics) \
    status = f_memory_new((void **) & dynamics.array, sizeof(f_string_dynamic), length); \
    if (status == F_none) { \
      dynamics.size = length; \
      dynamics.used = 0; \
    }

  #define f_macro_string_dynamics_delete(status, dynamics) \
    status = F_none; \
    dynamics.used = dynamics.size; \
    while (dynamics.used > 0) { \
      dynamics.used--; \
      f_macro_string_dynamic_delete(status, dynamics.array[dynamics.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & dynamics.array, sizeof(f_string_dynamic), dynamics.size); \
    if (status == F_none) dynamics.size = 0;

  #define f_macro_string_dynamics_destroy(status, dynamics) \
    status = F_none; \
    dynamics.used = dynamics.size; \
    while (dynamics.used > 0) { \
      dynamics.used--; \
      f_macro_string_dynamic_destroy(status, dynamics.array[dynamics.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & dynamics.array, sizeof(f_string_dynamic), dynamics.size); \
    if (status == F_none) dynamics.size = 0;

  #define f_macro_string_dynamics_delete_simple(dynamics) \
    dynamics.used = dynamics.size; \
    while (dynamics.used > 0) { \
      dynamics.used--; \
      f_macro_string_dynamic_delete_simple(dynamics.array[dynamics.used]); \
      if (dynamics.used == 0) { \
        if (f_memory_delete((void **) & dynamics.array, sizeof(f_string_dynamic), dynamics.size)) { \
          dynamics.size = 0; \
        } \
      } \
    }

  #define f_macro_string_dynamics_destroy_simple(dynamics) \
    dynamics.used = dynamics.size; \
    while (dynamics.used > 0) { \
      dynamics.used--; \
      f_macro_string_dynamic_destroy_simple(dynamics.array[dynamics.used]); \
      if (dynamics.used == 0) { \
        if (f_memory_destroy((void **) & dynamics.array, sizeof(f_string_dynamic), dynamics.size)) { \
          dynamics.size = 0; \
        } \
      } \
    }

  #define f_macro_string_dynamics_resize(status, dynamics, new_length) \
    status = F_none; \
    if (new_length < dynamics.size) { \
      f_array_length i = dynamics.size - new_length; \
      for (; i < dynamics.size; i++) { \
        f_macro_string_dynamic_delete(status, dynamics.array[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & dynamics.array, sizeof(f_string_dynamic), dynamics.size, new_length); \
    if (status == F_none) { \
      if (new_length > dynamics.size) { \
        f_array_length i = dynamics.size; \
        for (; i < new_length; i++) { \
          memset(&dynamics.array[i], 0, sizeof(f_string_dynamic)); \
        } \
      } \
      dynamics.size = new_length; \
      if (dynamics.used > dynamics.size) dynamics.used = new_length; \
    }

  #define f_macro_string_dynamics_adjust(status, dynamics, new_length) \
    status = F_none; \
    if (new_length < dynamics.size) { \
      f_array_length i = dynamics.size - new_length; \
      for (; i < dynamics.size; i++) { \
        f_macro_string_dynamic_destroy(status, dynamics.array[i], f_string_dynamic); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & dynamics.array, sizeof(f_string_dynamic), dynamics.size, new_length); \
    if (status == F_none) { \
      if (new_length > dynamics.size) { \
        f_array_length i = dynamics.size; \
        for (; i < new_length; i++) { \
          memset(&dynamics.array[i], 0, sizeof(f_string_dynamic)); \
        } \
      } \
      dynamics.size = new_length; \
      if (dynamics.used > dynamics.size) dynamics.used = new_length; \
    }
#endif // _di_f_string_dynamics_

/**
 * A string map consisting of a name and value.
 *
 * name: A string representing the map name.
 * value: A string representing the map value.
 */
#ifndef _di_f_string_map_
  typedef struct {
    f_string_dynamic name;
    f_string_dynamic value;
  } f_string_map;

  #define f_string_map_initialize { f_string_dynamic_initialize, f_string_dynamic_initialize }

  #define f_macro_string_map_clear(map) \
    map.array = 0; \
    map.size = 0; \
    map.used = 0;

  #define f_macro_string_map_delete(status, map) \
    f_macro_string_dynamic_delete(status, map.name) \
    if (status == F_none) { \
      f_macro_string_dynamic_delete(status, map.value) \
    }

  #define f_macro_string_map_destroy(status, map) \
    f_macro_string_dynamic_destroy(status, map.name) \
    if (status == F_none) { \
      f_macro_string_dynamic_destroy(status, map.value) \
    }

  #define f_macro_string_map_delete_simple(map) \
    f_macro_string_dynamic_delete_simple(map.name) \
    f_macro_string_dynamic_delete_simple(map.value)

  #define f_macro_string_map_destroy_simple(map) \
    f_macro_string_dynamic_destroy_simple(map.name) \
    f_macro_string_dynamic_destroy_simple(map.value)
#endif // _di_f_string_map_

/**
 * An array of string maps.
 *
 * array: the array of string maps.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_maps_
  typedef struct {
    f_string_map *array;

    f_array_length size;
    f_array_length used;
  } f_string_maps;

  #define f_string_maps_initialize f_string_statics_initialize

  #define f_macro_string_maps_clear(maps) \
    maps.array = 0; \
    maps.size = 0; \
    maps.used = 0;

  #define f_macro_string_maps_new(status, maps, length) \
    f_macro_string_maps_clear(maps) \
    status = f_memory_new((void **) & maps.array, sizeof(f_string_map), length); \
    if (status == F_none) { \
      maps.size = length; \
      maps.used = 0; \
    }

  #define f_macro_string_maps_delete(status, maps) \
    status = F_none; \
    maps.used = maps.size; \
    while (maps.used > 0) { \
      maps.used--; \
      f_macro_string_map_delete(status, maps.array[maps.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & maps.array, sizeof(f_string_map), maps.size); \
    if (status == F_none) maps.size = 0;

  #define f_macro_string_maps_destroy(status, maps) \
    status = F_none; \
    maps.used = maps.size; \
    while (maps.used > 0) { \
      maps.used--; \
      f_macro_string_map_destroy(status, maps.array[maps.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & maps.array, sizeof(f_string_map), maps.size); \
    if (status == F_none) maps.size = 0;

  #define f_macro_string_maps_delete_simple(maps) \
    maps.used = maps.size; \
    while (maps.used > 0) { \
      maps.used--; \
      f_macro_string_map_delete_simple(maps.array[maps.used]); \
      if (maps.used == 0) { \
        if (f_memory_delete((void **) & maps.array, sizeof(f_string_map), maps.size)) { \
          maps.size = 0; \
        } \
      } \
    }

  #define f_macro_string_maps_destroy_simple(maps) \
    maps.used = maps.size; \
    while (maps.used > 0) { \
      maps.used--; \
      f_macro_string_map_destroy_simple(maps.array[maps.used]); \
      if (maps.used == 0) { \
        if (f_memory_destroy((void **) & maps.array, sizeof(f_string_map), maps.size)) { \
          maps.size = 0; \
        } \
      } \
    }

  #define f_macro_string_maps_resize(status, maps, new_length) \
    status = F_none; \
    if (new_length < maps.size) { \
      f_array_length i = maps.size - new_length; \
      for (; i < maps.size; i++) { \
        f_macro_string_map_delete(status, maps.array[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & maps.array, sizeof(f_string_map), maps.size, new_length); \
    if (status == F_none) { \
      if (new_length > maps.size) { \
        f_array_length i = maps.size; \
        for (; i < new_length; i++) { \
          memset(&maps.array[i], 0, sizeof(f_string_map)); \
        } \
      } \
      maps.size = new_length; \
      if (maps.used > maps.size) maps.used = new_length; \
    }

  #define f_macro_string_maps_adjust(status, maps, new_length) \
    status = F_none; \
    if (new_length < maps.size) { \
      f_array_length i = maps.size - new_length; \
      for (; i < maps.size; i++) { \
        f_macro_string_map_destroy(status, maps.array[i], f_string_map); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & maps.array, sizeof(f_string_map), maps.size, new_length); \
    if (status == F_none) { \
      if (new_length > maps.size) { \
        f_array_length i = maps.size; \
        for (; i < new_length; i++) { \
          memset(&maps.array[i], 0, sizeof(f_string_map)); \
        } \
      } \
      maps.size = new_length; \
      if (maps.used > maps.size) maps.used = new_length; \
    }
#endif // _di_f_string_maps_

/**
 * A string map consisting of a name and multiple values.
 *
 * name: A string representing the map name.
 * value: An array of strings representing the map value.
 */
#ifndef _di_f_string_map_multi_
  typedef struct {
    f_string_dynamic name;
    f_string_dynamics value;
  } f_string_map_multi;

  #define f_string_map_multi_initialize { f_string_dynamic_initialize, f_string_dynamics_initialize }

  #define f_macro_string_map_multi_clear(map) \
    f_macro_string_dynamic_clear(map.name) \
    f_macro_string_dynamics_clear(map.value)

  #define f_macro_string_map_multi_delete(status, map) \
    f_macro_string_dynamic_delete(status, map.name) \
    if (status == F_none) { \
      f_macro_string_dynamics_delete(status, map.value) \
    }

  #define f_macro_string_map_multi_destroy(status, map) \
    f_macro_string_dynamic_destroy(status, map.name) \
    if (status == F_none) { \
      f_macro_string_dynamics_destroy(status, map.value) \
    }

  #define f_macro_string_map_multi_delete_simple(map) \
    f_macro_string_dynamic_delete_simple(map.name) \
    f_macro_string_dynamics_delete_simple(map.value)

  #define f_macro_string_map_multi_destroy_simple(map) \
    f_macro_string_dynamic_destroy_simple(map.name) \
    f_macro_string_dynamics_destroy_simple(map.value)
#endif // _di_f_string_map_multi_

/**
 * An array of string maps.
 *
 * array: the array of string maps.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_map_multis_
  typedef struct {
    f_string_map_multi *array;

    f_array_length size;
    f_array_length used;
  } f_string_map_multis;

  #define f_string_map_multis_initialize f_string_statics_initialize

  #define f_macro_string_map_multis_clear(maps) f_macro_string_statics_clear(maps)

  #define f_macro_string_map_multis_new(status, maps, length) \
    f_macro_string_map_multis_clear(maps) \
    status = f_memory_new((void **) & maps.array, sizeof(f_string_map_multi), length); \
    if (status == F_none) { \
      maps.size = length; \
      maps.used = 0; \
    }

  #define f_macro_string_map_multis_delete(status, maps) \
    status = F_none; \
    maps.used = maps.size; \
    while (maps.used > 0) { \
      maps.used--; \
      f_macro_string_map_multi_delete(status, maps.array[maps.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & maps.array, sizeof(f_string_map_multi), maps.size); \
    if (status == F_none) maps.size = 0;

  #define f_macro_string_map_multis_destroy(status, maps) \
    status = F_none; \
    maps.used = maps.size; \
    while (maps.used > 0) { \
      maps.used--; \
      f_macro_string_map_multi_destroy(status, maps.array[maps.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & maps.array, sizeof(f_string_map_multi), maps.size); \
    if (status == F_none) maps.size = 0;

  #define f_macro_string_map_multis_delete_simple(maps) \
    maps.used = maps.size; \
    while (maps.used > 0) { \
      maps.used--; \
      f_macro_string_map_multi_delete_simple(maps.array[maps.used]); \
      if (maps.used == 0) { \
        if (f_memory_delete((void **) & maps.array, sizeof(f_string_map_multi), maps.size)) { \
          maps.size = 0; \
        } \
      } \
    }

  #define f_macro_string_map_multis_destroy_simple(maps) \
    maps.used = maps.size; \
    while (maps.used > 0) { \
      maps.used--; \
      f_macro_string_map_multi_destroy_simple(maps.array[maps.used]); \
      if (maps.used == 0) { \
        if (f_memory_destroy((void **) & maps.array, sizeof(f_string_map_multi), maps.size)) { \
          maps.size = 0; \
        } \
      } \
    }

  #define f_macro_string_map_multis_resize(status, maps, new_length) \
    status = F_none; \
    if (new_length < maps.size) { \
      f_array_length i = maps.size - new_length; \
      for (; i < maps.size; i++) { \
        f_macro_string_map_multi_delete(status, maps.array[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & maps.array, sizeof(f_string_map_multi), maps.size, new_length); \
    if (status == F_none) { \
      if (new_length > maps.size) { \
        f_array_length i = maps.size; \
        for (; i < new_length; i++) { \
          memset(&maps.array[i], 0, sizeof(f_string_map_multi)); \
        } \
      } \
      maps.size = new_length; \
      if (maps.used > maps.size) maps.used = new_length; \
    }

  #define f_macro_string_map_multis_adjust(status, maps, new_length) \
    status = F_none; \
    if (new_length < maps.size) { \
      f_array_length i = maps.size - new_length; \
      for (; i < maps.size; i++) { \
        f_macro_string_map_multi_destroy(status, maps.array[i], f_string_map_multi); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & maps.array, sizeof(f_string_map_multi), maps.size, new_length); \
    if (status == F_none) { \
      if (new_length > maps.size) { \
        f_array_length i = maps.size; \
        for (; i < new_length; i++) { \
          memset(&maps.array[i], 0, sizeof(f_string_map_multi)); \
        } \
      } \
      maps.size = new_length; \
      if (maps.used > maps.size) maps.used = new_length; \
    }
#endif // _di_f_string_map_multis_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_h
