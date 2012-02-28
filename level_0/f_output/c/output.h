/* FLL - Level 0
 * Project:       Output
 * Version:       0.2.0
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides some standard I/O functions not available in a libc
 */
#ifndef _F_output_h
#define _F_output_h

// libc includes
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

// fll-0 includes
#include <level_0/strings.h>
#include <level_0/types.h>
#include <level_0/errors.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_f_print_string_
  // Similar to a c-library printf, except that this will only print a specific range
  // will not stop at \0
  // will not print \0
  // This implementation will not proces special characters, such as %s in the same way as printf functions, I am undecided whether or not to add this capability
  extern f_return_status f_print_string(f_file_type output, const f_string string, const f_string_length length);
#endif // _di_f_print_string_

#ifndef _di_f_print_dynamic_string_
  // Similar to a c-library printf, except that this will only print a specific range
  // will not stop at \0
  // will not print \0
  // will print the entire dynamic string
  // This implementation will not proces special characters, such as %s in the same way as printf functions, I am undecided whether or not to add this capability
  extern f_return_status f_print_dynamic_string(f_file_type output, const f_dynamic_string buffer);
#endif // _di_f_print_dynamic_string_


#ifndef _di_f_print_partial_dynamic_string_
  // Similar to a c-library printf, except that this will only print a specific range (
  // will not stop at \0
  // will not print \0
  // will print the only the buffer range specified by location
  // This implementation will not proces special characters, such as %s in the same way as printf functions, I am undecided whether or not to add this capability
  extern f_return_status f_print_partial_dynamic_string(f_file_type output, const f_dynamic_string buffer, const f_string_location location);
#endif // _di_f_print_partial_dynamic_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_output_h
