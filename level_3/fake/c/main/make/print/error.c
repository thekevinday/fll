#include "../../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_print_error_argument_invalid_section_
  f_status_t fake_make_print_error_argument_invalid_section(fl_print_t * const print, const f_string_static_t name) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(print, "The argument ", name, " is not a valid section name");

    return F_okay;
  }
#endif // _di_fake_make_print_error_argument_invalid_section_

#ifndef _di_fake_make_print_error_compiler_not_specified_
  f_status_t fake_make_print_error_compiler_not_specified(fl_print_t * const print, const f_string_static_t action) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(print, "No compiler has been specified, cannot perform ", action, " section operation");

    return F_okay;
  }
#endif // _di_fake_make_print_error_compiler_not_specified_

#ifndef _di_fake_make_print_error_content_not_directory_
  f_status_t fake_make_print_error_content_not_directory(fl_print_t * const print, const f_string_t content, const f_string_static_t file) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe %S%rcontent '%]", print->to, print->context, print->prefix, content, content ? f_string_space_s : f_string_empty_s, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, file, print->notable);
    fl_print_format("%[' must be a valid directory.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fake_make_print_error_content_not_directory_

#ifndef _di_fake_make_print_error_define_name_empty_
  f_status_t fake_make_print_error_define_name_empty(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_simple(print, "Define name must not be an empty string");

    return F_okay;
  }
#endif // _di_fake_make_print_error_define_name_empty_

#ifndef _di_fake_make_print_error_define_invalid_character_
  f_status_t fake_make_print_error_define_invalid_character(fl_print_t * const print, const f_string_static_t name) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(print, "Invalid characters in the define name ", name, ", only alpha-numeric ASCII characters and underscore (without a leading digit) are allowed");

    return F_okay;
  }
#endif // _di_fake_make_print_error_define_invalid_character_

#ifndef _di_fake_make_print_error_fakefile_section_missing_
  f_status_t fake_make_print_error_fakefile_section_missing(fl_print_t * const print, const f_string_static_t fakefile, const f_string_static_t section) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe fakefile '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, fakefile, print->notable);
    fl_print_format("%[' is missing the required '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, section, print->notable);
    fl_print_format("%[' section.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fake_make_print_error_fakefile_section_missing_

#ifndef _di_fake_make_print_error_file_name_empty_
  f_status_t fake_make_print_error_file_name_empty(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_simple(print, "File name argument must not be an empty string");

    return F_okay;
  }
#endif // _di_fake_make_print_error_file_name_empty_

#ifndef _di_fake_make_print_error_file_type_
  f_status_t fake_make_print_error_file_type(fl_print_t * const print, const f_string_static_t type, const f_string_static_t file) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe file '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, file, print->notable);
    fl_print_format("%[' must be a %Q file.%]%r", print->to, print->context, print->context, type, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fake_make_print_error_file_type_

#ifndef _di_fake_make_print_error_indexer_not_specified_
  f_status_t fake_make_print_error_indexer_not_specified(fl_print_t * const print, const f_string_static_t action) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(print, "No indexer has been specified, cannot perform ", action, " section operation");

    return F_okay;
  }
#endif // _di_fake_make_print_error_indexer_not_specified_

#ifndef _di_fake_make_print_error_after_condition_
  f_status_t fake_make_print_error_after_condition(fl_print_t * const print, const f_string_t message) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%Q%S '%]", print->to, print->context, print->prefix, message, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, fake_make_operation_if_s, print->notable);
    fl_print_format("%[', '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, fake_make_operation_and_s, print->notable);
    fl_print_format("%[', or '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, fake_make_operation_or_s, print->notable);
    fl_print_format("%[' section operation.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fake_make_print_error_after_condition_

#ifndef _di_fake_make_print_error_after_condition_may_only_
  f_status_t fake_make_print_error_after_condition_may_only(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_make_print_error_after_condition(print, "May only be used immediately after");

    return F_okay;
  }
#endif // _di_fake_make_print_error_after_condition_may_only_

#ifndef _di_fake_make_print_error_after_condition_must_not_
  f_status_t fake_make_print_error_after_condition_must_not(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_make_print_error_after_condition(print, "Must not be used immediately after");

    return F_okay;
  }
#endif // _di_fake_make_print_error_after_condition_must_not_

#ifndef _di_fake_make_print_error_after_condition_no_preceding_
  f_status_t fake_make_print_error_after_condition_no_preceding(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_make_print_error_after_condition(print, "Has no preceding");

    return F_okay;
  }
#endif // _di_fake_make_print_error_after_condition_no_preceding_

#ifndef _di_fake_make_print_error_operation_incomplete_
  f_status_t fake_make_print_error_operation_incomplete(fl_print_t * const print, const uint8_t operation) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QIncomplete '%]", print->to, print->context, print->prefix, print->context);

    if (operation == fake_make_operation_type_and_e) {
      fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, fake_make_operation_and_s, print->notable);
    }
    else if (operation == fake_make_operation_type_else_e) {
      fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, fake_make_operation_else_s, print->notable);
    }
    else if (operation == fake_make_operation_type_if_e) {
      fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, fake_make_operation_if_s, print->notable);
    }
    else {
      fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, fake_make_operation_or_s, print->notable);
    }

    fl_print_format("%[' at end of the section.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fake_make_print_error_operation_incomplete_

#ifndef _di_fake_make_print_error_operation_recursion_
  f_status_t fake_make_print_error_operation_recursion(fl_print_t * const print, const f_string_static_t buffer, const f_range_t range) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe section operation '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, buffer, range, print->notable);
    fl_print_format("%[' is already in the operation stack, recursion is not allowed.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fake_make_print_error_operation_recursion_

#ifndef _di_fake_make_print_error_operation_section_not_found_
  f_status_t fake_make_print_error_operation_section_not_found(fl_print_t * const print, const f_string_static_t name) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(print, "No operation section named ", name, " is found");

    return F_okay;
  }
#endif // _di_fake_make_print_error_operation_section_not_found_

#ifndef _di_fake_make_print_error_out_of_range_number_
  f_status_t fake_make_print_error_out_of_range_number(fl_print_t * const print, const f_string_static_t number, const f_number_unsigned_t minimum, const f_number_unsigned_t maximum) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe number '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, number, print->notable);
    fl_print_format("%[' may only be between the ranges -%un to %un.%]%r", print->to, print->context, minimum, maximum, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fake_make_print_error_out_of_range_number_

#ifndef _di_fake_make_print_error_pop_last_path_
  f_status_t fake_make_print_error_pop_last_path(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_simple(print, "Must not attempt to pop project root off of path stack");

    return F_okay;
  }
#endif // _di_fake_make_print_error_pop_last_path_

#ifndef _di_fake_make_print_error_program_failed_
  f_status_t fake_make_print_error_program_failed(fl_print_t * const print, const int return_code) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QFailed with return code %]", print->to, print->context, print->prefix, print->context);
    fl_print_format("%[%i%]", print->to, print->notable, return_code, print->notable);
    fl_print_format("%[.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fake_make_print_error_program_failed_

#ifndef _di_fake_make_print_error_program_not_found_
  f_status_t fake_make_print_error_program_not_found(fl_print_t * const print, const f_string_static_t program) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(print, "Failed to find program ", program, " for executing");

    return F_okay;
  }
#endif // _di_fake_make_print_error_program_not_found_

#ifndef _di_fake_make_print_error_reserved_parameter_name_
  f_status_t fake_make_print_error_reserved_parameter_name(fl_print_t * const print, const f_string_static_t name) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(print, "Cannot assign a value to the parameter name ", name, " because it is a reserved parameter name");

    return F_okay;
  }
#endif // _di_fake_make_print_error_reserved_parameter_name_

#ifndef _di_fake_make_print_error_target_file_name_empty_
  f_status_t fake_make_print_error_target_file_name_empty(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_simple(print, "Target file name argument must not be an empty string");

    return F_okay;
  }
#endif // _di_fake_make_print_error_target_file_name_empty_

#ifndef _di_fake_make_print_error_unsupported_number_
  f_status_t fake_make_print_error_unsupported_number(fl_print_t * const print, const f_string_static_t number) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(print, "Invalid or unsupported number provided ", number, 0);

    return F_okay;
  }
#endif // _di_fake_make_print_error_unsupported_number_

#ifndef _di_fake_make_print_error_unsupported_type_
  f_status_t fake_make_print_error_unsupported_type(fl_print_t * const print, f_string_static_t type, const f_string_static_t value) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QUnsupported %Q type '%]", print->to, print->context, print->prefix, type, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, value, print->notable);
    fl_print_format("%['.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fake_make_print_error_unsupported_type_

#ifdef __cplusplus
} // extern "C"
#endif
