#include "error.h"
#include "private-error.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_)
  f_status_t private_fll_error_print(const fl_print_t print, const f_status_t status, const f_string_t function, const uint8_t flag) {

    if (status == F_access_denied) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%[%QAccess denied", print.to, print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_array_too_large) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%[%QMaximum array length reached", print.to, print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_buffer_too_large) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%[%QMaximum buffer length reached", print.to, print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_error) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%[%QAn error has occurred", print.to, print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_file_found_not) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%[%QFile not found", print.to, print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_memory_not) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%[%QUnable to allocate memory", print.to, print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%[%QInvalid parameter", print.to, print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_string_too_large) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%[%QMaximum string length reached", print.to, print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_utf_not) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%[%QInvalid UTF-8 character found", print.to, print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_utf_fragment) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%[%QUTF-8 character (fragment) found", print.to, print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_complete_not_utf || status == F_complete_not_utf_eos || status == F_complete_not_utf_stop) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%[%QInvalid (incomplete) UTF-8 character found", print.to, print.context, print.prefix);

        private_fll_error_print_function(print, function);

        if (status == F_complete_not_utf_eos) {
          fl_print_format(" at the end of string.%]%r", print.to, print.context, f_string_eol_s);
        }
        else if (status == F_complete_not_utf_stop) {
          fl_print_format(" at the stop point of string.%]%r", print.to, print.context, f_string_eol_s);
        }
        else {
          fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);
        }

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_failure) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%[%QFailure", print.to, print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_signal) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%[%QSignal received", print.to, print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if (status == F_interrupt) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%[%QInterrupt signal received", print.to, print.context, print.prefix);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }

      return F_false;
    }

    if ((flag & fll_error_file_flag_fallback_e) && print.verbosity != f_console_verbosity_quiet_e) {
      if (print.verbosity != f_console_verbosity_quiet_e) {
        flockfile(print.to.stream);

        fl_print_format("%[%Q(%]", print.to, print.context, print.prefix, print.context);
        fl_print_format("%[%ui%]%[)", print.to, print.notable, status, print.notable, print.context);

        private_fll_error_print_function(print, function);

        fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

        funlockfile(print.to.stream);
      }
    }

    return F_true;
  }
#endif // !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_)

#if !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_)
  void private_fll_error_print_function(const fl_print_t print, const f_string_t function) {

    if (function) {
      fl_print_format(" when calling function%] ", print.to, print.context);
      fl_print_format("%[%S%]", print.to, print.notable, function, print.notable);
      fl_print_format("%[()", print.to, print.context);
    }
  }
#endif // !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_)

#if !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_)
  void private_fll_error_print_unable_to(const fl_print_t print, const f_string_static_t operation, const f_string_static_t name, const f_string_static_t type, const f_string_t message) {

    if (print.verbosity < f_console_verbosity_error_e) return;

    flockfile(print.to.stream);

    fl_print_format("%[%QUnable to %Q %Q '%]", print.to, print.context, print.prefix, operation, type, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, name, print.notable);
    fl_print_format("%['%S%S.%]%r", print.to, print.context, message ? ", " : "", message ? message : "", print.context, f_string_eol_s);

    funlockfile(print.to.stream);
  }
#endif // !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_)

#ifdef __cplusplus
} // extern "C"
#endif
