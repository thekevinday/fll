#include "fake.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_error_
  f_return_status fake_print_error(const fake_data_t data, const f_status_t status, const f_string_t function, const bool fallback) {
    const fake_make_print_t print = fake_macro_make_print_t_initialize(fake_make_print_error, data.context.set.error, f_type_error);

    return fake_print_message(data, status, function, fallback, print);
  }
#endif // _di_fake_print_error_

#ifndef _di_fake_print_error_build_operation_file_
  bool fake_print_error_build_operation_file(const fake_data_t data, const f_status_t status, const f_string_t function, const f_string_t operation, const f_string_t how, const f_string_t source, const f_string_t destination, const bool fallback) {

    if (status == F_file_found_not) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.set.error, "ERROR: Failed to find '");

        if (f_file_exists(source) == F_true) {
          fl_color_print(f_type_error, data.context.set.notable, "%s", destination);
        }
        else {
          fl_color_print(f_type_error, data.context.set.notable, "%s", source);
        }

        fl_color_print(f_type_error, data.context.set.error, "' while trying to %s '", operation);
        fl_color_print(f_type_error, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.set.error, "' %s '", how);
          fl_color_print(f_type_error, data.context.set.notable, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.set.error, "INTERNAL ERROR: Invalid parameter when calling ");
        fl_color_print(f_type_error, data.context.set.notable, "%s", function);
        fl_color_print(f_type_error, data.context.set.error, "() to %s '", operation);
        fl_color_print(f_type_error, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.set.error, "' %s '", how);
          fl_color_print(f_type_error, data.context.set.notable, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_name) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.set.error, "ERROR: Invalid name for '");
        fl_color_print(f_type_error, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.set.error, "' or '");
          fl_color_print(f_type_error, data.context.set.notable, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_memory_out) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.set.error, "CRITICAL ERROR: Unable to allocate memory, while trying to %s '", operation);
        fl_color_print(f_type_error, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.set.error, "' %s '", how);
          fl_color_print(f_type_error, data.context.set.notable, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (data.verbosity != fake_verbosity_quiet) {

        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.set.error, "ERROR: Overflow while trying to %s '", operation);
        fl_color_print(f_type_error, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.set.error, "' %s '", how);
          fl_color_print(f_type_error, data.context.set.notable, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_directory) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.set.error, "ERROR: Invalid directory while trying to %s '", operation);
        fl_color_print(f_type_error, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.set.error, "' %s '", how);
          fl_color_print(f_type_error, data.context.set.notable, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_access_denied) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.set.error, "ERROR: Access denied while trying to %s '", operation);
        fl_color_print(f_type_error, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.set.error, "' %s '", how);
          fl_color_print(f_type_error, data.context.set.notable, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_loop) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.set.error, "ERROR: Loop while trying to %s '", operation);
        fl_color_print(f_type_error, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.set.error, "' %s '", how);
          fl_color_print(f_type_error, data.context.set.notable, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.set.error, "ERROR: Prohibited by system while trying to %s '", operation);
        fl_color_print(f_type_error, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.set.error, "' %s '", how);
          fl_color_print(f_type_error, data.context.set.notable, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_directory_found_not) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.set.error, "ERROR: Failed to %s '", operation);
        fl_color_print(f_type_error, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.set.error, "' %s '", how);
          fl_color_print(f_type_error, data.context.set.notable, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.set.error, "' due to an invalid directory in the path.");
      }

      return F_false;
    }

    if (status == F_failure) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.set.error, "ERROR: Failed to %s '", operation);
        fl_color_print(f_type_error, data.context.set.notable, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.set.error, "' %s '", how);
          fl_color_print(f_type_error, data.context.set.notable, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.set.error, "'.");
      }

      return F_false;
    }

    if (fake_print_error(data, status, function, F_false) == F_unknown && fallback && data.verbosity != fake_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, data.context.set.error, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, data.context.set.notable, "%llu", status);
      fl_color_print(f_type_error, data.context.set.error, ") occurred while trying to %s '", operation);
      fl_color_print(f_type_error, data.context.set.notable, "%s", source);

      if (destination) {
        fl_color_print(f_type_error, data.context.set.error, "' %s '", how);
        fl_color_print(f_type_error, data.context.set.notable, "%s", destination);
      }

      fl_color_print_line(f_type_error, data.context.set.error, "'.");
    }

    return F_true;
  }
#endif // _di_fake_print_error_build_operation_file_

#ifndef _di_fake_print_error_file_
  bool fake_print_error_file(const fake_data_t data, const f_status_t status, const f_string_t function, const f_string_t name, const f_string_t operation, const bool is_file, const bool fallback) {
    const fake_make_print_t print = fake_macro_make_print_t_initialize(fake_make_print_error, data.context.set.error, f_type_error);

    return fake_print_message_file(data, status, function, name, operation, is_file, fallback, print);
  }
#endif // _di_fake_print_error_file_

#ifndef _di_fake_print_error_fss
  bool fake_print_error_fss(const fake_data_t data, const f_status_t status, const f_string_t function, const f_string_t path_file, const f_string_range_t range, const bool fallback) {

    if (status == F_file_found_not) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.set.error, "ENCODING ERROR: error occurred on invalid UTF-8 character at stop position (at ");
        fl_color_print(f_type_error, data.context.set.notable, "%d", range.start);
        fl_color_print(f_type_error, data.context.set.error, " of setting file '");
        fl_color_print(f_type_error, data.context.set.notable, "%s", path_file);
        fl_color_print_line(f_type_error, data.context.set.error, "').");
      }

      return F_false;
    }

    if (status == F_status_set_error(F_incomplete_utf_stop)) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.set.error, "ENCODING ERROR: error occurred on invalid UTF-8 character at end of string (at ");
        fl_color_print(f_type_error, data.context.set.notable, "%d", range.start);
        fl_color_print(f_type_error, data.context.set.error, " of setting file '");
        fl_color_print(f_type_error, data.context.set.notable, "%s", path_file);
        fl_color_print_line(f_type_error, data.context.set.error, "').");
      }

      return F_false;
    }

    if (fake_print_error(data, status, function, F_false) == F_unknown && fallback && data.verbosity != fake_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, data.context.set.error, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, data.context.set.notable, "%llu", status);
      fl_color_print(f_type_error, data.context.set.error, ") in function ");
      fl_color_print(f_type_error, data.context.set.notable, "%s", function);
      fl_color_print_line(f_type_error, data.context.set.error, "().");
    }

    return F_true;
  }
#endif // _di_fake_print_error_fss

#ifndef _di_fake_print_error_parameter_missing_value_
  void fake_print_error_parameter_missing_value(const fake_data_t data, const f_string_t parameter) {
    if (data.verbosity == fake_verbosity_quiet) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_error, data.context.set.error, "ERROR: The parameter '");
    fl_color_print(f_type_error, data.context.set.notable, "%s%s", f_console_symbol_long_enable, parameter);

    fl_color_print_line(f_type_error, data.context.set.error, "' was specified, but no value was given.");
  }
#endif // _di_fake_print_error_parameter_missing_value_

#ifndef _di_fake_print_error_parameter_too_many_
  void fake_print_error_parameter_too_many(const fake_data_t data, const f_string_t parameter) {
    if (data.verbosity == fake_verbosity_quiet) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_error, data.context.set.error, "ERROR: The parameter '");
    fl_color_print(f_type_error, data.context.set.notable, "%s%s", f_console_symbol_long_enable, parameter);

    fl_color_print_line(f_type_error, data.context.set.error, "' specified too many times.");
  }
#endif // _di_fake_print_error_parameter_too_many_

#ifndef _di_fake_print_message_
  f_return_status fake_print_message(const fake_data_t data, const f_status_t status, const f_string_t function, const bool fallback, const fake_make_print_t print) {

    if (status == F_parameter) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, "%s: Invalid parameter", print.prefix);

        if (function) {
          fl_color_print(print.to, print.context, " when calling function ");
          fl_color_print(print.to, data.context.set.notable, "%s", function);
          fl_color_print_line(print.to, print.context, "().");
        }
        else {
          fl_color_print_line(print.to, print.context, ".");
        }
      }

      return F_none;
    }

    if (status == F_memory_allocation || status == F_memory_reallocation) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, "%s: Unable to allocate memory", print.prefix);

        if (function) {
          fl_color_print(print.to, print.context, " in function ");
          fl_color_print(print.to, data.context.set.notable, "%s", function);
          fl_color_print_line(print.to, print.context, "().");
        }
        else {
          fl_color_print_line(print.to, print.context, ".");
        }
      }

      return F_none;
    }

    if (fallback && data.verbosity != fake_verbosity_quiet) {
      fprintf(print.to, "%c", f_string_eol[0]);
      fl_color_print(print.to, print.context, "UNKNOWN %s: (", print.prefix);
      fl_color_print(print.to, data.context.set.notable, "%llu", status);
      fl_color_print(print.to, print.context, ")");

        if (function) {
          fl_color_print(print.to, print.context, " in function ");
          fl_color_print(print.to, data.context.set.notable, "%s", function);
          fl_color_print_line(print.to, print.context, "().");
        }
        else {
          fl_color_print_line(print.to, print.context, ".");
        }
    }

    return F_unknown;
  }
#endif // _di_fake_print_message_

#ifndef _di_fake_print_message_file_
  bool fake_print_message_file(const fake_data_t data, const f_status_t status, const f_string_t function, const f_string_t name, const f_string_t operation, const bool is_file, const bool fallback, const fake_make_print_t print) {
    const f_string_t file_or_directory = is_file ? "file" : "directory";

    if (status == F_file_found_not) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, "%s: Failed to find %s '", print.prefix, file_or_directory);
        fl_color_print(print.to, data.context.set.notable, "%s", name);
        fl_color_print_line(print.to, print.context, "'.");
      }

      return F_false;
    }

    if (status == F_file_found) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, "%s: The %s '", print.prefix, file_or_directory);
        fl_color_print(print.to, data.context.set.notable, "%s", name);
        fl_color_print_line(print.to, print.context, "' already exists.");
      }

      return F_false;
    }

    if (status == F_directory_empty_not) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, "%s: The %s '", print.prefix, file_or_directory);
        fl_color_print(print.to, data.context.set.notable, "%s", name);
        fl_color_print_line(print.to, print.context, "' is not empty.");
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, "INTERNAL %s: Invalid parameter when calling ", print.prefix);
        fl_color_print(print.to, data.context.set.notable, "%s", function);
        fl_color_print(print.to, print.context, "() for the %s '", file_or_directory);
        fl_color_print(print.to, data.context.set.notable, "%s", name);
        fl_color_print_line(print.to, print.context, "'.");
      }

      return F_false;
    }

    if (status == F_name) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, "%s: Invalid %s name '", print.prefix, file_or_directory);
        fl_color_print(print.to, data.context.set.notable, "%s", name);
        fl_color_print_line(print.to, print.context, "'.");
      }

      return F_false;
    }

    if (status == F_memory_out) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, "CRITICAL %s: Unable to allocate memory, while trying to %s %s '", print.prefix, operation, file_or_directory);
        fl_color_print(print.to, data.context.set.notable, "%s", name);
        fl_color_print_line(print.to, print.context, "'.");
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, "%s: Overflow while trying to %s %s '", print.prefix, operation, file_or_directory);
        fl_color_print(print.to, data.context.set.notable, "%s", name);
        fl_color_print_line(print.to, print.context, "'.");
      }

      return F_false;
    }

    if (status == F_directory) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, "%s: Invalid directory while trying to %s %s '", print.prefix, operation, file_or_directory);
        fl_color_print(print.to, data.context.set.notable, "%s", name);
        fl_color_print_line(print.to, print.context, "'.");
      }

      return F_false;
    }

    if (status == F_access_denied) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, "%s: Access denied while trying to %s %s '", print.prefix, operation, file_or_directory);
        fl_color_print(print.to, data.context.set.notable, "%s", name);
        fl_color_print_line(print.to, print.context, "'.");
      }

      return F_false;
    }

    if (status == F_loop) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, "%s: Loop while trying to %s %s '", print.prefix, operation, file_or_directory);
        fl_color_print(print.to, data.context.set.notable, "%s", name);
        fl_color_print_line(print.to, print.context, "'.");
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, "%s: Prohibited by system while trying to %s %s '", print.prefix, operation, file_or_directory);
        fl_color_print(print.to, data.context.set.notable, "%s", name);
        fl_color_print_line(print.to, print.context, "'.");
      }

      return F_false;
    }

    if (status == F_access_owner) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, "%s: Currrent user is not allowed to use the given owner while trying to %s %s '", print.prefix, operation, file_or_directory);
        fl_color_print(print.to, data.context.set.notable, "%s", name);
        fl_color_print_line(print.to, print.context, "'.");
      }

      return F_false;
    }

    if (status == F_access_group) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, "%s: Currrent user is not allowed to use the given group while trying to %s %s '", print.prefix, operation, file_or_directory);
        fl_color_print(print.to, data.context.set.notable, "%s", name);
        fl_color_print_line(print.to, print.context, "'.");
      }

      return F_false;
    }

    if (is_file) {
      if (status == F_directory_found_not) {
        if (data.verbosity != fake_verbosity_quiet) {
          fprintf(print.to, "%c", f_string_eol[0]);
          fl_color_print(print.to, print.context, "%s: Failed to %s %s '", print.prefix, operation, file_or_directory);
          fl_color_print(print.to, data.context.set.notable, "%s", name);
          fl_color_print_line(print.to, print.context, "' due to an invalid directory in the path.");
        }

        return F_false;
      }
    }
    else {
      if (status == F_directory_found_not) {
        if (data.verbosity != fake_verbosity_quiet) {
          fprintf(print.to, "%c", f_string_eol[0]);
          fl_color_print(print.to, print.context, "%s: Failed to %s %s '", print.prefix, operation, file_or_directory);
          fl_color_print(print.to, data.context.set.notable, "%s", name);
          fl_color_print_line(print.to, print.context, "' due to an invalid directory in the path.");
        }

        return F_false;
      }

      if (status == F_failure) {
        if (data.verbosity != fake_verbosity_quiet) {
          fprintf(print.to, "%c", f_string_eol[0]);
          fl_color_print(print.to, print.context, "%s: Failed to %s %s '", print.prefix, operation, file_or_directory);
          fl_color_print(print.to, data.context.set.notable, "%s", name);
          fl_color_print_line(print.to, print.context, "'.");
        }

        return F_false;
      }
    }

    if (fake_print_error(data, status, function, F_false) == F_unknown && fallback && data.verbosity != fake_verbosity_quiet) {
      fprintf(print.to, "%c", f_string_eol[0]);
      fl_color_print(print.to, print.context, "UNKNOWN %s: (", print.prefix);
      fl_color_print(print.to, data.context.set.notable, "%llu", status);
      fl_color_print(print.to, print.context, ") occurred while trying to %s %s '", operation, file_or_directory);
      fl_color_print(print.to, data.context.set.notable, "%s", name);
      fl_color_print_line(print.to, print.context, "'.");
    }

    return F_true;
  }
#endif // _di_fake_print_message_file_

#ifndef _di_fake_print_message_section_operation_failed_
  void fake_print_message_section_operation_failed(const fake_data_t data, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name, const fake_make_print_t print) {
    if (data.verbosity == fake_verbosity_quiet || !print.to) return;

    f_string_length_t line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(print.to, "%c", f_string_eol[0]);
    fl_color_print(print.to, print.context, "%s: The section operation '", print.prefix);

    fl_color_print_code(print.to, data.context.notable);
    f_print_dynamic_partial(print.to, buffer, operation_name);
    fl_color_print_code(print.to, data.context.reset);

    fl_color_print(print.to, print.context, "' from section '");

    fl_color_print_code(print.to, data.context.notable);
    f_print_dynamic_partial(print.to, buffer, section_name);
    fl_color_print_code(print.to, data.context.reset);

    fl_color_print(print.to, print.context, "' on line ");
    fl_color_print(print.to, data.context.set.notable, "%llu", line);
    fl_color_print_line(print.to, print.context, " failed.");
  }
#endif // _di_fake_print_message_section_operation_failed_

#ifndef _di_fake_print_message_section_operation_path_outside_
  void fake_print_message_section_operation_path_outside(const fake_data_t data, const f_status_t status, const f_string_t function, const f_string_t path, const fake_make_print_t print) {
    if (data.verbosity == fake_verbosity_quiet || !print.to) return;

    if (F_status_set_fine(status) == F_false) {
      fprintf(print.to, "%c", f_string_eol[0]);
      fl_color_print(print.to, print.context, "%s: The path '", print.prefix);
      fl_color_print(print.to, data.context.set.notable, "%s", path);
      fl_color_print_line(print.to, print.context, "' is outside the project root.");
    }
    else {
      fake_print_error_file(data, status, function, path, "determine real path of", F_true, F_true);
    }
  }
#endif // _di_fake_print_message_section_operation_path_outside_

#ifndef _di_fake_print_message_section_operation_path_stack_max_
  void fake_print_message_section_operation_path_stack_max(const fake_data_t data, const f_status_t status, const f_string_t function, const f_string_t path, const fake_make_print_t print) {
    if (data.verbosity == fake_verbosity_quiet || !print.to) return;

    if (status == F_buffer_too_large) {
      fprintf(print.to, "%c", f_string_eol[0]);
      fl_color_print(print.to, print.context, "%s: Maximum stack size reached while processing path '", print.prefix);
      fl_color_print(print.to, data.context.set.notable, "%s", path);
      fl_color_print(print.to, print.context, "'");

      if (function) {
        fl_color_print(print.to, print.context, " while calling ");
        fl_color_print(print.to, data.context.set.notable, "%s", function);
        fl_color_print(print.to, print.context, "()");
      }

      fl_color_print_line(print.to, print.context, ".");
    }
    else {
      fake_print_message_file(data, status, function, path, "change path to", F_false, F_true, print);
    }
  }
#endif // _di_fake_print_message_section_operation_path_stack_max_

#ifndef _di_fake_print_message_section_operation_stack_max_
  void fake_print_message_section_operation_stack_max(const fake_data_t data, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name, const f_array_length_t stack_max, const fake_make_print_t print) {
    if (data.verbosity == fake_verbosity_quiet || !print.to) return;

    f_string_length_t line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(print.to, "%c", f_string_eol[0]);
    fl_color_print(print.to, print.context, "%s: The section operation '", print.prefix);

    fl_color_print_code(print.to, data.context.notable);
    f_print_dynamic_partial(print.to, buffer, operation_name);
    fl_color_print_code(print.to, data.context.reset);

    fl_color_print(print.to, print.context, "' from section '");

    fl_color_print_code(print.to, data.context.notable);
    f_print_dynamic_partial(print.to, buffer, section_name);
    fl_color_print_code(print.to, data.context.reset);

    fl_color_print(print.to, print.context, "' on line ");
    fl_color_print(print.to, data.context.set.notable, "%llu", line);
    fl_color_print(print.to, print.context, " cannot be processed because the max stack depth of ");
    fl_color_print(print.to, data.context.set.notable, "%llu", stack_max);
    fl_color_print_line(print.to, print.context, " has been reached.");
  }
#endif // _di_fake_print_message_section_operation_stack_max_

#ifndef _di_fake_print_message_section_operation_unknown_
  void fake_print_message_section_operation_unknown(const fake_data_t data, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name, const fake_make_print_t print) {
    if (data.verbosity == fake_verbosity_quiet || !print.to) return;

    f_string_length_t line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(print.to, "%c", f_string_eol[0]);
    fl_color_print(print.to, print.context, "%s: The section operation '", print.prefix);

    fl_color_print_code(print.to, data.context.notable);
    f_print_dynamic_partial(print.to, buffer, operation_name);
    fl_color_print_code(print.to, data.context.reset);

    fl_color_print(print.to, print.context, "' from section '");

    fl_color_print_code(print.to, data.context.notable);
    f_print_dynamic_partial(print.to, buffer, section_name);
    fl_color_print_code(print.to, data.context.reset);

    fl_color_print(print.to, print.context, "' on line ");
    fl_color_print(print.to, data.context.set.notable, "%llu", line);
    fl_color_print_line(print.to, print.context, " is not a known operation name.");
  }
#endif // _di_fake_print_message_section_operation_unknown_

#ifndef _di_fake_print_warning_settings_content_empty_
  void fake_print_warning_settings_content_empty(const fake_data_t data, const f_string_t path_file, const f_string_dynamic_t buffer, const f_string_range_t range_object, const f_string_t settings_name) {
    if (data.verbosity == fake_verbosity_quiet) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_warning, data.context.set.warning, "WARNING: the fakefile '");
    fl_color_print(f_type_warning, data.context.set.notable, "%s", path_file);
    fl_color_print(f_type_warning, data.context.set.warning, "' has empty content for the '");
    fl_color_print(f_type_warning, data.context.set.notable, "%s", settings_name);
    fl_color_print(f_type_warning, data.context.set.warning, "' object '");

    fl_color_print_code(f_type_warning, data.context.notable);
    f_print_dynamic_partial(f_type_warning, buffer, range_object);
    fl_color_print_code(f_type_warning, data.context.reset);

    fl_color_print_line(f_type_warning, data.context.set.warning, "'.");
  }
#endif // _di_fake_print_warning_settings_content_empty_

#ifndef _di_fake_print_warning_settings_content_invalid_
  void fake_print_warning_settings_content_invalid(const fake_data_t data, const f_string_t path_file, const f_string_dynamic_t buffer, const f_string_range_t range_object, const f_string_range_t range_content, const f_string_t settings_name) {
    if (data.verbosity == fake_verbosity_quiet) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_warning, data.context.set.warning, "WARNING: the fakefile '");
    fl_color_print(f_type_warning, data.context.set.notable, "%s", path_file);
    fl_color_print(f_type_warning, data.context.set.warning, "' has an invalid content '");

    fl_color_print_code(f_type_warning, data.context.notable);
    f_print_dynamic_partial(f_type_warning, buffer, range_content);
    fl_color_print_code(f_type_warning, data.context.reset);

    fl_color_print(f_type_warning, data.context.set.warning, "' for the '");
    fl_color_print(f_type_warning, data.context.set.notable, "%s", settings_name);
    fl_color_print(f_type_warning, data.context.set.warning, "' object '");

    fl_color_print_code(f_type_warning, data.context.notable);
    f_print_dynamic_partial(f_type_warning, buffer, range_object);
    fl_color_print_code(f_type_warning, data.context.reset);

    fl_color_print_line(f_type_warning, data.context.set.warning, "'.");
  }
#endif // _di_fake_print_warning_settings_content_invalid_

#ifndef _di_fake_print_warning_settings_content_multiple_
  void fake_print_warning_settings_content_multiple(const fake_data_t data, const f_string_t path_file, const f_string_t name_object) {
    if (data.verbosity != fake_verbosity_verbose) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_warning, data.context.set.warning, "WARNING: the setting '");
    fl_color_print(f_type_warning, data.context.set.notable, "%s", name_object);
    fl_color_print(f_type_warning, data.context.set.warning, "' in the file '");
    fl_color_print(f_type_warning, data.context.set.notable, "%s", path_file);

    fl_color_print_line(f_type_warning, data.context.set.warning, "' may only have a single property, only using the first.");
  }
#endif // _di_fake_print_warning_settings_content_multiple_

#ifndef _di_fake_print_warning_settings_object_multiple_
  void fake_print_warning_settings_object_multiple(const fake_data_t data, const f_string_t path_file, const f_string_t label, const f_string_t name_object) {
    if (data.verbosity != fake_verbosity_verbose) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_warning, data.context.set.warning, "WARNING: the %s object '", label);
    fl_color_print(f_type_warning, data.context.set.notable, "%s", name_object);
    fl_color_print(f_type_warning, data.context.set.warning, "' in the file '");
    fl_color_print(f_type_warning, data.context.set.notable, "%s", path_file);

    fl_color_print_line(f_type_warning, data.context.set.warning, "' may only be specified once, only using the first.");
  }
#endif // _di_fake_print_warning_settings_object_multiple_

#ifdef __cplusplus
} // extern "C"
#endif
