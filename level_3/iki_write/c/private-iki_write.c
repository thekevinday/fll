#include "iki_write.h"
#include "private-iki_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_print_error_
  f_return_status iki_write_print_error(const f_color_context_t context, const uint8_t verbosity, const f_status_t status, const f_string_t function, const bool fallback) {

    if (status == F_parameter) {
      if (verbosity != iki_write_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.set.error, "ERROR: Invalid parameter when calling function ");
        fl_color_print(f_type_error, context.set.notable, "%s", function);
        fl_color_print_line(f_type_error, context.set.error, "().");
      }

      return F_none;
    }

    if (status == F_memory_allocation || status == F_memory_reallocation) {
      if (verbosity != iki_write_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.set.error, "ERROR: Unable to allocate memory in function ");
        fl_color_print(f_type_error, context.set.notable, "%s", function);
        fl_color_print_line(f_type_error, context.set.error, "().");
      }

      return F_none;
    }

    if (status == F_buffer_too_large) {
      if (verbosity != iki_write_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.set.error, "ERROR: Maximum buffer limit reached while processing ");
        fl_color_print(f_type_error, context.set.notable, "%s", function);
        fl_color_print_line(f_type_error, context.set.error, "().");
      }

      return F_none;
    }

    if (status == F_string_too_large) {
      if (verbosity != iki_write_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.set.error, "ERROR: Maximum string limit reached while processing ");
        fl_color_print(f_type_error, context.set.notable, "%s", function);
        fl_color_print_line(f_type_error, context.set.error, "().");
      }

      return F_none;
    }

    if (fallback && verbosity != iki_write_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, context.set.error, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, context.set.notable, "%llu", status);
      fl_color_print(f_type_error, context.set.error, ") in function ");
      fl_color_print(f_type_error, context.set.notable, "%s", function);
      fl_color_print_line(f_type_error, context.set.error, "().");
    }

    return F_unknown;
  }
#endif // _di_iki_write_print_error_

#ifndef _di_iki_write_print_error_file_
  bool iki_write_print_error_file(const f_color_context_t context, const uint8_t verbosity, const f_status_t status, const f_string_t function, const f_string_t name, const f_string_t operation, const uint8_t type, const bool fallback) {
    f_string_t type_name = "file";

    if (type == 1) {
      type_name = "directory";
    }
    else if (type == 2) {
      type_name = "pipe";
    }

    if (status == F_file_found_not) {
      if (verbosity != iki_write_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.set.error, "ERROR: Failed to find %s '", type_name);
        fl_color_print(f_type_error, context.set.notable, "%s", name);
        fl_color_print_line(f_type_error, context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_file_closed) {
      if (verbosity != iki_write_verbosity_quiet) {
        fl_color_print(f_type_error, context.set.error, "INTERNAL ERROR: The %s '", type_name);
        fl_color_print(f_type_error, context.set.notable, "%s", name);
        fl_color_print_line(f_type_error, context.set.error, "' is no longer open.");
      }

      return F_false;
    }

    if (status == F_file_seek) {
      if (verbosity != iki_write_verbosity_quiet) {
        fl_color_print(f_type_error, context.set.error, "ERROR: A seek error occurred while accessing the file '");
        fl_color_print(f_type_error, context.set.notable, "%s", name);
        fl_color_print_line(f_type_error, context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_file_read) {
      if (verbosity != iki_write_verbosity_quiet) {
        fl_color_print(f_type_error, context.set.error, "ERROR: A read error occurred while accessing the file '");
        fl_color_print(f_type_error, context.set.notable, "%s", name);
        fl_color_print_line(f_type_error, context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_file_found) {
      if (verbosity != iki_write_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.set.error, "ERROR: The %s '", type_name);
        fl_color_print(f_type_error, context.set.notable, "%s", name);
        fl_color_print_line(f_type_error, context.set.error, "' already exists.");
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (verbosity != iki_write_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.set.error, "INTERNAL ERROR: Invalid parameter when calling ");
        fl_color_print(f_type_error, context.set.notable, "%s", function);
        fl_color_print(f_type_error, context.set.error, "() for the %s '", type_name);
        fl_color_print(f_type_error, context.set.notable, "%s", name);
        fl_color_print_line(f_type_error, context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_name) {
      if (verbosity != iki_write_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.set.error, "ERROR: Invalid %s name '", type_name);
        fl_color_print(f_type_error, context.set.notable, "%s", name);
        fl_color_print_line(f_type_error, context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_memory_out) {
      if (verbosity != iki_write_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.set.error, "CRITICAL ERROR: Unable to allocate memory, while trying to %s %s '", operation, type_name);
        fl_color_print(f_type_error, context.set.notable, "%s", name);
        fl_color_print_line(f_type_error, context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (verbosity != iki_write_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.set.error, "ERROR: Overflow while trying to %s %s '", operation, type_name);
        fl_color_print(f_type_error, context.set.notable, "%s", name);
        fl_color_print_line(f_type_error, context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_directory) {
      if (verbosity != iki_write_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.set.error, "ERROR: Invalid directory while trying to %s %s '", operation, type_name);
        fl_color_print(f_type_error, context.set.notable, "%s", name);
        fl_color_print_line(f_type_error, context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_access_denied) {
      if (verbosity != iki_write_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.set.error, "ERROR: Access denied while trying to %s %s '", operation, type_name);
        fl_color_print(f_type_error, context.set.notable, "%s", name);
        fl_color_print_line(f_type_error, context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_loop) {
      if (verbosity != iki_write_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.set.error, "ERROR: Loop while trying to %s %s '", operation, type_name);
        fl_color_print(f_type_error, context.set.notable, "%s", name);
        fl_color_print_line(f_type_error, context.set.error, "'.");
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (verbosity != iki_write_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.set.error, "ERROR: Prohibited by system while trying to %s %s '", operation, type_name);
        fl_color_print(f_type_error, context.set.notable, "%s", name);
        fl_color_print_line(f_type_error, context.set.error, "'.");
      }

      return F_false;
    }

    if (!type) {
      if (status == F_directory_found_not) {
        if (verbosity != iki_write_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, context.set.error, "ERROR: Failed to %s %s '", operation, type_name);
          fl_color_print(f_type_error, context.set.notable, "%s", name);
          fl_color_print_line(f_type_error, context.set.error, "' due to an invalid directory in the path.");
        }

        return F_false;
      }
    }
    else if (type == 1) {
      if (status == F_directory_found_not) {
        if (verbosity != iki_write_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, context.set.error, "ERROR: Failed to %s %s '", operation, type_name);
          fl_color_print(f_type_error, context.set.notable, "%s", name);
          fl_color_print_line(f_type_error, context.set.error, "' due to an invalid directory in the path.");
        }

        return F_false;
      }

      if (status == F_failure) {
        if (verbosity != iki_write_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, context.set.error, "ERROR: Failed to %s %s '", operation, type_name);
          fl_color_print(f_type_error, context.set.notable, "%s", name);
          fl_color_print_line(f_type_error, context.set.error, "'.");
        }

        return F_false;
      }
    }

    if (iki_write_print_error(context, verbosity, status, function, F_false) == F_unknown && fallback && verbosity != iki_write_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, context.set.error, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, context.set.notable, "%llu", status);
      fl_color_print(f_type_error, context.set.error, ") occurred while trying to %s %s '", operation, type_name);
      fl_color_print(f_type_error, context.set.notable, "%s", name);
      fl_color_print_line(f_type_error, context.set.error, "'.");
    }

    return F_true;
  }
#endif // _di_iki_write_print_error_file_

#ifndef _di_iki_write_process_
  f_return_status iki_write_process(const iki_write_data_t data, const f_string_static_t object, const f_string_static_t content, const uint8_t quote, const int output, f_string_dynamic_t *escaped) {

    if (!object.used) {
      if (data.verbosity != iki_write_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.set.error, "ERROR: The object is missing, it must not have a length of ");
        fl_color_print(f_type_error, data.context.set.notable, "0");
        fl_color_print_line(f_type_error, data.context.set.error, ".");
      }

      return F_status_set_error(F_failure);
    }

    f_status_t status = f_iki_object_is(object);

    if (status == F_false) {
      if (data.verbosity != iki_write_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data.context.set.error, "ERROR: The object '");

        fl_color_print_code(f_type_error, data.context.notable);
        f_print_dynamic(f_type_error, object);
        fl_color_print_code(f_type_error, data.context.reset);

        fl_color_print_line(f_type_error, data.context.set.error, "' is not a valid IKI object.");
      }

      return F_status_set_error(F_failure);
    }
    else if (F_status_is_error(status)) {
      iki_write_print_error(data.context, data.verbosity, F_status_set_fine(status), "f_iki_object_is", F_true);

      return F_status_set_error(F_failure);
    }

    escaped->used = 0;

    status = fll_iki_content_escape(content, quote, escaped);

    if (F_status_is_error(status)) {
      iki_write_print_error(data.context, data.verbosity, F_status_set_fine(status), "fll_iki_content_escape", F_true);

      f_macro_string_dynamic_t_delete_simple((*escaped));
      return F_status_set_error(F_failure);
    }

    dprintf(output, "%s%c%c%s%c", object.string, f_iki_syntax_separator, quote, escaped->string, quote);

    return F_none;
  }
#endif // _di_iki_write_process_

#ifdef __cplusplus
} // extern "C"
#endif
