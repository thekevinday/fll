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
  f_return_status fake_print_error(const fake_data data, const f_status status, const f_string function, const bool fallback) {
    const fake_make_print print = fake_macro_make_print_initialize(fake_make_print_error, data.context.error, f_type_error);

    return fake_print_message(data, status, function, fallback, print);
  }
#endif // _di_fake_print_error_

#ifndef _di_fake_print_error_build_operation_file_
  bool fake_print_error_build_operation_file(const fake_data data, const f_status status, const f_string function, const f_string operation, const f_string how, const f_string source, const f_string destination, const bool fallback) {

    if (status == F_file_found_not) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Failed to find '");

        if (f_file_exists(source) == F_true) {
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", destination);
        }
        else {
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", source);
        }

        fl_color_print(f_type_error, data.context.error, data.context.reset, "' while trying to %s '", operation);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.error, data.context.reset, "' %s '", how);
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "INTERNAL ERROR: Invalid parameter when calling ");
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", function);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "() to %s '", operation);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.error, data.context.reset, "' %s '", how);
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_name) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Invalid name for '");
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.error, data.context.reset, "' or '");
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_memory_out) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "CRITICAL ERROR: Unable to allocate memory, while trying to %s '", operation);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.error, data.context.reset, "' %s '", how);
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (data.verbosity != fake_verbosity_quiet) {

        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Overflow while trying to %s '", operation);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.error, data.context.reset, "' %s '", how);
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_directory) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Invalid directory while trying to %s '", operation);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.error, data.context.reset, "' %s '", how);
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_access_denied) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Access denied while trying to %s '", operation);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.error, data.context.reset, "' %s '", how);
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_loop) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Loop while trying to %s '", operation);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.error, data.context.reset, "' %s '", how);
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Prohibited by system while trying to %s '", operation);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.error, data.context.reset, "' %s '", how);
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_directory_found_not) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Failed to %s '", operation);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.error, data.context.reset, "' %s '", how);
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' due to an invalid directory in the path.");
      }

      return F_false;
    }

    if (status == F_failure) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Failed to %s '", operation);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, data.context.error, data.context.reset, "' %s '", how);
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (fake_print_error(data, status, function, F_false) == F_unknown && fallback && data.verbosity != fake_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, data.context.error, data.context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, data.context.notable, data.context.reset, "%llu", status);
      fl_color_print(f_type_error, data.context.error, data.context.reset, ") occurred while trying to %s '", operation);
      fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", source);

      if (destination) {
        fl_color_print(f_type_error, data.context.error, data.context.reset, "' %s '", how);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", destination);
      }

      fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
    }

    return F_true;
  }
#endif // _di_fake_print_error_build_operation_file_

#ifndef _di_fake_print_error_file_
  bool fake_print_error_file(const fake_data data, const f_status status, const f_string function, const f_string name, const f_string operation, const bool is_file, const bool fallback) {
    const fake_make_print print = fake_macro_make_print_initialize(fake_make_print_error, data.context.error, f_type_error);

    return fake_print_message_file(data, status, function, name, operation, is_file, fallback, print);
  }
#endif // _di_fake_print_error_file_

#ifndef _di_fake_print_error_fss
  bool fake_print_error_fss(const fake_data data, const f_status status, const f_string function, const f_string path_file, const f_string_range range, const bool fallback) {

    if (status == F_file_found_not) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ENCODING ERROR: error occurred on invalid UTF-8 character at stop position (at ");
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%d", range.start);
        fl_color_print(f_type_error, data.context.error, data.context.reset, " of setting file '");
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", path_file);
        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "').");
      }

      return F_false;
    }

    if (status == F_status_set_error(F_incomplete_utf_stop)) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ENCODING ERROR: error occurred on invalid UTF-8 character at end of string (at ");
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%d", range.start);
        fl_color_print(f_type_error, data.context.error, data.context.reset, " of setting file '");
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", path_file);
        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "').");
      }

      return F_false;
    }

    if (fake_print_error(data, status, function, F_false) == F_unknown && fallback && data.verbosity != fake_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, data.context.error, data.context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, data.context.notable, data.context.reset, "%llu", status);
      fl_color_print(f_type_error, data.context.error, data.context.reset, ") in function ");
      fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", function);
      fl_color_print_line(f_type_error, data.context.error, data.context.reset, "().");
    }

    return F_true;
  }
#endif // _di_fake_print_error_fss

#ifndef _di_fake_print_error_parameter_missing_value_
  void fake_print_error_parameter_missing_value(const fake_data data, const f_string parameter) {
    if (data.verbosity == fake_verbosity_quiet) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: The parameter '");
    fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s%s", f_console_symbol_long_enable, parameter);

    fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' was specified, but no value was given.");
  }
#endif // _di_fake_print_error_parameter_missing_value_

#ifndef _di_fake_print_error_parameter_too_many_
  void fake_print_error_parameter_too_many(const fake_data data, const f_string parameter) {
    if (data.verbosity == fake_verbosity_quiet) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: The parameter '");
    fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s%s", f_console_symbol_long_enable, parameter);

    fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' specified too many times.");
  }
#endif // _di_fake_print_error_parameter_too_many_

#ifndef _di_fake_print_message_
  f_return_status fake_print_message(const fake_data data, const f_status status, const f_string function, const bool fallback, const fake_make_print print) {

    if (status == F_parameter) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, data.context.reset, "%s: Invalid parameter", print.prefix);

        if (function) {
          fl_color_print(print.to, print.context, data.context.reset, " when calling function ");
          fl_color_print(print.to, data.context.notable, data.context.reset, "%s", function);
          fl_color_print_line(print.to, print.context, data.context.reset, "().");
        }
        else {
          fl_color_print_line(print.to, print.context, data.context.reset, ".");
        }
      }

      return F_none;
    }

    if (status == F_memory_allocation || status == F_memory_reallocation) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, data.context.reset, "%s: Unable to allocate memory", print.prefix);

        if (function) {
          fl_color_print(print.to, print.context, data.context.reset, " in function ");
          fl_color_print(print.to, data.context.notable, data.context.reset, "%s", function);
          fl_color_print_line(print.to, print.context, data.context.reset, "().");
        }
        else {
          fl_color_print_line(print.to, print.context, data.context.reset, ".");
        }
      }

      return F_none;
    }

    if (fallback && data.verbosity != fake_verbosity_quiet) {
      fprintf(print.to, "%c", f_string_eol[0]);
      fl_color_print(print.to, print.context, data.context.reset, "UNKNOWN %s: (", print.prefix);
      fl_color_print(print.to, data.context.notable, data.context.reset, "%llu", status);
      fl_color_print(print.to, print.context, data.context.reset, ")");

        if (function) {
          fl_color_print(print.to, print.context, data.context.reset, " in function ");
          fl_color_print(print.to, data.context.notable, data.context.reset, "%s", function);
          fl_color_print_line(print.to, print.context, data.context.reset, "().");
        }
        else {
          fl_color_print_line(print.to, print.context, data.context.reset, ".");
        }
    }

    return F_unknown;
  }
#endif // _di_fake_print_message_

#ifndef _di_fake_print_message_file_
  bool fake_print_message_file(const fake_data data, const f_status status, const f_string function, const f_string name, const f_string operation, const bool is_file, const bool fallback, const fake_make_print print) {
    const f_string file_or_directory = is_file ? "file" : "directory";

    if (status == F_file_found_not) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, data.context.reset, "%s: Failed to find %s '", print.prefix, file_or_directory);
        fl_color_print(print.to, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(print.to, print.context, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_file_found) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, data.context.reset, "%s: The %s '", print.prefix, file_or_directory);
        fl_color_print(print.to, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(print.to, print.context, data.context.reset, "' already exists.");
      }

      return F_false;
    }

    if (status == F_directory_empty_not) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, data.context.reset, "%s: The %s '", print.prefix, file_or_directory);
        fl_color_print(print.to, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(print.to, print.context, data.context.reset, "' is not empty.");
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, data.context.reset, "INTERNAL %s: Invalid parameter when calling ", print.prefix);
        fl_color_print(print.to, data.context.notable, data.context.reset, "%s", function);
        fl_color_print(print.to, print.context, data.context.reset, "() for the %s '", file_or_directory);
        fl_color_print(print.to, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(print.to, print.context, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_name) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, data.context.reset, "%s: Invalid %s name '", print.prefix, file_or_directory);
        fl_color_print(print.to, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(print.to, print.context, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_memory_out) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, data.context.reset, "CRITICAL %s: Unable to allocate memory, while trying to %s %s '", print.prefix, operation, file_or_directory);
        fl_color_print(print.to, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(print.to, print.context, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, data.context.reset, "%s: Overflow while trying to %s %s '", print.prefix, operation, file_or_directory);
        fl_color_print(print.to, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(print.to, print.context, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_directory) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, data.context.reset, "%s: Invalid directory while trying to %s %s '", print.prefix, operation, file_or_directory);
        fl_color_print(print.to, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(print.to, print.context, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_access_denied) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, data.context.reset, "%s: Access denied while trying to %s %s '", print.prefix, operation, file_or_directory);
        fl_color_print(print.to, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(print.to, print.context, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_loop) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, data.context.reset, "%s: Loop while trying to %s %s '", print.prefix, operation, file_or_directory);
        fl_color_print(print.to, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(print.to, print.context, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, data.context.reset, "%s: Prohibited by system while trying to %s %s '", print.prefix, operation, file_or_directory);
        fl_color_print(print.to, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(print.to, print.context, data.context.reset, "'.");
      }

      return F_false;
    }

    if (is_file) {
      if (status == F_directory_found_not) {
        if (data.verbosity != fake_verbosity_quiet) {
          fprintf(print.to, "%c", f_string_eol[0]);
          fl_color_print(print.to, print.context, data.context.reset, "%s: Failed to %s %s '", print.prefix, operation, file_or_directory);
          fl_color_print(print.to, data.context.notable, data.context.reset, "%s", name);
          fl_color_print_line(print.to, print.context, data.context.reset, "' due to an invalid directory in the path.");
        }

        return F_false;
      }
    }
    else {
      if (status == F_directory_found_not) {
        if (data.verbosity != fake_verbosity_quiet) {
          fprintf(print.to, "%c", f_string_eol[0]);
          fl_color_print(print.to, print.context, data.context.reset, "%s: Failed to %s %s '", print.prefix, operation, file_or_directory);
          fl_color_print(print.to, data.context.notable, data.context.reset, "%s", name);
          fl_color_print_line(print.to, print.context, data.context.reset, "' due to an invalid directory in the path.");
        }

        return F_false;
      }

      if (status == F_failure) {
        if (data.verbosity != fake_verbosity_quiet) {
          fprintf(print.to, "%c", f_string_eol[0]);
          fl_color_print(print.to, print.context, data.context.reset, "%s: Failed to %s %s '", print.prefix, operation, file_or_directory);
          fl_color_print(print.to, data.context.notable, data.context.reset, "%s", name);
          fl_color_print_line(print.to, print.context, data.context.reset, "'.");
        }

        return F_false;
      }
    }

    if (fake_print_error(data, status, function, F_false) == F_unknown && fallback && data.verbosity != fake_verbosity_quiet) {
      fprintf(print.to, "%c", f_string_eol[0]);
      fl_color_print(print.to, print.context, data.context.reset, "UNKNOWN %s: (", print.prefix);
      fl_color_print(print.to, data.context.notable, data.context.reset, "%llu", status);
      fl_color_print(print.to, print.context, data.context.reset, ") occurred while trying to %s %s '", operation, file_or_directory);
      fl_color_print(print.to, data.context.notable, data.context.reset, "%s", name);
      fl_color_print_line(print.to, print.context, data.context.reset, "'.");
    }

    return F_true;
  }
#endif // _di_fake_print_message_file_

#ifndef _di_fake_print_message_section_operation_failed_
  void fake_print_message_section_operation_failed(const fake_data data, const f_string_static buffer, const f_string_range section_name, const f_string_range operation_name, const fake_make_print print) {
    if (data.verbosity == fake_verbosity_quiet || !print.to) return;

    f_string_length line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(print.to, "%c", f_string_eol[0]);
    fl_color_print(print.to, print.context, data.context.reset, "%s The section operation '", print.prefix);

    fl_color_print_code(print.to, data.context.notable);
    f_print_string_dynamic_partial(print.to, buffer, operation_name);
    fl_color_print_code(print.to, data.context.reset);

    fl_color_print(print.to, print.context, data.context.reset, "' from section '");

    fl_color_print_code(print.to, data.context.notable);
    f_print_string_dynamic_partial(print.to, buffer, section_name);
    fl_color_print_code(print.to, data.context.reset);

    fl_color_print(print.to, print.context, data.context.reset, "' on line ");
    fl_color_print(print.to, data.context.notable, data.context.reset, "%llu", line);
    fl_color_print_line(print.to, print.context, data.context.reset, " failed.");
  }
#endif // _di_fake_print_message_section_operation_failed_

#ifndef _di_fake_print_message_section_operation_path_outside_
  void fake_print_message_section_operation_path_outside(const fake_data data, const f_status status, const f_string function, const f_string path, const fake_make_print print) {
    if (data.verbosity == fake_verbosity_quiet || !print.to) return;

    if (F_status_set_fine(status) == F_false) {
      fprintf(print.to, "%c", f_string_eol[0]);
      fl_color_print(print.to, print.context, data.context.reset, "%s: The path '", print.prefix);
      fl_color_print(print.to, data.context.notable, data.context.reset, "%s", path);
      fl_color_print_line(print.to, print.context, data.context.reset, "' is outside the project root.");
    }
    else {
      fake_print_error_file(data, status, function, path, "determine real path of", F_true, F_true);
    }
  }
#endif // _di_fake_print_message_section_operation_path_outside_

#ifndef _di_fake_print_message_section_operation_path_stack_max_
  void fake_print_message_section_operation_path_stack_max(const fake_data data, const f_status status, const f_string function, const f_string string, const fake_make_print print) {
    if (data.verbosity == fake_verbosity_quiet || !print.to) return;

    if (status == F_buffer_too_large) {
      fprintf(print.to, "%c", f_string_eol[0]);
      fl_color_print(print.to, print.context, data.context.reset, "%s: Maximum size reached for %s array", print.prefix, string);

      if (function) {
        fl_color_print(print.to, print.context, data.context.reset, " while calling ");
        fl_color_print(print.to, data.context.notable, data.context.reset, "%s", function);
        fl_color_print(print.to, print.context, data.context.reset, "()");
      }

      fl_color_print_line(print.to, print.context, data.context.reset, ".");
    }
    else {
      fake_print_error(data, status, function, F_true);
    }
  }
#endif // _di_fake_print_message_section_operation_path_stack_max_

#ifndef _di_fake_print_message_section_operation_stack_max_
  void fake_print_message_section_operation_stack_max(const fake_data data, const f_string_static buffer, const f_string_range section_name, const f_string_range operation_name, const f_array_length stack_max, const fake_make_print print) {
    if (data.verbosity == fake_verbosity_quiet || !print.to) return;

    f_string_length line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(print.to, "%c", f_string_eol[0]);
    fl_color_print(print.to, print.context, data.context.reset, "%s: The section operation '", print.prefix);

    fl_color_print_code(print.to, data.context.notable);
    f_print_string_dynamic_partial(print.to, buffer, operation_name);
    fl_color_print_code(print.to, data.context.reset);

    fl_color_print(print.to, print.context, data.context.reset, "' from section '");

    fl_color_print_code(print.to, data.context.notable);
    f_print_string_dynamic_partial(print.to, buffer, section_name);
    fl_color_print_code(print.to, data.context.reset);

    fl_color_print(print.to, print.context, data.context.reset, "' on line ");
    fl_color_print(print.to, data.context.notable, data.context.reset, "%llu", line);
    fl_color_print(print.to, print.context, data.context.reset, " cannot be processed because the max stack depth of ");
    fl_color_print(print.to, data.context.notable, data.context.reset, "%llu", stack_max);
    fl_color_print_line(print.to, print.context, data.context.reset, " has been reached.");
  }
#endif // _di_fake_print_message_section_operation_stack_max_

#ifndef _di_fake_print_message_section_operation_unknown_
  void fake_print_message_section_operation_unknown(const fake_data data, const f_string_static buffer, const f_string_range section_name, const f_string_range operation_name, const fake_make_print print) {
    if (data.verbosity == fake_verbosity_quiet || !print.to) return;

    f_string_length line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(print.to, "%c", f_string_eol[0]);
    fl_color_print(print.to, print.context, data.context.reset, "%s: The section operation '", print.prefix);

    fl_color_print_code(print.to, data.context.notable);
    f_print_string_dynamic_partial(print.to, buffer, operation_name);
    fl_color_print_code(print.to, data.context.reset);

    fl_color_print(print.to, print.context, data.context.reset, "' from section '");

    fl_color_print_code(print.to, data.context.notable);
    f_print_string_dynamic_partial(print.to, buffer, section_name);
    fl_color_print_code(print.to, data.context.reset);

    fl_color_print(print.to, print.context, data.context.reset, "' on line ");
    fl_color_print(print.to, data.context.notable, data.context.reset, "%llu", line);
    fl_color_print_line(print.to, print.context, data.context.reset, " is not a known operation name.");
  }
#endif // _di_fake_print_message_section_operation_unknown_

#ifndef _di_fake_print_warning_settings_content_empty_
  void fake_print_warning_settings_content_empty(const fake_data data, const f_string path_file, const f_string_dynamic buffer, const f_string_range range_object, const f_string settings_name) {
    if (data.verbosity == fake_verbosity_quiet) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_warning, data.context.warning, data.context.reset, "WARNING: the fakefile '");
    fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", path_file);
    fl_color_print(f_type_warning, data.context.warning, data.context.reset, "' has empty content for the '");
    fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", settings_name);
    fl_color_print(f_type_warning, data.context.warning, data.context.reset, "' object '");

    fl_color_print_code(f_type_warning, data.context.notable);
    f_print_string_dynamic_partial(f_type_warning, buffer, range_object);
    fl_color_print_code(f_type_warning, data.context.reset);

    fl_color_print_line(f_type_warning, data.context.warning, data.context.reset, "'.");
  }
#endif // _di_fake_print_warning_settings_content_empty_

#ifndef _di_fake_print_warning_settings_content_invalid_
  void fake_print_warning_settings_content_invalid(const fake_data data, const f_string path_file, const f_string_dynamic buffer, const f_string_range range_object, const f_string_range range_content, const f_string settings_name) {
    if (data.verbosity == fake_verbosity_quiet) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_warning, data.context.warning, data.context.reset, "WARNING: the fakefile '");
    fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", path_file);
    fl_color_print(f_type_warning, data.context.warning, data.context.reset, "' has an invalid content '");

    fl_color_print_code(f_type_warning, data.context.notable);
    f_print_string_dynamic_partial(f_type_warning, buffer, range_content);
    fl_color_print_code(f_type_warning, data.context.reset);

    fl_color_print(f_type_warning, data.context.warning, data.context.reset, "' for the '");
    fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", settings_name);
    fl_color_print(f_type_warning, data.context.warning, data.context.reset, "' object '");

    fl_color_print_code(f_type_warning, data.context.notable);
    f_print_string_dynamic_partial(f_type_warning, buffer, range_object);
    fl_color_print_code(f_type_warning, data.context.reset);

    fl_color_print_line(f_type_warning, data.context.warning, data.context.reset, "'.");
  }
#endif // _di_fake_print_warning_settings_content_invalid_

#ifndef _di_fake_print_warning_settings_content_multiple_
  void fake_print_warning_settings_content_multiple(const fake_data data, const f_string path_file, const f_string name_object) {
    if (data.verbosity != fake_verbosity_verbose) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_warning, data.context.warning, data.context.reset, "WARNING: the setting '");
    fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", name_object);
    fl_color_print(f_type_warning, data.context.warning, data.context.reset, "' in the file '");
    fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", path_file);

    fl_color_print_line(f_type_warning, data.context.warning, data.context.reset, "' may only have a single property, only using the first.");
  }
#endif // _di_fake_print_warning_settings_content_multiple_

#ifndef _di_fake_print_warning_settings_object_multiple_
  void fake_print_warning_settings_object_multiple(const fake_data data, const f_string path_file, const f_string label, const f_string name_object) {
    if (data.verbosity != fake_verbosity_verbose) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_warning, data.context.warning, data.context.reset, "WARNING: the %s object '", label);
    fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", name_object);
    fl_color_print(f_type_warning, data.context.warning, data.context.reset, "' in the file '");
    fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", path_file);

    fl_color_print_line(f_type_warning, data.context.warning, data.context.reset, "' may only be specified once, only using the first.");
  }
#endif // _di_fake_print_warning_settings_object_multiple_

#ifdef __cplusplus
} // extern "C"
#endif
