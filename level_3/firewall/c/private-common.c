#include "firewall.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

void firewall_print_debug_tool(const fll_error_print_t output, const f_string_t tool, const f_string_dynamics_t arguments) {

  if (output.verbosity != f_console_verbosity_debug) return;

  flockfile(output.to.stream);

  fl_print_format("%[%s", output.to.stream, output.context, tool);

  for (f_array_length_t i = 0; i < arguments.used; ++i) {
    fl_print_format(" %Q", output.to.stream, arguments.array[i]);
  } // for

  fl_print_format("%]%c", output.to.stream, output.context, f_string_eol_s[0]);

  funlockfile(output.to.stream);
}

void firewall_print_error_on_allocation_failure(const fll_error_print_t output) {

  if (output.verbosity == f_console_verbosity_quiet) return;

  fll_print_format("%c%[%sUnable to allocate memory.%]%c", output.to.stream, f_string_eol_s[0], output.context, output.prefix, output.context, f_string_eol_s[0]);
}

void firewall_print_error_on_invalid_parameter(const fll_error_print_t output, const f_string_t function) {

  if (output.verbosity == f_console_verbosity_quiet) return;

  fll_print_format("%c%[%sInvalid parameter when calling %S().%]%c", output.to.stream, f_string_eol_s[0], output.context, output.prefix, function, output.context, f_string_eol_s[0]);
}

void firewall_print_error_on_invalid_parameter_for_file(const fll_error_print_t output, const f_string_t function, const f_string_t filename) {

  if (output.verbosity == f_console_verbosity_quiet) return;

  fll_print_format("%c%[%sInvalid parameter when calling %S() for the file '%S'.%]%c", output.to.stream, f_string_eol_s[0], output.context, output.prefix, function, filename, output.context, f_string_eol_s[0]);
}

void firewall_print_error_on_operation(const fll_error_print_t output, const f_string_t tool, const f_string_dynamics_t arguments) {

  if (output.verbosity == f_console_verbosity_quiet) return;

  flockfile(output.to.stream);

  fl_print_format("%c%[%sFailed to perform requested %s operation:%]", output.to.stream, f_string_eol_s[0], output.context, output.prefix, tool, output.context);
  fl_print_format("%c  %[%s", output.to.stream, f_string_eol_s[0], output.context, tool);

  for (f_array_length_t i = 0; i < arguments.used; ++i) {
    fl_print_format(" %Q", output.to.stream, arguments.array[i]);
  } // for

  fl_print_format("%]%c", output.to.stream, output.context, f_string_eol_s[0]);

  funlockfile(output.to.stream);
}

void firewall_print_error_on_unhandled(const fll_error_print_t output, const f_string_t function, const f_status_t status) {

  if (output.verbosity == f_console_verbosity_quiet) return;

  fll_print_format("%c%[%sAn unhandled error (%ui) has occurred while calling %S().%]%c", output.to.stream, f_string_eol_s[0], output.context, output.prefix, status, function, output.context, f_string_eol_s[0]);
}

void firewall_print_error_on_unhandled_for_file(const fll_error_print_t output, const f_string_t function, const f_status_t status, const f_string_t filename) {

  if (output.verbosity == f_console_verbosity_quiet) return;

  fll_print_format("%c%[%sAn unhandled error (%ui) has occurred while calling %S() for the file '%S'.%]%c", output.to.stream, f_string_eol_s[0], output.context, output.prefix, status, function, filename, output.context, f_string_eol_s[0]);
}

#ifdef __cplusplus
} // extern "C"
#endif
