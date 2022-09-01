#include "fake.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_error_build_operation_file_
  bool fake_print_error_build_operation_file(fake_data_t * const data, const f_status_t status, const char *function, const f_string_static_t operation, const f_string_static_t source, const f_string_static_t destination, const f_string_static_t how, const bool fallback) {

    if (status == F_file_found_not) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%r%[%QFailed to find '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);

        fake_print_error_build_operation_file_message(data, operation, source, destination, how);

        fl_print_format("%['.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%r%[%QInvalid parameter when calling '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
        fl_print_format("%[%S%]", data->main->error.to.stream, data->main->error.notable, function, data->main->error.notable);
        fl_print_format("%[() to %Q '%]", data->main->error.to.stream, data->main->error.context, operation, data->main->error.context);

        fake_print_error_build_operation_file_message(data, operation, source, destination, how);

        fl_print_format("%['.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_name) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%r%[%QInvalid name for '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);

        if (source.used) {
          fl_print_format("%[%Q%]", data->main->error.to.stream, data->main->error.notable, source, data->main->error.notable);
        }

        if (destination.used) {
          fl_print_format("%[' or '%]", data->main->error.to.stream, data->main->error.context, data->main->error.context);
          fl_print_format("%[%Q%]", data->main->error.to.stream, data->main->error.notable, destination, data->main->error.notable);
        }

        fl_print_format("%['.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_memory_not) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%r%[%QUnable to allocate memory, while trying to %Q '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, operation, data->main->error.context);

        fake_print_error_build_operation_file_message(data, operation, source, destination, how);

        fl_print_format("%['.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%r%[%QOverflow while trying to %Q '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, operation, data->main->error.context);

        fake_print_error_build_operation_file_message(data, operation, source, destination, how);

        fl_print_format("%['.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_directory) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%r%[%QInvalid directory while trying to %Q '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, operation, data->main->error.context);

        fake_print_error_build_operation_file_message(data, operation, source, destination, how);

        fl_print_format("%['.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_access_denied) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%r%[%QAccess denied while trying to %Q '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, operation, data->main->error.context);

        fake_print_error_build_operation_file_message(data, operation, source, destination, how);

        fl_print_format("%['.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_loop) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%r%[%QLoop while trying to %Q '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, operation, data->main->error.context);

        fake_print_error_build_operation_file_message(data, operation, source, destination, how);

        fl_print_format("%['.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%r%[%QProhibited by system while trying to %Q '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, operation, data->main->error.context);

        fake_print_error_build_operation_file_message(data, operation, source, destination, how);

        fl_print_format("%['.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_directory_found_not) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%r%[%QFailed to %Q '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, operation, data->main->error.context);

        fake_print_error_build_operation_file_message(data, operation, source, destination, how);

        fl_print_format("%[' due to an invalid directory in the path.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_failure) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%r%[%QFailed to %Q '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, operation, data->main->error.context);

        fake_print_error_build_operation_file_message(data, operation, source, destination, how);

        fl_print_format("%['.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      return F_false;
    }

    if (fll_error_print(data->main->error, status, function, F_false) == F_known_not && fallback && data->main->error.verbosity > f_console_verbosity_quiet_e) {
      flockfile(data->main->error.to.stream);

      fl_print_format("%r%[UNKNOWN %Q(%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
      fl_print_format("%[%ui%]", data->main->error.to.stream, data->main->error.notable, status, data->main->error.notable);
      fl_print_format("%[) occurred while trying to %Q '%]", data->main->error.to.stream, data->main->error.context, operation, data->main->error.context);

      fake_print_error_build_operation_file_message(data, operation, source, destination, how);

      fl_print_format("%['.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

      funlockfile(data->main->error.to.stream);
    }

    return F_true;
  }
#endif // _di_fake_print_error_build_operation_file_

#ifndef _di_fake_print_error_build_operation_file_message_
  void fake_print_error_build_operation_file_message(fake_data_t * const data, const f_string_static_t operation, const f_string_static_t source, const f_string_static_t destination, const f_string_static_t how) {

    if (source.used) {
      fl_print_format("%[%Q%]", data->main->error.to.stream, data->main->error.notable, source, data->main->error.notable);
    }

    fl_print_format("%[while trying to %Q '%]", data->main->error.to.stream, data->main->error.context, operation, data->main->error.context);

    if (destination.used) {
      fl_print_format("%[' %Q '%]", data->main->error.to.stream, data->main->error.context, how, data->main->error.context);
      fl_print_format("%[%Q%]", data->main->error.to.stream, data->main->error.notable, destination, data->main->error.notable);
    }
    else if (source.used) {
      fl_print_format("%[%Q%]", data->main->error.to.stream, data->main->error.notable, source, data->main->error.notable);
    }
  }
#endif // #ifndef _di_fake_print_error_build_operation_file_message_

#ifndef _di_fake_print_error_fss
  bool fake_print_error_fss(fake_data_t * const data, const f_status_t status, const char *function, const f_string_static_t path_file, const f_string_range_t range, const bool fallback) {

    if (status == F_file_found_not) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%r%[%QOccurred on invalid UTF-8 character at stop position (at '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
        fl_print_format("%[%un%]", data->main->error.to.stream, data->main->error.notable, range.start, data->main->error.notable);
        fl_print_format("%[ of setting file '%]", data->main->error.to.stream, data->main->error.context, data->main->error.context);
        fl_print_format("%[%Q%]", data->main->error.to.stream, data->main->error.notable, path_file, data->main->error.notable);
        fl_print_format("%[').%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_complete_not_utf || status == F_complete_not_utf_eos || status == F_complete_not_utf_stop) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%r%[%QOccurred on invalid UTF-8 character at %s (at '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, status == F_complete_not_utf_eos ? "end of string" : "stop point of string", data->main->error.context);
        fl_print_format("%[%un%]", data->main->error.to.stream, data->main->error.notable, range.start, data->main->error.notable);
        fl_print_format("%[ of setting file '%]", data->main->error.to.stream, data->main->error.context, data->main->error.context);
        fl_print_format("%[%Q%]", data->main->error.to.stream, data->main->error.notable, path_file, data->main->error.notable);
        fl_print_format("%[').%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_complete_not_utf_stop) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%r%[%QOccurred on invalid UTF-8 character at stop point of string (at '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
        fl_print_format("%[%un%]", data->main->error.to.stream, data->main->error.notable, range.start, data->main->error.notable);
        fl_print_format("%[ of setting file '%]", data->main->error.to.stream, data->main->error.context, data->main->error.context);
        fl_print_format("%[%Q%]", data->main->error.to.stream, data->main->error.notable, path_file, data->main->error.notable);
        fl_print_format("%[').%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      return F_false;
    }

    if (fll_error_print(data->main->error, status, function, F_false) == F_known_not && fallback && data->main->error.verbosity > f_console_verbosity_quiet_e) {
      flockfile(data->main->error.to.stream);

      fl_print_format("%r%[UNKNOWN %Q(%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
      fl_print_format("%[%ui%]", data->main->error.to.stream, data->main->error.notable, status, data->main->error.notable);
      fl_print_format("%[) in function '%]", data->main->error.to.stream, data->main->error.context, data->main->error.context);
      fl_print_format("%[%Q%]", data->main->error.to.stream, data->main->error.notable, function, data->main->error.notable);
      fl_print_format("%[().%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

      funlockfile(data->main->error.to.stream);
    }

    return F_true;
  }
#endif // _di_fake_print_error_fss

#ifndef _di_fake_print_error_parameter_missing_value_
  void fake_print_error_parameter_missing_value(fake_data_t * const data, const f_string_static_t parameter) {

    if (data->main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(data->main->error.to.stream);

    fl_print_format("%r%[%QThe parameter '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
    fl_print_format("%[%r%r%]", data->main->error.to.stream, data->main->error.notable, f_console_symbol_long_enable_s, parameter, data->main->error.notable);
    fl_print_format("%[' is specified, but no value is given.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

    funlockfile(data->main->error.to.stream);
  }
#endif // _di_fake_print_error_parameter_missing_value_

#ifndef _di_fake_print_error_parameter_too_many_
  void fake_print_error_parameter_too_many(fake_data_t * const data, const f_string_static_t parameter) {

    if (data->main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(data->main->error.to.stream);

    fl_print_format("%r%[%QThe parameter '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
    fl_print_format("%[%r%r%]", data->main->error.to.stream, data->main->error.notable, f_console_symbol_long_enable_s, parameter, data->main->error.notable);
    fl_print_format("%[' was specified too many times.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

    funlockfile(data->main->error.to.stream);
  }
#endif // _di_fake_print_error_parameter_too_many_

#ifndef _di_fake_print_error_requires_more_arguments_
  void fake_print_error_requires_more_arguments(fake_make_data_t * const data_make) {

    if (data_make->error.verbosity == f_console_verbosity_quiet_e) return;
    if (!data_make->error.to.stream) return;

    fll_print_format("%r%[%QRequires more arguments.%]%r", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s);
  }
#endif // _di_fake_print_error_requires_more_arguments_

#ifndef _di_fake_print_error_too_many_arguments_
  void fake_print_error_too_many_arguments(fake_make_data_t * const data_make) {

    if (data_make->error.verbosity == f_console_verbosity_quiet_e) return;
    if (!data_make->error.to.stream) return;

    fll_print_format("%r%[%QHas too many arguments.%]%r", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s);
  }
#endif // _di_fake_print_error_too_many_arguments_

#ifndef _di_fake_print_error_argument_empty_
  void fake_print_error_argument_empty(fake_make_data_t * const data_make, const f_array_length_t index) {

    if (data_make->error.verbosity == f_console_verbosity_quiet_e) return;
    if (!data_make->error.to.stream) return;

    flockfile(data_make->error.to.stream);

    fl_print_format("%r%[%QThe %]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
    fl_print_format("%[%un%]", data_make->error.to.stream, data_make->error.notable, index, data_make->error.notable);
    fl_print_format("%[ argument must not be an empty string.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

    funlockfile(data_make->error.to.stream);
  }
#endif // _di_fake_print_error_argument_empty_

#ifndef _di_fake_print_message_section_operation_failed_
  void fake_print_message_section_operation_failed(fake_data_t * const data, const fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name) {

    if (print.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return;

    f_array_length_t line = 1;
    f_state_t state = f_state_t_initialize;

    f_fss_count_lines(state, buffer, operation_name.start, &line);

    flockfile(print.to.stream);

    fl_print_format("%r%[%QThe section operation '%]", print.to, f_string_eol_s, print.context, print.prefix, print.context);
    fl_print_format("%[%/Q%]", print.to, print.notable, buffer, operation_name, print.notable);
    fl_print_format("%[' from section '%]", print.to, print.context, print.context);
    fl_print_format("%[%/Q%]", print.to, print.notable, buffer, section_name, print.notable);
    fl_print_format("%[' on line%] ", print.to, print.context, print.context);
    fl_print_format("%[%un%]", print.to, print.notable, line, print.notable);
    fl_print_format(" %[failed.%]%r", print.to, print.context, print.context, f_string_eol_s);

    funlockfile(print.to.stream);
  }
#endif // _di_fake_print_message_section_operation_failed_

#ifndef _di_fake_print_message_section_operation_link_argument_unknown_
  void fake_print_message_section_operation_link_argument_unknown(fake_data_t * const data, const fl_print_t print, const f_string_static_t argument) {

    if (print.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return;

    flockfile(print.to.stream);

    fl_print_format("%r%[%QThe argument '%]", print.to, f_string_eol_s, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, argument, print.notable);
    fl_print_format("%[' is not not valid and may only be one of either '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, fake_make_operation_argument_force_s, print.notable);
    fl_print_format("%[' or '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, fake_make_operation_argument_strict_s, print.notable);
    fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

    funlockfile(print.to.stream);

  }
#endif // _di_fake_print_message_section_operation_link_argument_unknown_

#ifndef _di_fake_print_message_section_operation_link_point_exists_
  void fake_print_message_section_operation_link_point_exists(fake_data_t * const data, const fl_print_t print, const f_string_static_t argument) {

    if (print.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return;

    flockfile(print.to.stream);

    fl_print_format("%r%[%QThe point file '%]", print.to, f_string_eol_s, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, argument, print.notable);
    fl_print_format("%[' already exists.%]%r", print.to, print.context, print.context, f_string_eol_s);

    funlockfile(print.to.stream);

  }
#endif // _di_fake_print_message_section_operation_link_point_exists_

#ifndef _di_fake_print_message_section_operation_link_target_exists_not_
  void fake_print_message_section_operation_link_target_exists_not(fake_data_t * const data, const fl_print_t print, const f_string_static_t argument) {

    if (print.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return;

    flockfile(print.to.stream);

    fl_print_format("%r%[%QThe target file '%]", print.to, f_string_eol_s, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, argument, print.notable);
    fl_print_format("%[' does not exist.%]%r", print.to, print.context, print.context, f_string_eol_s);

    funlockfile(print.to.stream);

  }
#endif // _di_fake_print_message_section_operation_link_target_exists_not_

#ifndef _di_fake_print_message_section_operation_path_outside_
  void fake_print_message_section_operation_path_outside(fake_data_t * const data, const fl_print_t print, const f_status_t status, const char *function, const f_string_static_t path) {

    if (data->main->error.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return;

    flockfile(data->main->error.to.stream);

    if (F_status_set_fine(status) == F_false) {
      fl_print_format("%r%[%QThe path '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
      fl_print_format("%[%Q%]", data->main->error.to.stream, data->main->error.notable, path, data->main->error.notable);
      fl_print_format("%[' is outside the project root.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);
    }
    else {
      fll_error_file_print(data->main->error, F_status_set_fine(status), function, F_true, path, fake_common_file_path_determine_real_s, fll_error_file_type_file_e);
    }

    funlockfile(data->main->error.to.stream);
  }
#endif // _di_fake_print_message_section_operation_path_outside_

#ifndef _di_fake_print_message_section_operation_path_stack_max_
  void fake_print_message_section_operation_path_stack_max(fake_data_t * const data, fl_print_t print, const f_status_t status, const char *function, const f_string_static_t path) {

    if (data->main->error.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return;

    if (status == F_array_too_large) {
      flockfile(data->main->error.to.stream);

      fl_print_format("%r%[%QMaximum stack size reached while processing path '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
      fl_print_format("%[%Q%]", data->main->error.to.stream, data->main->error.notable, path, data->main->error.notable);
      fl_print_format("%['", data->main->error.to.stream, data->main->error.context);

      if (function) {
        fl_print_format(" while calling%] %[%S%]", data->main->error.to.stream, data->main->error.context, data->main->error.notable, function, data->main->error.notable);
        fl_print_format("%[()", data->main->error.to.stream, data->main->error.context);
      }

      fl_print_format(".%]%r", data->main->error.to.stream, data->main->error.context, f_string_eol_s);

      funlockfile(data->main->error.to.stream);
    }
    else {
      fll_error_file_print(print, status, function, F_true, path, fake_common_file_path_change_to_s, fll_error_file_type_directory_e);
    }
  }
#endif // _di_fake_print_message_section_operation_path_stack_max_

#ifndef _di_fake_print_message_section_operation_stack_max_
  void fake_print_message_section_operation_stack_max(fake_data_t * const data, fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name, const f_array_length_t stack_max) {

    if (data->main->error.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return;

    f_array_length_t line = 1;
    f_state_t state = f_state_t_initialize;

    f_fss_count_lines(state, buffer, operation_name.start, &line);

    flockfile(data->main->error.to.stream);

    fl_print_format("%r%[%QThe section operation '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
    fl_print_format("%[%/Q%]", data->main->error.to.stream, data->main->error.notable, buffer, operation_name, data->main->error.notable);
    fl_print_format("%[' from section '%]", data->main->error.to.stream, data->main->error.context, buffer, data->main->error.context);
    fl_print_format("%[%/Q%]", data->main->error.to.stream, data->main->error.notable, buffer, section_name, data->main->error.notable);
    fl_print_format("%[' on line%] ", data->main->error.to.stream, data->main->error.context, data->main->error.context);
    fl_print_format("%[%ul%]", data->main->error.to.stream, data->main->error.notable, line, data->main->error.notable);
    fl_print_format("%[' cannot be processed because the max stack depth of%] ", data->main->error.to.stream, data->main->error.context, data->main->error.context);
    fl_print_format("%[%ul%]", data->main->error.to.stream, data->main->error.notable, stack_max, data->main->error.notable);
    fl_print_format(" %[has been reached.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

    funlockfile(data->main->error.to.stream);
  }
#endif // _di_fake_print_message_section_operation_stack_max_

#ifndef _di_fake_print_message_section_operation_unknown_
  void fake_print_message_section_operation_unknown(fake_data_t * const data, const fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name) {

    if (data->main->error.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return;

    f_array_length_t line = 1;
    f_state_t state = f_state_t_initialize;

    f_fss_count_lines(state, buffer, operation_name.start, &line);

    flockfile(data->main->error.to.stream);

    fl_print_format("%r%[%QThe section operation '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
    fl_print_format("%[%/Q%]", data->main->error.to.stream, data->main->error.notable, buffer, operation_name, data->main->error.notable);
    fl_print_format("%[' from section '%]", data->main->error.to.stream, data->main->error.context, buffer, data->main->error.context);
    fl_print_format("%[%/Q%]", data->main->error.to.stream, data->main->error.notable, buffer, section_name, data->main->error.notable);
    fl_print_format("%[' on line%] ", data->main->error.to.stream, data->main->error.context, data->main->error.context);
    fl_print_format("%[%ul%]", data->main->error.to.stream, data->main->error.notable, line, data->main->error.notable);
    fl_print_format(" %[is not a known operation name.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

    funlockfile(data->main->error.to.stream);
  }
#endif // _di_fake_print_message_section_operation_unknown_

#ifndef _di_fake_print_warning_settings_content_empty_
  void fake_print_warning_settings_content_empty(fake_data_t * const data, const f_string_static_t path_file, const f_string_dynamic_t buffer, const f_string_range_t range_object, const f_string_static_t settings_name) {

    if (data->main->warning.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(data->main->warning.to.stream);

    fl_print_format("%r%[%QThe fakefile '%]", data->main->warning.to.stream, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, data->main->warning.context);
    fl_print_format("%[%Q%]", data->main->warning.to.stream, data->main->warning.notable, path_file, data->main->warning.notable);
    fl_print_format("%[' has empty content for the '%]", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context);
    fl_print_format("%[%r%]", data->main->warning.to.stream, data->main->warning.notable, settings_name, data->main->warning.notable);
    fl_print_format("%[' object '%]", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context);
    fl_print_format("%[%/Q%]", data->main->warning.to.stream, data->main->warning.notable, buffer, range_object, data->main->warning.notable);
    fl_print_format("%['.%]%r", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context, f_string_eol_s);

    funlockfile(data->main->warning.to.stream);
  }
#endif // _di_fake_print_warning_settings_content_empty_

#ifndef _di_fake_print_warning_settings_content_invalid_
  void fake_print_warning_settings_content_invalid(fake_data_t * const data, const f_string_static_t path_file, const f_string_dynamic_t buffer, const f_string_range_t range_object, const f_string_range_t range_content, const f_string_static_t settings_name) {

    if (data->main->warning.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(data->main->warning.to.stream);

    fl_print_format("%r%[%QThe fakefile '%]", data->main->warning.to.stream, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, data->main->warning.context);
    fl_print_format("%[%Q%]", data->main->warning.to.stream, data->main->warning.notable, path_file, data->main->warning.notable);
    fl_print_format("%[' has invalid content '%]", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context);
    fl_print_format("%[%/Q%]", data->main->warning.to.stream, data->main->warning.notable, buffer, range_content, data->main->warning.notable);
    fl_print_format("%[' for the '%]", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context);
    fl_print_format("%[%r%]", data->main->warning.to.stream, data->main->warning.notable, settings_name, data->main->warning.notable);
    fl_print_format("%[' object '%]", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context);
    fl_print_format("%[%/Q%]", data->main->warning.to.stream, data->main->warning.notable, buffer, range_object, data->main->warning.notable);
    fl_print_format("%['.%]%r", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context, f_string_eol_s);

    funlockfile(data->main->warning.to.stream);
  }
#endif // _di_fake_print_warning_settings_content_invalid_

#ifndef _di_fake_print_warning_settings_content_multiple_
  void fake_print_warning_settings_content_multiple(fake_data_t * const data, const f_string_static_t path_file, const f_string_static_t name_object) {

    if (data->main->warning.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(data->main->warning.to.stream);

    fl_print_format("%r%[%QThe fakefile '%]", data->main->warning.to.stream, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, data->main->warning.context);
    fl_print_format("%[%r%]", data->main->warning.to.stream, data->main->warning.notable, name_object, data->main->warning.notable);
    fl_print_format("%[' in the file '%]", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context);
    fl_print_format("%[%Q%]", data->main->warning.to.stream, data->main->warning.notable, path_file, data->main->warning.notable);
    fl_print_format("%[' may only have a single property, only using the first.%]%r", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context, f_string_eol_s);

    funlockfile(data->main->warning.to.stream);
  }
#endif // _di_fake_print_warning_settings_content_multiple_

#ifndef _di_fake_print_warning_settings_object_multiple_
  void fake_print_warning_settings_object_multiple(fake_data_t * const data, const f_string_static_t path_file, const f_string_static_t label, const f_string_static_t name_object) {

    if (data->main->warning.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(data->main->warning.to.stream);

    fl_print_format("%r%[%QThe object '%]", data->main->warning.to.stream, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, data->main->warning.context);
    fl_print_format("%[%r%]", data->main->warning.to.stream, data->main->warning.notable, name_object, data->main->warning.notable);
    fl_print_format("%[' in the file '%]", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context);
    fl_print_format("%[%Q%]", data->main->warning.to.stream, data->main->warning.notable, path_file, data->main->warning.notable);
    fl_print_format("%[' may only be specified once, only using the first.%]%r", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context, f_string_eol_s);

    funlockfile(data->main->warning.to.stream);
  }
#endif // _di_fake_print_warning_settings_object_multiple_

#ifdef __cplusplus
} // extern "C"
#endif
