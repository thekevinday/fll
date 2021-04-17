#include "error.h"
#include "private-error.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_) || !defined(_di_fll_error_number_print_)
  f_status_t private_fll_error_print(const fll_error_print_t print, const f_status_t status, const f_string_t function, const bool fallback) {

    if (status == F_access_denied) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sAccess denied", print.context.before->string, print.prefix);

        private_fll_error_print_function(print, function);

        fprintf(print.to.stream, ".%s%c", print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_array_too_large) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sMaximum array length reached", print.context.before->string, print.prefix);

        private_fll_error_print_function(print, function);

        fprintf(print.to.stream, ".%s%c", print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_buffer_too_large) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sMaximum buffer length reached", print.context.before->string, print.prefix);

        private_fll_error_print_function(print, function);

        fprintf(print.to.stream, ".%s%c", print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_memory_not) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sUnable to allocate memory", print.context.before->string, print.prefix);

        private_fll_error_print_function(print, function);

        fprintf(print.to.stream, ".%s%c", print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sInvalid parameter", print.context.before->string, print.prefix);

        private_fll_error_print_function(print, function);

        fprintf(print.to.stream, ".%s%c", print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_string_too_large) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sMaximum string length reached", print.context.before->string, print.prefix);

        private_fll_error_print_function(print, function);

        fprintf(print.to.stream, ".%s%c", print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_utf) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sInvalid UTF-8 character", print.context.before->string, print.prefix);

        private_fll_error_print_function(print, function);

        fprintf(print.to.stream, ".%s%c", print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_complete_not_utf) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sInvalid (incomplete) UTF-8 character", print.context.before->string, print.prefix);

        private_fll_error_print_function(print, function);

        fprintf(print.to.stream, ".%s%c", print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (status == F_failure) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%sFailure", print.context.before->string, print.prefix);

        private_fll_error_print_function(print, function);

        fprintf(print.to.stream, ".%s%c", print.context.after->string, f_string_eol_s[0]);
      }

      return F_false;
    }

    if (fallback && print.verbosity != f_console_verbosity_quiet) {
      if (print.verbosity != f_console_verbosity_quiet) {
        fprintf(print.to.stream, "%c", f_string_eol_s[0]);
        fprintf(print.to.stream, "%s%s(", print.context.before->string, print.prefix);
        fprintf(print.to.stream, "%s%s%llu%s", print.context.after->string, print.notable.before->string, status, print.notable.after->string);
        fprintf(print.to.stream, "%s)", print.context.before->string);

        private_fll_error_print_function(print, function);

        fprintf(print.to.stream, ".%s%c", print.context.after->string, f_string_eol_s[0]);
      }
    }

    return F_true;
  }
#endif // !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_) || !defined(_di_fll_error_number_print_)

#if !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_) || !defined(_di_fll_error_number_print_)
  void private_fll_error_print_function(const fll_error_print_t print, const f_string_t function) {

    if (function) {
      fprintf(print.to.stream, " when calling function %s", print.context.after->string);
      fprintf(print.to.stream, "%s%s%s", print.notable.before->string, function, print.notable.after->string);
      fprintf(print.to.stream, "%s()", print.context.before->string);
    }
  }
#endif // !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_) || !defined(_di_fll_error_number_print_)

#ifdef __cplusplus
} // extern "C"
#endif
