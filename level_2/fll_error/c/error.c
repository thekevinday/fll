#include "error.h"
#include "private-error.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_error_print_
  f_return_status fll_error_print(const fll_error_print_t print, const f_status_t status, const f_string_t function, const bool fallback) {
    return private_fll_error_print(print, status, function, fallback);
  }
#endif // _di_fll_error_print_

#ifndef _di_fll_error_file_print_
  f_return_status fll_error_file_print(const fll_error_print_t print, const f_status_t status, const f_string_t function, const bool fallback, const f_string_t name, const f_string_t operation, const uint8_t type) {
    const char *type_name = fll_error_file_type_string_file;

    if (type == fll_error_file_type_directory) {
      type_name = fll_error_file_type_string_directory;
    }
    else if (type == fll_error_file_type_pipe) {
      type_name = fll_error_file_type_string_pipe;
    }

    if (status == F_access_denied) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sAccess denied while trying to %s %s '", print.context.before->string, print.prefix ? print.prefix : "", operation, type_name);
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        dprintf(print.to, "'.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_access_group) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sCurrrent user is not allowed to use the given group while trying to %s %s '", print.context.before->string, print.prefix ? print.prefix : "", operation, type_name);
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        dprintf(print.to, "'.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_access_owner) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sCurrrent user is not allowed to use the given owner while trying to %s %s '", print.context.before->string, print.prefix ? print.prefix : "", operation, type_name);
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        dprintf(print.to, "'.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_directory) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sInvalid directory while trying to %s %s '", print.context.before->string, print.prefix ? print.prefix : "", operation, type_name);
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        dprintf(print.to, "'.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_directory_empty_not) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sThe %s '", print.context.before->string, print.prefix ? print.prefix : "", type_name);
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        dprintf(print.to, "' is not empty.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_file_closed) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sThe %s '", print.context.before->string, print.prefix ? print.prefix : "", type_name);
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        dprintf(print.to, "' is not open.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_file_found) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sThe %s '", print.context.before->string, print.prefix ? print.prefix : "", type_name);
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        dprintf(print.to, "' already exists.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_file_found_not) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sFailed to find %s '", print.context.before->string, print.prefix ? print.prefix : "", type_name);
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        dprintf(print.to, "'.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_file_read) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sA read error occurred while accessing the file '", print.context.before->string, print.prefix ? print.prefix : "");
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        dprintf(print.to, "'.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_file_seek) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sA seek error occurred while accessing the file '", print.context.before->string, print.prefix ? print.prefix : "");
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        dprintf(print.to, "'.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_loop) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sLoop while trying to %s %s '", print.context.before->string, print.prefix ? print.prefix : "", operation, type_name);
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        dprintf(print.to, "'.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_name) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sInvalid %s name '", print.context.before->string, print.prefix ? print.prefix : "", type_name);
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        dprintf(print.to, "'.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sOverflow while trying to %s %s '", print.context.before->string, print.prefix ? print.prefix : "", operation, type_name);
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        dprintf(print.to, "'.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sInvalid parameter", print.context.before->string, print.prefix ? print.prefix : "");

        private_fll_error_print_function(print, function);

        dprintf(print.to, " for the %s '", type_name);
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        dprintf(print.to, "'.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sProhibited by system while trying to %s %s '", print.context.before->string, print.prefix ? print.prefix : "", operation, type_name);
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        dprintf(print.to, "'.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (type == fll_error_file_type_file) {
      if (status == F_directory_found_not) {
        if (print.verbosity != f_console_verbosity_quiet) {
          dprintf(print.to, "%c", f_string_eol[0]);
          dprintf(print.to, "%s%sFailed to %s %s '", print.context.before->string, print.prefix ? print.prefix : "", operation, type_name);
          dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
          dprintf(print.to, "' due to an invalid directory in the path.%s%c", print.context.after->string, f_string_eol[0]);
        }

        return F_false;
      }
    }
    else if (type == fll_error_file_type_directory) {
      if (status == F_directory_found_not) {
        if (print.verbosity != f_console_verbosity_quiet) {
          dprintf(print.to, "%c", f_string_eol[0]);
          dprintf(print.to, "%s%sFailed to %s %s '", print.context.before->string, print.prefix ? print.prefix : "", operation, type_name);
          dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
          dprintf(print.to, "' due to an invalid directory in the path.%s%c", print.context.after->string, f_string_eol[0]);
        }

        return F_false;
      }

      if (status == F_failure) {
        if (print.verbosity != f_console_verbosity_quiet) {
          dprintf(print.to, "%c", f_string_eol[0]);
          dprintf(print.to, "%s%sFailed to %s %s '", print.context.before->string, print.prefix ? print.prefix : "", operation, type_name);
          dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        }

        return F_false;
      }
    }

    return private_fll_error_print(print, status, function, fallback);
  }
#endif // _di_fll_error_file_print_

#ifndef _di_fll_error_parameter_print_
  f_return_status fll_error_parameter_print(const fll_error_print_t print, const f_status_t status, const f_string_t function, const bool fallback) {

    if (status == F_data_not) {
      if (print.verbosity != f_console_verbosity_quiet) {
        // @todo there is a way to identify which parameter is incorrect
        //       to do this, one must look for any "has_additional" and then see if the "additional" location is set to 0
        //       nothing can be 0 as that represents the program name, unless argv[] is improperly created
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sOne of the parameters passed requires an additional argument that was not passed.%s%c", print.context.before->string, print.prefix ? print.prefix : "");
        dprintf(print.to, "' must not be an empty string.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_utf) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sInvalid UTF-8 character in a parameter when calling ", print.context.before->string, print.prefix ? print.prefix : "");

        private_fll_error_print_function(print, function);

        dprintf(print.to, ".%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    return private_fll_error_print(print, status, function, fallback);
  }
#endif // _di_fll_error_parameter_print_

#ifndef _di_fll_error_parameter_integer_print_
  f_return_status fll_error_parameter_integer_print(const fll_error_print_t print, const f_status_t status, const f_string_t function, const bool fallback, const f_string_t parameter, const f_string_t argument) {

    if (status == F_data_not) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sThe argument for the parameter '", print.context.before->string, print.prefix ? print.prefix : "");
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, parameter, print.notable.after->string);
        dprintf(print.to, "' must not be an empty string.%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_number) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", argument[0]);
        dprintf(print.to, "%s%sThe argument '", print.context.before->string, print.prefix ? print.prefix : "");
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, argument, print.notable.after->string);
        dprintf(print.to, "' is not a valid number for the parameter '");
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, argument, print.notable.after->string);
        dprintf(print.to, "%s%s%s%s%c", print.context.after->string, print.notable.before->string, parameter, print.notable.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_number_negative) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", argument[0]);
        dprintf(print.to, "%s%sThe argument '", print.context.before->string, print.prefix ? print.prefix : "");
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, argument, print.notable.after->string);
        dprintf(print.to, "' is negative, which is not allowed for the parameter '");
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, argument, print.notable.after->string);
        dprintf(print.to, "%s%s%s%s%c", print.context.after->string, print.notable.before->string, parameter, print.notable.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", argument[0]);
        dprintf(print.to, "%s%sThe argument '", print.context.before->string, print.prefix ? print.prefix : "");
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, argument, print.notable.after->string);
        dprintf(print.to, "' is too large for the parameter '");
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, argument, print.notable.after->string);
        dprintf(print.to, "%s%s%s%s%c", print.context.after->string, print.notable.before->string, parameter, print.notable.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_number_positive) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", argument[0]);
        dprintf(print.to, "%s%sThe argument '", print.context.before->string, print.prefix ? print.prefix : "");
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, argument, print.notable.after->string);
        dprintf(print.to, "' is positive, which is not allowed for the parameter '");
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, argument, print.notable.after->string);
        dprintf(print.to, "%s%s%s%s%c", print.context.after->string, print.notable.before->string, parameter, print.notable.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_number_underflow) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", argument[0]);
        dprintf(print.to, "%s%sThe argument '", print.context.before->string, print.prefix ? print.prefix : "");
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, argument, print.notable.after->string);
        dprintf(print.to, "' is too small for the parameter '");
        dprintf(print.to, "%s%s%s%s", print.context.after->string, print.notable.before->string, argument, print.notable.after->string);
        dprintf(print.to, "%s%s%s%s%c", print.context.after->string, print.notable.before->string, parameter, print.notable.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    return private_fll_error_print(print, status, function, fallback);
  }
#endif // _di_fll_error_parameter_integer_print_

#ifdef __cplusplus
} // extern "C"
#endif
