/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines fll type data.
 *
 * This is auto-included by type.h and should not need to be explicitly included.
 */
#ifndef _F_type_fll_h
#define _F_type_fll_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An FLL Identifier represents a way to identify FLL related text files and possibly binary files.
 *
 * This was originally designed for FSS (Featureless Settings Specification) but has been expanded to be used by the entire project.
 *
 * An FLL Identifier consists of two parts:
 * 1) A 64-byte long string representing a machine-name for the type.
 * 2) A 16-bit digit representing 2^16 possible type classifications, which is representeed by 4 hexadecial 1-byte strings for text.
 *
 * For example "fss-1234" is a valid type such that:
 * 1) name: "fss".
 * 2) type: "1234", (or 0x1 in binary.
 *
 * UTF-8 codes are available, but one must consider that 1 4-byte characte still takes up 4-bytes.
 * Therefore for all 4-byte UTF-8 characters, there is a maximum of 16 characters available.
 *
 * This intentionally utilizes a fixed array to avoid the need of dynamic allocation.
 *
 * The macro_f_fll_id_t_clear() only performs a minimalistic clear on the id.name string.
 * The first character in the string array is assigned to NULL.
 * For a more accurate clear, use memset() or something similar.
 *
 * The name must only be "word" characters (therefore "-" is not allowed).
 *
 * Properties:
 *   - name: The string representing the name of the FLL Identifier (This is not a NULL terminated string).
 *   - type: The code representing the type of the Identifier.
 *   - used: A representation of how many bytes in name are in used (if 0, then there is no name, thus this can be seen as not a valid identifier).
 */
#ifndef _di_f_fll_id_t_
  #define f_fll_id_name_length_d 64

  typedef struct {
    char name[f_fll_id_name_length_d];

    uint16_t type;
    uint8_t used;
  } f_fll_id_t;

  #define f_fll_id_t_initialize { \
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, \
    0, \
    0, \
  }

  #define macro_f_fll_id_t_initialize_1(name, type, used) { name, type, used }

  #define macro_f_fll_id_t_clear(id) \
    id.name[0] = 0; \
    id.type = 0; \
    id.used = 0;
#endif // _di_f_fll_id_t_

/**
 * An array of f_fll_id_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of f_fll_id_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fll_ids_t_
  typedef struct {
    f_fll_id_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_fll_ids_t;

  #define f_fll_ids_t_initialize { 0, 0, 0 }

  #define macro_f_fll_ids_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_fll_ids_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_fll_ids_t_

/**
 * This holds an array of f_fll_ids_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of f_fll_id_t arrays.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fll_idss_t_
  typedef struct {
    f_fll_ids_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_fll_idss_t;

  #define f_fll_idss_t_initialize { 0, 0, 0 }

  #define macro_f_fll_idss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_fll_idss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_fll_idss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_fll_h
