#include "../fake.h"
#include "print-error.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_print_error_argument_invalid_section_
  f_status_t fake_make_print_error_argument_invalid_section(fake_setting_t * const setting, const fl_print_t print, const f_console_parameters_t parameters, const f_array_length_t index) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QThe argument '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, parameters.arguments.array[index], print.notable);
    fl_print_format("%[' is not a valid section name.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_argument_invalid_section_

#ifndef _di_fake_make_print_error_compiler_not_specified_
  f_status_t fake_make_print_error_compiler_not_specified(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t action) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QNo compiler has been specified, cannot perform '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, action, print.notable);
    fl_print_format("%[' section operation.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_compiler_not_specified_

#ifndef _di_fake_make_print_error_content_not_directory_
  f_status_t fake_make_print_error_content_not_directory(fake_setting_t * const setting, const fl_print_t print, const f_string_t content, const f_string_static_t file) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QThe %S content '%]", print.to, print.context, print.prefix, content, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, file, print.notable);
    fl_print_format("%[' must be a valid directory.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_content_not_directory_

#ifndef _di_fake_make_print_error_define_invalid_character_
  f_status_t fake_make_print_error_define_invalid_character(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QInvalid characters in the define setting name '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, name, print.notable);
    fl_print_format("%[', only alpha-numeric ASCII characters and underscore (without a leading digit) are allowed.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_define_invalid_character_

#ifndef _di_fake_make_print_error_fakefile_section_missing_
  f_status_t fake_make_print_error_fakefile_section_missing(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile, const f_string_static_t section) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QThe fakefile '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, fakefile, print.notable);
    fl_print_format("%[' is missing the required '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, section, print.notable);
    fl_print_format("%[' section.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_fakefile_section_missing_

#ifndef _di_fake_make_print_error_file_name_empty_
  f_status_t fake_make_print_error_file_name_empty(fake_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fll_print_format("%[%QFilename argument must not be an empty string.%]%r", print.to, print.context, print.prefix, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_file_name_empty_

#ifndef _di_fake_make_print_error_file_type_
  f_status_t fake_make_print_error_file_type(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t type, const f_string_static_t file) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QThe file '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, file, print.notable);
    fl_print_format("%[' must be a %Q file.%]%r", print.to, print.context, print.context, type, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_file_type_

#ifndef _di_fake_make_print_error_not_after_condition_
  f_status_t fake_make_print_error_not_after_condition(fake_setting_t * const setting, const fl_print_t print, const f_string_t message) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%Q%S used immediately after another '%]", print.to, print.context, print.prefix, message, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, fake_make_operation_if_s, print.notable);
    fl_print_format("%[', '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, fake_make_operation_and_s, print.notable);
    fl_print_format("%[', or '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, fake_make_operation_or_s, print.notable);
    fl_print_format("%[' section operation.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_not_after_condition_

#ifndef _di_fake_make_print_error_operation_incomplete_
  f_status_t fake_make_print_error_operation_incomplete(fake_setting_t * const setting, const fl_print_t print, const uint8_t operation) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QIncomplete '%]", print.to, print.context, print.prefix, print.context);

    if (operation == fake_make_operation_type_and_e) {
      fl_print_format("%[%r%]", print.to, print.notable, fake_make_operation_and_s, print.notable);
    }
    else if (operation == fake_make_operation_type_else_e) {
      fl_print_format("%[%r%]", print.to, print.notable, fake_make_operation_else_s, print.notable);
    }
    else if (operation == fake_make_operation_type_if_e) {
      fl_print_format("%[%r%]", print.to, print.notable, fake_make_operation_if_s, print.notable);
    }
    else {
      fl_print_format("%[%r%]", print.to, print.notable, fake_make_operation_or_s, print.notable);
    }

    fl_print_format("%[' at end of the section.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_operation_incomplete_

#ifndef _di_fake_make_print_error_out_of_range_number_
  f_status_t fake_make_print_error_out_of_range_number(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t number, const f_number_unsigned_t minimum, const f_number_unsigned_t maximum) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QThe number '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, number, print.notable);
    fl_print_format("%[' may only be between the ranges -%un to %un.%]%r", print.to, print.context, minimum, maximum, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_out_of_range_number_

#ifndef _di_fake_make_print_error_program_failed_
  f_status_t fake_make_print_error_program_failed(fake_setting_t * const setting, const fl_print_t print, const int return_code) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QFailed with return code %]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%i%]", print.to, print.notable, return_code, print.notable);
    fl_print_format("%[.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_program_failed_

#ifndef _di_fake_make_print_error_program_not_found_
  f_status_t fake_make_print_error_program_not_found(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t program) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QFailed to find program '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, program, print.notable);
    fl_print_format("%[' for executing.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_program_not_found_

#ifndef _di_fake_make_print_error_unsupported_number_
  f_status_t fake_make_print_error_unsupported_number(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t number) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QInvalid or unsupported number provided '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, number, print.notable);
    fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_unsupported_number_

#ifndef _di_fake_make_print_error_unsupported_type_
  f_status_t fake_make_print_error_unsupported_type(fake_setting_t * const setting, const fl_print_t print, f_string_static_t type, const f_string_static_t value) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QUnsupported %Q type '%]", print.to, print.context, print.prefix, type, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, value, print.notable);
    fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_unsupported_type_

#ifdef __cplusplus
} // extern "C"
#endif
