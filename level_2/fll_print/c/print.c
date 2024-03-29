#include "print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_print_
  f_status_t fll_print(const f_string_t string, const f_array_length_t length, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print(string, length, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_

#ifndef _di_fll_print_character_
  f_status_t fll_print_character(const f_char_t character, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_character(character, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_character_

#ifndef _di_fll_print_character_safely_
  f_status_t fll_print_character_safely(const f_char_t character, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_character_safely(character, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_character_safely_

#ifndef _di_fll_print_dynamic_
  f_status_t fll_print_dynamic(const f_string_static_t buffer, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_dynamic(buffer, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_dynamic_

#ifndef _di_fll_print_dynamic_partial_
  f_status_t fll_print_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_dynamic_partial(buffer, range, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_dynamic_partial_

#ifndef _di_fll_print_dynamic_partial_raw_
  f_status_t fll_print_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_dynamic_partial_raw(buffer, range, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_dynamic_partial_raw_

#ifndef _di_fll_print_dynamic_partial_raw_safely_
  f_status_t fll_print_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_string_range_t range, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_dynamic_partial_raw_safely(buffer, range, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_dynamic_partial_raw_safely_

#ifndef _di_fll_print_dynamic_partial_safely_
  f_status_t fll_print_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_dynamic_partial_safely(buffer, range, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_dynamic_partial_safely_

#ifndef _di_fll_print_dynamic_raw_
  f_status_t fll_print_dynamic_raw(const f_string_static_t buffer, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_dynamic_raw(buffer, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_dynamic_raw_

#ifndef _di_fll_print_dynamic_raw_safely_
  f_status_t fll_print_dynamic_raw_safely(const f_string_static_t buffer, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_dynamic_raw_safely(buffer, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_dynamic_raw_safely_

#ifndef _di_fll_print_dynamic_safely_
  f_status_t fll_print_dynamic_safely(const f_string_static_t buffer, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_dynamic_safely(buffer, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_dynamic_safely_

#ifndef _di_fll_print_except_
  f_status_t fll_print_except(const f_string_t buffer, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except(buffer, offset, length, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_

#ifndef _di_fll_print_except_dynamic_
  f_status_t fll_print_except_dynamic(const f_string_static_t buffer, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_dynamic(buffer, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_dynamic_

#ifndef _di_fll_print_except_dynamic_partial_
  f_status_t fll_print_except_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_dynamic_partial(buffer, range, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_dynamic_partial_

#ifndef _di_fll_print_except_dynamic_partial_raw_
  f_status_t fll_print_except_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_dynamic_partial_raw(buffer, range, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_dynamic_partial_raw_

#ifndef _di_fll_print_except_dynamic_partial_raw_safely_
  f_status_t fll_print_except_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_dynamic_partial_raw_safely(buffer, range, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_dynamic_partial_raw_safely_

#ifndef _di_fll_print_except_dynamic_partial_safely_
  f_status_t fll_print_except_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_dynamic_partial_safely(buffer, range, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_dynamic_partial_safely_

#ifndef _di_fll_print_except_dynamic_raw_
  f_status_t fll_print_except_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_dynamic_raw(buffer, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_dynamic_raw_

#ifndef _di_fll_print_except_dynamic_raw_safely_
  f_status_t fll_print_except_dynamic_raw_safely(const f_string_static_t buffer, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_dynamic_raw_safely(buffer, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_dynamic_raw_safely_

#ifndef _di_fll_print_except_dynamic_safely_
  f_status_t fll_print_except_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_dynamic_safely(buffer, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_dynamic_safely_

#ifndef _di_fll_print_except_raw_
  f_status_t fll_print_except_raw(const f_string_t buffer, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_raw(buffer, offset, length, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_raw_

#ifndef _di_fll_print_except_raw_safely_
  f_status_t fll_print_except_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_raw_safely(string, offset, length, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_raw_safely_

#ifndef _di_fll_print_except_safely_
  f_status_t fll_print_except_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_safely(string, offset, length, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_safely_

#ifndef _di_fll_print_except_in_
  f_status_t fll_print_except_in(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_in(string, offset, length, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_in_

#ifndef _di_fll_print_except_in_dynamic_
  f_status_t fll_print_except_in_dynamic(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_in_dynamic(buffer, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_in_dynamic_

#ifndef _di_fll_print_except_in_dynamic_partial_
  f_status_t fll_print_except_in_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_in_dynamic_partial(buffer, range, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_in_dynamic_partial_

#ifndef _di_fll_print_except_in_dynamic_partial_raw_
  f_status_t fll_print_except_in_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_in_dynamic_partial_raw(buffer, range, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_in_dynamic_partial_raw_

#ifndef _di_fll_print_except_in_dynamic_partial_raw_safely_
  f_status_t fll_print_except_in_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_in_dynamic_partial_raw_safely(buffer, range, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_in_dynamic_partial_raw_safely_

#ifndef _di_fll_print_except_in_dynamic_partial_safely_
  f_status_t fll_print_except_in_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_in_dynamic_partial_safely(buffer, range, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_in_dynamic_partial_safely_

#ifndef _di_fll_print_except_in_dynamic_raw_
  f_status_t fll_print_except_in_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_in_dynamic_raw(buffer, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_in_dynamic_raw_

#ifndef _di_fll_print_except_in_dynamic_raw_safely_
  f_status_t fll_print_except_in_dynamic_raw_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_in_dynamic_raw_safely(buffer, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_in_dynamic_raw_safely_

#ifndef _di_fll_print_except_in_dynamic_safely_
  f_status_t fll_print_except_in_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_in_dynamic_safely(buffer, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_in_dynamic_safely_

#ifndef _di_fll_print_except_in_raw_
  f_status_t fll_print_except_in_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_in_raw(string, offset, length, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_in_raw_

#ifndef _di_fll_print_except_in_raw_safely_
  f_status_t fll_print_except_in_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_in_raw_safely(string, offset, length, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_in_raw_safely_

#ifndef _di_fll_print_except_in_safely_
  f_status_t fll_print_except_in_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_except_in_safely(string, offset, length, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_except_in_safely_

#ifndef _di_fll_print_format_
  f_status_t fll_print_format(const f_string_t string, FILE * const output, ...) {

    flockfile(output);

    va_list ap;

    va_start(ap, output);

    const f_status_t status = fl_print_string_va(string, output, ap);

    va_end(ap);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_format_

#ifndef _di_fll_print_format_convert_
  f_string_t fll_print_format_convert(const f_string_t string, FILE * const output, va_list ap, f_status_t * const status) {

    flockfile(output);

    f_string_t str = fl_print_format_convert(string, output, ap, status);

    funlockfile(output);

    return str;
  }
#endif // _di_fll_print_format_convert_

#ifndef _di_fll_print_raw_
  f_status_t fll_print_raw(const f_string_t string, const f_array_length_t length, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_raw(string, length, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_raw_

#ifndef _di_fll_print_raw_safely_
  f_status_t fll_print_raw_safely(const f_string_t string, const f_array_length_t length, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_raw_safely(string, length, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_raw_safely_

#ifndef _di_fll_print_raw_terminated_
  f_status_t fll_print_raw_terminated(const f_string_t string, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_raw_terminated(string, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_raw_terminated_

#ifndef _di_fll_print_safely_
  f_status_t fll_print_safely(const f_string_t string, const f_array_length_t length, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_safely(string, length, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_safely_

#ifndef _di_fll_print_safely_terminated_
  f_status_t fll_print_safely_terminated(const f_string_t string, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_safely_terminated(string, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_safely_terminated_

#ifndef _di_fll_print_string_va_
  f_status_t fll_print_string_va(const f_string_t string, FILE * const output, va_list ap) {

    flockfile(output);

    const f_status_t status = fl_print_string_va(string, output, ap);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_string_va_

#ifndef _di_fll_print_terminated_
  f_status_t fll_print_terminated(const f_string_t string, FILE * const output) {

    flockfile(output);

    const f_status_t status = f_print_terminated(string, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_terminated_

#ifndef _di_fll_print_trim_raw_
  f_status_t fll_print_trim_raw(const f_string_t string, const f_array_length_t length, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_raw(string, length, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_raw_

#ifndef _di_fll_print_trim_raw_safely_
  f_status_t fll_print_trim_raw_safely(const f_string_t string, const f_array_length_t length, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_raw_safely(string, length, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_raw_safely_

#ifndef _di_fll_print_trim_safely_
  f_status_t fll_print_trim_safely(const f_string_t string, const f_array_length_t length, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_safely(string, length, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_safely_

#ifndef _di_fll_print_trim_dynamic_
  f_status_t fll_print_trim_dynamic(const f_string_static_t buffer, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_dynamic(buffer, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_dynamic_

#ifndef _di_fll_print_trim_dynamic_raw_
  f_status_t fll_print_trim_dynamic_raw(const f_string_static_t buffer, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_dynamic_raw(buffer, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_dynamic_raw_

#ifndef _di_fll_print_trim_dynamic_raw_safely_
  f_status_t fll_print_trim_dynamic_raw_safely(const f_string_static_t buffer, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_dynamic_raw_safely(buffer, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_dynamic_raw_safely_

#ifndef _di_fll_print_trim_dynamic_safely_
  f_status_t fll_print_trim_dynamic_safely(const f_string_static_t buffer, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_dynamic_safely(buffer, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_dynamic_safely_

#ifndef _di_fll_print_trim_dynamic_partial_
  f_status_t fll_print_trim_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_dynamic_partial(buffer, range, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_dynamic_partial_

#ifndef _di_fll_print_trim_dynamic_partial_raw_
  f_status_t fll_print_trim_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_dynamic_partial_raw(buffer, range, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_dynamic_partial_raw_

#ifndef _di_fll_print_trim_dynamic_partial_raw_safely_
  f_status_t fll_print_trim_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_string_range_t range, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_dynamic_partial_raw_safely(buffer, range, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_dynamic_partial_raw_safely_

#ifndef _di_fll_print_trim_dynamic_partial_safely_
  f_status_t fll_print_trim_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_dynamic_partial_safely(buffer, range, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_dynamic_partial_safely_

#ifndef _di_fll_print_trim_except_
  f_status_t fll_print_trim_except(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except(string, offset, length, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_

#ifndef _di_fll_print_trim_except_raw_
  f_status_t fll_print_trim_except_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_raw(string, offset, length, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_raw_

#ifndef _di_fll_print_trim_except_raw_safely_
  f_status_t fll_print_trim_except_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_raw_safely(string, offset, length, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_raw_safely_

#ifndef _di_fll_print_trim_except_safely_
  f_status_t fll_print_trim_except_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_safely(string, offset, length, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_safely_

#ifndef _di_fll_print_trim_except_dynamic_
  f_status_t fll_print_trim_except_dynamic(const f_string_static_t buffer, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_dynamic(buffer, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_dynamic_

#ifndef _di_fll_print_trim_except_dynamic_raw_
  f_status_t fll_print_trim_except_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_dynamic_raw(buffer, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_dynamic_raw_

#ifndef _di_fll_print_trim_except_dynamic_raw_safely_
  f_status_t fll_print_trim_except_dynamic_raw_safely(const f_string_static_t buffer, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_dynamic_raw_safely(buffer, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_dynamic_raw_safely_

#ifndef _di_fll_print_trim_except_dynamic_safely_
  f_status_t fll_print_trim_except_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_dynamic_safely(buffer, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_dynamic_safely_

#ifndef _di_fll_print_trim_except_in_
  f_status_t fll_print_trim_except_in(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_in(string, offset, length, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_in_

#ifndef _di_fll_print_trim_except_in_raw_
  f_status_t fll_print_trim_except_in_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_in_raw(string, offset, length, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_in_raw_

#ifndef _di_fll_print_trim_except_in_raw_safely_
  f_status_t fll_print_trim_except_in_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_in_raw_safely(string, offset, length, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_in_raw_safely_

#ifndef _di_fll_print_trim_except_in_safely_
  f_status_t fll_print_trim_except_in_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_in_safely(string, offset, length, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_in_safely_

#ifndef _di_fll_print_trim_except_in_dynamic_
  f_status_t fll_print_trim_except_in_dynamic(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_in_dynamic(buffer, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_in_dynamic_

#ifndef _di_fll_print_trim_except_in_dynamic_raw_
  f_status_t fll_print_trim_except_in_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_in_dynamic_raw(buffer, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_in_dynamic_raw_

#ifndef _di_fll_print_trim_except_in_dynamic_raw_safely_
  f_status_t fll_print_trim_except_in_dynamic_raw_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_in_dynamic_raw_safely(buffer, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_in_dynamic_raw_safely_

#ifndef _di_fll_print_trim_except_in_dynamic_safely_
  f_status_t fll_print_trim_except_in_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_in_dynamic_safely(buffer, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_in_dynamic_safely_

#ifndef _di_fll_print_trim_except_in_dynamic_partial_
  f_status_t fll_print_trim_except_in_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_in_dynamic_partial(buffer, range, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_in_dynamic_partial_

#ifndef _di_fll_print_trim_except_in_dynamic_partial_raw_
  f_status_t fll_print_trim_except_in_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_in_dynamic_partial_raw(buffer, range, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_in_dynamic_partial_raw_

#ifndef _di_fll_print_trim_except_in_dynamic_partial_raw_safely_
  f_status_t fll_print_trim_except_in_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_in_dynamic_partial_raw_safely(buffer, range, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_in_dynamic_partial_raw_safely_

#ifndef _di_fll_print_trim_except_in_dynamic_partial_safely_
  f_status_t fll_print_trim_except_in_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_in_dynamic_partial_safely(buffer, range, except_at, except_in, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_in_dynamic_partial_safely_

#ifndef _di_fll_print_trim_except_dynamic_partial_
  f_status_t fll_print_trim_except_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_dynamic_partial(buffer, range, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_dynamic_partial_

#ifndef _di_fll_print_trim_except_dynamic_partial_raw_
  f_status_t fll_print_trim_except_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_dynamic_partial_raw(buffer, range, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_dynamic_partial_raw_

#ifndef _di_fll_print_trim_except_dynamic_partial_raw_safely_
  f_status_t fll_print_trim_except_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_dynamic_partial_raw_safely(buffer, range, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_dynamic_partial_raw_safely_

#ifndef _di_fll_print_trim_except_dynamic_partial_safely_
  f_status_t fll_print_trim_except_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE * const output) {

    flockfile(output);

    const f_status_t status = fl_print_trim_except_dynamic_partial_safely(buffer, range, except, output);

    funlockfile(output);

    return status;
  }
#endif // _di_fll_print_trim_except_dynamic_partial_safely_

#ifdef __cplusplus
} // extern "C"
#endif
