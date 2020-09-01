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
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>

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

  #define f_console_symbol_short_enable_length  1
  #define f_console_symbol_short_disable_length 1

  #define f_console_symbol_long_enable  "--"
  #define f_console_symbol_long_disable "++"

  #define f_console_symbol_long_enable_length  2
  #define f_console_symbol_long_disable_length 2
#endif // _di_f_console_symbols_

/**
 * Create some standard command line parameter options required/expected by the kevux/fss/fll specifications.
 *
 * It is expected that all of the "+" and "++" console options described below are reserved for these purposes.
 * This is not a strict requirement as such a thing is non-sense in open-source, but this should be considered a strong recommendation.
 *
 * It is acceptable for any of these options, when specified multiple times, for that number of times to represent the "level".
 * For example, a "+D +D" means more debug output than simply "+D".
 *
 * The following options are subjective in interpretation but are expected to follow the general interpretation:
 * - debug: Enable debugging, which will likely increase output verbosity.
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
 * - status: Represents the return status code from another program.
 *           Because it is associated with the status from another program, its structure is very subjective.
 *           The only expectation is that it somehow communicates the fss status codes.
 *           Example of complex use: "failed_program_name:error:123".
 *           Example of simple use: "123".
 */
#ifndef _di_f_standard_console_parameters_
  #define f_console_standard_short_dark     "d"
  #define f_console_standard_short_debug    "D"
  #define f_console_standard_short_help     "h"
  #define f_console_standard_short_light    "l"
  #define f_console_standard_short_no_color "n"
  #define f_console_standard_short_quiet    "q"
  #define f_console_standard_short_verbose  "V"
  #define f_console_standard_short_version  "v"

  #define f_console_standard_short_dark_length     1
  #define f_console_standard_short_debug_length    1
  #define f_console_standard_short_help_length     1
  #define f_console_standard_short_light_length    1
  #define f_console_standard_short_no_color_length 1
  #define f_console_standard_short_quiet_length    1
  #define f_console_standard_short_verbose_length  1
  #define f_console_standard_short_version_length  1

  #define f_console_standard_long_dark     "dark"
  #define f_console_standard_long_debug    "debug"
  #define f_console_standard_long_help     "help"
  #define f_console_standard_long_light    "light"
  #define f_console_standard_long_no_color "no_color"
  #define f_console_standard_long_status   "status"
  #define f_console_standard_long_quiet    "quiet"
  #define f_console_standard_long_verbose  "verbose"
  #define f_console_standard_long_version  "version"

  #define f_console_standard_long_dark_length     4
  #define f_console_standard_long_debug_length    5
  #define f_console_standard_long_help_length     4
  #define f_console_standard_long_light_length    5
  #define f_console_standard_long_no_color_length 8
  #define f_console_standard_long_status_length   6
  #define f_console_standard_long_quiet_length    5
  #define f_console_standard_long_verbose_length  7
  #define f_console_standard_long_version_length  7
#endif // _di_f_standard_console_parameters_

/**
 * The maximum size for a single parameter.
 */
#ifndef _di_f_console_length_size_
  #define f_console_length_size f_string_length_t_size
#endif // _di_f_console_length_size_

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
 *
 * - result: A code representing that the parameter is found and how it is found ('-h' vs '--help').
 * - total: A number representing the total number of times this parameter is found ('-h -h' would result in a total of 2).
 *
 * - location: The last location in argv[] where this parameter is found.
 * - location_sub: The last sub-location at location in argv (only used by short parameters, such as -h or +l).
 * - locations: All locations within argv where this parameter is found (order is preserved).
 * - additional: An array of locations representing where in the argv[] the additional arguments are found.
 */
#ifndef _di_f_console_parameter_t_
  typedef struct {
    const int8_t *symbol_short;
    const int8_t *symbol_long;
    const int8_t *symbol_other;

    const uint8_t has_additional;
    const uint8_t type;

    uint8_t result;
    uint8_t total;

    f_string_length_t  location;
    f_string_length_t  location_sub;
    f_string_lengths_t locations;
    f_string_lengths_t additional;
  } f_console_parameter_t;

  #define f_console_parameter_t_initialize(symbol_short, symbol_long, symbol_other, has_additional, type_value) { symbol_short, symbol_long, symbol_other, has_additional, type_value, f_console_result_none, 0, 0, 0, f_string_lengths_t_initialize, f_string_lengths_t_initialize }
#endif // _di_f_console_parameter_t_

/**
 * Provide a helper structure for references and processing parameters.
 *
 * Designed for passing this to a function as a single argument.
 *
 * parameter: Intended to be populated with an array of f_console_parameter_id_t whose size is defined by the "used" property.
 *            This is not intended to be dynamically allocated, so there is no "size" property.
 * order:
 */
#ifndef _di_f_console_parameters_t_
  typedef struct {
    f_console_parameter_t *parameter;

    f_array_length_t used;
  } f_console_parameters_t;

  #define f_console_parameters_t_initialize { 0, 0 }
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
#endif // _di_f_console_arguments_t_

/**
 * Determine the type code the given input parameter represents.
 *
 * @param input
 *   The input parameter to process.
 * @param result
 *   The resulting console type code determined by this function.
 *
 * @return
 *   F_none on success.
 *   F_data_not the input string is empty.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 */
#ifndef _di_f_console_identify_
  extern f_return_status f_console_identify(const f_string_t input, f_console_id_t *result);
#endif // _di_f_console_identify_

/**
 * Process console parameters.
 *
 * Short parameters are processed as follows:
 * - Begin with either '-' or '+'.
 * - "Empty" parameters are allow, such that '-' or '+' are valid parameters.
 * - Are one character long.
 * - May be grouped as a single parameter, such as "tar -xcf" and "tar -x -c -f" are equivalent.
 * - Additional parameters must immediately follow the parameter or grouped parameters, such as "tar -xfc file.tar.gz" or "tar -x -f file.tar.gz -c".
 *
 * Long parameters are processed as follows:
 * - Begin with either '--' or '++'.
 * - "Empty" parameters are allow, such that '--' or '++' are valid parameters.
 * - Are any length long so long as it is less than f_console_length_size.
 * - May not be grouped and must be separated from any subsequent parameter, such as: "tar --extract --create --file".
 * - Additional parameters must immediately follow the parameter, such as "tar --extract --file file.tar.gz --create".
 *
 * Other parameters are processed as follows:
 * - Anything that does not begin with '-', '+', '--', or '++'.
 * - Are any length long so long as it is less than f_console_length_size.
 * - May not be grouped and must be separated from any subsequent parameter, such as: "tar extract create file".
 * - Additional parameters must immediately follow the parameter, such as "tar extract file file.tar.gz create".
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param parameters
 *   The console parameters to look for.
 *   This will be updated by this function with the results.
 * @param remaining
 *   A list of remaining parameters not associated with anything.
 *
 * @return
 *   F_none on success.
 *   F_data_not if "additional" parameters were expected but not found.
 *   F_buffer_too_large (with error bit) if a buffer would exceed max length.
 *   F_failure (with error bit) if width is not long enough to convert when processing arguments as UTF-8.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character, when processing arguments.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 */
#ifndef _di_f_console_parameter_process_
  extern f_return_status f_console_parameter_process(const f_console_arguments_t arguments, f_console_parameters_t parameters, f_string_lengths_t *remaining);
#endif // _di_f_console_parameter_process_

/**
 * Given a set of parameter choices, determine which one has the highest priority.
 *
 * The priority is determined by viewing the parameters from left to right.
 * The left-most parameter defined in the set has the priority over others.
 *
 * For example, the color context modes override each other, so only one gets priority.
 * If given, say "+l ++no_color +d", the "+d" would be the left-most parameter "+l" and "++no_color".
 * The decision would be "+d".
 *
 * This also applies to short parameters combined into one, such as "+lnd", the "d" would again be the decision.
 *
 * @param parameters
 *   The parameters to process.
 * @param choices
 *   An array of numeric ids, each representing a parameter within the parameters variable.
 *   The order does not matter.
 * @param decision
 *   The resulting decision.
 *   If none of the parameters are found, then this will not be updated (therefore it is safe to have it pre-initialized to the default).
 *
 * @return
 *   F_none on success.
 *   F_data_not if no parameters were found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_console_parameter_prioritize_left_
  extern f_return_status f_console_parameter_prioritize_left(const f_console_parameters_t parameters, const f_console_parameter_ids_t choices, f_console_parameter_id_t *decision);
#endif // _di_f_console_parameter_prioritize_left_

/**
 * Given a set of parameter choices, determine which one has the highest priority.
 *
 * The priority is determined by viewing the parameters from left to right.
 * The right-most parameter defined in the set has the priority over others.
 *
 * For example, the color context modes override each other, so only one gets priority.
 * If given, say "+l ++no_color +d", the "+d" would be the right-most parameter "+l" and "++no_color".
 * The decision would be "+d".
 *
 * This also applies to short parameters combined into one, such as "+lnd", the "d" would again be the decision.
 *
 * @param parameters
 *   The parameters to process.
 * @param choices
 *   An array of numeric ids, each representing a parameter within the parameters variable.
 *   The order does not matter.
 * @param decision
 *   The resulting decision.
 *   If none of the parameters are found, then this will not be updated (therefore it is safe to have it pre-initialized to the default).
 *
 * @return
 *   F_none on success.
 *   F_data_not if no parameters were found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_console_parameter_prioritize_right_
  extern f_return_status f_console_parameter_prioritize_right(const f_console_parameters_t parameters, const f_console_parameter_ids_t choices, f_console_parameter_id_t *decision);
#endif // _di_f_console_parameter_prioritize_right_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_console_h
