#include "error.h"
#include "private-error.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_) || !defined(_di_fll_error_number_print_)
  f_return_status private_fll_error_print(const fll_error_print_t error, const f_status_t status, const f_string_t function, const bool fallback) {

    if (status == F_array_too_large) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sMaximum array length reached while processing ", error.context.before->string, error.prefix ? error.prefix : "");

        private_fll_error_print_function(error, function);

        fprintf(error.to.stream, ".%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_buffer_too_large) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sMaximum buffer length reached while processing ", error.context.before->string, error.prefix ? error.prefix : "");

        private_fll_error_print_function(error, function);

        fprintf(error.to.stream, ".%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_memory_allocation || status == F_memory_reallocation || status == F_memory_not) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sUnable to allocate memory in function ", error.context.before->string, error.prefix ? error.prefix : "");

        private_fll_error_print_function(error, function);

        fprintf(error.to.stream, ".%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sInvalid parameter", error.context.before->string, error.prefix ? error.prefix : "");

        private_fll_error_print_function(error, function);

        fprintf(error.to.stream, ".%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_string_too_large) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sMaximum string length reached while processing ", error.context.before->string, error.prefix ? error.prefix : "");

        private_fll_error_print_function(error, function);

        fprintf(error.to.stream, ".%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_utf) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sInvalid UTF-8 character while calling ", error.context.before->string, error.prefix ? error.prefix : "");

        private_fll_error_print_function(error, function);

        fprintf(error.to.stream, ".%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (status == F_complete_not_utf) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%sInvalid (incomplete) UTF-8 character while calling ", error.context.before->string, error.prefix ? error.prefix : "");

        private_fll_error_print_function(error, function);

        fprintf(error.to.stream, ".%s%c", error.context.after->string, f_string_eol[0]);
      }

      return F_false;
    }

    if (fallback && error.verbosity != f_console_verbosity_quiet) {
      if (error.verbosity != f_console_verbosity_quiet) {
        fprintf(error.to.stream, "%c", f_string_eol[0]);
        fprintf(error.to.stream, "%s%s(", error.context.before->string, error.prefix ? error.prefix : "");
        fprintf(error.to.stream, "%s%s%llu%s", error.context.after->string, error.notable.before->string, status, error.notable.after->string);
        fprintf(error.to.stream, "%s)", error.context.before->string);

        private_fll_error_print_function(error, function);

        fprintf(error.to.stream, ".%s%c", error.context.after->string, f_string_eol[0]);
      }
    }

    return F_true;
  }
#endif // !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_) || !defined(_di_fll_error_number_print_)

#if !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_) || !defined(_di_fll_error_number_print_)
  void private_fll_error_print_function(const fll_error_print_t error, const f_string_t function) {

    if (function) {
      fprintf(error.to.stream, " when calling function %s", error.context.after->string);
      fprintf(error.to.stream, "%s%s%s", error.notable.before->string, function, error.notable.after->string);
      fprintf(error.to.stream, "%s()", error.context.before->string);
    }
  }
#endif // !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_) || !defined(_di_fll_error_number_print_)

#ifdef __cplusplus
} // extern "C"
#endif
