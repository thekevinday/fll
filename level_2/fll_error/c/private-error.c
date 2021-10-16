#include "error.h"
#include "private-error.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_) || !defined(_di_fll_error_number_print_)
  f_status_t private_fll_error_print(const fl_print_t print, const f_status_t status, const f_string_t function, const bool fallback) {

    if (status == F_access_denied) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SAccess denied", print.to.stream, f_string_eol_s[0], print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%c", print.to.stream, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_array_too_large) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SMaximum array length reached", print.to.stream, f_string_eol_s[0], print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%c", print.to.stream, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_buffer_too_large) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SMaximum buffer length reached", print.to.stream, f_string_eol_s[0], print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%c", print.to.stream, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_memory_not) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SUnable to allocate memory", print.to.stream, f_string_eol_s[0], print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%c", print.to.stream, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SInvalid parameter", print.to.stream, f_string_eol_s[0], print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%c", print.to.stream, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_string_too_large) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SMaximum string length reached", print.to.stream, f_string_eol_s[0], print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%c", print.to.stream, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_utf) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SInvalid UTF-8 character", print.to.stream, f_string_eol_s[0], print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%c", print.to.stream, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_complete_not_utf || status == F_complete_not_utf_eos || status == F_complete_not_utf_stop) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SInvalid (incomplete) UTF-8 character found", print.to.stream, f_string_eol_s[0], print.context, print.prefix);

        private_fll_error_print_function(print, function);

        if (status == F_complete_not_utf_eos) {
          fl_print_format(" at the end of string.%]%c", print.to.stream, print.context, f_string_eol_s[0]);
        }
        else if (status == F_complete_not_utf_stop) {
          fl_print_format(" at the stop point of string.%]%c", print.to.stream, print.context, f_string_eol_s[0]);
        }
        else {
          fl_print_format(".%]%c", print.to.stream, print.context, f_string_eol_s[0]);
        }

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_failure) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%SFailure", print.to.stream, f_string_eol_s[0], print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%c", print.to.stream, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (fallback && print.verbosity != f_console_verbosity_quiet) {
      if (print.verbosity != f_console_verbosity_quiet) {
        flockfile(print.to.stream);

        fl_print_format("%c%[%S(%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, print.context);
        fl_print_format("%[%ui%]%[)", print.to.stream, print.notable, status, print.notable, print.context);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%c", print.to.stream, print.context, f_string_eol_s[0]);

        funlockfile(print.to.stream);
      }
    }

    return F_true;
  }
#endif // !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_) || !defined(_di_fll_error_number_print_)

#if !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_) || !defined(_di_fll_error_number_print_)
  void private_fll_error_print_function(const fl_print_t print, const f_string_t function) {

    if (function) {
      fl_print_format(" when calling function%] ", print.to.stream, print.context);
      fl_print_format("%[%S%]", print.to.stream, print.notable, function, print.notable);
      fl_print_format("%[()", print.to.stream, print.context);
    }
  }
#endif // !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_) || !defined(_di_fll_error_number_print_)

#ifdef __cplusplus
} // extern "C"
#endif
