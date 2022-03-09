#include "error.h"
#include "private-error.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_error_print_
  f_status_t fll_error_print(const fl_print_t print, const f_status_t status, const char *function, const bool fallback) {

    return private_fll_error_print(print, status, function, fallback);
  }
#endif // _di_fll_error_print_

#ifndef _di_fll_error_file_print_
  f_status_t fll_error_file_print(const fl_print_t print, const f_status_t status, const char *function, const bool fallback, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    f_string_static_t type_name = fll_error_file_type_file_s;

    if (type == fll_error_file_type_directory_e) {
      type_name = fll_error_file_type_directory_s;
    }
    else if (type == fll_error_file_type_path_e) {
      type_name = fll_error_file_type_path_s;
    }
    else if (type == fll_error_file_type_pipe_e) {
      type_name = fll_error_file_type_pipe_s;
    }
    else if (type == fll_error_file_type_socket_e) {
      type_name = fll_error_file_type_socket_s;
    }

    if (status == F_access_denied) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QAccess denied while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_access_group) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QCurrent user is not allowed to use the given group while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_access_owner) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QCurrent user is not allowed to use the given owner while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_directory) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QInvalid directory while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_directory_empty_not) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QUnable to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', not empty.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_failure) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QFailed to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_close) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QUnable to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', failed to close.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_closed) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QUnable to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', is closed.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_descriptor) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QFile descriptor error while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_descriptor_max) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QMax file descriptors reached while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_descriptor_not) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QInvalid file descriptor while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_empty) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QUnable to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', %Q is empty.%]%r", print.to.stream, print.context, type_name, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_flush) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QUnable to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', flush failed.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_found) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QUnable to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', found.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_found_not) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QUnable to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', could not find.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_open) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QUnable to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', already open.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_open_max) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QMax open files reached while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_overflow) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QOverflow while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_purge) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QUnable to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', purge failed.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_read) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QRead failed while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_seek) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QSeek failed while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_stat) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QStat failed while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_synchronize) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QSynchronize failed while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_type_unknown) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QFailed to %Q %Q, the path '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[' is an unknown file type.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_utf) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QUTF failure while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_utf_not) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QInvalid UTF while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_underflow) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QUnderflow while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_write) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QFailed to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', write failure.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_loop) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QLoop while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_name) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QInvalid %Q name '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QNumber overflow while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_number_underflow) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QNumber underflow while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QInvalid parameter", print.to.stream, f_string_eol_s, print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(" for the %Q '%]", print.to.stream, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QProhibited by system while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_read_only) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QUnable to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', %Q is read only.%]%r", print.to.stream, print.context, type_name, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_write_only) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QUnable to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
        fl_print_format("%[', %Q is write only.%]%r", print.to.stream, print.context, type_name, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (type == fll_error_file_type_file_e) {
      if (status == F_file_type_not_directory) {
        if (print.verbosity != f_console_verbosity_quiet_e) {
          flockfile(print.to.stream);

          fl_print_format("%r%[%QInvalid or missing directory in path while trying to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
          fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
          fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

          funlockfile(print.to.stream);
        }

        return F_false;
      }

      if (status == F_file_type_directory) {
        if (print.verbosity != f_console_verbosity_quiet_e) {
          flockfile(print.to.stream);

          fl_print_format("%r%[%QFailed to %Q %Q, the path '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
          fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
          fl_print_format("%[' is a directory.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

          funlockfile(print.to.stream);
        }

        return F_false;
      }
    }
    else if (type == fll_error_file_type_directory_e) {
      if (status == F_file_type_regular) {
        if (print.verbosity != f_console_verbosity_quiet_e) {
          flockfile(print.to.stream);

          fl_print_format("%r%[%QFailed to %Q %Q, the path '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
          fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
          fl_print_format("%[' is a file.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

          funlockfile(print.to.stream);
        }

        return F_false;
      }
    }

    if (type == fll_error_file_type_file_e || type == fll_error_file_type_directory_e || type == fll_error_file_type_path_e) {
      if (status == F_directory_found_not) {
        if (print.verbosity != f_console_verbosity_quiet_e) {
          flockfile(print.to.stream);

          fl_print_format("%r%[%QFailed to %Q %Q '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
          fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
          fl_print_format("%[' due to an invalid directory in the path.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

          funlockfile(print.to.stream);
        }

        return F_false;
      }

      if (status == F_file_type_pipe || status == F_file_type_socket) {
        if (print.verbosity != f_console_verbosity_quiet_e) {
          flockfile(print.to.stream);

          fl_print_format("%r%[%QFailed to %Q %Q, the path '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, operation, type_name, print.context);
          fl_print_format("%[%Q%]", print.to.stream, print.notable, name, print.notable);
          fl_print_format("%[' is a %Q.%]%r", print.to.stream, print.context, status == F_file_type_pipe ? fll_error_file_type_pipe_s : fll_error_file_type_socket_s, print.context, f_string_eol_s);

          funlockfile(print.to.stream);
        }

        return F_false;
      }
    }

    return private_fll_error_print(print, status, function, fallback);
  }
#endif // _di_fll_error_file_print_

#ifndef _di_fll_error_parameter_integer_print_
  f_status_t fll_error_parameter_integer_print(const fl_print_t print, const f_status_t status, const char *function, const bool fallback, const f_string_static_t parameter, const f_string_static_t argument) {

    if (status == F_data_not) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QThe argument for the parameter '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, parameter, print.notable);
        fl_print_format("%[' must not be an empty string.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_number) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QThe argument '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, argument, print.notable);
        fl_print_format("%[' is not a valid number for the parameter '%]", print.to.stream, print.context, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, parameter, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_number_negative) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QThe argument '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, argument, print.notable);
        fl_print_format("%[' is negative, which is not allowed for the parameter '%]", print.to.stream, print.context, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, parameter, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QThe argument '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, argument, print.notable);
        fl_print_format("%[' is too large for the parameter '%]", print.to.stream, print.context, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, parameter, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_number_positive) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QThe argument '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, argument, print.notable);
        fl_print_format("%[' is positive, which is not allowed for the parameter '%]", print.to.stream, print.context, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, parameter, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_number_underflow) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%r%[%QThe argument '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, argument, print.notable);
        fl_print_format("%[' is too small for the parameter '%]", print.to.stream, print.context, print.context);
        fl_print_format("%[%Q%]", print.to.stream, print.notable, parameter, print.notable);
        fl_print_format("%['.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

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
