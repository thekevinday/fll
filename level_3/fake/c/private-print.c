#include <level_3/fake.h>
#include "private-fake.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_error_
  f_return_status fake_print_error(const fake_data data, const f_status status, const f_string function, const bool fallback) {

    if (status == F_parameter) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Invalid parameter when calling function ");
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", function);
        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "().");
      }

      return F_none;
    }

    if (status == F_memory_allocation || status == F_memory_reallocation) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Unable to allocate memory in function ");
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", function);
        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "().");
      }

      return F_none;
    }

    if (fallback && data.verbosity != fake_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, data.context.error, data.context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, data.context.notable, data.context.reset, "%llu", status);
      fl_color_print(f_type_error, data.context.error, data.context.reset, ") in function ");
      fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", function);
      fl_color_print_line(f_type_error, data.context.error, data.context.reset, "().");
    }

    return F_unknown;
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

#ifndef _di_fake_print_error_fakefile_section_line_
  void fake_print_error_fakefile_section_line(const fake_data data, const f_status status, const f_string function, const f_string string) {
    if (data.verbosity == fake_verbosity_quiet) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    if (status == F_parameter) {
      fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Invalid parameter");
    }
    else if (status == F_memory_allocation || status == F_memory_reallocation) {
      fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Unable to allocate memory");
    }
    else if (status == F_buffer_too_large) {
      fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Maximum size reached for%s%s array", string ? " " : "", string ? string : "");
    }
    else {
      fl_color_print(f_type_error, data.context.error, data.context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, data.context.notable, data.context.reset, "%llu", status);
      fl_color_print(f_type_error, data.context.error, data.context.reset, ") occurred");
    }

    if (function) {
      fl_color_print(f_type_error, data.context.error, data.context.reset, " while calling ");
      fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", function);
      fl_color_print(f_type_error, data.context.error, data.context.reset, "()");
    }

    fl_color_print_line(f_type_error, data.context.error, data.context.reset, ".");
  }
#endif // _di_fake_print_error_fakefile_section_line_

#ifndef _di_fake_print_error_fakefile_section_operation_failed_
  void fake_print_error_fakefile_section_operation_failed(const fake_data data, const f_string_static buffer, const f_string_range section_name, const f_string_range operation_name) {
    if (data.verbosity == fake_verbosity_quiet) return;

    f_string_length line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(f_type_error, "%c", f_string_eol[0]);
    fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: The section operation '");

    fl_color_print_code(f_type_error, data.context.notable);
    f_print_string_dynamic_partial(f_type_error, buffer, operation_name);
    fl_color_print_code(f_type_error, data.context.reset);

    fl_color_print(f_type_error, data.context.error, data.context.reset, "' from section '");

    fl_color_print_code(f_type_error, data.context.notable);
    f_print_string_dynamic_partial(f_type_error, buffer, section_name);
    fl_color_print_code(f_type_error, data.context.reset);

    fl_color_print(f_type_error, data.context.error, data.context.reset, "' on line ");
    fl_color_print(f_type_error, data.context.notable, data.context.reset, "%llu", line);
    fl_color_print_line(f_type_error, data.context.error, data.context.reset, " failed.");
  }
#endif // _di_fake_print_error_fakefile_section_operation_failed_

#ifndef _di_fake_print_error_fakefile_section_operation_stack_max_
  void fake_print_error_fakefile_section_operation_stack_max(const fake_data data, const f_string_static buffer, const f_string_range section_name, const f_string_range operation_name, const f_array_length stack_max) {
    if (data.verbosity == fake_verbosity_quiet) return;

    f_string_length line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(f_type_error, "%c", f_string_eol[0]);
    fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: The section operation '");

    fl_color_print_code(f_type_error, data.context.notable);
    f_print_string_dynamic_partial(f_type_error, buffer, operation_name);
    fl_color_print_code(f_type_error, data.context.reset);

    fl_color_print(f_type_error, data.context.error, data.context.reset, "' from section '");

    fl_color_print_code(f_type_error, data.context.notable);
    f_print_string_dynamic_partial(f_type_error, buffer, section_name);
    fl_color_print_code(f_type_error, data.context.reset);

    fl_color_print(f_type_error, data.context.error, data.context.reset, "' on line ");
    fl_color_print(f_type_error, data.context.notable, data.context.reset, "%llu", line);
    fl_color_print(f_type_error, data.context.error, data.context.reset, " cannot be processed because the max stack depth of ");
    fl_color_print(f_type_error, data.context.notable, data.context.reset, "%llu", stack_max);
    fl_color_print_line(f_type_error, data.context.error, data.context.reset, " has been reached.");
  }
#endif // _di_fake_print_error_fakefile_section_operation_stack_max_

#ifndef _di_fake_print_error_fakefile_section_operation_unknown_
  void fake_print_error_fakefile_section_operation_unknown(const fake_data data, const f_string_static buffer, const f_string_range section_name, const f_string_range operation_name) {
    if (data.verbosity == fake_verbosity_quiet) return;

    f_string_length line = 1;

    f_fss_count_lines(buffer, operation_name.start, &line);

    fprintf(f_type_error, "%c", f_string_eol[0]);
    fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: The section operation '");

    fl_color_print_code(f_type_error, data.context.notable);
    f_print_string_dynamic_partial(f_type_error, buffer, operation_name);
    fl_color_print_code(f_type_error, data.context.reset);

    fl_color_print(f_type_error, data.context.error, data.context.reset, "' from section '");

    fl_color_print_code(f_type_error, data.context.notable);
    f_print_string_dynamic_partial(f_type_error, buffer, section_name);
    fl_color_print_code(f_type_error, data.context.reset);

    fl_color_print(f_type_error, data.context.error, data.context.reset, "' on line ");
    fl_color_print(f_type_error, data.context.notable, data.context.reset, "%llu", line);
    fl_color_print_line(f_type_error, data.context.error, data.context.reset, " is not a known operation name.");
  }
#endif // _di_fake_print_error_fakefile_section_operation_unknown_

#ifndef _di_fake_print_error_fakefile_settings_content_invalid_
  void fake_print_error_fakefile_settings_content_invalid(const fake_data data, const f_string path_file, const f_string_dynamic buffer, const f_string_range range_object, const f_string_range range_content, const f_string settings_name) {
    if (data.verbosity != fake_verbosity_verbose) return;

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
#endif // _di_fake_print_error_fakefile_settings_content_invalid_

#ifndef _di_fake_print_error_file_
  bool fake_print_error_file(const fake_data data, const f_status status, const f_string function, const f_string name, const f_string operation, const bool is_file, const bool fallback) {
    const f_string file_or_directory = is_file ? "file" : "directory";

    if (status == F_file_found_not) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: failed to find %s '", file_or_directory);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_file_found) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: the %s '", file_or_directory);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' already exists.");
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "INTERNAL ERROR: Invalid parameter when calling ");
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", function);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "() for the %s '", file_or_directory);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_name) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Invalid %s name '", file_or_directory);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_memory_out) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "CRITICAL ERROR: Unable to allocate memory, while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Overflow while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_directory) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Invalid directory while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_access_denied) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Access denied while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_loop) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Loop while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Prohibited by system while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", name);
        fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
      }

      return F_false;
    }

    if (is_file) {
      if (status == F_directory_found_not) {
        if (data.verbosity != fake_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: failed to %s %s '", operation, file_or_directory);
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", name);
          fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' due to an invalid directory in the path.");
        }

        return F_false;
      }
    }
    else {
      if (status == F_directory_found_not) {
        if (data.verbosity != fake_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: failed to %s %s '", operation, file_or_directory);
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", name);
          fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' due to an invalid directory in the path.");
        }

        return F_false;
      }

      if (status == F_failure) {
        if (data.verbosity != fake_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: failed to %s %s '", operation, file_or_directory);
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", name);
          fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
        }

        return F_false;
      }
    }

    if (fake_print_error(data, status, function, F_false) == F_unknown && fallback && data.verbosity != fake_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, data.context.error, data.context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, data.context.notable, data.context.reset, "%llu", status);
      fl_color_print(f_type_error, data.context.error, data.context.reset, ") occurred while trying to %s %s '", operation, file_or_directory);
      fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", name);
      fl_color_print_line(f_type_error, data.context.error, data.context.reset, "'.");
    }

    return F_true;
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

#ifndef _di_fake_print_error_fakefile_section_operation_path_outside_
  void fake_print_error_fakefile_section_operation_path_outside(const fake_data data, const f_status status, const f_string function, const f_string path) {
    if (data.verbosity == fake_verbosity_quiet) return;

    if (F_status_set_fine(status) == F_false) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: the path '");
      fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", path);
      fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' is outside the project root.");
    }
    else {
      fake_print_error_file(data, status, function, path, "determine real path of", F_true, F_true);
    }
  }
#endif // _di_fake_print_error_fakefile_section_operation_path_outside_

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

#ifndef _di_fake_print_error_section_operation_
  void fake_print_error_section_operation(const fake_data data, const f_string_static buffer, const f_string_range section_name, const f_string_static operation_name, const f_string message, ...) {
    if (data.verbosity == fake_verbosity_quiet) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Section '");

    fl_color_print_code(f_type_error, data.context.notable);
    f_print_string_dynamic_partial(f_type_error, buffer, section_name);
    fl_color_print_code(f_type_error, data.context.reset);

    fl_color_print(f_type_error, data.context.error, data.context.reset, "' operation '");

    fl_color_print_code(f_type_error, data.context.notable);
    f_print_string_dynamic(f_type_error, operation_name);
    fl_color_print_code(f_type_error, data.context.reset);

    fl_color_print(f_type_error, data.context.error, data.context.reset, "' ");

    f_print_string_dynamic(f_type_error, data.context.error);

    va_list ap;

    va_start(ap, message);

    vfprintf(f_type_error, message, ap);

    va_end(ap);

    f_print_string_dynamic(f_type_error, data.context.reset);

    fl_color_print_line(f_type_error, data.context.error, data.context.reset, ".");
  }
#endif // _di_fake_print_error_section_operation_

#ifndef _di_fake_print_warning_fakefile_object_multiple_
  void fake_print_warning_fakefile_object_multiple(const fake_data data, const f_string path_file, const f_string label, const f_string name_object) {
    if (data.verbosity != fake_verbosity_verbose) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    fl_color_print(f_type_warning, data.context.warning, data.context.reset, "WARNING: the %s object '", label);
    fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", name_object);
    fl_color_print(f_type_warning, data.context.warning, data.context.reset, "' in the file '");
    fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", path_file);

    fl_color_print_line(f_type_warning, data.context.warning, data.context.reset, "' may only be specified once, only using the first.");
  }
#endif // _di_fake_print_warning_fakefile_object_multiple_

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

#ifdef __cplusplus
} // extern "C"
#endif
