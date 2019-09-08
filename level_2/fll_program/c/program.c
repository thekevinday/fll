#include <level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_program_print_help_header_
  f_return_status fll_program_print_help_header(const fl_color_context context, const f_string name, const f_string version) {
    printf("%c", f_string_eol);
    fl_color_print(f_standard_output, context.title, context.reset, " %s", name);

    printf("%c", f_string_eol);
    fl_color_print(f_standard_output, context.notable, context.reset, "  Version %s", version);

    printf("%c%c", f_string_eol, f_string_eol);
    fl_color_print(f_standard_output, context.important, context.reset, " Available Options: ");

    return f_none;
  }
#endif // _di_fll_program_print_help_header_

#ifndef _di_fll_program_print_help_option_
  f_return_status fll_program_print_help_option(const fl_color_context context, const f_string option_short, const f_string option_long, const f_string symbol_short, const f_string symbol_long, const f_string description) {
    printf("%c", f_string_eol);
    printf("  %s", symbol_short);
    fl_color_print(f_standard_output, context.standout, context.reset, option_short);

    printf(", %s", symbol_long);
    fl_color_print(f_standard_output, context.standout, context.reset, option_long);
    printf("  %s", description);

    return f_none;
  }
#endif // _di_fll_program_print_help_option_

#ifndef _di_fll_program_print_help_option_long_
  f_return_status fll_program_print_help_option_long(const fl_color_context context, const f_string option_long, const f_string symbol_long, const f_string description) {
    printf("%c", f_string_eol);
    printf("      %s", symbol_long);
    fl_color_print(f_standard_output, context.standout, context.reset, option_long);
    printf("  %s", description);

    return f_none;
  }
#endif // _di_fll_program_print_help_option_long_

#ifndef _di_fll_program_print_help_usage_
  f_return_status fll_program_print_help_usage(const fl_color_context context, const f_string name, const f_string parameters) {
    printf("%c%c", f_string_eol, f_string_eol);
    fl_color_print(f_standard_output, context.important, context.reset, " Usage:");

    printf("%c  ", f_string_eol);
    fl_color_print(f_standard_output, context.standout, context.reset, name);

    printf(" ");
    fl_color_print(f_standard_output, context.notable, context.reset, "[");

    printf(" options ");
    fl_color_print(f_standard_output, context.notable, context.reset, "]");

    if (parameters[0] != '\0') {
      printf(" ");
      fl_color_print(f_standard_output, context.notable, context.reset, "[");

      printf(" %s ", parameters);
      fl_color_print(f_standard_output, context.notable, context.reset, "]");
    }

    printf("%c%c", f_string_eol, f_string_eol);
  }
#endif // _di_fll_program_print_help_usage_

#ifndef _di_fll_program_print_version_
  f_return_status fll_program_print_version(const f_string version) {
    printf("%s%c", version, f_string_eol);

    return f_none;
  }
#endif // _di_fll_program_print_version_

#ifndef _di_fll_program_process_parameters_
  f_return_status fll_program_process_parameters(const f_array_length argc, const f_string argv[], f_console_parameter parameters[], const f_array_length parameters_total, const f_array_length parameter_no_color, const f_array_length parameter_light, const f_array_length parameter_dark, f_string_lengths *remaining, fl_color_context *context) {
    f_status status = f_none;
    f_status allocation_status = f_none;

    status = fl_console_parameter_process(argc, argv, parameters, parameters_total, remaining);

    f_console_parameter_ids choices = f_console_parameter_ids_initialize;
    f_console_parameter_id decision = parameter_dark;
    f_console_parameter_id ids[3] = { parameter_no_color, parameter_light, parameter_dark};

    choices.ids = ids;
    choices.used = 3;

    fl_console_parameter_prioritize(parameters, parameters_total, choices, &decision);

    // load colors unless told not to.
    if (decision != parameter_no_color) {
      fl_macro_color_context_new(allocation_status, (*context));

      if (f_status_is_error(allocation_status)) {
        fprintf(f_standard_error, "Critical Error: unable to allocate memory.\n");
        return allocation_status;
      }

      fl_color_load_context(context, decision == parameter_light);
    }

    if (f_status_is_error(status)) {
      status = f_status_set_fine(status);

      if (status == f_no_data) {
        fl_color_print_line(f_standard_error, context->error, context->reset, "ERROR: One of the parameters you passed requires an additional parameter that you did not pass.");
        // TODO: there is a way to identify which parameter is incorrect
        //       to do this, one must look for any "has_additional" and then see if the "additional" location is set to 0
        //       nothing can be 0 as that represents the program name, unless argv[] is improperly created
      }
      else if (status == f_allocation_error || status == f_reallocation_error) {
        fl_color_print_line(f_standard_error, context->error, context->reset, "CRITICAL ERROR: unable to allocate memory.");
      }
      else if (status == f_invalid_parameter) {
        fl_color_print_line(f_standard_error, context->error, context->reset, "INTERNAL ERROR: Invalid parameter when calling fl_console_parameter_process().");
      }
      else {
        fl_color_print_line(f_standard_error, context->error, context->reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fl_console_parameter_process().", status);
      }

      return f_status_set_error(status);
    }

    return status;
  }
#endif // _di_fll_program_process_parameters_

#ifdef __cplusplus
} // extern "C"
#endif
