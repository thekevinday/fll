/**
 * FLL - Level 1
 *
 * Project: Print
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides some standard printing functions not available in a libc.
 *
 * Functions provided here are UTF-8 aware.
 */
#ifndef _FL_print_h
#define _FL_print_h

// Libc includes.
#include <stdio.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/color.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/file.h>
#include <fll/level_0/print.h>

// fll-1 print includes.
#include <fll/level_1/print-common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A formatted print function similar to (but not the same as) the c-library fprintf() function.
 *
 * This function attempts to operate as closely to how fprintf() operates, however, there are notable differences.
 *
 * This formatted print provides replacement variables for specific types of the FLL project, such f_string_static_t.
 * There is support for safe printing where certain control characters or invalid UTF-8 sequences are not directly printed.
 * There is support for color context printing.
 * There is support for more digit base forms than those provided by fprintf() such as base-2 (binary) or base-12 (duodecimal).
 *
 * The reserved formatting character is only the '%' character, which may be escaped by a second '%' character.
 * This '%' character designates the start of a format flag sequence which must be ended by another '%' or a format character.
 * A '%' at the end of the string is considered invalid.
 *
 * Each formatting flags is followed by basic flag or base flag and end on a type flag.
 * The basic, base, and type format flags are represented by a discrete set of reserved characters.
 *
 * Each basic format flags may be specified in any order but must be specified before the type flag.
 * The order in which basic format flags are processed in regards parameters is a present order irrespective to the order specified.
 * The basic format flags "/", ";", and ":" are examples of this.
 *
 * Floating and double floating format flags may be immediately followed by one of:
 *   - "e": Round and convert to [-]d.ddde±dd (exponent notation).
 *   - "E": Round and convert to [-]d.dddE±dd (exponent notation).
 *   - "g": Round and convert to notation of either decimal or exponent.
 *   - "G": Round and convert to notation of either decimal or exponent.
 *
 * The default format is decimal: [-]ddd.ddd.
 *
 * The case-sensitivity of above, such as 'e' vs 'E,' does not replace or relate to the case-sensitivity meaning of 'd' or 'D'.
 * Instead, when 'e' is specified 'e' is used (such as such as [-]d.ddde±dd), but when 'E' is specified, then 'E' is used (such as [-]d.dddE±dd).
 *
 * Note: Currently the float/double implementation does not support the notation modes except integer (default) or hexidecimal.
 * This is not intended but is simply a result of the temporary use of sprintf() to perform these operations.
 * Once a custom implementation is provided, replacing snprintf(), then this can properly support the notation modes.
 * Therefore, this function is supposed to support notation modes and does not yet do this (@fixme/@todo).
 *
 * This "%$" sequence is used to prevent characters from being interpreted.
 * For example, consider "%de" vs "%d%$e".
 * The first case "%de" is interpretted as a double using the "e" notation.
 * The second case "%d%$e" is interpretted as a double followed by the letter "e".
 *
 * For these basic format flags ("/", ";", and ":"), the order is always processed as:
 *   1) static/dynamic string.
 *   2) partial range.
 *   3) ignore at.
 *   4) ignore in.
 *
 * Uppercase base format flags designates to print the base designation in uppercase and lowercase base format flags designate to print the base designation in lowercase.
 * There are 5 support base format flags:
 *   - binary: 0b/0B, representing base-2 units.
 *   - octal: 0o/0O, representing base-8 units (note that this is a letter O, and not a zero).
 *   - decimal: 0t/0T, representing base-10 units (this is the default when no base is specified, in which case the 0t/0T is not printed).
 *   - duodecimal: 0d/0D, representing base-12 units.
 *   - hexidecimal: 0x/0X, representing base-16 units.
 *
 * When printing digits, using lowercase designates to print alphabetic digits in lowercase and using uppercase designates to print alphabetic digits in uppercase.
 *
 * To keep the design simple, this does not support index position variable replacement like fprintf() does (such as '%1$', '%2$', etc..).
 *
 * Basic Format Flags:
 *   - "-":        Use left-justification.
 *   - "#":        Use alternate form conversion (prefixing 0b/0B, 0o/0O, 0t/0T, 0d/0D, 0x/0X).
 *   - ";":        Ignore characters in the given positions from a f_array_length_t (only applies to static/dynamic string arguments but not character arguments).
 *   - ":":        Ignore characters in the given ranges from a f_string_range_t (only applies to static/dynamic string arguments but not character arguments).
 *   - "/",        Print only the given range of a string, specified by f_string_range_t (only applies to static/dynamic string arguments but not character arguments).
 *   - "+",        Always show the signs (+ or -).
 *   - " ",        Add a space where a sign would be if the sign is not displayed (this is the space character).
 *   - "=",        Trim leading and trailing whitespaces (only applies to static/dynamic string arguments but not character arguments).
 *   - "0" to "9", The width to use, however if a leading 0 is used, then a 0 is printed in each leading digit as needed.
 *   - "*",        For number-based values, designates that the width is specified in the parameter (order is: (width, value)).
 *   - ".*",       For number-based values, designates that the precision is specified in the parameter (order is: (precision, value), but if *.* is specified, then order is: (width, precision, value)).
 *
 * Base Format Flags:
 *   - "!": Display digits in Binary notation.
 *   - "@": Display digits in Octal notation.
 *   - "^": Display digits in Decimal notation.
 *   - "&": Display digits in Duodecimal notation.
 *   - "_": Display digits in Hexidecimal notation.
 *
 * Special Format Flags:
 *   - "$": Ignore flag.
 *   - "%": Use left-justification.
 *
 * Type Format Flags:
 *   - "d", "D":     Type is a double digit (32-bit), may be immediately followed by an "e", "E", "g", or "G".
 *   - "dl", "DL":   Type is a long double digit (64-bit), may be immediately followed by an "e", "E", "g", or "G".
 *   - "c":          Type is a 1-byte unsigned character.
 *   - "C":          Type is a 1-byte unsigned character, where control characters and invalid UTF-8 are replaced.
 *   - "[":          Type is a f_color_set_t such that the f_color_set_t.begin is used.
 *   - "]":          Type is a f_color_set_t such that the f_color_set_t.after is used.
 *   - "iii" "III":  Type is a int8_t digit.
 *   - "ii", "II":   Type is a int16_t digit.
 *   - "i", "I":     Type is a int32_t digit.
 *   - "il", "IL":   Type is a signed int64_t digit.
 *   - "ill", "ILL": Type is a f_int_128_t digit.
 *   - "in", "IN":   Type is a f_number_signed_t digit.
 *   - "z", "Z":     Type is a size_t digit.
 *   - "s":          Type is a NULL terminated string, where the string is printed as-is.
 *   - "S":          Type is a NULL terminated string, where control characters and invalid UTF-8 are replaced.
 *   - "q":          Type is a f_string_static_t or f_string_dynamic_t and NULLs are ignored (not printed).
 *   - "Q":          Type is a f_string_static_t or f_string_dynamic_t and NULLs are ignored (not printed), where control characters and invalid UTF-8 are replaced.
 *   - "r":          Type is a f_string_static_t or f_string_dynamic_t and NULLs (and all other control characters) are printed.
 *   - "R":          Type is a f_string_static_t or f_string_dynamic_t and NULLs are printed, but control characters and invalid UTF-8 are replaced. @todo not yet implemented.
 *   - "uii", "UII": Type is a uint8_t digit.
 *   - "ui", "UI":   Type is a uint16_t digit.
 *   - "u", "U":     Type is a uint32_t digit.
 *   - "ul", "UL":   Type is a uint64_t digit.
 *   - "ull", "ULL": Type is a f_uint_128_t digit.
 *   - "un", "UN":   Type is a f_number_unsigned_t digit (which by default is what f_array_length_t is a type of).
 *
 * The following are control characters and their replacements for "safe" printing (unknown is used for invalid UTF-8 sequences):
 *   - "␆": Acknowledge.
 *   - "␕": Negative Acknowledge.
 *   - "␈": Backspace.
 *   - "␇": Bell.
 *   - "␘": Cancel.
 *   - "␍": Carriage Return.
 *   - "␐": Data Link Escape.
 *   - "␡": Delete.
 *   - "␑": Device Control 1.
 *   - "␒": Device Control 2.
 *   - "␓": Device Control 3.
 *   - "␔": Device Control 4.
 *   - "␙": End of Medium.
 *   - "␃": End of Text.
 *   - "␄": End of Transmission.
 *   - "␗": End of Transmission Block.
 *   - "␅": Enquiry.
 *   - "␛": Escape.
 *   - "␌": Form Feed.
 *   - "␊": Line Feed.
 *   - "␀": Null.
 *   - "␜": Separator File.
 *   - "␝": Separator Group.
 *   - "␞": Separator Record.
 *   - "␟": Separator Unit.
 *   - "␏": Shift In.
 *   - "␎": Shift Out.
 *   - "␁": Start Of Header.
 *   - "␂": Start Of Text.
 *   - "␚": Substitute.
 *   - "␖": Synchronous Idle.
 *   - "␉": Tab.
 *   - "␋": Vertical Tab.
 *   - "�": Unknown/Invalid.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The formatted string to process and output.
 *   This is a NULL terminated string.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 * @param ...
 *   Additional arguments relating to the string.
 *
 * @return
 *   F_none on success.
 *
 *   F_eos (with error bit) on EOS reached.
 *   F_output (with error bit) on failure to print to the output file.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_valid_not (with error bit) on invalid syntax (such as terminating the string on a single '%').
 *
 *   Errors (with error bit) from: f_conversion_number_signed_print().
 *   Errors (with error bit) from: f_conversion_number_unsigned_print().
 *   Errors (with error bit) from: f_print_dynamic().
 *   Errors (with error bit) from: f_print_dynamic_raw().
 *   Errors (with error bit) from: f_print_dynamic_safely().
 *   Errors (with error bit) from: f_print_safely().
 *   Errors (with error bit) from: f_print_terminated().
 *
 * @see fprintf()
 * @see fputc_unlocked()
 * @see snprintf()
 * @see va_start()
 * @see va_end()
 *
 * @see f_conversion_number_signed_print()
 * @see f_conversion_number_unsigned_print()
 * @see f_print_dynamic()
 * @see f_print_dynamic_raw()
 * @see f_print_dynamic_safely()
 * @see f_print_safely()
 * @see f_print_terminated()
 */
#ifndef _di_fl_print_format_
  extern f_status_t fl_print_format(const f_string_t string, FILE *stream, ...);
#endif // _di_fl_print_format_

/**
 * Convert and print a single part of a formatted string represented by the '%'.
 *
 * This should be called after each first '%' is encountered.
 * This should return only after a single '%' group is fully processed, end of current is reached, or an error occurs.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The current character position within the string.
 *   This pointer might be updated by this function.
 * @param stream
 *   The file stream to stream to, including standard streams such as stdout and stderr.
 * @param ap
 *   The variable arguments list.
 * @param status
 *   The status is stored here rather then via the return.
 *
 * @return
 *   This returns a string at either the start position (if nothing done or an error occurred) or at the character last processed.
 *   The caller is expected to increment past this if they wish to continue processing the string.
 *
 *   The status parameter will be set as follows:
 *
 *     F_none on success.
 *
 *     F_output (with error bit) on failure to print to the output file.
 *     F_parameter (with error bit) if a parameter is invalid.
 *     F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *     F_valid_not (with error bit) on invalid syntax (such as terminating the string on a single '%').
 *
 *     Success from: f_print_dynamic().
 *     Success from: f_print_dynamic_raw().
 *     Success from: f_print_dynamic_safely().
 *     Success from: f_print_safely().
 *     Success from: f_print_terminated().
 *
 *     Errors (with error bit) from: f_conversion_number_signed_print().
 *     Errors (with error bit) from: f_conversion_number_unsigned_print().
 *     Errors (with error bit) from: f_print_dynamic().
 *     Errors (with error bit) from: f_print_dynamic_raw().
 *     Errors (with error bit) from: f_print_dynamic_safely().
 *     Errors (with error bit) from: f_print_safely().
 *     Errors (with error bit) from: f_print_terminated().
 *
 * @see fputc_unlocked()
 *
 * @see f_conversion_number_signed_print()
 * @see f_conversion_number_unsigned_print()
 * @see f_print_dynamic()
 * @see f_print_dynamic_raw()
 * @see f_print_dynamic_safely()
 * @see f_print_safely()
 * @see f_print_terminated()
 */
#ifndef _di_fl_print_format_convert_
  extern f_string_t fl_print_format_convert(const f_string_t string, FILE *stream, va_list *ap, f_status_t *status);
#endif // _di_fl_print_format_convert_

/**
 * A formatted print function similar to (but not the same as) the c-library vfprintf() function.
 *
 * This is identical to fl_print_format() except it accepts a va_list as a variable instead of as "...".
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The formatted string to process and output.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 * @param ap
 *   The variable list.
 *   The va_start(ap, string) and va_end(ap) is required to be called outside this function.
 *
 * @return
 *   F_none on success.
 *
 *   F_eos (with error bit) on EOS reached.
 *   F_output (with error bit) on failure to print to the output file.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_valid_not (with error bit) on invalid syntax (such as terminating the string on a single '%').
 *
 *   Errors (with error bit) from: f_conversion_number_signed_print().
 *   Errors (with error bit) from: f_conversion_number_unsigned_print().
 *   Errors (with error bit) from: f_print_dynamic().
 *   Errors (with error bit) from: f_print_dynamic_raw().
 *   Errors (with error bit) from: f_print_dynamic_safely().
 *   Errors (with error bit) from: f_print_safely().
 *   Errors (with error bit) from: f_print_terminated().
 *
 * @see fputc_unlocked()
 * @see va_start()
 * @see va_end()
 *
 * @see f_conversion_number_signed_print()
 * @see f_conversion_number_unsigned_print()
 * @see f_print_dynamic()
 * @see f_print_dynamic_raw()
 * @see f_print_dynamic_safely()
 * @see f_print_safely()
 * @see f_print_terminated()
 * @see fl_print_format()
 */
#ifndef _di_fl_print_string_va_
  extern f_status_t fl_print_string_va(const f_string_t string, FILE *stream, va_list *ap);
#endif // _di_fl_print_string_va_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_
  extern f_status_t fl_print_trim(const f_string_t string, const f_array_length_t length, FILE *stream);
#endif // _di_fl_print_trim_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_raw_
  extern f_status_t fl_print_trim_raw(const f_string_t string, const f_array_length_t length, FILE *stream);
#endif // _di_fl_print_trim_raw_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_safely_
  extern f_status_t fl_print_trim_safely(const f_string_t string, const f_array_length_t length, FILE *stream);
#endif // _di_fl_print_trim_safely_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_dynamic_
  extern f_status_t fl_print_trim_dynamic(const f_string_static_t buffer, FILE *stream);
#endif // _di_fl_print_trim_dynamic_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_dynamic_raw_
  extern f_status_t fl_print_trim_dynamic_raw(const f_string_static_t buffer, FILE *stream);
#endif // _di_fl_print_trim_dynamic_raw_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_dynamic_safely_
  extern f_status_t fl_print_trim_dynamic_safely(const f_string_static_t buffer, FILE *stream);
#endif // _di_fl_print_trim_dynamic_safely_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_dynamic_partial_
  extern f_status_t fl_print_trim_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, FILE *stream);
#endif // _di_fl_print_trim_dynamic_partial_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_dynamic_partial_raw_
  extern f_status_t fl_print_trim_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, FILE *stream);
#endif // _di_fl_print_trim_dynamic_partial_raw_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_dynamic_partial_safely_
  extern f_status_t fl_print_trim_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, FILE *stream);
#endif // _di_fl_print_trim_dynamic_partial_safely_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_
  extern f_status_t fl_print_trim_except(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, FILE *stream);
#endif // _di_fl_print_trim_except_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_raw_
  extern f_status_t fl_print_trim_except_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, FILE *stream);
#endif // _di_fl_print_trim_except_raw_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_safely_
  extern f_status_t fl_print_trim_except_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, FILE *stream);
#endif // _di_fl_print_trim_except_safely_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 * Will not print any 1-byte character at a location specified in except_at array.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_dynamic_
  extern f_status_t fl_print_trim_except_dynamic(const f_string_static_t buffer, const f_array_lengths_t except_at, FILE *stream);
#endif // _di_fl_print_trim_except_dynamic_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 * Will not print any 1-byte character at a location specified in except_at array.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_dynamic_raw_
  extern f_status_t fl_print_trim_except_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except_at, FILE *stream);
#endif // _di_fl_print_trim_except_dynamic_raw_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 * Will not print any 1-byte character at a location specified in except_at array.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_dynamic_safely_
  extern f_status_t fl_print_trim_except_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, FILE *stream);
#endif // _di_fl_print_trim_except_dynamic_safely_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_
  extern f_status_t fl_print_trim_except_in(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream);
#endif // _di_fl_print_trim_except_in_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_raw_
  extern f_status_t fl_print_trim_except_in_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream);
#endif // _di_fl_print_trim_except_in_raw_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_safely_
  extern f_status_t fl_print_trim_except_in_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream);
#endif // _di_fl_print_trim_except_in_safely_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_dynamic_
  extern f_status_t fl_print_trim_except_in_dynamic(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream);
#endif // _di_fl_print_trim_except_in_dynamic_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_dynamic_raw_
  extern f_status_t fl_print_trim_except_in_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream);
#endif // _di_fl_print_trim_except_in_dynamic_raw_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_dynamic_safely_
  extern f_status_t fl_print_trim_except_in_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream);
#endif // _di_fl_print_trim_except_in_dynamic_safely_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_dynamic_partial_
  extern f_status_t fl_print_trim_except_in_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream);
#endif // _di_fl_print_trim_except_in_dynamic_partial_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_dynamic_partial_raw_
  extern f_status_t fl_print_trim_except_in_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream);
#endif // _di_fl_print_trim_except_in_dynamic_partial_raw_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_dynamic_partial_safely_
  extern f_status_t fl_print_trim_except_in_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *stream);
#endif // _di_fl_print_trim_except_in_dynamic_partial_safely_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_dynamic_partial_
  extern f_status_t fl_print_trim_except_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *stream);
#endif // _di_fl_print_trim_except_dynamic_partial_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_dynamic_partial_raw_
  extern f_status_t fl_print_trim_except_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *stream);
#endif // _di_fl_print_trim_except_dynamic_partial_raw_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param stream
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_dynamic_partial_safely_
  extern f_status_t fl_print_trim_except_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *stream);
#endif // _di_fl_print_trim_except_dynamic_partial_safely_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_print_h
