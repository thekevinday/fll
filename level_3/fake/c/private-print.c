#include "fake.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_error_build_operation_file_
  bool fake_print_error_build_operation_file(const fake_main_t main, const f_status_t status, const f_string_t function, const f_string_t operation, const f_string_t how, const f_string_t source, const f_string_t destination, const bool fallback) {

    if (status == F_file_found_not) {
      if (main.error.verbosity != f_console_verbosity_quiet) {
        fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
        f_color_print(main.error.to.stream, main.context.set.error, "%sFailed to find '", fll_error_print_error);

        if (f_file_exists(source) == F_true) {
          f_color_print(main.error.to.stream, main.context.set.notable, "%s", destination);
        }
        else {
          f_color_print(main.error.to.stream, main.context.set.notable, "%s", source);
        }

        f_color_print(main.error.to.stream, main.context.set.error, "' while trying to %s '", operation);
        f_color_print(main.error.to.stream, main.context.set.notable, "%s", source);

        if (destination) {
          f_color_print(main.error.to.stream, main.context.set.error, "' %s '", how);
          f_color_print(main.error.to.stream, main.context.set.notable, "%s", destination);
        }

        f_color_print(main.error.to.stream, main.context.set.error, "'.%c", f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (main.error.verbosity != f_console_verbosity_quiet) {
        fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
        f_color_print(main.error.to.stream, main.context.set.error, "%sInvalid parameter when calling ", fll_error_print_error);
        f_color_print(main.error.to.stream, main.context.set.notable, "%s", function);
        f_color_print(main.error.to.stream, main.context.set.error, "() to %s '", operation);
        f_color_print(main.error.to.stream, main.context.set.notable, "%s", source);

        if (destination) {
          f_color_print(main.error.to.stream, main.context.set.error, "' %s '", how);
          f_color_print(main.error.to.stream, main.context.set.notable, "%s", destination);
        }

        f_color_print(main.error.to.stream, main.context.set.error, "'.%c", f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_name) {
      if (main.error.verbosity != f_console_verbosity_quiet) {
        fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
        f_color_print(main.error.to.stream, main.context.set.error, "%sInvalid name for '", fll_error_print_error);
        f_color_print(main.error.to.stream, main.context.set.notable, "%s", source);

        if (destination) {
          f_color_print(main.error.to.stream, main.context.set.error, "' or '");
          f_color_print(main.error.to.stream, main.context.set.notable, "%s", destination);
        }

        f_color_print(main.error.to.stream, main.context.set.error, "'.%c", f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_memory_not) {
      if (main.error.verbosity != f_console_verbosity_quiet) {
        fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
        f_color_print(main.error.to.stream, main.context.set.error, "%sUnable to allocate memory, while trying to %s '", fll_error_print_error, operation);
        f_color_print(main.error.to.stream, main.context.set.notable, "%s", source);

        if (destination) {
          f_color_print(main.error.to.stream, main.context.set.error, "' %s '", how);
          f_color_print(main.error.to.stream, main.context.set.notable, "%s", destination);
        }

        f_color_print(main.error.to.stream, main.context.set.error, "'.%c", f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (main.error.verbosity != f_console_verbosity_quiet) {

        fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
        f_color_print(main.error.to.stream, main.context.set.error, "%sOverflow while trying to %s '", fll_error_print_error, operation);
        f_color_print(main.error.to.stream, main.context.set.notable, "%s", source);

        if (destination) {
          f_color_print(main.error.to.stream, main.context.set.error, "' %s '", how);
          f_color_print(main.error.to.stream, main.context.set.notable, "%s", destination);
        }

        f_color_print(main.error.to.stream, main.context.set.error, "'.%c", f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_directory) {
      if (main.error.verbosity != f_console_verbosity_quiet) {
        fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
        f_color_print(main.error.to.stream, main.context.set.error, "%sInvalid directory while trying to %s '", fll_error_print_error, operation);
        f_color_print(main.error.to.stream, main.context.set.notable, "%s", source);

        if (destination) {
          f_color_print(main.error.to.stream, main.context.set.error, "' %s '", how);
          f_color_print(main.error.to.stream, main.context.set.notable, "%s", destination);
        }

        f_color_print(main.error.to.stream, main.context.set.error, "'.%c", f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_access_denied) {
      if (main.error.verbosity != f_console_verbosity_quiet) {
        fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
        f_color_print(main.error.to.stream, main.context.set.error, "%sAccess denied while trying to %s '", fll_error_print_error, operation);
        f_color_print(main.error.to.stream, main.context.set.notable, "%s", source);

        if (destination) {
          f_color_print(main.error.to.stream, main.context.set.error, "' %s '", how);
          f_color_print(main.error.to.stream, main.context.set.notable, "%s", destination);
        }

        f_color_print(main.error.to.stream, main.context.set.error, "'.%c", f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_loop) {
      if (main.error.verbosity != f_console_verbosity_quiet) {
        fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
        f_color_print(main.error.to.stream, main.context.set.error, "%sLoop while trying to %s '", fll_error_print_error, operation);
        f_color_print(main.error.to.stream, main.context.set.notable, "%s", source);

        if (destination) {
          f_color_print(main.error.to.stream, main.context.set.error, "' %s '", how);
          f_color_print(main.error.to.stream, main.context.set.notable, "%s", destination);
        }

        f_color_print(main.error.to.stream, main.context.set.error, "'.%c", f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (main.error.verbosity != f_console_verbosity_quiet) {
        fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
        f_color_print(main.error.to.stream, main.context.set.error, "%sProhibited by system while trying to %s '", fll_error_print_error, operation);
        f_color_print(main.error.to.stream, main.context.set.notable, "%s", source);

        if (destination) {
          f_color_print(main.error.to.stream, main.context.set.error, "' %s '", how);
          f_color_print(main.error.to.stream, main.context.set.notable, "%s", destination);
        }

        f_color_print(main.error.to.stream, main.context.set.error, "'.%c", f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_directory_found_not) {
      if (main.error.verbosity != f_console_verbosity_quiet) {
        fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
        f_color_print(main.error.to.stream, main.context.set.error, "%sFailed to %s '", fll_error_print_error, operation);
        f_color_print(main.error.to.stream, main.context.set.notable, "%s", source);

        if (destination) {
          f_color_print(main.error.to.stream, main.context.set.error, "' %s '", how);
          f_color_print(main.error.to.stream, main.context.set.notable, "%s", destination);
        }

        f_color_print(main.error.to.stream, main.context.set.error, "' due to an invalid directory in the path.%c", f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_failure) {
      if (main.error.verbosity != f_console_verbosity_quiet) {
        fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
        f_color_print(main.error.to.stream, main.context.set.error, "%sFailed to %s '", fll_error_print_error, operation);
        f_color_print(main.error.to.stream, main.context.set.notable, "%s", source);

        if (destination) {
          f_color_print(main.error.to.stream, main.context.set.error, "' %s '", how);
          f_color_print(main.error.to.stream, main.context.set.notable, "%s", destination);
        }

        f_color_print(main.error.to.stream, main.context.set.error, "'.%c", f_string_eol_s[0]);
      }

      return F_false;
    }

    if (fll_error_print(main.error, status, function, F_false) == F_known_not && fallback && main.error.verbosity != f_console_verbosity_quiet) {
      fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
      f_color_print(main.error.to.stream, main.context.set.error, "UNKNOWN %s(", fll_error_print_error);
      f_color_print(main.error.to.stream, main.context.set.notable, "%llu", status);
      f_color_print(main.error.to.stream, main.context.set.error, ") occurred while trying to %s '", operation);
      f_color_print(main.error.to.stream, main.context.set.notable, "%s", source);

      if (destination) {
        f_color_print(main.error.to.stream, main.context.set.error, "' %s '", how);
        f_color_print(main.error.to.stream, main.context.set.notable, "%s", destination);
      }

      f_color_print(main.error.to.stream, main.context.set.error, "'.%c", f_string_eol_s[0]);
    }

    return F_true;
  }
#endif // _di_fake_print_error_build_operation_file_

#ifndef _di_fake_print_error_fss
  bool fake_print_error_fss(const fake_main_t main, const f_status_t status, const f_string_t function, const f_string_t path_file, const f_string_range_t range, const bool fallback) {

    if (status == F_file_found_not) {
      if (main.error.verbosity != f_console_verbosity_quiet) {
        fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
        f_color_print(main.error.to.stream, main.context.set.error, "%serror occurred on invalid UTF-8 character at stop position (at ", fll_error_print_error);
        f_color_print(main.error.to.stream, main.context.set.notable, "%d", range.start);
        f_color_print(main.error.to.stream, main.context.set.error, " of setting file '");
        f_color_print(main.error.to.stream, main.context.set.notable, "%s", path_file);
        f_color_print(main.error.to.stream, main.context.set.error, "').%c", f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_status_set_error(F_complete_not_utf_stop)) {
      if (main.error.verbosity != f_console_verbosity_quiet) {
        fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
        f_color_print(main.error.to.stream, main.context.set.error, "%serror occurred on invalid UTF-8 character at end of string (at ", fll_error_print_error);
        f_color_print(main.error.to.stream, main.context.set.notable, "%d", range.start);
        f_color_print(main.error.to.stream, main.context.set.error, " of setting file '");
        f_color_print(main.error.to.stream, main.context.set.notable, "%s", path_file);
        f_color_print(main.error.to.stream, main.context.set.error, "').%c", f_string_eol_s[0]);
      }

      return F_false;
    }

    if (fll_error_print(main.error, status, function, F_false) == F_known_not && fallback && main.error.verbosity != f_console_verbosity_quiet) {
      fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);
      f_color_print(main.error.to.stream, main.context.set.error, "UNKNOWN %s(", fll_error_print_error);
      f_color_print(main.error.to.stream, main.context.set.notable, "%llu", status);
      f_color_print(main.error.to.stream, main.context.set.error, ") in function ");
      f_color_print(main.error.to.stream, main.context.set.notable, "%s", function);
      f_color_print(main.error.to.stream, main.context.set.error, "().%c", f_string_eol_s[0]);
    }

    return F_true;
  }
#endif // _di_fake_print_error_fss

#ifndef _di_fake_print_error_parameter_missing_value_
  void fake_print_error_parameter_missing_value(const fake_main_t main, const f_string_t parameter) {
    if (main.error.verbosity == f_console_verbosity_quiet) return;

    fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);

    f_color_print(main.error.to.stream, main.context.set.error, "%sThe parameter '", fll_error_print_error);
    f_color_print(main.error.to.stream, main.context.set.notable, "%s%s", f_console_symbol_long_enable_s, parameter);

    f_color_print(main.error.to.stream, main.context.set.error, "' was specified, but no value was given.%c", f_string_eol_s[0]);
  }
#endif // _di_fake_print_error_parameter_missing_value_

#ifndef _di_fake_print_error_parameter_too_many_
  void fake_print_error_parameter_too_many(const fake_main_t main, const f_string_t parameter) {
    if (main.error.verbosity == f_console_verbosity_quiet) return;

    fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);

    f_color_print(main.error.to.stream, main.context.set.error, "%sThe parameter '", fll_error_print_error);
    f_color_print(main.error.to.stream, main.context.set.notable, "%s%s", f_console_symbol_long_enable_s, parameter);

    f_color_print(main.error.to.stream, main.context.set.error, "' specified too many times.%c", f_string_eol_s[0]);
  }
#endif // _di_fake_print_error_parameter_too_many_

#ifndef _di_fake_print_message_section_operation_failed_
  void fake_print_message_section_operation_failed(const fake_main_t main, const fll_error_print_t error, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name) {
    if (main.error.verbosity == f_console_verbosity_quiet || !error.to.stream) return;

    f_array_length_t line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(error.to.stream, "%c", f_string_eol_s[0]);
    f_color_print(error.to.stream, main.error.context, "%sThe section operation '", main.error.prefix);

    f_color_print_code(error.to.stream, main.context.notable);
    f_print_dynamic_partial(error.to.stream, buffer, operation_name);
    f_color_print_code(error.to.stream, main.context.reset);

    f_color_print(error.to.stream, main.error.context, "' from section '");

    f_color_print_code(error.to.stream, main.context.notable);
    f_print_dynamic_partial(error.to.stream, buffer, section_name);
    f_color_print_code(error.to.stream, main.context.reset);

    f_color_print(error.to.stream, main.error.context, "' on line ");
    f_color_print(error.to.stream, main.context.set.notable, "%llu", line);
    f_color_print(error.to.stream, main.error.context, " failed.%c", f_string_eol_s[0]);
  }
#endif // _di_fake_print_message_section_operation_failed_

#ifndef _di_fake_print_message_section_operation_path_outside_
  void fake_print_message_section_operation_path_outside(const fake_main_t main, const fll_error_print_t error, const f_status_t status, const f_string_t function, const f_string_t path) {
    if (main.error.verbosity == f_console_verbosity_quiet || !error.to.stream) return;

    if (F_status_set_fine(status) == F_false) {
      fprintf(error.to.stream, "%c", f_string_eol_s[0]);
      f_color_print(error.to.stream, main.error.context, "%sThe path '", main.error.prefix);
      f_color_print(error.to.stream, main.context.set.notable, "%s", path);
      f_color_print(error.to.stream, main.error.context, "' is outside the project root.%c", f_string_eol_s[0]);
    }
    else {
      fll_error_file_print(main.error, F_status_set_fine(status), function, F_true, path, "determine real path of", fll_error_file_type_file);
    }
  }
#endif // _di_fake_print_message_section_operation_path_outside_

#ifndef _di_fake_print_message_section_operation_path_stack_max_
  void fake_print_message_section_operation_path_stack_max(const fake_main_t main, fll_error_print_t error, const f_status_t status, const f_string_t function, const f_string_t path) {
    if (main.error.verbosity == f_console_verbosity_quiet || !error.to.stream) return;

    if (status == F_array_too_large) {
      fprintf(error.to.stream, "%c", f_string_eol_s[0]);
      f_color_print(error.to.stream, main.error.context, "%s: Maximum stack size reached while processing path '", main.error.prefix);
      f_color_print(error.to.stream, main.context.set.notable, "%s", path);
      f_color_print(error.to.stream, main.error.context, "'");

      if (function) {
        f_color_print(error.to.stream, main.error.context, " while calling ");
        f_color_print(error.to.stream, main.context.set.notable, "%s", function);
        f_color_print(error.to.stream, main.error.context, "()");
      }

      f_color_print(error.to.stream, main.error.context, ".%c", f_string_eol_s[0]);
    }
    else {
      fll_error_file_print(error, status, function, F_true, path, "change path to", fll_error_file_type_directory);
    }
  }
#endif // _di_fake_print_message_section_operation_path_stack_max_

#ifndef _di_fake_print_message_section_operation_stack_max_
  void fake_print_message_section_operation_stack_max(const fake_main_t main, fll_error_print_t error, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name, const f_array_length_t stack_max) {
    if (main.error.verbosity == f_console_verbosity_quiet || !error.to.stream) return;

    f_array_length_t line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(error.to.stream, "%c", f_string_eol_s[0]);
    f_color_print(error.to.stream, main.error.context, "The section operation '", main.error.prefix);

    f_color_print_code(error.to.stream, main.context.notable);
    f_print_dynamic_partial(error.to.stream, buffer, operation_name);
    f_color_print_code(error.to.stream, main.context.reset);

    f_color_print(error.to.stream, main.error.context, "' from section '");

    f_color_print_code(error.to.stream, main.context.notable);
    f_print_dynamic_partial(error.to.stream, buffer, section_name);
    f_color_print_code(error.to.stream, main.context.reset);

    f_color_print(error.to.stream, main.error.context, "' on line ");
    f_color_print(error.to.stream, main.context.set.notable, "%llu", line);
    f_color_print(error.to.stream, main.error.context, " cannot be processed because the max stack depth of ");
    f_color_print(error.to.stream, main.context.set.notable, "%llu", stack_max);
    f_color_print(error.to.stream, main.error.context, " has been reached.%c", f_string_eol_s[0]);
  }
#endif // _di_fake_print_message_section_operation_stack_max_

#ifndef _di_fake_print_message_section_operation_unknown_
  void fake_print_message_section_operation_unknown(const fake_main_t main, const fll_error_print_t error, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name) {
    if (main.error.verbosity == f_console_verbosity_quiet || !error.to.stream) return;

    f_array_length_t line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(error.to.stream, "%c", f_string_eol_s[0]);
    f_color_print(error.to.stream, main.error.context, "%sThe section operation '", main.error.prefix);

    f_color_print_code(error.to.stream, main.context.notable);
    f_print_dynamic_partial(error.to.stream, buffer, operation_name);
    f_color_print_code(error.to.stream, main.context.reset);

    f_color_print(error.to.stream, main.error.context, "' from section '");

    f_color_print_code(error.to.stream, main.context.notable);
    f_print_dynamic_partial(error.to.stream, buffer, section_name);
    f_color_print_code(error.to.stream, main.context.reset);

    f_color_print(error.to.stream, main.error.context, "' on line ");
    f_color_print(error.to.stream, main.context.set.notable, "%llu", line);
    f_color_print(error.to.stream, main.error.context, " is not a known operation name.%c", f_string_eol_s[0]);
  }
#endif // _di_fake_print_message_section_operation_unknown_

#ifndef _di_fake_print_warning_settings_content_empty_
  void fake_print_warning_settings_content_empty(const fake_main_t main, const f_string_t path_file, const f_string_dynamic_t buffer, const f_string_range_t range_object, const f_string_t settings_name) {
    if (main.error.verbosity == f_console_verbosity_quiet) return;

    fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);

    f_color_print(f_type_warning, main.context.set.warning, "%sthe fakefile '", fll_error_print_warning);
    f_color_print(f_type_warning, main.context.set.notable, "%s", path_file);
    f_color_print(f_type_warning, main.context.set.warning, "' has empty content for the '");
    f_color_print(f_type_warning, main.context.set.notable, "%s", settings_name);
    f_color_print(f_type_warning, main.context.set.warning, "' object '");

    f_color_print_code(f_type_warning, main.context.notable);
    f_print_dynamic_partial(f_type_warning, buffer, range_object);
    f_color_print_code(f_type_warning, main.context.reset);

    f_color_print(f_type_warning, main.context.set.warning, "'.%c", f_string_eol_s[0]);
  }
#endif // _di_fake_print_warning_settings_content_empty_

#ifndef _di_fake_print_warning_settings_content_invalid_
  void fake_print_warning_settings_content_invalid(const fake_main_t main, const f_string_t path_file, const f_string_dynamic_t buffer, const f_string_range_t range_object, const f_string_range_t range_content, const f_string_t settings_name) {
    if (main.error.verbosity == f_console_verbosity_quiet) return;

    fprintf(main.output.stream, "%c", f_string_eol_s[0]);

    f_color_print(main.output.stream, main.context.set.warning, "%sthe fakefile '", fll_error_print_warning);
    f_color_print(main.output.stream, main.context.set.notable, "%s", path_file);
    f_color_print(main.output.stream, main.context.set.warning, "' has an invalid content '");

    f_color_print_code(main.output.stream, main.context.notable);
    f_print_dynamic_partial(main.output.stream, buffer, range_content);
    f_color_print_code(main.output.stream, main.context.reset);

    f_color_print(main.output.stream, main.context.set.warning, "' for the '");
    f_color_print(main.output.stream, main.context.set.notable, "%s", settings_name);
    f_color_print(main.output.stream, main.context.set.warning, "' object '");

    f_color_print_code(main.output.stream, main.context.notable);
    f_print_dynamic_partial(main.output.stream, buffer, range_object);
    f_color_print_code(main.output.stream, main.context.reset);

    f_color_print(main.output.stream, main.context.set.warning, "'.%c", f_string_eol_s[0]);
  }
#endif // _di_fake_print_warning_settings_content_invalid_

#ifndef _di_fake_print_warning_settings_content_multiple_
  void fake_print_warning_settings_content_multiple(const fake_main_t main, const f_string_t path_file, const f_string_t name_object) {
    if (main.error.verbosity != f_console_verbosity_verbose) return;

    fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);

    f_color_print(f_type_warning, main.context.set.warning, "%sthe setting '", fll_error_print_warning);
    f_color_print(f_type_warning, main.context.set.notable, "%s", name_object);
    f_color_print(f_type_warning, main.context.set.warning, "' in the file '");
    f_color_print(f_type_warning, main.context.set.notable, "%s", path_file);

    f_color_print(f_type_warning, main.context.set.warning, "' may only have a single property, only using the first.%c", f_string_eol_s[0]);
  }
#endif // _di_fake_print_warning_settings_content_multiple_

#ifndef _di_fake_print_warning_settings_object_multiple_
  void fake_print_warning_settings_object_multiple(const fake_main_t main, const f_string_t path_file, const f_string_t label, const f_string_t name_object) {
    if (main.error.verbosity != f_console_verbosity_verbose) return;

    fprintf(main.error.to.stream, "%c", f_string_eol_s[0]);

    f_color_print(f_type_warning, main.context.set.warning, "%sthe %s object '", fll_error_print_warning, label);
    f_color_print(f_type_warning, main.context.set.notable, "%s", name_object);
    f_color_print(f_type_warning, main.context.set.warning, "' in the file '");
    f_color_print(f_type_warning, main.context.set.notable, "%s", path_file);

    f_color_print(f_type_warning, main.context.set.warning, "' may only be specified once, only using the first.%c", f_string_eol_s[0]);
  }
#endif // _di_fake_print_warning_settings_object_multiple_

#ifdef __cplusplus
} // extern "C"
#endif
