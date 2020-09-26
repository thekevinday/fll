#include "error.h"
#include "private-error.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_error_print_
  f_return_status fll_error_print(const fll_error_print_t error, const f_status_t status, const f_string_t function, const bool fallback) {
    return private_fll_error_print(error, status, function, fallback);
  }
#endif // _di_fll_error_print_

#ifndef _di_fll_error_file_print_
  f_return_status fll_error_file_print(const fll_error_print_t error, const f_status_t status, const f_string_t function, const bool fallback, const f_string_t name, const f_string_t operation, const uint8_t type) {
    const char *type_name = fll_error_file_type_string_file;

    if (type == fll_error_file_type_directory) {
      type_name = fll_error_file_type_string_directory;
    }
    else if (type == fll_error_file_type_pipe) {
      type_name = fll_error_file_type_string_pipe;
    }

    if (status == F_access_denied) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sAccess denied while trying to %s %s '", error.context.before->string, error.prefix ? error.prefix : "", operation, type_name);
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
        fprintf(error.to.stream, "'.%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_access_group) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sCurrrent user is not allowed to use the given group while trying to %s %s '", error.context.before->string, error.prefix ? error.prefix : "", operation, type_name);
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
        fprintf(error.to.stream, "'.%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_access_owner) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sCurrrent user is not allowed to use the given owner while trying to %s %s '", error.context.before->string, error.prefix ? error.prefix : "", operation, type_name);
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
        fprintf(error.to.stream, "'.%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_directory) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sInvalid directory while trying to %s %s '", error.context.before->string, error.prefix ? error.prefix : "", operation, type_name);
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
        fprintf(error.to.stream, "'.%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_directory_empty_not) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sThe %s '", error.context.before->string, error.prefix ? error.prefix : "", type_name);
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
        fprintf(error.to.stream, "' is not empty.%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_file_closed) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sThe %s '", error.context.before->string, error.prefix ? error.prefix : "", type_name);
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
        fprintf(error.to.stream, "' is not open.%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_file_found) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sThe %s '", error.context.before->string, error.prefix ? error.prefix : "", type_name);
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
        fprintf(error.to.stream, "' already exists.%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_file_found_not) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sFailed to find %s '", error.context.before->string, error.prefix ? error.prefix : "", type_name);
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
        fprintf(error.to.stream, "'.%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_file_open) {
      fl_color_print(error.to.stream, error.context, "%s%sUnable to open the file '", error.context.before->string, error.prefix ? error.prefix : "");
      fl_color_print(error.to.stream, error.notable, "%s", file_name);
      fl_color_print(error.to.stream, error.context, "'.");
      fprintf(error.to.stream, "%c", f_string_eol[0]);

      return F_false;
    }

    if (status == F_file_descriptor) {
      fl_color_print(error.to.stream, error.context, "%s%sFile descriptor error while trying to open the file '", error.context.before->string, error.prefix ? error.prefix : "");
      fl_color_print(error.to.stream.to.stream, error.notable, "%s", file_name);
      fl_color_print(stream, error.context, "'.");
      fprintf(error.to.stream, "%c", f_string_eol[0]);

      return F_false;
    }

    if (status == F_number_underflow) {
      fl_color_print(error.to.stream, error.context, "%s%sInteger underflow while trying to buffer the file '", error.context.before->string, error.prefix ? error.prefix : "");
      fl_color_print(error.to.stream, error.notable, "%s", file_name);
      fl_color_print(error.to.stream, error.context, "'.");
      fprintf(error.to.stream, "%c", f_string_eol[0]);

      return F_false;
    }

    if (status == F_file_read) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sA read error occurred while accessing the file '", error.context.before->string, error.prefix ? error.prefix : "");
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
        fprintf(error.to.stream, "'.%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_file_seek) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sA seek error occurred while accessing the file '", error.context.before->string, error.prefix ? error.prefix : "");
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
        fprintf(error.to.stream, "'.%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_loop) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sLoop while trying to %s %s '", error.context.before->string, error.prefix ? error.prefix : "", operation, type_name);
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
        fprintf(error.to.stream, "'.%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_name) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sInvalid %s name '", error.context.before->string, error.prefix ? error.prefix : "", type_name);
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
        fprintf(error.to.stream, "'.%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sOverflow while trying to %s %s '", error.context.before->string, error.prefix ? error.prefix : "", operation, type_name);
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
        fprintf(error.to.stream, "'.%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sInvalid parameter", error.context.before->string, error.prefix ? error.prefix : "");

        private_fll_error_print_function(error, function);

        fprintf(error.to.stream, " for the %s '", type_name);
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
        fprintf(error.to.stream, "'.%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sProhibited by system while trying to %s %s '", error.context.before->string, error.prefix ? error.prefix : "", operation, type_name);
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
        fprintf(error.to.stream, "'.%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (type == fll_error_file_type_file) {
      if (status == F_directory_found_not) {
        if (error.verbosity != f_console_verbosity_quiet) {
          fprintf(error.to.stream, "%c", f_string_eol[0]);
          fprintf(error.to.stream, "%s%sFailed to %s %s '", error.context.before->string, error.prefix ? error.prefix : "", operation, type_name);
          fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
          fprintf(error.to.stream, "' due to an invalid directory in the path.%s%c", error.context.after->string, f_string_eol[0]);
        }

        return F_false;
      }
    }
    else if (type == fll_error_file_type_directory) {
      if (status == F_directory_found_not) {
        if (error.verbosity != f_console_verbosity_quiet) {
          fprintf(error.to.stream, "%c", f_string_eol[0]);
          fprintf(error.to.stream, "%s%sFailed to %s %s '", error.context.before->string, error.prefix ? error.prefix : "", operation, type_name);
          fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
          fprintf(error.to.stream, "' due to an invalid directory in the path.%s%c", error.context.after->string, f_string_eol[0]);
        }

        return F_false;
      }

      if (status == F_failure) {
        if (error.verbosity != f_console_verbosity_quiet) {
          fprintf(error.to.stream, "%c", f_string_eol[0]);
          fprintf(error.to.stream, "%s%sFailed to %s %s '", error.context.before->string, error.prefix ? error.prefix : "", operation, type_name);
          fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, name, error.notable.after->string);
        }

        return F_false;
      }
    }

    return private_fll_error_print(error, status, function, fallback);
  }
#endif // _di_fll_error_file_print_

#ifndef _di_fll_error_parameter_integer_print_
  f_return_status fll_error_parameter_integer_print(const fll_error_print_t error, const f_status_t status, const f_string_t function, const bool fallback, const f_string_t parameter, const f_string_t argument) {

    if (status == F_data_not) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sThe argument for the parameter '", error.context.before->string, error.prefix ? error.prefix : "");
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, parameter, error.notable.after->string);
        fprintf(error.to.stream, "' must not be an empty string.%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_number) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", argument[0]);
        fprintf(error.to.stream, "%s%sThe argument '", error.context.before->string, error.prefix ? error.prefix : "");
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, argument, error.notable.after->string);
        fprintf(error.to.stream, "' is not a valid number for the parameter '");
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, argument, error.notable.after->string);
        fprintf(error.to.stream, "%s%s%s%s%c", error.context.after->string, error.notable.before->string, parameter, error.notable.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_number_negative) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", argument[0]);
        fprintf(error.to.stream, "%s%sThe argument '", error.context.before->string, error.prefix ? error.prefix : "");
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, argument, error.notable.after->string);
        fprintf(error.to.stream, "' is negative, which is not allowed for the parameter '");
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, argument, error.notable.after->string);
        fprintf(error.to.stream, "%s%s%s%s%c", error.context.after->string, error.notable.before->string, parameter, error.notable.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", argument[0]);
        fprintf(error.to.stream, "%s%sThe argument '", error.context.before->string, error.prefix ? error.prefix : "");
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, argument, error.notable.after->string);
        fprintf(error.to.stream, "' is too large for the parameter '");
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, argument, error.notable.after->string);
        fprintf(error.to.stream, "%s%s%s%s%c", error.context.after->string, error.notable.before->string, parameter, error.notable.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_number_positive) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", argument[0]);
        fprintf(error.to.stream, "%s%sThe argument '", error.context.before->string, error.prefix ? error.prefix : "");
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, argument, error.notable.after->string);
        fprintf(error.to.stream, "' is positive, which is not allowed for the parameter '");
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, argument, error.notable.after->string);
        fprintf(error.to.stream, "%s%s%s%s%c", error.context.after->string, error.notable.before->string, parameter, error.notable.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_number_underflow) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", argument[0]);
        fprintf(error.to.stream, "%s%sThe argument '", error.context.before->string, error.prefix ? error.prefix : "");
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, argument, error.notable.after->string);
        fprintf(error.to.stream, "' is too small for the parameter '");
        fprintf(error.to.stream, "%s%s%s%s", error.context.after->string, error.notable.before->string, argument, error.notable.after->string);
        fprintf(error.to.stream, "%s%s%s%s%c", error.context.after->string, error.notable.before->string, parameter, error.notable.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    return private_fll_error_print(error, status, function, fallback);
  }
#endif // _di_fll_error_parameter_integer_print_

#ifdef __cplusplus
} // extern "C"
#endif
