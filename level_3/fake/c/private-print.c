#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_error_build_operation_file_
  bool fake_print_error_build_operation_file(fake_main_t * const main, const f_status_t status, const f_string_t function, const f_string_static_t operation, const f_string_static_t source, const f_string_static_t destination, const f_string_static_t how, const bool fallback) {

    if (status == F_file_found_not) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QFailed to find '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);

        fake_print_error_build_operation_file_message(main, operation, source, destination, how);

        fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QInvalid parameter when calling '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%S%]", main->error.to.stream, main->error.notable, function, main->error.notable);
        fl_print_format("%[() to %Q '%]", main->error.to.stream, main->error.context, operation, main->error.context);

        fake_print_error_build_operation_file_message(main, operation, source, destination, how);

        fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_name) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QInvalid name for '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);

        if (source.used) {
          fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, source, main->error.notable);
        }

        if (destination.used) {
          fl_print_format("%[' or '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, destination, main->error.notable);
        }

        fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_memory_not) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QUnable to allocate memory, while trying to %Q '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, operation, main->error.context);

        fake_print_error_build_operation_file_message(main, operation, source, destination, how);

        fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QOverflow while trying to %Q '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, operation, main->error.context);

        fake_print_error_build_operation_file_message(main, operation, source, destination, how);

        fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_directory) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QInvalid directory while trying to %Q '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, operation, main->error.context);

        fake_print_error_build_operation_file_message(main, operation, source, destination, how);

        fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_access_denied) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QAccess denied while trying to %Q '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, operation, main->error.context);

        fake_print_error_build_operation_file_message(main, operation, source, destination, how);

        fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_loop) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QLoop while trying to %Q '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, operation, main->error.context);

        fake_print_error_build_operation_file_message(main, operation, source, destination, how);

        fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QProhibited by system while trying to %Q '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, operation, main->error.context);

        fake_print_error_build_operation_file_message(main, operation, source, destination, how);

        fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_directory_found_not) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QFailed to %Q '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, operation, main->error.context);

        fake_print_error_build_operation_file_message(main, operation, source, destination, how);

        fl_print_format("%[' due to an invalid directory in the path.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_failure) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QFailed to %Q '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, operation, main->error.context);

        fake_print_error_build_operation_file_message(main, operation, source, destination, how);

        fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }

      return F_false;
    }

    if (fll_error_print(main->error, status, function, F_false) == F_known_not && fallback && main->error.verbosity != f_console_verbosity_quiet_e) {
      flockfile(main->error.to.stream);

      fl_print_format("%r%[UNKNOWN %Q(%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
      fl_print_format("%[%ui%]", main->error.to.stream, main->error.notable, status, main->error.notable);
      fl_print_format("%[) occurred while trying to %Q '%]", main->error.to.stream, main->error.context, operation, main->error.context);

      fake_print_error_build_operation_file_message(main, operation, source, destination, how);

      fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

      funlockfile(main->error.to.stream);
    }

    return F_true;
  }
#endif // _di_fake_print_error_build_operation_file_

#ifndef _di_fake_print_error_build_operation_file_message_
  void fake_print_error_build_operation_file_message(fake_main_t * const main, const f_string_static_t operation, const f_string_static_t source, const f_string_static_t destination, const f_string_static_t how) {

    if (source.used) {
      fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, source, main->error.notable);
    }

    fl_print_format("%[while trying to %Q '%]", main->error.to.stream, main->error.context, operation, main->error.context);

    if (destination.used) {
      fl_print_format("%[' %Q '%]", main->error.to.stream, main->error.context, how, main->error.context);
      fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, destination, main->error.notable);
    }
    else if (source.used) {
      fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, source, main->error.notable);
    }
  }
#endif // #ifndef _di_fake_print_error_build_operation_file_message_

#ifndef _di_fake_print_error_fss
  bool fake_print_error_fss(fake_main_t * const main, const f_status_t status, const f_string_t function, const f_string_static_t path_file, const f_string_range_t range, const bool fallback) {

    if (status == F_file_found_not) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QOccurred on invalid UTF-8 character at stop position (at '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%un%]", main->error.to.stream, main->error.notable, range.start, main->error.notable);
        fl_print_format("%[ of setting file '%]", main->error.to.stream, main->error.context, main->error.context);
        fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, path_file, main->error.notable);
        fl_print_format("%[').%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_complete_not_utf || status == F_complete_not_utf_eos || status == F_complete_not_utf_stop) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QOccurred on invalid UTF-8 character at %s (at '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, status == F_complete_not_utf_eos ? "end of string" : "stop point of string", main->error.context);
        fl_print_format("%[%un%]", main->error.to.stream, main->error.notable, range.start, main->error.notable);
        fl_print_format("%[ of setting file '%]", main->error.to.stream, main->error.context, main->error.context);
        fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, path_file, main->error.notable);
        fl_print_format("%[').%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }

      return F_false;
    }

    if (status == F_complete_not_utf_stop) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QOccurred on invalid UTF-8 character at stop point of string (at '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%un%]", main->error.to.stream, main->error.notable, range.start, main->error.notable);
        fl_print_format("%[ of setting file '%]", main->error.to.stream, main->error.context, main->error.context);
        fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, path_file, main->error.notable);
        fl_print_format("%[').%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }

      return F_false;
    }

    if (fll_error_print(main->error, status, function, F_false) == F_known_not && fallback && main->error.verbosity != f_console_verbosity_quiet_e) {
      flockfile(main->error.to.stream);

      fl_print_format("%r%[UNKNOWN %Q(%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
      fl_print_format("%[%ui%]", main->error.to.stream, main->error.notable, status, main->error.notable);
      fl_print_format("%[) in function '%]", main->error.to.stream, main->error.context, main->error.context);
      fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, function, main->error.notable);
      fl_print_format("%[().%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

      funlockfile(main->error.to.stream);
    }

    return F_true;
  }
#endif // _di_fake_print_error_fss

#ifndef _di_fake_print_error_parameter_missing_value_
  void fake_print_error_parameter_missing_value(fake_main_t * const main, const f_string_static_t parameter) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
    fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, parameter, main->error.notable);
    fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_fake_print_error_parameter_missing_value_

#ifndef _di_fake_print_error_parameter_too_many_
  void fake_print_error_parameter_too_many(fake_main_t * const main, const f_string_static_t parameter) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
    fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, parameter, main->error.notable);
    fl_print_format("%[' was specified too many times.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

    funlockfile(main->error.to.stream);
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

#ifndef _di_fake_print_message_section_operation_failed_
  void fake_print_message_section_operation_failed(fake_main_t * const main, const fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name) {

    if (main->error.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return;

    f_array_length_t line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThe section operation '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
    fl_print_format("%[%/Q%]", main->error.to.stream, main->error.notable, buffer, operation_name, main->error.notable);
    fl_print_format("%[' from section '%]", main->error.to.stream, main->error.context, main->error.context);
    fl_print_format("%[%/Q%]", main->error.to.stream, main->error.notable, buffer, section_name, main->error.notable);
    fl_print_format("%[' on line%] ", main->error.to.stream, main->error.context, main->error.context);
    fl_print_format("%[%un%]", main->error.to.stream, main->error.notable, line, main->error.notable);
    fl_print_format(" %[failed.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_fake_print_message_section_operation_failed_

#ifndef _di_fake_print_message_section_operation_path_outside_
  void fake_print_message_section_operation_path_outside(fake_main_t * const main, const fl_print_t print, const f_status_t status, const f_string_t function, const f_string_static_t path) {

    if (main->error.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return;

    flockfile(main->error.to.stream);

    if (F_status_set_fine(status) == F_false) {
      fl_print_format("%r%[%QThe path '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
      fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, path, main->error.notable);
      fl_print_format("%[' is outside the project root.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);
    }
    else {
      fll_error_file_print(main->error, F_status_set_fine(status), function, F_true, path, fake_common_file_path_determine_real_s, fll_error_file_type_file_e);
    }

    funlockfile(main->error.to.stream);
  }
#endif // _di_fake_print_message_section_operation_path_outside_

#ifndef _di_fake_print_message_section_operation_path_stack_max_
  void fake_print_message_section_operation_path_stack_max(fake_main_t * const main, fl_print_t print, const f_status_t status, const f_string_t function, const f_string_static_t path) {

    if (main->error.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return;

    if (status == F_array_too_large) {
      flockfile(main->error.to.stream);

      fl_print_format("%r%[%QMaximum stack size reached while processing path '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
      fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, path, main->error.notable);
      fl_print_format("%['", main->error.to.stream, main->error.context);

      if (function) {
        fl_print_format(" while calling%] %[%S%]", main->error.to.stream, main->error.context, main->error.notable, function, main->error.notable);
        fl_print_format("%[()", main->error.to.stream, main->error.context);
      }

      fl_print_format(".%]%r", main->error.to.stream, main->error.context, f_string_eol_s);

      funlockfile(main->error.to.stream);
    }
    else {
      fll_error_file_print(print, status, function, F_true, path, fake_common_file_path_change_to_s, fll_error_file_type_directory_e);
    }
  }
#endif // _di_fake_print_message_section_operation_path_stack_max_

#ifndef _di_fake_print_message_section_operation_stack_max_
  void fake_print_message_section_operation_stack_max(fake_main_t * const main, fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name, const f_array_length_t stack_max) {

    if (main->error.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return;

    f_array_length_t line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThe section operation '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
    fl_print_format("%[%/Q%]", main->error.to.stream, main->error.notable, buffer, operation_name, main->error.notable);
    fl_print_format("%[' from section '%]", main->error.to.stream, main->error.context, buffer, main->error.context);
    fl_print_format("%[%/Q%]", main->error.to.stream, main->error.notable, buffer, section_name, main->error.notable);
    fl_print_format("%[' on line%] ", main->error.to.stream, main->error.context, main->error.context);
    fl_print_format("%[%ul%]", main->error.to.stream, main->error.notable, line, main->error.notable);
    fl_print_format("%[' cannot be processed because the max stack depth of%] ", main->error.to.stream, main->error.context, main->error.context);
    fl_print_format("%[%ul%]", main->error.to.stream, main->error.notable, stack_max, main->error.notable);
    fl_print_format(" %[has been reached.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_fake_print_message_section_operation_stack_max_

#ifndef _di_fake_print_message_section_operation_unknown_
  void fake_print_message_section_operation_unknown(fake_main_t * const main, const fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name) {

    if (main->error.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return;

    f_array_length_t line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThe section operation '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
    fl_print_format("%[%/Q%]", main->error.to.stream, main->error.notable, buffer, operation_name, main->error.notable);
    fl_print_format("%[' from section '%]", main->error.to.stream, main->error.context, buffer, main->error.context);
    fl_print_format("%[%/Q%]", main->error.to.stream, main->error.notable, buffer, section_name, main->error.notable);
    fl_print_format("%[' on line%] ", main->error.to.stream, main->error.context, main->error.context);
    fl_print_format("%[%ul%]", main->error.to.stream, main->error.notable, line, main->error.notable);
    fl_print_format(" %[is not a known operation name.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_fake_print_message_section_operation_unknown_

#ifndef _di_fake_print_signal_received_
  void fake_print_signal_received(fake_main_t * const main, const f_status_t signal) {

    if (main->warning.verbosity != f_console_verbosity_verbose_e) return;

    // Must flush and reset color because the interrupt may have interrupted the middle of a print function.
    fflush(main->warning.to.stream);

    flockfile(main->warning.to.stream);

    fl_print_format("%]%r%r%[Received signal code %]", main->warning.to.stream, main->context.set.reset, f_string_eol_s, f_string_eol_s, main->context.set.warning, main->context.set.warning);
    fl_print_format("%[%i%]", main->warning.to.stream, main->context.set.notable, signal, main->context.set.notable);
    fl_print_format("%[.%]%r", main->warning.to.stream, main->context.set.warning, main->context.set.warning, f_string_eol_s);

    funlockfile(main->warning.to.stream);
  }
#endif // _di_fake_print_signal_received_

#ifndef _di_fake_print_warning_settings_content_empty_
  void fake_print_warning_settings_content_empty(fake_main_t * const main, const f_string_static_t path_file, const f_string_dynamic_t buffer, const f_string_range_t range_object, const f_string_static_t settings_name) {

    if (main->warning.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->warning.to.stream);

    fl_print_format("%r%[%QThe fakefile '%]", main->warning.to.stream, f_string_eol_s, main->warning.context, main->warning.prefix, main->warning.context);
    fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, path_file, main->warning.notable);
    fl_print_format("%[' has empty content for the '%]", main->warning.to.stream, main->warning.context, main->warning.context);
    fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, settings_name, main->warning.notable);
    fl_print_format("%[' object '%]", main->warning.to.stream, main->warning.context, main->warning.context);
    fl_print_format("%[%/Q%]", main->warning.to.stream, main->warning.notable, buffer, range_object, main->warning.notable);
    fl_print_format("%['.%]%r", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s);

    funlockfile(main->warning.to.stream);
  }
#endif // _di_fake_print_warning_settings_content_empty_

#ifndef _di_fake_print_warning_settings_content_invalid_
  void fake_print_warning_settings_content_invalid(fake_main_t * const main, const f_string_static_t path_file, const f_string_dynamic_t buffer, const f_string_range_t range_object, const f_string_range_t range_content, const f_string_static_t settings_name) {

    if (main->warning.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->warning.to.stream);

    fl_print_format("%r%[%QThe fakefile '%]", main->warning.to.stream, f_string_eol_s, main->warning.context, main->warning.prefix, main->warning.context);
    fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, path_file, main->warning.notable);
    fl_print_format("%[' has invalid content '%]", main->warning.to.stream, main->warning.context, main->warning.context);
    fl_print_format("%[%/Q%]", main->warning.to.stream, main->warning.notable, buffer, range_content, main->warning.notable);
    fl_print_format("%[' for the '%]", main->warning.to.stream, main->warning.context, main->warning.context);
    fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, settings_name, main->warning.notable);
    fl_print_format("%[' object '%]", main->warning.to.stream, main->warning.context, main->warning.context);
    fl_print_format("%[%/Q%]", main->warning.to.stream, main->warning.notable, buffer, range_object, main->warning.notable);
    fl_print_format("%['.%]%r", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s);

    funlockfile(main->warning.to.stream);
  }
#endif // _di_fake_print_warning_settings_content_invalid_

#ifndef _di_fake_print_warning_settings_content_multiple_
  void fake_print_warning_settings_content_multiple(fake_main_t * const main, const f_string_static_t path_file, const f_string_static_t name_object) {

    if (main->warning.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->warning.to.stream);

    fl_print_format("%r%[%QThe fakefile '%]", main->warning.to.stream, f_string_eol_s, main->warning.context, main->warning.prefix, main->warning.context);
    fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, name_object, main->warning.notable);
    fl_print_format("%[' in the file '%]", main->warning.to.stream, main->warning.context, main->warning.context);
    fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, path_file, main->warning.notable);
    fl_print_format("%[' may only have a single property, only using the first.%]%r", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s);

    funlockfile(main->warning.to.stream);
  }
#endif // _di_fake_print_warning_settings_content_multiple_

#ifndef _di_fake_print_warning_settings_object_multiple_
  void fake_print_warning_settings_object_multiple(fake_main_t * const main, const f_string_static_t path_file, const f_string_static_t label, const f_string_static_t name_object) {

    if (main->warning.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->warning.to.stream);

    fl_print_format("%r%[%QThe object '%]", main->warning.to.stream, f_string_eol_s, main->warning.context, main->warning.prefix, main->warning.context);
    fl_print_format("%[%r%]", main->warning.to.stream, main->warning.notable, name_object, main->warning.notable);
    fl_print_format("%[' in the file '%]", main->warning.to.stream, main->warning.context, main->warning.context);
    fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, path_file, main->warning.notable);
    fl_print_format("%[' may only be specified once, only using the first.%]%r", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s);

    funlockfile(main->warning.to.stream);
  }
#endif // _di_fake_print_warning_settings_object_multiple_

#ifdef __cplusplus
} // extern "C"
#endif
