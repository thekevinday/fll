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

#ifndef _di_fll_program_print_help_option_other_
  f_return_status fll_program_print_help_option_other(const fl_color_context context, const f_string option_other, const f_string description) {
    printf("%c  ", f_string_eol);
    fl_color_print(f_standard_output, context.standout, context.reset, option_other);

    printf("  %s", description);

    return f_none;
  }
#endif // _di_fll_program_print_help_option_other_

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

#ifndef _di_fll_program_parameter_process_
  f_return_status fll_program_parameter_process(const f_console_arguments arguments, f_console_parameters parameters, const f_console_parameter_ids choices, f_string_lengths *remaining, fl_color_context *context) {
    f_status status = f_none;

    status = f_console_parameter_process(arguments, parameters, remaining);

    f_console_parameter_id decision = choices.id[2];

    f_console_parameter_prioritize(parameters, choices, &decision);

    // load colors unless told not to.
    if (decision != choices.id[0]) {
      f_status allocation_status = f_none;

      fl_macro_color_context_new(allocation_status, (*context));

      if (f_status_is_error(allocation_status)) {
        fprintf(f_standard_error, "CRITICAL ERROR: Unable to allocate memory.\n");
        return allocation_status;
      }

      fl_color_load_context(context, decision == choices.id[1]);
    }

    if (f_status_is_error(status)) {
      status = f_status_set_fine(status);

      if (status == f_no_data) {
        fl_color_print_line(f_standard_error, context->error, context->reset, "ERROR: One of the parameters you passed requires an additional parameter that you did not pass.");
        // TODO: there is a way to identify which parameter is incorrect
        //       to do this, one must look for any "has_additional" and then see if the "additional" location is set to 0
        //       nothing can be 0 as that represents the program name, unless argv[] is improperly created
      }
      else if (status == f_error_allocation || status == f_error_reallocation) {
        fl_color_print_line(f_standard_error, context->error, context->reset, "CRITICAL ERROR: Unable to allocate memory.");
      }
      else if (status == f_invalid_utf) {
        fl_color_print(f_standard_error, context->error, context->reset, "ENCODING ERROR: Invalid UTF-8 character in parameter when calling ");
        fl_color_print(f_standard_error, context->notable, context->reset, "f_console_parameter_process()");
        fl_color_print_line(f_standard_error, context->error, context->reset, ".");
      }
      else if (status == f_invalid_parameter) {
        fl_color_print(f_standard_error, context->error, context->reset, "INTERNAL ERROR: Invalid parameter when calling ");
        fl_color_print(f_standard_error, context->notable, context->reset, "f_console_parameter_process()");
        fl_color_print_line(f_standard_error, context->error, context->reset, ".");
      }
      else {
        fl_color_print(f_standard_error, context->error, context->reset, "INTERNAL ERROR: An unhandled error (");
        fl_color_print(f_standard_error, context->notable, context->reset, "%u", status);
        fl_color_print(f_standard_error, context->error, context->reset, ") has occurred while calling ");
        fl_color_print(f_standard_error, context->notable, context->reset, "f_console_parameter_process()");
        fl_color_print_line(f_standard_error, context->error, context->reset, ".");
      }

      return f_status_set_error(status);
    }

    return status;
  }
#endif // _di_fll_program_parameter_process_

#ifndef _di_fll_program_parameter_additional_mash_
  f_return_status fll_program_parameter_additional_mash(const f_string glue, const f_string_length glue_length, const f_string *argv, const f_string_lengths additional, f_string_dynamic *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (argv == 0) return f_status_set_error(f_invalid_parameter);
      if (glue_length < 1) return f_status_set_error(f_invalid_parameter);
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status status = f_none;

    f_string_length length = 0;
    f_string_length start = destination->used;

    for (f_string_length i = 0; i < additional.used; i++) {
      length = strnlen(argv[additional.array[i]], f_console_max_size);

      if (length > 0) {
        status = fl_string_mash(glue, glue_length, argv[additional.array[i]], length, destination);

        if (f_status_is_error(status)) return f_status_set_error(f_string_too_large);
      }
    } // for

    if (status == f_none && start == destination->used) {
      return f_no_data;
    }

    return status;
  }
#endif // _di_fll_program_parameter_additional_mash_

#ifndef _di_fll_program_parameter_additional_mash_trim_
  f_return_status fll_program_parameter_additional_mash_trim(const f_string glue, const f_string_length glue_length, const f_string *argv, const f_string_lengths additional, f_string_dynamic *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (argv == 0) return f_status_set_error(f_invalid_parameter);
      if (glue_length < 1) return f_status_set_error(f_invalid_parameter);
      if (destination == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status status = f_none;

    f_string_length length = 0;
    f_string_length start = destination->used;
    f_string_dynamic ripped = f_string_dynamic_initialize;

    for (f_string_length i = 0; i < additional.used; i++) {
      length = strnlen(argv[additional.array[i]], f_console_max_size);

      if (length > 0) {
        status = fl_string_rip_trim(argv[additional.array[i]], 0, length - 1, &ripped);

        if (f_status_is_error(status)) {
          f_macro_string_dynamic_delete_simple(ripped);
          return status;
        }

        if (ripped.used > 0) {
          status = fl_string_dynamic_mash(glue, glue_length, ripped, destination);

          if (f_status_is_error(status)) {
            f_macro_string_dynamic_delete_simple(ripped);
            return f_status_set_error(f_string_too_large);
          }
        }
      }
    } // for

    if (ripped.size) {
      f_macro_string_dynamic_delete(status, ripped);
    }

    if (status == f_none && start == destination->used) {
      return f_no_data;
    }

    return status;
  }
#endif // _di_fll_program_parameter_additional_mash_trim_

#ifndef _di_fll_program_parameter_additional_rip_
  f_return_status fll_program_parameter_additional_rip(const f_string *argv, const f_string_lengths additional, f_string_dynamics *result) {
    #ifndef _di_level_2_parameter_checking_
      if (argv == 0) return f_status_set_error(f_invalid_parameter);
      if (result == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status status = f_none;

    f_string_length length = 0;
    f_string_length start = result->used;

    for (f_string_length i = 0; i < additional.used; i++) {
      length = strnlen(argv[additional.array[i]], f_console_max_size);

      if (length > 0) {
        f_string_dynamic ripped = f_string_dynamic_initialize;

        status = fl_string_rip(argv[additional.array[i]], 0, length - 1, &ripped);

        if (f_status_is_error(status)) return status;

        if (status == f_no_data) {
          status = f_none;
        }
        else {
          if (result->used >= result->size) {
            f_macro_string_dynamics_resize(status, (*result), result->size + f_console_default_allocation_step);

            if (f_status_is_error(status)) return status;
          }

          result->array[result->used] = ripped;
          result->used++;
        }
      }
    } // for

    if (status == f_none && start == result->used) {
      return f_no_data;
    }

    return status;
  }
#endif // _di_fll_program_parameter_additional_rip_

#ifndef _di_fll_program_parameter_additional_rip_trim_
  f_return_status fll_program_parameter_additional_rip_trim(const f_string *argv, const f_string_lengths additional, f_string_dynamics *result) {
    #ifndef _di_level_2_parameter_checking_
      if (argv == 0) return f_status_set_error(f_invalid_parameter);
      if (result == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status status = f_none;
    f_string_length length = 0;
    f_string_length start = result->used;

    for (f_string_length i = 0; i < additional.used; i++) {
      length = strnlen(argv[additional.array[i]], f_console_max_size);

      if (length > 0) {
        f_string_dynamic ripped = f_string_dynamic_initialize;

        status = fl_string_rip_trim(argv[additional.array[i]], 0, length - 1, &ripped);

        if (f_status_is_error(status)) return status;

        if (status == f_no_data) {
          status = f_none;
        }
        else {
          if (result->used >= result->size) {
            f_macro_string_dynamics_resize(status, (*result), result->size + f_console_default_allocation_step);

            if (f_status_is_error(status)) return status;
          }

          result->array[result->used] = ripped;
          result->used++;
        }
      }
    } // for

    if (status == f_none && start == result->used) {
      return f_no_data;
    }

    return status;
  }
#endif // _di_fll_program_parameter_additional_rip_trim_

#ifdef __cplusplus
} // extern "C"
#endif
