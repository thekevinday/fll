#include "error.h"
#include "private-error.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_error_print_
  f_status_t fll_error_print(const fll_error_print_t print, const f_status_t status, const f_string_t function, const bool fallback) {
    return private_fll_error_print(print, status, function, fallback);
  }
#endif // _di_fll_error_print_

#ifndef _di_fll_error_file_print_
  f_status_t fll_error_file_print(const fll_error_print_t print, const f_status_t status, const f_string_t function, const bool fallback, const f_string_t name, const f_string_t operation, const uint8_t type) {
    const char *type_name = fll_error_file_type_string_file;

    if (type == fll_error_file_type_directory) {
      type_name = fll_error_file_type_string_directory;
    }
    else if (type == fll_error_file_type_pipe) {
      type_name = fll_error_file_type_string_pipe;
    }

    if (status == F_access_denied) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sAccess denied while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_access_group) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sCurrent user is not allowed to use the given group while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_access_owner) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sCurrent user is not allowed to use the given owner while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_directory) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sInvalid directory while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_directory_empty_not) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sUnable to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s', not empty.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_file_close) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sUnable to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s', failed to close.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_file_closed) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sUnable to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s', is closed.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_file_found) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sUnable to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s', found %s.%s%c", print.context.before->string, type_name, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_file_found_not) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sUnable to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s', could not find %s.%s%c", print.context.before->string, type_name, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_file_open) {
      fprintf(print.to.stream, "%s%sUnable to %s %s '", print.context.before->string, print.prefix, operation, type_name);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
      fprintf(print.to.stream, "%s', already open.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);

      return F_false;
    }

    if (status == F_file_descriptor) {
      fprintf(print.to.stream, "%s%sFile descriptor error while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
      fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);

      return F_false;
    }

    if (status == F_file_descriptor_max) {
      fprintf(print.to.stream, "%s%sMax file descriptors reached while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
      fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);

      return F_false;
    }

    if (status == F_file_descriptor_not) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sInvalid file descriptor while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_file_empty) {
      fprintf(print.to.stream, "%s%sUnable to %s %s '", print.context.before->string, print.prefix, operation, type_name);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
      fprintf(print.to.stream, "%s', %s is empty.%s%c", print.context.before->string, type_name, print.context.after->string, f_string_eol_s[0]);

      return F_false;
    }

    if (status == F_file_flush) {
      fprintf(print.to.stream, "%s%sUnable to %s %s '", print.context.before->string, print.prefix, operation, type_name);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
      fprintf(print.to.stream, "%s', flush failed.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);

      return F_false;
    }

    if (status == F_file_open_max) {
      fprintf(print.to.stream, "%s%sMax open files reached while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
      fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);

      return F_false;
    }

    if (status == F_file_overflow) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sOverflow while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_file_purge) {
      fprintf(print.to.stream, "%s%sUnable to %s %s '", print.context.before->string, print.prefix, operation, type_name);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
      fprintf(print.to.stream, "%s', purge failed.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);

      return F_false;
    }

    if (status == F_file_read) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sRead failed while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_file_seek) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sSeek failed while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_file_stat) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sStat failed while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_file_synchronize) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sSynchronize failed while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_file_utf) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sUTF failure while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_file_utf_not) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sInvalid UTF while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_file_underflow) {
      fprintf(print.to.stream, "%s%sUnderflow while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
      fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);

      return F_false;
    }

    if (status == F_file_write) {
      fprintf(print.to.stream, "%s%sFailed to %s %s '", print.context.before->string, print.prefix, operation, type_name);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
      fprintf(print.to.stream, "%s', write failure.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);

      return F_false;
    }

    if (status == F_loop) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sLoop while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_name) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sInvalid %s name '", print.context.before->string, print.prefix, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sNumber overflow while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_number_underflow) {
      fprintf(print.to.stream, "%s%sNumber underflow while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
      fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);

      return F_false;
    }

    if (status == F_parameter) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sInvalid parameter", print.context.before->string, print.prefix);

        private_fll_error_print_function(print, function);

        fprintf(print.to.stream, " for the %s '", type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sProhibited by system while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (type == fll_error_file_type_file) {
      if (status == F_file_type_not_directory) {
        if (print.verbosity != f_console_verbosity_quiet) {
          fprintf(print.to.stream, "%c", f_string_eol_s[0]);
          fprintf(print.to.stream, "%s%sInvalid or missing directory in path while trying to %s %s '", print.context.before->string, print.prefix, operation, type_name);
          fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
          fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
        }

        return F_false;
      }
    }

    if (status == F_failure) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sFailed to %s %s '", print.context.before->string, print.prefix, operation, type_name);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (type == fll_error_file_type_file || type == fll_error_file_type_directory) {
      if (status == F_directory_found_not) {
        if (print.verbosity != f_console_verbosity_quiet) {
          fprintf(print.to.stream, "%c", f_string_eol_s[0]);
          fprintf(print.to.stream, "%s%sFailed to %s %s '", print.context.before->string, print.prefix, operation, type_name);
          fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name, print.notable.after->string);
          fprintf(print.to.stream, "%s' due to an invalid directory in the path.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
        }

        return F_false;
      }
    }

    return private_fll_error_print(print, status, function, fallback);
  }
#endif // _di_fll_error_file_print_

#ifndef _di_fll_error_parameter_integer_print_
  f_status_t fll_error_parameter_integer_print(const fll_error_print_t print, const f_status_t status, const f_string_t function, const bool fallback, const f_string_t parameter, const f_string_t argument) {

    if (status == F_data_not) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sThe argument for the parameter '", print.context.before->string, print.prefix);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, parameter, print.notable.after->string);
        fprintf(print.to.stream, "%s' must not be an empty string.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_number) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sThe argument '", print.context.before->string, print.prefix);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, argument, print.notable.after->string);
        fprintf(print.to.stream, "%s' is not a valid number for the parameter '", print.context.before->string);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, parameter, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_number_negative) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sThe argument '", print.context.before->string, print.prefix);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, argument, print.notable.after->string);
        fprintf(print.to.stream, "%s' is negative, which is not allowed for the parameter '", print.context.before->string);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, parameter, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sThe argument '", print.context.before->string, print.prefix);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, argument, print.notable.after->string);
        fprintf(print.to.stream, "%s' is too large for the parameter '", print.context.before->string);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, parameter, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_number_positive) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sThe argument '", print.context.before->string, print.prefix);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, argument, print.notable.after->string);
        fprintf(print.to.stream, "%s' is positive, which is not allowed for the parameter '", print.context.before->string);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, parameter, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_number_underflow) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sThe argument '", print.context.before->string, print.prefix);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, argument, print.notable.after->string);
        fprintf(print.to.stream, "%s' is too small for the parameter '", print.context.before->string);
        fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, parameter, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    return private_fll_error_print(print, status, function, fallback);
  }
#endif // _di_fll_error_parameter_integer_print_

#ifdef __cplusplus
} // extern "C"
#endif
