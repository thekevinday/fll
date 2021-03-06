/**
 * FLL - Level 0
 *
 * Project: Console
 * API Version: 0.5
 * Licenses: lgplv2.1
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
 * Result values that represent the type of command found.
 *
 * Here "empty" refers to '-', or '++', in that they only have the symbols (whereas '-x', or '++x' would not be empty).
 */
#ifndef _di_f_console_ids_
  enum {
    f_console_none = 1,
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
 */
#ifndef _di_f_console_symbol_s_
  #define f_console_symbol_short_enable  "-"
  #define f_console_symbol_short_disable "+"

  #define f_console_symbol_short_enable_length  1
  #define f_console_symbol_short_disable_length 1

  #define f_console_symbol_long_enable  "--"
  #define f_console_symbol_long_disable "++"

  #define f_console_symbol_long_enable_length  2
  #define f_console_symbol_long_disable_length 2

  extern const f_string_t f_console_symbol_short_enable_s;
  extern const f_string_t f_console_symbol_short_disable_s;

  extern const f_string_t f_console_symbol_long_enable_s;
  extern const f_string_t f_console_symbol_long_disable_s;
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
 * This is not stricly a requirement, but expect level 3 projects to work this way.
 *
 * The following options are subjective in interpretation of the verbosity but are expected to be follow the general interpretation:
 * - debug: Enable debugging, which will likely increase output verbosity.
 * - normal: Use normal printing (don't use debug/quiet/verbose).
 * - quiet: Decrease verbosity, print less, in some use cases this could mean printing nothing.
 * - verbose: Increase verbosity, print more, in some use cases this could mean printing just about everything.
 *
 * The following are less subjective in interpretation but do allow some flexibility.
 * - dark: Do display color intended for dark backgrounds (often the default behavior) when printing to the console. Other contexts may be acceptable (such as voice inflections, or lack-thereof) for audio.)
 * - help: Display the help text. This does not define how the text is displayed only that the text is displayed.
 * - light: Do display color intended for light backgrounds when printing to the console. Other contexts may be acceptable (such as voice inflections, or lack-thereof) for audio.)
 * - no_color: Do not display color when printing to the console. Other contexts may be acceptable (such as voice inflections, or lack-thereof) for audio.)
 * - version: Should always print only the version number, no colors, but what represents the version number is undefined by this project.
 *
 * The following options are for special purposes:
 * - status_in: Is intended to accept the name of an environment variable in which to read the status from.
 * - status_out: Is intended to accept the name of an environment variable in which to ride the status to.
 *
 * In the case of "status_in" and "status_out", the environment variable will store a string representing the base-10 unsigned 16-bit status code.
 * - In the case of "status_in" the environment variable is being read in, which means that it should be the status from some previous execution.
 * - In the case of "status_out" the environment variable is being written to, which means that it should store the status this program exits with.
 *   - To avoid problems with the status code after a program is forcibly killed, the status_out environment variable should be cleared at program start.
 */
#ifndef _di_f_console_standard_s_
  #define f_console_standard_short_dark       "d"
  #define f_console_standard_short_debug      "D"
  #define f_console_standard_short_help       "h"
  #define f_console_standard_short_light      "l"
  #define f_console_standard_short_no_color   "n"
  #define f_console_standard_short_normal     "N"
  #define f_console_standard_short_quiet      "q"
  #define f_console_standard_short_status_in  "s"
  #define f_console_standard_short_status_out "S"
  #define f_console_standard_short_verbose    "V"
  #define f_console_standard_short_version    "v"

  #define f_console_standard_short_dark_length       1
  #define f_console_standard_short_debug_length      1
  #define f_console_standard_short_help_length       1
  #define f_console_standard_short_light_length      1
  #define f_console_standard_short_no_color_length   1
  #define f_console_standard_short_normal_length     1
  #define f_console_standard_short_quiet_length      1
  #define f_console_standard_short_status_in_length  1
  #define f_console_standard_short_status_out_length 1
  #define f_console_standard_short_verbose_length    1
  #define f_console_standard_short_version_length    1

  #define f_console_standard_long_dark       "dark"
  #define f_console_standard_long_debug      "debug"
  #define f_console_standard_long_help       "help"
  #define f_console_standard_long_light      "light"
  #define f_console_standard_long_no_color   "no_color"
  #define f_console_standard_long_normal     "normal"
  #define f_console_standard_long_quiet      "quiet"
  #define f_console_standard_long_status_in  "status_in"
  #define f_console_standard_long_status_out "status_out"
  #define f_console_standard_long_verbose    "verbose"
  #define f_console_standard_long_version    "version"

  #define f_console_standard_long_dark_length       4
  #define f_console_standard_long_debug_length      5
  #define f_console_standard_long_help_length       4
  #define f_console_standard_long_light_length      5
  #define f_console_standard_long_no_color_length   8
  #define f_console_standard_long_normal_length     6
  #define f_console_standard_long_quiet_length      5
  #define f_console_standard_long_status_in_length  9
  #define f_console_standard_long_status_out_length 10
  #define f_console_standard_long_verbose_length    7
  #define f_console_standard_long_version_length    7

  extern const f_string_t f_console_standard_short_dark_s;
  extern const f_string_t f_console_standard_short_debug_s;
  extern const f_string_t f_console_standard_short_help_s;
  extern const f_string_t f_console_standard_short_light_s;
  extern const f_string_t f_console_standard_short_no_color_s;
  extern const f_string_t f_console_standard_short_normal_s;
  extern const f_string_t f_console_standard_short_quiet_s;
  extern const f_string_t f_console_standard_short_status_in_s;
  extern const f_string_t f_console_standard_short_status_out_s;
  extern const f_string_t f_console_standard_short_verbose_s;
  extern const f_string_t f_console_standard_short_version_s;

  extern const f_string_t f_console_standard_long_dark_s;
  extern const f_string_t f_console_standard_long_debug_s;
  extern const f_string_t f_console_standard_long_help_s;
  extern const f_string_t f_console_standard_long_light_s;
  extern const f_string_t f_console_standard_long_no_color_s;
  extern const f_string_t f_console_standard_long_normal_s;
  extern const f_string_t f_console_standard_long_quiet_s;
  extern const f_string_t f_console_standard_long_status_in_s;
  extern const f_string_t f_console_standard_long_status_out_s;
  extern const f_string_t f_console_standard_long_verbose_s;
  extern const f_string_t f_console_standard_long_version_s;
#endif // _di_f_console_standard_s_

/**
 * The maximum size for a single parameter (the length of the string representing the parameter).
 */
#ifndef _di_f_console_length_size_
  #define f_console_parameter_size f_array_length_t_size
#endif // _di_f_console_length_size_

/**
 * Provide console type enumerations:
 *
 * - none: parameter not found.
 * - found: parameter found.
 * - values: parameter found, extra data exists (such as '-f filename', 'filename' would be the extra data).
 *
 * - normal: parameters using minus sign, such as '--help'.
 * - inverse: parameters using plus sign, such as '++version'.
 * - other: parameters using neither minus nor plus sign, such as 'build'.
 */
#ifndef _di_f_console_types_t_
  typedef uint16_t f_console_id_t;

  enum {
    f_console_result_none = 1,
    f_console_result_found,
    f_console_result_additional,
  };

  enum {
    f_console_type_normal = 1,
    f_console_type_inverse,
    f_console_type_other,
  };
#endif // _di_f_console_types_t_

/**
 * Provide the standard verbosity codes.
 *
 * Intended to be used for the basic/standard verbosity modes for all programs following this practice.
 */
#ifndef _di_f_console_verbosity_
  enum {
    f_console_verbosity_quiet = 1,
    f_console_verbosity_normal,
    f_console_verbosity_verbose,
    f_console_verbosity_debug,
  };
#endif // _di_f_console_verbosity_

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
 * - has_values: Designates that a parameter will have a given number of values arguments, such as 'blue' in '--color blue'.
 * - type: One of the f_console_type_* codes, defining how this parameter is to be processed.
 *
 * - result: A code representing that the parameter is found and how it is found ('-h' vs '--help').
 *
 * - location: The last location in argv[] where this parameter is found.
 * - location_sub: The last sub-location at location in argv (only used by short parameters, such as -h or +l).
 * - locations: All locations within argv where this parameter is found (order is preserved).
 * - locations_sub: All sub-locations within argv where this parameter is found (order is preserved).
 * - values: An array of locations representing where in the argv[] the values arguments are found.
 */
#ifndef _di_f_console_parameter_t_
  typedef struct {
    const int8_t *symbol_short;
    const int8_t *symbol_long;
    const int8_t *symbol_other;

    const uint8_t has_values;
    const uint8_t type;

    f_array_length_t result;
    f_array_length_t location;
    f_array_length_t location_sub;
    f_array_lengths_t locations;
    f_array_lengths_t locations_sub;
    f_array_lengths_t values;
  } f_console_parameter_t;

  #define f_console_parameter_t_initialize(symbol_short, symbol_long, symbol_other, has_values, type_value) { symbol_short, symbol_long, symbol_other, has_values, type_value, f_console_result_none, 0, 0, f_array_lengths_t_initialize, f_array_lengths_t_initialize, f_array_lengths_t_initialize }

  #define f_macro_console_parameter_t_initialize(symbol_short, symbol_long, symbol_other, has_values, type_value, result, location, location_sub, locations, locations_sub, values) { symbol_short, symbol_long, symbol_other, has_values, type_value, result, total, location, location_sub, locations, locations_sub, values }
#endif // _di_f_console_parameter_t_

/**
 * Provide a helper structure for references and processing parameters.
 *
 * Designed for passing this to a function as a single argument.
 *
 * parameters: Intended to be populated with an array of f_console_parameter_id_t whose size is defined by the "used" property.
 *             This is not intended to be dynamically allocated, so there is no "size" property.
 * length:     The total number of parameters in the parameters array.
 */
#ifndef _di_f_console_parameters_t_
  typedef struct {
    f_console_parameter_t *parameter;

    f_array_length_t used;
  } f_console_parameters_t;

  #define f_console_parameters_t_initialize { 0, 0 }

  #define f_macro_console_parameters_t_initialize(parameters, length) { parameters, length }
#endif // _di_f_console_parameters_t_

/**
 * Provide a helper structure for references and processing standard C main() arguments.
 *
 * The f_console_parameter_id_t is designed to be used for the enums to represent a any given parameter by the ID.
 *
 * The f_console_parameter_ids_t is designed for passing this to a function as a single argument.
 * The "id" property is intended to be populated with an aray of f_console_parameter_id_t whose size is defined by the "used" property.
 * This follows the idea of f_string_dynamic_t and has a "used" instead of length, but because this is not intended to be dynamically allocated there is no "size" property.
 */
#ifndef _di_f_console_parameter_id_t_
  typedef uint16_t f_console_parameter_id_t;

  typedef struct {
    f_console_parameter_id_t *id;

    f_array_length_t used;
  } f_console_parameter_ids_t;

  #define f_console_parameter_ids_t_initialize { 0, 0 }

  #define f_macro_console_parameter_ids_t_initialize(id, used) { id, used }
#endif // _di_f_console_parameter_id_t_

/**
 * Provide a helper structure for referencing the argc and argv standard main arguments.
 *
 * This is intended to only store the argc and argv and should not be treated as dynamic.
 *
 * No structure initializer is provided due to the use of constant properties.
 */
#ifndef _di_f_console_arguments_t_
  typedef struct {
    const f_number_unsigned_t argc;

    const f_string_t *argv;
  } f_console_arguments_t;

  #define f_console_arguments_t_initialize { 0, 0 }

  #define f_macro_console_arguments_t_initialize(argc, argv) { argc, argv }
#endif // _di_f_console_arguments_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_console_common_h
