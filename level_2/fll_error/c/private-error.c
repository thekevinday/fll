#include "error.h"
#include "private-error.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_) || !defined(_di_fll_error_number_print_)
  f_return_status private_fll_error_print(const fll_error_print_t print, const f_status_t status, const f_string_t function, const bool fallback) {

    if (status == F_buffer_too_large) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sMaximum buffer length reached while processing ", print.context.before->string, print.prefix ? print.prefix : "");

        private_fll_error_print_function(print, function);

        dprintf(print.to, ".%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_memory_allocation || status == F_memory_reallocation || status == F_memory_out) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sUnable to allocate memory in function ", print.context.before->string, print.prefix ? print.prefix : "");

        private_fll_error_print_function(print, function);

        dprintf(print.to, ".%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sInvalid parameter", print.context.before->string, print.prefix ? print.prefix : "");

        private_fll_error_print_function(print, function);

        dprintf(print.to, ".%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_string_too_large) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sMaximum string length reached while processing ", print.context.before->string, print.prefix ? print.prefix : "");

        private_fll_error_print_function(print, function);

        dprintf(print.to, ".%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_utf) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%sInvalid UTF-8 character while calling ", print.context.before->string, print.prefix ? print.prefix : "");

        private_fll_error_print_function(print, function);

        dprintf(print.to, ".%s%c", print.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (fallback && print.verbosity != f_console_verbosity_quiet) {
      if (print.verbosity != f_console_verbosity_quiet) {
        dprintf(print.to, "%c", f_string_eol[0]);
        dprintf(print.to, "%s%s(%llu)", print.context.before->string, print.prefix ? print.prefix : "", status);

        private_fll_error_print_function(print, function);

        dprintf(print.to, ".%s%c", print.context.after->string, f_string_eol[0]);
      }
    }

    return F_true;
  }
#endif // !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_) || !defined(_di_fll_error_number_print_)

#if !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_) || !defined(_di_fll_error_number_print_)
  void private_fll_error_print_function(const fll_error_print_t print, const f_string_t function) {

    if (function) {
      dprintf(print.to, " when calling function %s", print.context.after->string);
      dprintf(print.to, "%s%s%s", print.notable.before->string, function, print.notable.after->string);
      dprintf(print.to, "%s()", print.context.before->string);
    }
  }
#endif // !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_) || !defined(_di_fll_error_number_print_)

#ifdef __cplusplus
} // extern "C"
#endif
