#include "error.h"
#include "private-error.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_error_print_
  f_status_t fll_error_print(const fl_print_t print, const f_status_t status, const f_string_t function, const bool fallback) {

    return private_fll_error_print(print, status, function, fallback);
  }
#endif // _di_fll_error_print_

#ifndef _di_fll_error_file_print_
  f_status_t fll_error_file_print(const fl_print_t print, const f_status_t status, const f_string_t function, const bool fallback, const f_string_t name, const f_string_t operation, const uint8_t type) {

    const char *type_name = FLL_error_file_type_file_s;

    if (type == fll_error_file_type_directory) {
      type_name = FLL_error_file_type_directory_s;
    }
    else if (type == fll_error_file_type_pipe) {
      type_name = FLL_error_file_type_pipe_s;
    }

    if (status == F_access_denied) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SAccess denied while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_access_group) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SCurrent user is not allowed to use the given group while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_access_owner) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SCurrent user is not allowed to use the given owner while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_directory) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SInvalid directory while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_directory_empty_not) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SUnable to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', not empty.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_close) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SUnable to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', failed to close.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_closed) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SUnable to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', is closed.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_descriptor) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SFile descriptor error while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_descriptor_max) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SMax file descriptors reached while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_descriptor_not) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SInvalid file descriptor while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_empty) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SUnable to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', %s is empty.%]%c", print.to.stream, print.context, type_name, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_flush) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SUnable to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', flush failed.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_found) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SUnable to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', found.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_found_not) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SUnable to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', could not find.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_open) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SUnable to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', already open.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_open_max) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SMax open files reached while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_overflow) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SOverflow while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_purge) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SUnable to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', purge failed.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_read) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SRead failed while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_read_only) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SUnable to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', %S is read only.%]%c", print.to.stream, print.context, type_name, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_seek) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SSeek failed while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_stat) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SStat failed while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_synchronize) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SSynchronize failed while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_utf) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SUTF failure while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_utf_not) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SInvalid UTF while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_underflow) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SUnderflow while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_write) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SFailed to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', write failure.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_write_only) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SUnable to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', %S is write only.%]%c", print.to.stream, print.context, type_name, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_loop) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SLoop while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_name) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SInvalid %S name '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SNumber overflow while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_number_underflow) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SNumber underflow while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SInvalid parameter", print.to.stream, f_string_eol_s[0], print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(" for the %S '%]", print.to.stream, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SProhibited by system while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (type == fll_error_file_type_file) {
      if (status == F_file_type_not_directory) {
        if (print.verbosity != f_console_verbosity_quiet) {
          flockfile(print.to.stream);

          fl_print_format("%c%[%SInvalid or missing directory in path while trying to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
          fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
          fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

          funlockfile(print.to.stream);
        }

        return F_false;
      }
    }

    if (status == F_failure) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SFailed to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (type == fll_error_file_type_file || type == fll_error_file_type_directory) {
      if (status == F_directory_found_not) {
        if (print.verbosity != f_console_verbosity_quiet) {
          flockfile(print.to.stream);

          fl_print_format("%c%[%SFailed to %S %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, operation, type_name, print.context);
          fl_print_format("%[%S%]", print.to.stream, print.notable, name, print.notable);
          fl_print_format("%[' due to an invalid directory in the path.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

          funlockfile(print.to.stream);
        }

        return F_false;
      }
    }

    return private_fll_error_print(print, status, function, fallback);
  }
#endif // _di_fll_error_file_print_

#ifndef _di_fll_error_parameter_integer_print_
  f_status_t fll_error_parameter_integer_print(const fl_print_t print, const f_status_t status, const f_string_t function, const bool fallback, const f_string_t parameter, const f_string_t argument) {

    if (status == F_data_not) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SThe argument for the parameter '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, parameter, print.notable);
        fl_print_format("%[' must not be an empty string.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_number) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SThe argument '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, argument, print.notable);
        fl_print_format("%[' is not a valid number for the parameter '%]", print.to.stream, print.context, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, parameter, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_number_negative) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SThe argument '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, argument, print.notable);
        fl_print_format("%[' is negative, which is not allowed for the parameter '%]", print.to.stream, print.context, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, parameter, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SThe argument '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, argument, print.notable);
        fl_print_format("%[' is too large for the parameter '%]", print.to.stream, print.context, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, parameter, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_number_positive) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SThe argument '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, argument, print.notable);
        fl_print_format("%[' is positive, which is not allowed for the parameter '%]", print.to.stream, print.context, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, parameter, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_number_underflow) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SThe argument '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, argument, print.notable);
        fl_print_format("%[' is too small for the parameter '%]", print.to.stream, print.context, print.context);
        fl_print_format("%[%S%]", print.to.stream, print.notable, parameter, print.notable);
        fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    return private_fll_error_print(print, status, function, fallback);
  }
#endif // _di_fll_error_parameter_integer_print_

#ifdef __cplusplus
} // extern "C"
#endif
