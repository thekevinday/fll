/* FLL - Level 0
 * Project:       FSS
 * Version:       0.4.2
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Defines all datatypes to be used for/by project fss
 *
 * The purpose of compression is not to compression the entire file's contents but only and individual objects content, so the file is still partially readable
 * NOTE: all start/stop locations must be defined as a (start < stop) and not (start <= stop), therefore if (start == stop) then stop
 */
#ifndef _F_fss_h
#define _F_fss_h

// fll includes
#include <level_0/errors.h>
#include <level_0/types.h>
#include <level_0/strings.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_f_fss_types_
  #define f_fss_comment             '#'
  #define f_fss_space               ' '
  #define f_fss_space_holder        '_'
  #define f_fss_basic_open          ' '
  #define f_fss_basic_close         '\n'
  #define f_fss_extended_open       ' '
  #define f_fss_extended_close      '\n'
  #define f_fss_list_terminator     '\n'
  #define f_fss_basic_list_open     ':'
  #define f_fss_basic_list_close    '\0'
  #define f_fss_extended_list_open  '{'
  #define f_fss_extended_list_close '}'
  #define f_fss_type_header_open    '#'
  #define f_fss_type_header_part1   ' '
  #define f_fss_type_header_part2   'f'
  #define f_fss_type_header_part3   's'
  #define f_fss_type_header_part4   's'
  #define f_fss_type_header_part5   '-'
  #define f_fss_type_header_close   '\n'

  #define f_fss_id            f_u_long
  #define f_fss_checksum      f_dynamic_string
  #define f_fss_header_length f_string_length

  #define f_fss_id_initialize            0
  #define f_fss_checksum_initialize      0
  #define f_fss_header_length_initailize 0
#endif // _di_f_fss_types_

#ifndef _di_f_fss_delimiters_
  #define f_fss_delimit_slash        '\\'
  #define f_fss_delimit_single_quote '\''
  #define f_fss_delimit_double_quote '"'
  #define f_fss_delimit_placeholder  f_placeholder
#endif //_di_f_fss_delimiters_

#ifndef _di_f_fss_codes_
enum {
  f_fss_basic,
  f_fss_extended,
  f_fss_basic_list,
  f_fss_extended_list,
  f_fss_very_basic_list,
  f_fss_somewhat_basic_list,
  f_fss_somewhat_extended_list,
  f_fss_very_extended_list,
  f_fss_embeded_list,
  f_fss_reverse_mapping,
  f_fss_extended_reverse_mapping,
  f_fss_advanced_reverse_mapping,
  f_fss_simple_list,
};
#endif // _di_f_fss_codes_

#ifndef _di_f_fss_max_header_length_
  #define f_fss_max_header_length 12
#endif // _di_f_fss_max_header_length_

#ifndef _di_f_fss_default_allocation_step_
  #define f_fss_default_allocation_step f_memory_default_allocation_step
#endif // _di_f_fss_default_allocation_step_

#ifndef _di_f_fss_delimits_
  typedef f_string_locations f_fss_delimits;
  #define f_fss_delimits_initialize f_string_locations_initialize

  #define f_delete_fss_delimits(status, array)  f_delete_string_location_array(status, array)
  #define f_destroy_fss_delimits(status, array) f_destroy_string_location_array(status, array)

  #define f_resize_fss_delimits(status, array, new_length) f_resize_string_location_array(status, array, new_length)
  #define f_adjust_fss_delimits(status, array, new_length) f_adjust_string_location_array(status, array, new_length)
#endif // _di_f_fss_delimits_

// stores information about a particular fss file, otherwise know as its header
#ifndef _di_f_fss_header_
  typedef struct {
    f_fss_id            type;   // what kind of fss file is this?
    f_fss_header_length length; // Total length of the header
  } f_fss_header;

  #define f_fss_header_initialize { f_fss_id_initialize, f_fss_header_length_initialize }
#endif // _di_f_fss_header_

// This holds an array of fss_headers
#ifndef _di_f_fss_headers_
  typedef struct {
    f_fss_header    *array; // the array of fss headers
    f_string_length size;   // total amount of allocated space
    f_string_length used;   // total number of allocated spaces used
  } f_fss_headers;

  #define f_fss_headers_initialize { 0, 0, 0 }

  #define f_delete_fss_headers(status, headers) \
    f_delete_structure(status, headers, f_fss_header)

  #define f_destroy_fss_headers(status, headers) \
    f_destroy_structure(status, headers, f_fss_header)

  #define f_resize_fss_headers(status, headers, new_length) \
    f_resize_structure(status, headers, f_fss_header, new_length)


  #define f_adjust_fss_headers(status, headers, new_length) \
    f_adjust_structure(status, headers, f_fss_header, new_length)
#endif // _di_f_fss_headers_


// This is a location that represents an object
#ifndef _di_fss_object_
  typedef f_string_location f_fss_object;
  #define f_fss_object_initialize f_string_location_initialize

  #define f_new_fss_object(status, object, length)   status = f_new_array((void **) & object, sizeof(f_fss_object), length)
  #define f_delete_fss_object(status, object)        status = f_delete((void **) & object)
  #define f_destroy_fss_object(status, object, size) status = f_destroy((void **) & object, sizeof(f_fss_object), size)

  #define f_resize_fss_object(status, object, old_length, new_length) \
    status = f_resize((void **) & object, sizeof(f_fss_object), old_length, new_length)

  #define f_adjust_fss_object(status, object, old_length, new_length) \
    status = f_adjust((void **) & object, sizeof(f_fss_object), old_length, new_length)
#endif // _di_fss_object_

// This holds an array of fss_object
#ifndef _di_fss_objects_
  typedef struct {
    f_fss_object    *array; // the array of fss objects
    f_string_length size;   // total amount of allocated space
    f_string_length used;   // total number of allocated spaces used
  } f_fss_objects;

  #define f_fss_objects_initialize { 0, 0, 0 }

  #define f_delete_fss_objects(status, objects) \
    f_delete_structure(status, objects, f_fss_object)

  #define f_destroy_fss_objects(status, objects) \
    f_destroy_structure(status, objects, f_fss_object)

  #define f_resize_fss_objects(status, objects, new_length) \
    f_resize_structure(status, objects, f_fss_object, new_length)

  #define f_adjust_fss_objects(status, objects, new_length) \
    f_destroy_structure(status, objects, f_fss_object, new_length)
#endif // _di_fss_objects_

// This holds an array of string locations that represent the content
// The very first string location will represent the outmost content
// All of the following string locations will represent the first level of nesting of all sub-content
// There will be no nesting beyond the first level recorded in this structure
#ifndef _di_fss_content_
  typedef struct {
    f_string_location *array; // the array of locations
    f_array_length   size;   // total amount of allocated space
    f_array_length   used;   // total number of allocated spaces used
  } f_fss_content;

  #define f_fss_content_initialize { 0, 0, 0 }

  #define f_delete_fss_content(status, content) \
    f_delete_structure(status, content, f_string_location)

  #define f_destroy_fss_content(status, content) \
    f_destroy_structure(status, content, f_string_location)

  #define f_resize_fss_content(status, content, new_length) \
    f_resize_structure(status, content, f_string_location, new_length)

  #define f_adjust_fss_content(status, content, new_length) \
    f_adjust_structure(status, content, f_string_location, new_length)
#endif // _di_fss_content_

// This holds an array of fss_content
#ifndef _di_f_fss_contents_
  typedef struct {
    f_fss_content   *array; // the array of fss content
    f_array_length  size;  // total amount of allocated space
    f_array_length  used;  // total number of allocated spaces used
  } f_fss_contents;

  #define f_fss_contents_initialize { 0, 0, 0 }

  #define f_delete_fss_contents(status, contents) \
    f_delete_structures(status, contents, f_fss_content)

  #define f_destroy_fss_contents(status, contents) \
    f_destroy_structures(status, contents, f_fss_content)

  #define f_resize_fss_contents(status, contents, new_length) \
    f_resize_structures(status, contents, f_fss_content, new_length, f_array_length)

  #define f_adjust_fss_contents(status, contents, new_length) \
    f_resize_structures(status, contents, f_fss_content, new_length, f_array_length)
#endif // _di_f_fss_contents_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_h
