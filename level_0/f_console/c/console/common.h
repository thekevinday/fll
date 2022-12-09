/**
 * FLL - Level 0
 *
 * Project: Console
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project console.
 *
 * This is auto-included by console.h and should not need to be explicitly included.
 */
#ifndef _F_console_common_h
#define _F_console_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The symbols passed to the program for option handling.
 *
 * For historical reasons the "-" is the normal symbol and "+" is the inverse.
 */
#ifndef _di_f_console_symbol_s_
  #define F_console_symbol_short_normal_s  "-"
  #define F_console_symbol_short_inverse_s "+"

  #define F_console_symbol_short_normal_s_length  1
  #define F_console_symbol_short_inverse_s_length 1

  #define F_console_symbol_long_normal_s  "--"
  #define F_console_symbol_long_inverse_s "++"

  #define F_console_symbol_long_normal_s_length  2
  #define F_console_symbol_long_inverse_s_length 2

  #ifndef _di_f_console_symbol_short_normal_s_
    extern const f_string_static_t f_console_symbol_short_normal_s;
  #endif // _di_f_console_symbol_short_normal_s_

  #ifndef _di_f_console_symbol_short_inverse_s_
    extern const f_string_static_t f_console_symbol_short_inverse_s;
  #endif // _di_f_console_symbol_short_inverse_s_

  #ifndef _di_f_console_symbol_long_normal_s_
    extern const f_string_static_t f_console_symbol_long_normal_s;
  #endif // _di_f_console_symbol_long_normal_s_

  #ifndef _di_f_console_symbol_long_inverse_s_
    extern const f_string_static_t f_console_symbol_long_inverse_s;
  #endif // _di_f_console_symbol_long_inverse_s_
#endif // _di_f_console_symbol_s_

/**
 * Create some standard command line parameter options required/expected by the kevux/fss/fll specifications.
 *
 * It is expected that all of the "+" and "++" console options described below are reserved for these purposes.
 * This is not a strict requirement as such a thing is non-sense in open-source, but this should be considered a strong recommendation.
 *
 * It is acceptable for any of these options, when specified multiple times, for that number of times to represent the "level".
 * For example, a "+D +D" means more debug output than simply "+D".
 *
 * The verbosity interpretation used as the default for many of the level 3 programs in this process, is to treat verbosity modes as a scale from quiet to debug with quiet as the least verbose and debug as the most verbose.
 * This is not strictly a requirement, but expect level 3 projects to work this way.
 *
 * The following options are subjective in interpretation of the verbosity but are expected to be follow the general interpretation:
 *   - debug:         Enable debugging, which will likely increase output verbosity.
 *   - error:         Similar to quiet, except that error messages are printed (this is less verbose than "normal").
 *   - normal:        Use normal printing (don't use debug/quiet/verbose).
 *   - quiet:         Decrease verbosity, print less, in some use cases this could mean printing nothing.
 *   - verbose:       Increase verbosity, print more, in some use cases this could mean printing just about everything.
 *   - line_first_no: Don't print the first line if one is to be printed (useful in scripts) (may include error/warning messages).
 *   - line_last_no:  Don't print the last line if one is to be printed (useful in scripts) (may include error/warning messages).
 *
 * The following are less subjective in interpretation but do allow some flexibility.
 *   - dark:     Do display color intended for dark backgrounds (often the default behavior) when printing to the console. Other contexts may be acceptable (such as voice inflections, or lack-thereof) for audio.)
 *   - help:     Display the help text. This does not define how the text is displayed only that the text is displayed.
 *   - light:    Do display color intended for light backgrounds when printing to the console. Other contexts may be acceptable (such as voice inflections, or lack-thereof) for audio.)
 *   - no_color: Do not display color when printing to the console. Other contexts may be acceptable (such as voice inflections, or lack-thereof) for audio.)
 *   - version:  Should always print only the version number, no colors, but what represents the version number is undefined by this project.
 *
 * The following options are for special purposes:
 *   - status_in:  Is intended to accept the name of an environment variable in which to read the status from.
 *   - status_out: Is intended to accept the name of an environment variable in which to ride the status to.
 *
 * In the case of "status_in" and "status_out", the environment variable will store a string representing the base-10 unsigned 16-bit status code.
 *   - In the case of "status_in" the environment variable is being read in, which means that it should be the status from some previous execution.
 *   - In the case of "status_out" the environment variable is being written to, which means that it should store the status this program exits with.
 *     - To avoid problems with the status code after a program is forcibly killed, the status_out environment variable should be cleared at program start.
 */
#ifndef _di_f_console_standard_s_
  #define F_console_standard_short_dark_s          "d"
  #define F_console_standard_short_debug_s         "D"
  #define F_console_standard_short_error_s         "E"
  #define F_console_standard_short_help_s          "h"
  #define F_console_standard_short_light_s         "l"
  #define F_console_standard_short_line_first_no_s "F"
  #define F_console_standard_short_line_last_no_s  "L"
  #define F_console_standard_short_no_color_s      "n"
  #define F_console_standard_short_normal_s        "N"
  #define F_console_standard_short_quiet_s         "Q"
  #define F_console_standard_short_status_in_s     "s"
  #define F_console_standard_short_status_out_s    "S"
  #define F_console_standard_short_verbose_s       "V"
  #define F_console_standard_short_version_s       "v"

  #define F_console_standard_short_dark_s_length          1
  #define F_console_standard_short_debug_s_length         1
  #define F_console_standard_short_error_s_length         1
  #define F_console_standard_short_help_s_length          1
  #define F_console_standard_short_light_s_length         1
  #define F_console_standard_short_line_first_no_s_length 1
  #define F_console_standard_short_line_last_no_s_length  1
  #define F_console_standard_short_no_color_s_length      1
  #define F_console_standard_short_normal_s_length        1
  #define F_console_standard_short_quiet_s_length         1
  #define F_console_standard_short_status_in_s_length     1
  #define F_console_standard_short_status_out_s_length    1
  #define F_console_standard_short_verbose_s_length       1
  #define F_console_standard_short_version_s_length       1

  #define F_console_standard_long_dark_s          "dark"
  #define F_console_standard_long_debug_s         "debug"
  #define F_console_standard_long_error_s         "error"
  #define F_console_standard_long_help_s          "help"
  #define F_console_standard_long_light_s         "light"
  #define F_console_standard_long_line_first_no_s "line_first_no"
  #define F_console_standard_long_line_last_no_s  "line_last_no"
  #define F_console_standard_long_no_color_s      "no_color"
  #define F_console_standard_long_normal_s        "normal"
  #define F_console_standard_long_quiet_s         "quiet"
  #define F_console_standard_long_status_in_s     "status_in"
  #define F_console_standard_long_status_out_s    "status_out"
  #define F_console_standard_long_verbose_s       "verbose"
  #define F_console_standard_long_version_s       "version"

  #define F_console_standard_long_dark_s_length          4
  #define F_console_standard_long_debug_s_length         5
  #define F_console_standard_long_error_s_length         5
  #define F_console_standard_long_help_s_length          4
  #define F_console_standard_long_light_s_length         5
  #define F_console_standard_long_line_first_no_s_length 13
  #define F_console_standard_long_line_last_no_s_length  12
  #define F_console_standard_long_no_color_s_length      8
  #define F_console_standard_long_normal_s_length        6
  #define F_console_standard_long_quiet_s_length         5
  #define F_console_standard_long_status_in_s_length     9
  #define F_console_standard_long_status_out_s_length    10
  #define F_console_standard_long_verbose_s_length       7
  #define F_console_standard_long_version_s_length       7

  #ifndef _di_f_console_standard_short_dark_s_
    extern const f_string_static_t f_console_standard_short_dark_s;
  #endif // _di_f_console_standard_short_dark_s_

  #ifndef _di_f_console_standard_short_debug_s_
    extern const f_string_static_t f_console_standard_short_debug_s;
  #endif // _di_f_console_standard_short_debug_s_

  #ifndef _di_f_console_standard_short_error_s_
    extern const f_string_static_t f_console_standard_short_error_s;
  #endif // _di_f_console_standard_short_error_s_

  #ifndef _di_f_console_standard_short_help_s_
    extern const f_string_static_t f_console_standard_short_help_s;
  #endif // _di_f_console_standard_short_help_s_

  #ifndef _di_f_console_standard_short_light_s_
    extern const f_string_static_t f_console_standard_short_light_s;
  #endif // _di_f_console_standard_short_light_s_

  #ifndef _di_f_console_standard_short_line_first_no_s_
    extern const f_string_static_t f_console_standard_short_line_first_no_s;
  #endif // _di_f_console_standard_short_line_first_no_s_

  #ifndef _di_f_console_standard_short_line_last_no_s_
    extern const f_string_static_t f_console_standard_short_line_last_no_s;
  #endif // _di_f_console_standard_short_line_last_no_s_

  #ifndef _di_f_console_standard_short_no_color_s_
    extern const f_string_static_t f_console_standard_short_no_color_s;
  #endif // _di_f_console_standard_short_no_color_s_

  #ifndef _di_f_console_standard_short_normal_s_
    extern const f_string_static_t f_console_standard_short_normal_s;
  #endif // _di_f_console_standard_short_normal_s_

  #ifndef _di_f_console_standard_short_quiet_s_
    extern const f_string_static_t f_console_standard_short_quiet_s;
  #endif // _di_f_console_standard_short_quiet_s_

  #ifndef _di_f_console_standard_short_status_in_s_
    extern const f_string_static_t f_console_standard_short_status_in_s;
  #endif // _di_f_console_standard_short_status_in_s_

  #ifndef _di_f_console_standard_short_status_out_s_
    extern const f_string_static_t f_console_standard_short_status_out_s;
  #endif // _di_f_console_standard_short_status_out_s_

  #ifndef _di_f_console_standard_short_verbose_s_
    extern const f_string_static_t f_console_standard_short_verbose_s;
  #endif // _di_f_console_standard_short_verbose_s_

  #ifndef _di_f_console_standard_short_version_s_
    extern const f_string_static_t f_console_standard_short_version_s;
  #endif // _di_f_console_standard_short_version_s_

  #ifndef _di_f_console_standard_long_dark_s_
    extern const f_string_static_t f_console_standard_long_dark_s;
  #endif // _di_f_console_standard_long_dark_s_

  #ifndef _di_f_console_standard_long_debug_s_
    extern const f_string_static_t f_console_standard_long_debug_s;
  #endif // _di_f_console_standard_long_debug_s_

  #ifndef _di_f_console_standard_long_error_s_
    extern const f_string_static_t f_console_standard_long_error_s;
  #endif // _di_f_console_standard_long_error_s_

  #ifndef _di_f_console_standard_long_help_s_
    extern const f_string_static_t f_console_standard_long_help_s;
  #endif // _di_f_console_standard_long_help_s_

  #ifndef _di_f_console_standard_long_light_s_
    extern const f_string_static_t f_console_standard_long_light_s;
  #endif // _di_f_console_standard_long_light_s_

  #ifndef _di_f_console_standard_long_line_first_no_s_
    extern const f_string_static_t f_console_standard_long_line_first_no_s;
  #endif // _di_f_console_standard_long_line_first_no_s_

  #ifndef _di_f_console_standard_long_line_last_no_s_
    extern const f_string_static_t f_console_standard_long_line_last_no_s;
  #endif // _di_f_console_standard_long_line_last_no_s_

  #ifndef _di_f_console_standard_long_no_color_s_
    extern const f_string_static_t f_console_standard_long_no_color_s;
  #endif // _di_f_console_standard_long_no_color_s_

  #ifndef _di_f_console_standard_long_normal_s_
    extern const f_string_static_t f_console_standard_long_normal_s;
  #endif // _di_f_console_standard_long_normal_s_

  #ifndef _di_f_console_standard_long_quiet_s_
    extern const f_string_static_t f_console_standard_long_quiet_s;
  #endif // _di_f_console_standard_long_quiet_s_

  #ifndef _di_f_console_standard_long_status_in_s_
    extern const f_string_static_t f_console_standard_long_status_in_s;
  #endif // _di_f_console_standard_long_status_in_s_

  #ifndef _di_f_console_standard_long_status_out_s_
    extern const f_string_static_t f_console_standard_long_status_out_s;
  #endif // _di_f_console_standard_long_status_out_s_

  #ifndef _di_f_console_standard_long_verbose_s_
    extern const f_string_static_t f_console_standard_long_verbose_s;
  #endif // _di_f_console_standard_long_verbose_s_

  #ifndef _di_f_console_standard_long_version_s_
    extern const f_string_static_t f_console_standard_long_version_s;
  #endif // _di_f_console_standard_long_version_s_
#endif // _di_f_console_standard_s_

/**
 * The maximum size for a single parameter (the length of the string representing the parameter).
 *
 * The ideal parameter value is F_array_length_t_size_d, which generally defaults to 2^64 (unsigned).
 * However, the libc/POSIX appears to limit this to 2^63 (signed).
 */
#ifndef _di_f_console_length_size_
  #define F_console_parameter_size_d F_string_t_size_d
#endif // _di_f_console_length_size_

/**
 * Provide console flag data type.
 */
#ifndef _di_f_console_flag_t_
  typedef uint8_t f_console_flag_t;

  #define f_console_flag_t_initialize 0
#endif // _di_f_console_flag_t_

/**
 * Provide console flags.
 *
 * The flags are bits or sets of bits used for designating different states of the parameter.
 *
 * The disabled flag prevents it from being processed at all and will be treated as other data.
 * If the flag should still be processed, then do not set disabled flag and instead just ignore it when found.
 *
 * f_console_flag_*e:
 *   - none:    No flag data is set.
 *   - normal:  Parameters using minus sign, such as '--help' ("inverse" and "additional" bits are 0.
 *   - inverse: Parameters using plus sign, such as '++version'.
 *   - simple:  Parameters using neither minus nor plus sign, such as 'build'.
 *   - complex: Parameters that provide a set of additional parameters, similar to 'git clone http:s//..' (Not yet implemented).
 *   - disable: This parameter is disabled (does not get processed).
 *
 * f_console_flag_mask_*:
 *   - type:  A mask for selecting the bits representing all possible type value flags.
 *   - state: A mask for selecting the bits representing all possible state flags.
 */
#ifndef _di_f_console_flag_e_
  enum {
    f_console_flag_none_e    = 0x0,

    // Type flags.
    f_console_flag_normal_e  = 0x1,
    f_console_flag_inverse_e = 0x2,
    f_console_flag_simple_e  = 0x4,
    f_console_flag_complex_e = 0x8,

    // State flags.
    f_console_flag_disable_e = 0x10,
  }; // enum

  #define f_console_flag_mask_type_d  0xf
  #define f_console_flag_mask_state_d 0x10
#endif // _di_f_console_flag_e_

/**
 * The console result data type.
 */
#ifndef _di_f_console_result_t_
  typedef uint8_t f_console_result_t;

  #define f_console_result_t_initialize 0
#endif // _di_f_console_result_t_

/**
 * Result values that represent the type of command found.
 *
 * Here "alone" refers to '-', or '++', in that they only have the symbols (whereas '-x', or '++x' would not be alone).
 *
 * f_console_result_*e:
 *   - none:    No flags are set.
 *   - found:   The parameter has been found.
 *   - normal:  The normal prefix character ("-" by default) has been found.
 *   - inverse: The inverse prefix character ("+" by default) has been found.
 *   - short:   The found prefix is short (only a single character, such as "-" or "+").
 *   - long:    The found prefix is long (two characters, such as "--" or "++").
 *   - alone:   The prefix character is by itself (such as only "-" rather than "-h").
 *   - value:   One or more values associated with the parameter have been found.
 */
#ifndef _di_f_console_result_e_
  enum {
    f_console_result_none_e    = 0x0,
    f_console_result_found_e   = 0x1,
    f_console_result_normal_e  = 0x2,
    f_console_result_inverse_e = 0x4,
    f_console_result_short_e   = 0x8,
    f_console_result_long_e    = 0x10,
    f_console_result_alone_e   = 0x20,
    f_console_result_value_e   = 0x40,
  }; // enum
#endif // _di_f_console_result_e_

/**
 * Provide the standard verbosity codes.
 *
 * Intended to be used for the basic/standard verbosity modes for all programs following this practice.
 *
 * These are expected to be in numeric order such that the smallest number is the least verbose and the highest number is the most verbose.
 *
 * f_console_verbosity_*:
 *   - quiet:   Verbosity is set to quiet.
 *   - error:   Verbosity is set to error.
 *   - normal:  Verbosity is set to normal.
 *   - verbose: Verbosity is set to verbose.
 *   - debug:   Verbosity is set to debug.
 */
#ifndef _di_f_console_verbosity_
  enum {
    f_console_verbosity_quiet_e = 1,
    f_console_verbosity_error_e,
    f_console_verbosity_normal_e,
    f_console_verbosity_verbose_e,
    f_console_verbosity_debug_e,
  };
#endif // _di_f_console_verbosity_

/**
 * Provide a structure for describing console parameters for the console processing functions to use.
 *
 * The short parameters are prepended with either '-' or '+'.
 * The long parameters are prepended with either '--' or '++'.
 * The simple parameters have no prefix characters.
 *
 * symbol_short:  The NULL terminated single character string, such as 'h' in '-h'.
 * symbol_long:   The NULL terminated multi-character string, such as 'help' in '--help'.
 * symbol_simple: The NULL terminated parameter that has no prefix, such as 'all' in 'make all'.
 * values_total:  Designates that a parameter will have a given number of values arguments, such as 'blue' in '--color blue'.
 * flag:          A set of bits for providing.
 * result:        A set of bits representing if and how the parameter is found (such as '-h' vs '--help').
 * location:      The last location in argv[] where this parameter is found.
 * location_sub:  The last sub-location at location in argv (only used by short parameters, such as -h or +l).
 * locations:     All locations within argv where this parameter is found (order is preserved).
 * locations_sub: All sub-locations within argv where this parameter is found (order is preserved).
 * values:        An array of locations representing where in the argv[] the values arguments are found.
 *
 * The macro_f_console_parameter_t_initialize() all arguments.
 * The macro_f_console_parameter_t_initialize2() reduced arguments.
 * The macro_f_console_parameter_t_initialize3() reduced arguments, strings are of f_string_static_t, has short, long, and simple.
 * The macro_f_console_parameter_t_initialize4() reduced arguments, strings are of f_string_static_t, has short and long.
 * The macro_f_console_parameter_t_initialize5() reduced arguments, strings are of f_string_static_t, has short.
 * The macro_f_console_parameter_t_initialize6() reduced arguments, strings are of f_string_static_t, has long.
 * The macro_f_console_parameter_t_initialize7() reduced arguments, strings are of f_string_static_t, has simple.
 */
#ifndef _di_f_console_parameter_t_
  typedef struct {
    f_string_t symbol_short;
    f_string_t symbol_long;
    f_string_t symbol_simple;

    uint16_t values_total;

    f_console_flag_t flag;
    f_console_result_t result;
    f_array_length_t location;
    f_array_length_t location_sub;
    f_array_lengths_t locations;
    f_array_lengths_t locations_sub;
    f_array_lengths_t values;
  } f_console_parameter_t;

  #define f_console_parameter_t_initialize { \
    0, \
    0, \
    0, \
    f_console_flag_t_initialize, \
    f_console_result_t_initialize, \
    f_array_length_t_initialize, \
    f_array_length_t_initialize, \
    f_array_length_t_initialize, \
    f_array_lengths_t_initialize, \
    f_array_lengths_t_initialize, \
    f_array_lengths_t_initialize, \
  }

  #define macro_f_console_parameter_t_initialize(symbol_short, symbol_long, symbol_simple, values_total, flag, result, location, location_sub, locations, locations_sub, values) { \
    symbol_short, \
    symbol_long, \
    symbol_simple, \
    values_total, \
    flag, \
    result, \
    total, \
    location, \
    location_sub, \
    locations, \
    locations_sub, \
    values, \
  }

  #define macro_f_console_parameter_t_initialize2(symbol_short, symbol_long, symbol_simple, values_total, flag) { \
    symbol_short, \
    symbol_long, \
    symbol_simple, \
    values_total, \
    flag, \
    f_console_result_none_e, \
    0, \
    0, \
    f_array_lengths_t_initialize, \
    f_array_lengths_t_initialize, \
    f_array_lengths_t_initialize, \
  }

  #define macro_f_console_parameter_t_initialize3(symbol_short, symbol_long, symbol_simple, values_total, flag) { \
    symbol_short.string, \
    symbol_long.string, \
    symbol_simple.string, \
    values_total, \
    flag, \
    f_console_result_none_e, \
    0, \
    0, \
    f_array_lengths_t_initialize, \
    f_array_lengths_t_initialize, \
    f_array_lengths_t_initialize, \
  }

  #define macro_f_console_parameter_t_initialize4(symbol_short, symbol_long, values_total, flag) { \
    symbol_short.string, \
    symbol_long.string, \
    0, \
    values_total, \
    flag, \
    f_console_result_none_e, \
    0, \
    0, \
    f_array_lengths_t_initialize, \
    f_array_lengths_t_initialize, \
    f_array_lengths_t_initialize, \
  }

  #define macro_f_console_parameter_t_initialize5(symbol_short, values_total, flag) { \
    symbol_short.string, \
    0, \
    0, \
    values_total, \
    flag, \
    f_console_result_none_e, \
    0, \
    0, \
    f_array_lengths_t_initialize, \
    f_array_lengths_t_initialize, \
    f_array_lengths_t_initialize, \
  }

  #define macro_f_console_parameter_t_initialize6(symbol_long, values_total, flag) { \
    0, \
    symbol_long.string, \
    0, \
    values_total, \
    flag, \
    f_console_result_none_e, \
    0, \
    0, \
    f_array_lengths_t_initialize, \
    f_array_lengths_t_initialize, \
    f_array_lengths_t_initialize, \
  }

  #define macro_f_console_parameter_t_initialize7(symbol_simple, values_total, flag) { \
    0, \
    0, \
    symbol_simple.string, \
    values_total, \
    flag, \
    f_console_result_none_e, \
    0, \
    0, \
    f_array_lengths_t_initialize, \
    f_array_lengths_t_initialize, \
    f_array_lengths_t_initialize, \
  }
#endif // _di_f_console_parameter_t_

/**
 * Provide a helper structure for references and processing parameters.
 *
 * Designed for passing this to a function as a single argument.
 *
 * This is not intended to be dynamically allocated, so there is no "size" property.
 *
 * array:     Intended to be populated with an array of f_console_parameter_t whose size is defined by the "used" property.
 * arguments: An array of arguments pointing to the argv[] strings with the string lengths already calculated (This is a dynamic array of f_string_static_t).
 * remaining: An array of indexes within the arguments representing unmatched parameters.
 * length:    The total number of parameters in the parameters array.
 */
#ifndef _di_f_console_parameters_t_
  typedef struct {
    f_console_parameter_t *array;

    f_string_dynamics_t arguments;
    f_array_lengths_t remaining;

    f_array_length_t used;
  } f_console_parameters_t;

  #define f_console_parameters_t_initialize {0, f_string_dynamics_t_initialize, f_array_lengths_t_initialize, 0 }

  #define macro_f_console_parameters_t_initialize(parameter, used) { parameter, f_string_dynamics_t_initialize, f_array_lengths_t_initialize, used }
#endif // _di_f_console_parameters_t_

/**
 * Provide a helper structure for referencing the argc and argv standard main arguments.
 *
 * This is intended to only store the argc and argv and should not be treated as dynamic.
 *
 * argc: The total number of arguments in argv.
 *
 * argv: An array of strings representing arguments passed to some program.
 * envp: Any array of strings representing all environment variables at the time the program is called.
 *
 * macro_f_console_arguments_t_initialize() initializes the structure.
 */
#ifndef _di_f_console_arguments_t_
  typedef struct {
    const f_number_unsigned_t argc;

    const f_string_t *argv;
    const f_string_t *envp;
  } f_console_arguments_t;

  #define f_console_arguments_t_initialize { 0, 0, 0 }

  #define macro_f_console_arguments_t_initialize(argc, argv, envp) { argc, argv, envp }
#endif // _di_f_console_arguments_t_

/**
 * Delete any dynamic allocated data on the parameters object.
 *
 * @param parameters
 *   The parameters object.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamics_resize().
 *   Errors (with error bit) from: f_array_lengths_resize().
 *
 * @see f_string_dynamics_resize()
 * @see f_array_lengths_resize()
 */
#ifndef _di_f_console_parameters_delete_
  extern f_status_t f_console_parameters_delete(f_console_parameters_t * const parameters);
#endif // _di_f_console_parameters_delete_

/**
 * Destroy any dynamic allocated data on the parameters object.
 *
 * @param parameters
 *   The parameters object.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamics_adjust().
 *   Errors (with error bit) from: f_array_lengths_adjust().
 *
 * @see f_string_dynamics_adjust()
 * @see f_array_lengths_adjust()
 */
#ifndef _di_f_console_parameters_destroy_
  extern f_status_t f_console_parameters_destroy(f_console_parameters_t * const parameters);
#endif // _di_f_console_parameters_destroy_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_console_common_h
