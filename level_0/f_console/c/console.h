/**
 * FLL - Level 0
 *
 * Project: Console
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Some console input/output commands.
 */
#ifndef _F_console_h
#define _F_console_h

// libc include
#include <string.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/type.h>
#include <level_0/string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Result values that represent the type of command found.
 */
#ifndef _di_f_console_ids_
  enum {
    f_console_none,
    f_console_short_enable,
    f_console_short_disable,
    f_console_long_enable,
    f_console_long_disable,
    f_console_empty_short_enable,
    f_console_empty_short_disable,
    f_console_empty_long_enable,
    f_console_empty_long_disable,
  };
#endif // _di_f_console_ids_

/**
 * The symbols passed to the program for option handling.
 *
 * The following will be processed as an integer and therefore must not be string.
 * - f_console_symbol_enable
 * - f_console_symbol_disable
 */
#ifndef _di_f_console_symbols_
  #define f_console_symbol_enable  '-'
  #define f_console_symbol_disable '+'

  #define f_console_symbol_short_enable  "-"
  #define f_console_symbol_short_disable "+"

  #define f_console_symbol_long_enable  "--"
  #define f_console_symbol_long_disable "++"
#endif // _di_f_console_symbols_

/**
 * Create some standard command line parameter options required by the kevux/fss/fll specifications.
 */
#ifndef _di_f_standard_console_parameters_
  #define f_console_standard_short_debug    "d"
  #define f_console_standard_short_help     "h"
  #define f_console_standard_short_light    "l"
  #define f_console_standard_short_no_color "n"
  #define f_console_standard_short_version  "v"

  #define f_console_standard_long_debug    "debug"
  #define f_console_standard_long_help     "help"
  #define f_console_standard_long_light    "light"
  #define f_console_standard_long_no_color "no_color"
  #define f_console_standard_long_version  "version"
#endif // _di_f_standard_console_parameters_

/**
 * The maximum size for a single parameter.
 */
#ifndef _di_f_console_max_size_
  #define f_console_max_size f_string_max_size
#endif // _di_f_console_max_size_

/**
 * Provide a default allocation step.
 *
 * For a UTF-8 friendly allocation step, set to at least 4.
 */
#ifndef _di_f_console_default_allocation_step_
  #define f_console_default_allocation_step 4
#endif // _di_f_console_default_allocation_step_


/**
 * Provide console type enumerations:
 *
 * - none: parameter not found.
 * - found: parameter found.
 * - additional: parameter found, extra data exists (such as '-f filename', 'filename' would be the extra data).
 *
 * - normal: parameters using minus sign, such as '--help'.
 * - inverse: parameters using plus sign, such as '++version'.
 * - other: parameters using neither minus nor plus sign, such as 'build'.
 */
#ifndef _di_f_console_types_
  typedef f_min_u_short f_console_id;

  enum {
    f_console_result_none,
    f_console_result_found,
    f_console_result_additional,
  };

  enum {
    f_console_type_normal,
    f_console_type_inverse,
    f_console_type_other,
  };
#endif // _di_f_console_types_

/**
 * Provide a structure for describing console parameters for the console processing functions to use.
 *
 * The short parameters are will be prepended with either '-' or '+'.
 * The long parameters are will be prepended with either '--' or '++'.
 * The other parameters are for any other parameter that has no prepended characters.
 *
 * - symbol_short: The single character string, such as 'h' in '-h'.
 * - symbol_long: The multi-character string, such as 'help' in '--help'.
 * - symbol_other: The special meaning parameter, such as 'all' in 'make all'.
 *
 * - has_additional: Designates that a parameter will have a given number of additional arguments, such as 'blue' in '--color blue'.
 * - type: One of the f_console_type_* codes, defining how this parameter is to be processed.
 * - result: A code representing that the parameter was found and how it was found ('-h' vs '--help').
 * - total: A number representing the total number of times this parameter was found ('-h -h' would result in a total of 2).
 * - additional: An array of locations representing where in the argv[] the additional arguments are found.
 */
#ifndef _di_f_console_parameter_
  typedef struct {
    const char *symbol_short;
    const char *symbol_long;
    const char *symbol_other;

    const uint8_t has_additional;
    const uint8_t type;

    uint8_t result;
    uint8_t total;

    f_string_lengths additional;
  } f_console_parameter;

  #define f_console_parameter_initialize(symbol_short, symbol_long, symbol_other, has_additional, type_value) \
    { symbol_short, symbol_long, symbol_other, has_additional, type_value, f_console_result_none, 0, f_string_lengths_initialize }
#endif // _di_f_console_parameter_

/**
 * Determine the type code the given input parameter represents.
 *
 * @param input
 *   The input parameter to process.
 * @param result
 *   The resulting console type code determined by this function.
 *
 * @return
 *   f_none on success.
 *   f_no_data the input string is empty.
 *   f_reallocation_error (with error bit) on memory reallocation error.
 */
#ifndef _di_f_console_identify_
  extern f_return_status f_console_identify(const f_string input, f_console_id *result);
#endif // _di_f_console_identify_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_console_h
