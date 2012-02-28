/* FLL - Level 0
 * Project:       Console
 * Version:       0.2.0
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 *  Some console input/output commands
 */
#ifndef _F_console_h
#define _F_console_h

// libc include
#include <string.h>

// fll-0 includes
#include <level_0/types.h>
#include <level_0/errors.h>
#include <level_0/strings.h>

#ifdef __cplusplus
extern "C"{
#endif

// result values that represent the type of command found
#ifndef _di_f_console_ids_
  #define f_console_none                0
  #define f_console_short_enable        1
  #define f_console_short_disable       2
  #define f_console_long_enable         3
  #define f_console_long_disable        4
  #define f_console_extra_enable        5
  #define f_console_extra_disable       6
  #define f_console_empty_short_enable  7
  #define f_console_empty_short_disable 8
  #define f_console_empty_long_enable   9
  #define f_console_empty_long_disable  10
  #define f_console_empty_extra_enable  11
  #define f_console_empty_extra_disable 12
#endif // _di_f_console_ids_

// the symbols passed to the program for option handling
#ifndef _di_f_console_symbols_
  #define f_console_symbol_enable        '-'   // this will be processed as an integer and therefore must not be string
  #define f_console_symbol_disable       '+'   // this will be processed as an integer and therefore must not be string
  #define f_console_symbol_short_enable  "-"
  #define f_console_symbol_short_disable "+"
  #define f_console_symbol_long_enable   "--"
  #define f_console_symbol_long_disable  "++"
  #define f_console_symbol_extra_enable  "---"
  #define f_console_symbol_extra_disable "+++"
#endif // _di_f_console_symbols_

// create some standard command line parameter options required by the kevux/fss/fll specifications
#ifndef _di_f_standard_console_parameters_
  #define f_console_standard_short_help     "h"
  #define f_console_standard_short_light    "l" // usage: +l
  #define f_console_standard_short_no_color "n" // usage: +n
  #define f_console_standard_short_version  "v"

  #define f_console_standard_long_help     "help"
  #define f_console_standard_long_light    "light"
  #define f_console_standard_long_no_color "no_color"
  #define f_console_standard_long_version  "version"
#endif // _di_f_standard_console_parameters_

// the maximum size for a single parameter (this should be hellishly more than enough)
#ifndef _di_f_console_max_size_
  #define f_console_max_size f_string_max_size
#endif // _di_f_console_max_size_

#ifndef _di_f_console_default_allocation_step_
  #define f_console_default_allocation_step f_memory_default_allocation_step
#endif // _di_f_console_default_allocation_step_

#ifndef _di_f_console_types_
  typedef f_min_u_short f_console_id;

  enum {
    f_console_result_none,
    f_console_result_found,
    f_console_result_additional, // something was found and extra data exists (such as '-f filename', filename would be the extra data)
  };

  enum {
    f_console_type_normal,
    f_console_type_inverse,
    f_console_type_other,
  };
#endif // _di_f_console_types_

#ifndef _di_f_console_parameter_
  typedef struct {
    const f_autochar *symbol_short;
    const f_autochar *symbol_long;
    const f_autochar *symbol_extra;
    const f_autochar *symbol_other;

    const f_bool    has_additional;
    const f_u_int   type;
    f_u_int         result;
    f_string_length additional;
    f_string_length length;
  } f_console_parameter;

  #define f_console_parameter_initialize(symbol_short, symbol_long, symbol_extra, symbol_other, has_additional, type_value, length) \
    { symbol_short, symbol_long, symbol_extra, symbol_other, has_additional, type_value, f_console_result_none, 0, length }
#endif // _di_f_console_parameter_

#ifndef _di_f_console_identify_
  // This is used to help standardize a single method of handling command line option parsing.
  // This should allow for every single command line program to use the same form of syntax for command line options.
  extern f_return_status f_console_identify(const f_string input, f_console_id *result);
#endif // _di_f_console_identify_

// perform checks against short & long options to see if the string is one of them (normal)
#ifndef _di_f_console_is_enable_
  #define f_console_is_enable(result, string, short_option, long_option, max_length) \
          ((result == f_console_short_enable && strncmp(string, short_option, 1) == 0) || \
          (result == f_console_long_enable && strncmp(string, long_option,  max_length) == 0))
#endif // _di_f_console_is_enable_

// perform checks against short & long options to see if the string is one of them (inverse)
#ifndef _di_f_console_is_disable_
  #define f_console_is_disable(result, string, short_option, long_option, max_length) \
          ((result == f_console_short_disable && strncmp(string, short_option, 1) == 0) || \
          (result == f_console_long_disable && strncmp(string, long_option,  max_length) == 0))
#endif // _di_f_console_is_disable_

// perform checks against extra option to see if the string is one of them (normal)
#ifndef _di_f_console_is_extra_enable_
  #define f_console_is_extra_enable(result, string, extra_option, max_length) \
          (result == f_console_extra_enable && strncmp(string, extra_option, max_length) == 0)
#endif // _di_f_console_is_extra_enable_

// perform checks against extra option to see if the string is one of them (inverse)
#ifndef _di_f_console_is_extra_disable_
  #define f_console_is_extra_disable(result, string, extra_option, max_length) \
          (result == f_console_extra_disable && strncmp(string, extra_option, max_length) == 0)
#endif // _di_f_console_is_extra_disable_

// perform checks against empty options to see if the string is one of them (normal)
#ifndef _di_f_console_is_empty_enable_
  #define f_console_is_empty_enable(result, string) \
          (result == f_console_empty_short_enable || result == f_console_empty_long_enable || result == f_console_empty_extra_enable)
#endif // _di_f_console_is_empty_enable_

// perform checks against empty options to see if the string is one of them (inverse)
#ifndef _di_f_console_is_empty_disable_
  #define f_console_is_empty_disable(result, string) \
          (result == f_console_empty_short_disable || result == f_console_empty_long_disable || result == f_console_empty_extra_disable)
#endif // _di_f_console_is_empty_disable_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_console_h
