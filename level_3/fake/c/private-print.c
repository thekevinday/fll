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
  bool fake_print_error_build_operation_file(const fake_data_t data, const f_status_t status, const f_string_t function, const f_string_t operation, const f_string_t how, const f_string_t source, const f_string_t destination, const bool fallback) {

    if (status == F_file_found_not) {
      if (data.error.verbosity != f_console_verbosity_quiet) {
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%sFailed to find '", fll_error_print_error);

        if (f_file_exists(source) == F_true) {
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", destination);
        }
        else {
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", source);
        }

        fl_color_print(data.error.to.stream, data.context.set.error, "' while trying to %s '", operation);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(data.error.to.stream, data.context.set.error, "' %s '", how);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", destination);
        }

        fl_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (data.error.verbosity != f_console_verbosity_quiet) {
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%sInvalid parameter when calling ", fll_error_print_error);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s", function);
        fl_color_print(data.error.to.stream, data.context.set.error, "() to %s '", operation);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(data.error.to.stream, data.context.set.error, "' %s '", how);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", destination);
        }

        fl_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_name) {
      if (data.error.verbosity != f_console_verbosity_quiet) {
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%sInvalid name for '", fll_error_print_error);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(data.error.to.stream, data.context.set.error, "' or '");
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", destination);
        }

        fl_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_memory_not) {
      if (data.error.verbosity != f_console_verbosity_quiet) {
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%sUnable to allocate memory, while trying to %s '", fll_error_print_error, operation);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(data.error.to.stream, data.context.set.error, "' %s '", how);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", destination);
        }

        fl_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (data.error.verbosity != f_console_verbosity_quiet) {

        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%sOverflow while trying to %s '", fll_error_print_error, operation);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(data.error.to.stream, data.context.set.error, "' %s '", how);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", destination);
        }

        fl_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_directory) {
      if (data.error.verbosity != f_console_verbosity_quiet) {
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%sInvalid directory while trying to %s '", fll_error_print_error, operation);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(data.error.to.stream, data.context.set.error, "' %s '", how);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", destination);
        }

        fl_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_access_denied) {
      if (data.error.verbosity != f_console_verbosity_quiet) {
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%sAccess denied while trying to %s '", fll_error_print_error, operation);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(data.error.to.stream, data.context.set.error, "' %s '", how);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", destination);
        }

        fl_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_loop) {
      if (data.error.verbosity != f_console_verbosity_quiet) {
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%sLoop while trying to %s '", fll_error_print_error, operation);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(data.error.to.stream, data.context.set.error, "' %s '", how);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", destination);
        }

        fl_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (data.error.verbosity != f_console_verbosity_quiet) {
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%sProhibited by system while trying to %s '", fll_error_print_error, operation);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(data.error.to.stream, data.context.set.error, "' %s '", how);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", destination);
        }

        fl_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_directory_found_not) {
      if (data.error.verbosity != f_console_verbosity_quiet) {
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%sFailed to %s '", fll_error_print_error, operation);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(data.error.to.stream, data.context.set.error, "' %s '", how);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", destination);
        }

        fl_color_print(data.error.to.stream, data.context.set.error, "' due to an invalid directory in the path.%c", f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_failure) {
      if (data.error.verbosity != f_console_verbosity_quiet) {
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%sFailed to %s '", fll_error_print_error, operation);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(data.error.to.stream, data.context.set.error, "' %s '", how);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s", destination);
        }

        fl_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol[0]);
      }

      return F_false;
    }

    if (fll_error_print(data.error, status, function, F_false) == F_unknown && fallback && data.error.verbosity != f_console_verbosity_quiet) {
      fprintf(data.error.to.stream, "%c", f_string_eol[0]);
      fl_color_print(data.error.to.stream, data.context.set.error, "UNKNOWN %s(", fll_error_print_error);
      fl_color_print(data.error.to.stream, data.context.set.notable, "%llu", status);
      fl_color_print(data.error.to.stream, data.context.set.error, ") occurred while trying to %s '", operation);
      fl_color_print(data.error.to.stream, data.context.set.notable, "%s", source);

      if (destination) {
        fl_color_print(data.error.to.stream, data.context.set.error, "' %s '", how);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s", destination);
      }

      fl_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol[0]);
    }

    return F_true;
  }
#endif // _di_fake_print_error_build_operation_file_

#ifndef _di_fake_print_error_fss
  bool fake_print_error_fss(const fake_data_t data, const f_status_t status, const f_string_t function, const f_string_t path_file, const f_string_range_t range, const bool fallback) {

    if (status == F_file_found_not) {
      if (data.error.verbosity != f_console_verbosity_quiet) {
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%serror occurred on invalid UTF-8 character at stop position (at ", fll_error_print_error);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%d", range.start);
        fl_color_print(data.error.to.stream, data.context.set.error, " of setting file '");
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s", path_file);
        fl_color_print(data.error.to.stream, data.context.set.error, "').%c", f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_status_set_error(F_incomplete_utf_stop)) {
      if (data.error.verbosity != f_console_verbosity_quiet) {
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%serror occurred on invalid UTF-8 character at end of string (at ", fll_error_print_error);
        fl_color_print(data.error.to.stream, data.context.set.notable, "%d", range.start);
        fl_color_print(data.error.to.stream, data.context.set.error, " of setting file '");
        fl_color_print(data.error.to.stream, data.context.set.notable, "%s", path_file);
        fl_color_print(data.error.to.stream, data.context.set.error, "').%c", f_string_eol[0]);
      }

      return F_false;
    }

    if (fll_error_print(data.error, status, function, F_false) == F_unknown && fallback && data.error.verbosity != f_console_verbosity_quiet) {
      fprintf(data.error.to.stream, "%c", f_string_eol[0]);
      fl_color_print(data.error.to.stream, data.context.set.error, "UNKNOWN %s(", fll_error_print_error);
      fl_color_print(data.error.to.stream, data.context.set.notable, "%llu", status);
      fl_color_print(data.error.to.stream, data.context.set.error, ") in function ");
      fl_color_print(data.error.to.stream, data.context.set.notable, "%s", function);
      fl_color_print(data.error.to.stream, data.context.set.error, "().%c", f_string_eol[0]);
    }

    return F_true;
  }
#endif // _di_fake_print_error_fss

#ifndef _di_fake_print_error_parameter_missing_value_
  void fake_print_error_parameter_missing_value(const fake_data_t data, const f_string_t parameter) {
    if (data.error.verbosity == f_console_verbosity_quiet) return;

    fprintf(data.error.to.stream, "%c", f_string_eol[0]);

    fl_color_print(data.error.to.stream, data.context.set.error, "%sThe parameter '", fll_error_print_error);
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, parameter);

    fl_color_print(data.error.to.stream, data.context.set.error, "' was specified, but no value was given.%c", f_string_eol[0]);
  }
#endif // _di_fake_print_error_parameter_missing_value_

#ifndef _di_fake_print_error_parameter_too_many_
  void fake_print_error_parameter_too_many(const fake_data_t data, const f_string_t parameter) {
    if (data.error.verbosity == f_console_verbosity_quiet) return;

    fprintf(data.error.to.stream, "%c", f_string_eol[0]);

    fl_color_print(data.error.to.stream, data.context.set.error, "%sThe parameter '", fll_error_print_error);
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, parameter);

    fl_color_print(data.error.to.stream, data.context.set.error, "' specified too many times.%c", f_string_eol[0]);
  }
#endif // _di_fake_print_error_parameter_too_many_

#ifndef _di_fake_print_message_section_operation_failed_
  void fake_print_message_section_operation_failed(const fake_data_t data, const fll_error_print_t error, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name) {
    if (data.error.verbosity == f_console_verbosity_quiet || !error.to.stream) return;

    f_string_length_t line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(error.to.stream, "%c", f_string_eol[0]);
    fl_color_print(error.to.stream, data.error.context, "%sThe section operation '", data.error.prefix);

    fl_color_print_code(error.to.stream, data.context.notable);
    f_print_dynamic_partial(error.to.stream, buffer, operation_name);
    fl_color_print_code(error.to.stream, data.context.reset);

    fl_color_print(error.to.stream, data.error.context, "' from section '");

    fl_color_print_code(error.to.stream, data.context.notable);
    f_print_dynamic_partial(error.to.stream, buffer, section_name);
    fl_color_print_code(error.to.stream, data.context.reset);

    fl_color_print(error.to.stream, data.error.context, "' on line ");
    fl_color_print(error.to.stream, data.context.set.notable, "%llu", line);
    fl_color_print(error.to.stream, data.error.context, " failed.%c", f_string_eol[0]);
  }
#endif // _di_fake_print_message_section_operation_failed_

#ifndef _di_fake_print_message_section_operation_path_outside_
  void fake_print_message_section_operation_path_outside(const fake_data_t data, const fll_error_print_t error, const f_status_t status, const f_string_t function, const f_string_t path) {
    if (data.error.verbosity == f_console_verbosity_quiet || !error.to.stream) return;

    if (F_status_set_fine(status) == F_false) {
      fprintf(error.to.stream, "%c", f_string_eol[0]);
      fl_color_print(error.to.stream, data.error.context, "%sThe path '", data.error.prefix);
      fl_color_print(error.to.stream, data.context.set.notable, "%s", path);
      fl_color_print(error.to.stream, data.error.context, "' is outside the project root.%c", f_string_eol[0]);
    }
    else {
      fll_error_file_print(data.error, F_status_set_fine(status), function, F_true, path, "determine real path of", fll_error_file_type_file);
    }
  }
#endif // _di_fake_print_message_section_operation_path_outside_

#ifndef _di_fake_print_message_section_operation_path_stack_max_
  void fake_print_message_section_operation_path_stack_max(const fake_data_t data, fll_error_print_t error, const f_status_t status, const f_string_t function, const f_string_t path) {
    if (data.error.verbosity == f_console_verbosity_quiet || !error.to.stream) return;

    if (status == F_array_too_large) {
      fprintf(error.to.stream, "%c", f_string_eol[0]);
      fl_color_print(error.to.stream, data.error.context, "%s: Maximum stack size reached while processing path '", data.error.prefix);
      fl_color_print(error.to.stream, data.context.set.notable, "%s", path);
      fl_color_print(error.to.stream, data.error.context, "'");

      if (function) {
        fl_color_print(error.to.stream, data.error.context, " while calling ");
        fl_color_print(error.to.stream, data.context.set.notable, "%s", function);
        fl_color_print(error.to.stream, data.error.context, "()");
      }

      fl_color_print(error.to.stream, data.error.context, ".%c", f_string_eol[0]);
    }
    else {
      fll_error_file_print(error, status, function, F_true, path, "change path to", fll_error_file_type_directory);
    }
  }
#endif // _di_fake_print_message_section_operation_path_stack_max_

#ifndef _di_fake_print_message_section_operation_stack_max_
  void fake_print_message_section_operation_stack_max(const fake_data_t data, fll_error_print_t error, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name, const f_array_length_t stack_max) {
    if (data.error.verbosity == f_console_verbosity_quiet || !error.to.stream) return;

    f_string_length_t line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(error.to.stream, "%c", f_string_eol[0]);
    fl_color_print(error.to.stream, data.error.context, "The section operation '", data.error.prefix);

    fl_color_print_code(error.to.stream, data.context.notable);
    f_print_dynamic_partial(error.to.stream, buffer, operation_name);
    fl_color_print_code(error.to.stream, data.context.reset);

    fl_color_print(error.to.stream, data.error.context, "' from section '");

    fl_color_print_code(error.to.stream, data.context.notable);
    f_print_dynamic_partial(error.to.stream, buffer, section_name);
    fl_color_print_code(error.to.stream, data.context.reset);

    fl_color_print(error.to.stream, data.error.context, "' on line ");
    fl_color_print(error.to.stream, data.context.set.notable, "%llu", line);
    fl_color_print(error.to.stream, data.error.context, " cannot be processed because the max stack depth of ");
    fl_color_print(error.to.stream, data.context.set.notable, "%llu", stack_max);
    fl_color_print(error.to.stream, data.error.context, " has been reached.%c", f_string_eol[0]);
  }
#endif // _di_fake_print_message_section_operation_stack_max_

#ifndef _di_fake_print_message_section_operation_unknown_
  void fake_print_message_section_operation_unknown(const fake_data_t data, const fll_error_print_t error, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name) {
    if (data.error.verbosity == f_console_verbosity_quiet || !error.to.stream) return;

    f_string_length_t line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(error.to.stream, "%c", f_string_eol[0]);
    fl_color_print(error.to.stream, data.error.context, "%sThe section operation '", data.error.prefix);

    fl_color_print_code(error.to.stream, data.context.notable);
    f_print_dynamic_partial(error.to.stream, buffer, operation_name);
    fl_color_print_code(error.to.stream, data.context.reset);

    fl_color_print(error.to.stream, data.error.context, "' from section '");

    fl_color_print_code(error.to.stream, data.context.notable);
    f_print_dynamic_partial(error.to.stream, buffer, section_name);
    fl_color_print_code(error.to.stream, data.context.reset);

    fl_color_print(error.to.stream, data.error.context, "' on line ");
    fl_color_print(error.to.stream, data.context.set.notable, "%llu", line);
    fl_color_print(error.to.stream, data.error.context, " is not a known operation name.%c", f_string_eol[0]);
  }
#endif // _di_fake_print_message_section_operation_unknown_

#ifndef _di_fake_print_warning_settings_content_empty_
  void fake_print_warning_settings_content_empty(const fake_data_t data, const f_string_t path_file, const f_string_dynamic_t buffer, const f_string_range_t range_object, const f_string_t settings_name) {
    if (data.error.verbosity == f_console_verbosity_quiet) return;

    fprintf(data.error.to.stream, "%c", f_string_eol[0]);

    fl_color_print(f_type_warning, data.context.set.warning, "%sthe fakefile '", fll_error_print_warning);
    fl_color_print(f_type_warning, data.context.set.notable, "%s", path_file);
    fl_color_print(f_type_warning, data.context.set.warning, "' has empty content for the '");
    fl_color_print(f_type_warning, data.context.set.notable, "%s", settings_name);
    fl_color_print(f_type_warning, data.context.set.warning, "' object '");

    fl_color_print_code(f_type_warning, data.context.notable);
    f_print_dynamic_partial(f_type_warning, buffer, range_object);
    fl_color_print_code(f_type_warning, data.context.reset);

    fl_color_print(f_type_warning, data.context.set.warning, "'.%c", f_string_eol[0]);
  }
#endif // _di_fake_print_warning_settings_content_empty_

#ifndef _di_fake_print_warning_settings_content_invalid_
  void fake_print_warning_settings_content_invalid(const fake_data_t data, const f_string_t path_file, const f_string_dynamic_t buffer, const f_string_range_t range_object, const f_string_range_t range_content, const f_string_t settings_name) {
    if (data.error.verbosity == f_console_verbosity_quiet) return;

    fprintf(data.output.stream, "%c", f_string_eol[0]);

    fl_color_print(data.output.stream, data.context.set.warning, "%sthe fakefile '", fll_error_print_warning);
    fl_color_print(data.output.stream, data.context.set.notable, "%s", path_file);
    fl_color_print(data.output.stream, data.context.set.warning, "' has an invalid content '");

    fl_color_print_code(data.output.stream, data.context.notable);
    f_print_dynamic_partial(data.output.stream, buffer, range_content);
    fl_color_print_code(data.output.stream, data.context.reset);

    fl_color_print(data.output.stream, data.context.set.warning, "' for the '");
    fl_color_print(data.output.stream, data.context.set.notable, "%s", settings_name);
    fl_color_print(data.output.stream, data.context.set.warning, "' object '");

    fl_color_print_code(data.output.stream, data.context.notable);
    f_print_dynamic_partial(data.output.stream, buffer, range_object);
    fl_color_print_code(data.output.stream, data.context.reset);

    fl_color_print(data.output.stream, data.context.set.warning, "'.%c", f_string_eol[0]);
  }
#endif // _di_fake_print_warning_settings_content_invalid_

#ifndef _di_fake_print_warning_settings_content_multiple_
  void fake_print_warning_settings_content_multiple(const fake_data_t data, const f_string_t path_file, const f_string_t name_object) {
    if (data.error.verbosity != f_console_verbosity_verbose) return;

    fprintf(data.error.to.stream, "%c", f_string_eol[0]);

    fl_color_print(f_type_warning, data.context.set.warning, "%sthe setting '", fll_error_print_warning);
    fl_color_print(f_type_warning, data.context.set.notable, "%s", name_object);
    fl_color_print(f_type_warning, data.context.set.warning, "' in the file '");
    fl_color_print(f_type_warning, data.context.set.notable, "%s", path_file);

    fl_color_print(f_type_warning, data.context.set.warning, "' may only have a single property, only using the first.%c", f_string_eol[0]);
  }
#endif // _di_fake_print_warning_settings_content_multiple_

#ifndef _di_fake_print_warning_settings_object_multiple_
  void fake_print_warning_settings_object_multiple(const fake_data_t data, const f_string_t path_file, const f_string_t label, const f_string_t name_object) {
    if (data.error.verbosity != f_console_verbosity_verbose) return;

    fprintf(data.error.to.stream, "%c", f_string_eol[0]);

    fl_color_print(f_type_warning, data.context.set.warning, "%sthe %s object '", fll_error_print_warning, label);
    fl_color_print(f_type_warning, data.context.set.notable, "%s", name_object);
    fl_color_print(f_type_warning, data.context.set.warning, "' in the file '");
    fl_color_print(f_type_warning, data.context.set.notable, "%s", path_file);

    fl_color_print(f_type_warning, data.context.set.warning, "' may only be specified once, only using the first.%c", f_string_eol[0]);
  }
#endif // _di_fake_print_warning_settings_object_multiple_

#ifdef __cplusplus
} // extern "C"
#endif
