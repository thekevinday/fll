#include <level_3/fake.h>
#include "private-fake.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_error_
  f_return_status fake_print_error(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const bool fallback) {

    if (status == F_parameter) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Invalid parameter when calling function ");
        fl_color_print(f_type_error, context.notable, context.reset, "%s", function);
        fl_color_print_line(f_type_error, context.error, context.reset, "().");
      }

      return F_none;
    }

    if (status == F_memory_allocation || status == F_memory_reallocation) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Unable to allocate memory in function ");
        fl_color_print(f_type_error, context.notable, context.reset, "%s", function);
        fl_color_print_line(f_type_error, context.error, context.reset, "().");
      }

      return F_none;
    }

    if (fallback && verbosity != fake_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, context.error, context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, context.notable, context.reset, "%llu", status);
      fl_color_print(f_type_error, context.error, context.reset, ") in function ");
      fl_color_print(f_type_error, context.notable, context.reset, "%s", function);
      fl_color_print_line(f_type_error, context.error, context.reset, "().");
    }

    return F_unknown;
  }
#endif // _di_fake_print_error_

#ifndef _di_fake_print_error_fakefile_section_
  bool fake_print_error_fakefile_section(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const f_string_static buffer, const f_string_range section_name, const bool fallback) {

    if (fake_print_error(context, verbosity, status, function, F_false) == F_unknown && fallback && verbosity != fake_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, context.error, context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, context.notable, context.reset, "%llu", status);
      fl_color_print(f_type_error, context.error, context.reset, ") occurred while calling ");
      fl_color_print(f_type_error, context.notable, context.reset, "%s", function);
      fl_color_print(f_type_error, context.error, context.reset, "() for section '");

      fl_color_print_code(f_type_error, context.notable);
      f_print_string_dynamic_partial(f_type_error, buffer, section_name);
      fl_color_print_code(f_type_error, context.reset);

      fl_color_print_line(f_type_error, context.error, context.reset, "'.");
    }

    return F_true;
  }
#endif // _di_fake_print_error_fakefile_section_

#ifndef _di_fake_print_error_fakefile_section_line_
  bool fake_print_error_fakefile_section_line(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const f_string_static buffer, const f_string_range section_name, const f_string_range operation_name, const bool fallback) {

    f_string_length line = 0;

    f_fss_count_lines(buffer, operation_name.start, &line);

    if (fake_print_error(context, verbosity, status, function, F_false) == F_unknown && fallback && verbosity != fake_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, context.error, context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, context.notable, context.reset, "%llu", status);
      fl_color_print(f_type_error, context.error, context.reset, ") occurred while calling ");
      fl_color_print(f_type_error, context.notable, context.reset, "%s", function);
      fl_color_print(f_type_error, context.error, context.reset, "() for section '");

      fl_color_print_code(f_type_error, context.notable);
      f_print_string_dynamic_partial(f_type_error, buffer, section_name);
      fl_color_print_code(f_type_error, context.reset);

      fl_color_print(f_type_error, context.error, context.reset, " on line ");
      fl_color_print(f_type_error, context.notable, context.reset, "%llu", line);
      fl_color_print(f_type_error, context.error, context.reset, ", operation '");

      fl_color_print_code(f_type_error, context.notable);
      f_print_string_dynamic_partial(f_type_error, buffer, operation_name);
      fl_color_print_code(f_type_error, context.reset);

      fl_color_print_line(f_type_error, context.error, context.reset, "'.");
    }

    return F_true;
  }
#endif // _di_fake_print_error_fakefile_section_line_

#ifndef _di_fake_print_error_fakefile_section_operation_stack_max_
  void fake_print_error_fakefile_section_operation_stack_max(const fl_color_context context, const uint8_t verbosity, const f_string_static buffer, const f_string_range section_name, const f_string_range operation_name, const f_array_length stack_max) {
    if (verbosity == fake_verbosity_quiet) return;

    f_string_length line = 0;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(f_type_error, "%c", f_string_eol[0]);
    fl_color_print(f_type_error, context.error, context.reset, "ERROR: The section operation '");

    fl_color_print_code(f_type_error, context.notable);
    f_print_string_dynamic_partial(f_type_error, buffer, operation_name);
    fl_color_print_code(f_type_error, context.reset);

    fl_color_print(f_type_error, context.error, context.reset, "' from section '");

    fl_color_print_code(f_type_error, context.notable);
    f_print_string_dynamic_partial(f_type_error, buffer, section_name);
    fl_color_print_code(f_type_error, context.reset);

    fl_color_print(f_type_error, context.error, context.reset, "' on line ");
    fl_color_print(f_type_error, context.notable, context.reset, "%llu", line);
    fl_color_print(f_type_error, context.error, context.reset, " cannot be processed because the max stack depth of ");
    fl_color_print(f_type_error, context.notable, context.reset, "%llu", stack_max);
    fl_color_print_line(f_type_error, context.error, context.reset, " has been reached.");
  }
#endif // _di_fake_print_error_fakefile_section_operation_stack_max_

#ifndef _di_fake_print_error_fakefile_section_operation_unknown_
  void fake_print_error_fakefile_section_operation_unknown(const fl_color_context context, const uint8_t verbosity, const f_string_static buffer, const f_string_range section_name, const f_string_range operation_name) {
    if (verbosity == fake_verbosity_quiet) return;

    f_string_length line = 0;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(f_type_error, "%c", f_string_eol[0]);
    fl_color_print(f_type_error, context.error, context.reset, "ERROR: The section operation '");

    fl_color_print_code(f_type_error, context.notable);
    f_print_string_dynamic_partial(f_type_error, buffer, operation_name);
    fl_color_print_code(f_type_error, context.reset);

    fl_color_print(f_type_error, context.error, context.reset, "' from section '");

    fl_color_print_code(f_type_error, context.notable);
    f_print_string_dynamic_partial(f_type_error, buffer, section_name);
    fl_color_print_code(f_type_error, context.reset);

    fl_color_print(f_type_error, context.error, context.reset, "' on line ");
    fl_color_print(f_type_error, context.notable, context.reset, "%llu", line);
    fl_color_print_line(f_type_error, context.error, context.reset, " is not a known operation name.");
  }
#endif // _di_fake_print_error_fakefile_section_operation_unknown_

#ifndef _di_fake_print_error_fakefile_settings_content_invalid_
  void fake_print_error_fakefile_settings_content_invalid(const fl_color_context context, const uint8_t verbosity, const f_string path_file, const f_string_dynamic buffer, const f_string_range range_object, const f_string_range range_content, const f_string settings_name) {
    if (verbosity != fake_verbosity_verbose) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_warning, context.warning, context.reset, "WARNING: the fakefile '");
    fl_color_print(f_type_warning, context.notable, context.reset, "%s", path_file);
    fl_color_print(f_type_warning, context.warning, context.reset, "' has an invalid content '");

    fl_color_print_code(f_type_warning, context.notable);
    f_print_string_dynamic_partial(f_type_warning, buffer, range_content);
    fl_color_print_code(f_type_warning, context.reset);

    fl_color_print(f_type_warning, context.warning, context.reset, "' for the '");
    fl_color_print(f_type_warning, context.notable, context.reset, "%s", settings_name);
    fl_color_print(f_type_warning, context.warning, context.reset, "' object '");

    fl_color_print_code(f_type_warning, context.notable);
    f_print_string_dynamic_partial(f_type_warning, buffer, range_object);
    fl_color_print_code(f_type_warning, context.reset);

    fl_color_print_line(f_type_warning, context.warning, context.reset, "'.");
  }
#endif // _di_fake_print_error_fakefile_settings_content_invalid_

#ifndef _di_fake_print_error_file_
  bool fake_print_error_file(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const f_string name, const f_string operation, const bool is_file, const bool fallback) {
    const f_string file_or_directory = is_file ? "file" : "directory";

    if (status == F_file_found_not) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: failed to find %s '", file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_file_found) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: the %s '", file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "' already exists.");
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "INTERNAL ERROR: Invalid parameter when calling ");
        fl_color_print(f_type_error, context.notable, context.reset, "%s", function);
        fl_color_print(f_type_error, context.error, context.reset, "() for the %s '", file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_name) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Invalid %s name '", file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_memory_out) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "CRITICAL ERROR: Unable to allocate memory, while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Overflow while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_directory) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Invalid directory while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_access_denied) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Access denied while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_loop) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Loop while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Prohibited by system while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (is_file) {
      if (status == F_directory_found_not) {
        if (verbosity != fake_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, context.error, context.reset, "ERROR: failed to %s %s '", operation, file_or_directory);
          fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
          fl_color_print_line(f_type_error, context.error, context.reset, "' due to an invalid directory in the path.");
        }

        return F_false;
      }
    }
    else {
      if (status == F_directory_found_not) {
        if (verbosity != fake_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, context.error, context.reset, "ERROR: failed to %s %s '", operation, file_or_directory);
          fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
          fl_color_print_line(f_type_error, context.error, context.reset, "' due to an invalid directory in the path.");
        }

        return F_false;
      }

      if (status == F_failure) {
        if (verbosity != fake_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, context.error, context.reset, "ERROR: failed to %s %s '", operation, file_or_directory);
          fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
          fl_color_print_line(f_type_error, context.error, context.reset, "'.");
        }

        return F_false;
      }
    }

    if (fake_print_error(context, verbosity, status, function, F_false) == F_unknown && fallback && verbosity != fake_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, context.error, context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, context.notable, context.reset, "%llu", status);
      fl_color_print(f_type_error, context.error, context.reset, ") occurred while trying to %s %s '", operation, file_or_directory);
      fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
      fl_color_print_line(f_type_error, context.error, context.reset, "'.");
    }

    return F_true;
  }
#endif // _di_fake_print_error_file_

#ifndef _di_fake_print_error_fss
  bool fake_print_error_fss(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const f_string path_file, const f_string_range range, const bool fallback) {

    if (status == F_file_found_not) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ENCODING ERROR: error occurred on invalid UTF-8 character at stop position (at ");
        fl_color_print(f_type_error, context.notable, context.reset, "%d", range.start);
        fl_color_print(f_type_error, context.error, context.reset, " of setting file '");
        fl_color_print(f_type_error, context.notable, context.reset, "%s", path_file);
        fl_color_print_line(f_type_error, context.error, context.reset, "').");
      }

      return F_false;
    }

    if (status == F_status_set_error(F_incomplete_utf_stop)) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ENCODING ERROR: error occurred on invalid UTF-8 character at end of string (at ");
        fl_color_print(f_type_error, context.notable, context.reset, "%d", range.start);
        fl_color_print(f_type_error, context.error, context.reset, " of setting file '");
        fl_color_print(f_type_error, context.notable, context.reset, "%s", path_file);
        fl_color_print_line(f_type_error, context.error, context.reset, "').");
      }

      return F_false;
    }

    if (fake_print_error(context, verbosity, status, function, F_false) == F_unknown && fallback && verbosity != fake_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, context.error, context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, context.notable, context.reset, "%llu", status);
      fl_color_print(f_type_error, context.error, context.reset, ") in function ");
      fl_color_print(f_type_error, context.notable, context.reset, "%s", function);
      fl_color_print_line(f_type_error, context.error, context.reset, "().");
    }

    return F_true;
  }
#endif // _di_fake_print_error_fss

#ifndef _di_fake_print_error_operation_
  bool fake_print_error_operation(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const f_string operation, const f_string how, const f_string source, const f_string destination, const bool fallback) {

    if (status == F_file_found_not) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Failed to find '");

        if (f_file_exists(source) == F_true) {
          fl_color_print(f_type_error, context.notable, context.reset, "%s", destination);
        }
        else {
          fl_color_print(f_type_error, context.notable, context.reset, "%s", source);
        }

        fl_color_print(f_type_error, context.error, context.reset, "' while trying to %s '", operation);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, context.error, context.reset, "' %s '", how);
          fl_color_print(f_type_error, context.notable, context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "INTERNAL ERROR: Invalid parameter when calling ");
        fl_color_print(f_type_error, context.notable, context.reset, "%s", function);
        fl_color_print(f_type_error, context.error, context.reset, "() to %s '", operation);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, context.error, context.reset, "' %s '", how);
          fl_color_print(f_type_error, context.notable, context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_name) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Invalid name for '");
        fl_color_print(f_type_error, context.notable, context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, context.error, context.reset, "' or '");
          fl_color_print(f_type_error, context.notable, context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_memory_out) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "CRITICAL ERROR: Unable to allocate memory, while trying to %s '", operation);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, context.error, context.reset, "' %s '", how);
          fl_color_print(f_type_error, context.notable, context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (verbosity != fake_verbosity_quiet) {

        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Overflow while trying to %s '", operation);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, context.error, context.reset, "' %s '", how);
          fl_color_print(f_type_error, context.notable, context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_directory) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Invalid directory while trying to %s '", operation);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, context.error, context.reset, "' %s '", how);
          fl_color_print(f_type_error, context.notable, context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_access_denied) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Access denied while trying to %s '", operation);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, context.error, context.reset, "' %s '", how);
          fl_color_print(f_type_error, context.notable, context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_loop) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Loop while trying to %s '", operation);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, context.error, context.reset, "' %s '", how);
          fl_color_print(f_type_error, context.notable, context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Prohibited by system while trying to %s '", operation);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, context.error, context.reset, "' %s '", how);
          fl_color_print(f_type_error, context.notable, context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_directory_found_not) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Failed to %s '", operation);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, context.error, context.reset, "' %s '", how);
          fl_color_print(f_type_error, context.notable, context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, context.error, context.reset, "' due to an invalid directory in the path.");
      }

      return F_false;
    }

    if (status == F_failure) {
      if (verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Failed to %s '", operation);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", source);

        if (destination) {
          fl_color_print(f_type_error, context.error, context.reset, "' %s '", how);
          fl_color_print(f_type_error, context.notable, context.reset, "%s", destination);
        }

        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (fake_print_error(context, verbosity, status, function, F_false) == F_unknown && fallback && verbosity != fake_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, context.error, context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, context.notable, context.reset, "%llu", status);
      fl_color_print(f_type_error, context.error, context.reset, ") occurred while trying to %s '", operation);
      fl_color_print(f_type_error, context.notable, context.reset, "%s", source);

      if (destination) {
        fl_color_print(f_type_error, context.error, context.reset, "' %s '", how);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", destination);
      }

      fl_color_print_line(f_type_error, context.error, context.reset, "'.");
    }

    return F_true;
  }
#endif // _di_fake_print_error_operation_

#ifndef _di_fake_print_error_parameter_missing_value_
  void fake_print_error_parameter_missing_value(const fl_color_context context, const uint8_t verbosity, const f_string parameter) {
    if (verbosity != fake_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);

      fl_color_print(f_type_error, context.error, context.reset, "ERROR: The parameter '");
      fl_color_print(f_type_error, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, parameter);

      fl_color_print_line(f_type_error, context.error, context.reset, "' was specified, but no value was given.");
    }
  }
#endif // _di_fake_print_error_parameter_missing_value_

#ifndef _di_fake_print_error_parameter_too_many_
  void fake_print_error_parameter_too_many(const fl_color_context context, const uint8_t verbosity, const f_string parameter) {
    if (verbosity != fake_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);

      fl_color_print(f_type_error, context.error, context.reset, "ERROR: the parameter '");
      fl_color_print(f_type_error, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, parameter);

      fl_color_print_line(f_type_error, context.error, context.reset, "' specified too many times.");
    }
  }
#endif // _di_fake_print_error_parameter_too_many_

#ifndef _di_fake_print_warning_fakefile_object_multiple_
  void fake_print_warning_fakefile_object_multiple(const fl_color_context context, const uint8_t verbosity, const f_string path_file, const f_string label, const f_string name_object) {
    if (verbosity != fake_verbosity_verbose) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_warning, context.warning, context.reset, "WARNING: the %s object '", label);
    fl_color_print(f_type_warning, context.notable, context.reset, "%s", name_object);
    fl_color_print(f_type_warning, context.warning, context.reset, "' in the file '");
    fl_color_print(f_type_warning, context.notable, context.reset, "%s", path_file);

    fl_color_print_line(f_type_warning, context.warning, context.reset, "' may only be specified once, only using the first.");
  }
#endif // _di_fake_print_warning_fakefile_object_multiple_

#ifndef _di_fake_print_warning_settings_content_multiple_
  void fake_print_warning_settings_content_multiple(const fl_color_context context, const uint8_t verbosity, const f_string path_file, const f_string name_object) {
    if (verbosity != fake_verbosity_verbose) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_warning, context.warning, context.reset, "WARNING: the setting object '");
    fl_color_print(f_type_warning, context.notable, context.reset, "%s", name_object);
    fl_color_print(f_type_warning, context.warning, context.reset, "' in the file '");
    fl_color_print(f_type_warning, context.notable, context.reset, "%s", path_file);

    fl_color_print_line(f_type_warning, context.warning, context.reset, "' may only have a single content, only using the first.");
  }
#endif // _di_fake_print_warning_settings_content_multiple_

#ifdef __cplusplus
} // extern "C"
#endif
