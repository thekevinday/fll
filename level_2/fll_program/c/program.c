#include <level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_program_print_help_header_
  f_return_status fll_program_print_help_header(const fl_color_context context, const f_string name, const f_string version) {
    printf("%c", f_string_eol[0]);
    fl_color_print(f_type_output, context.title, context.reset, " %s", name);

    printf("%c", f_string_eol[0]);
    fl_color_print(f_type_output, context.notable, context.reset, "  Version %s", version);

    printf("%c%c", f_string_eol[0], f_string_eol[0]);
    fl_color_print(f_type_output, context.important, context.reset, " Available Options: ");

    return F_none;
  }
#endif // _di_fll_program_print_help_header_

#ifndef _di_fll_program_print_help_option_
  f_return_status fll_program_print_help_option(const fl_color_context context, const f_string option_short, const f_string option_long, const f_string symbol_short, const f_string symbol_long, const f_string description) {
    printf("%c", f_string_eol[0]);
    printf("  %s", symbol_short);
    fl_color_print(f_type_output, context.standout, context.reset, option_short);

    printf(", %s", symbol_long);
    fl_color_print(f_type_output, context.standout, context.reset, option_long);
    printf("  %s", description);

    return F_none;
  }
#endif // _di_fll_program_print_help_option_

#ifndef _di_fll_program_print_help_option_long_
  f_return_status fll_program_print_help_option_long(const fl_color_context context, const f_string option_long, const f_string symbol_long, const f_string description) {
    printf("%c", f_string_eol[0]);
    printf("      %s", symbol_long);
    fl_color_print(f_type_output, context.standout, context.reset, option_long);
    printf("  %s", description);

    return F_none;
  }
#endif // _di_fll_program_print_help_option_long_

#ifndef _di_fll_program_print_help_option_other_
  f_return_status fll_program_print_help_option_other(const fl_color_context context, const f_string option_other, const f_string description) {
    printf("%c  ", f_string_eol[0]);
    fl_color_print(f_type_output, context.standout, context.reset, option_other);

    printf("  %s", description);

    return F_none;
  }
#endif // _di_fll_program_print_help_option_other_

#ifndef _di_fll_program_print_help_usage_
  f_return_status fll_program_print_help_usage(const fl_color_context context, const f_string name, const f_string parameters) {
    printf("%c%c", f_string_eol[0], f_string_eol[0]);
    fl_color_print(f_type_output, context.important, context.reset, " Usage:");

    printf("%c  ", f_string_eol[0]);
    fl_color_print(f_type_output, context.standout, context.reset, name);

    printf(" ");
    fl_color_print(f_type_output, context.notable, context.reset, "[");

    printf(" options ");
    fl_color_print(f_type_output, context.notable, context.reset, "]");

    if (parameters[0] != '\0') {
      printf(" ");
      fl_color_print(f_type_output, context.notable, context.reset, "[");

      printf(" %s ", parameters);
      fl_color_print(f_type_output, context.notable, context.reset, "]");
    }

    printf("%c%c", f_string_eol[0], f_string_eol[0]);
  }
#endif // _di_fll_program_print_help_usage_

#ifndef _di_fll_program_print_version_
  f_return_status fll_program_print_version(const f_string version) {
    printf("%s%c", version, f_string_eol[0]);

    return F_none;
  }
#endif // _di_fll_program_print_version_

#ifndef _di_fll_program_parameter_process_
  f_return_status fll_program_parameter_process(const f_console_arguments arguments, f_console_parameters parameters, const f_console_parameter_ids choices, const bool right, f_string_lengths *remaining, fl_color_context *context) {
    f_status status = F_none;

    status = f_console_parameter_process(arguments, parameters, remaining);

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_data_not) {
        fl_color_print_line(f_type_error, context->error, context->reset, "ERROR: One of the parameters you passed requires an additional parameter that you did not pass.");
        // @todo there is a way to identify which parameter is incorrect
        //       to do this, one must look for any "has_additional" and then see if the "additional" location is set to 0
        //       nothing can be 0 as that represents the program name, unless argv[] is improperly created
      }
      else if (status == F_memory_allocation || status == F_memory_reallocation) {
        fl_color_print(f_type_error, context->error, context->reset, "CRITICAL ERROR: Unable to allocate memory while calling ");
        fl_color_print(f_type_error, context->notable, context->reset, "f_console_parameter_process");
        fl_color_print_line(f_type_error, context->error, context->reset, ").");
      }
      else if (status == F_utf) {
        fl_color_print(f_type_error, context->error, context->reset, "ENCODING ERROR: Invalid UTF-8 character in parameter when calling ");
        fl_color_print(f_type_error, context->notable, context->reset, "f_console_parameter_process()");
        fl_color_print_line(f_type_error, context->error, context->reset, ".");
      }
      else if (status == F_parameter) {
        fl_color_print(f_type_error, context->error, context->reset, "INTERNAL ERROR: Invalid parameter when calling ");
        fl_color_print(f_type_error, context->notable, context->reset, "f_console_parameter_process()");
        fl_color_print_line(f_type_error, context->error, context->reset, ".");
      }
      else {
        fl_color_print(f_type_error, context->error, context->reset, "INTERNAL ERROR: An unhandled error (");
        fl_color_print(f_type_error, context->notable, context->reset, "%u", status);
        fl_color_print(f_type_error, context->error, context->reset, ") has occurred while calling ");
        fl_color_print(f_type_error, context->notable, context->reset, "f_console_parameter_process()");
        fl_color_print_line(f_type_error, context->error, context->reset, ".");
      }

      return F_status_set_error(status);
    }

    f_console_parameter_id decision = choices.id[2];

    f_string function;

    if (right) {
      function = "f_console_parameter_prioritize_right";
      status = f_console_parameter_prioritize_right(parameters, choices, &decision);
    }
    else {
      function = "f_console_parameter_prioritize_left";
      status = f_console_parameter_prioritize_left(parameters, choices, &decision);
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_memory_allocation || status == F_memory_reallocation) {
        fl_color_print(f_type_error, context->error, context->reset, "CRITICAL ERROR: Unable to allocate memory while calling ");
        fl_color_print(f_type_error, context->notable, context->reset, "%s", function);
        fl_color_print_line(f_type_error, context->error, context->reset, ").");
      }
      else if (status == F_parameter) {
        fl_color_print(f_type_error, context->error, context->reset, "INTERNAL ERROR: Invalid parameter when calling ");
        fl_color_print(f_type_error, context->notable, context->reset, "%s", function);
        fl_color_print_line(f_type_error, context->error, context->reset, "().");
      }
      else {
        fl_color_print(f_type_error, context->error, context->reset, "INTERNAL ERROR: An unhandled error (");
        fl_color_print(f_type_error, context->notable, context->reset, "%u", status);
        fl_color_print(f_type_error, context->error, context->reset, ") has occurred while calling ");
        fl_color_print(f_type_error, context->notable, context->reset, "%s", function);
        fl_color_print_line(f_type_error, context->error, context->reset, "().");
      }

      return F_status_set_error(status);
    }

    // load colors unless told not to.
    if (decision != choices.id[0]) {
      f_status allocation_status = F_none;

      fl_macro_color_context_new(allocation_status, (*context));

      if (F_status_is_error(allocation_status)) {
        fl_color_print(f_type_error, context->error, context->reset, "CRITICAL ERROR: Unable to allocate memory while calling ");
        fl_color_print(f_type_error, context->notable, context->reset, "fl_macro_color_context_new");
        fl_color_print_line(f_type_error, context->error, context->reset, "().");

        return allocation_status;
      }

      status = fl_color_load_context(context, decision == choices.id[1]);
    }
    else {
      context->mode = f_color_mode_no_color;
    }

    return status;
  }
#endif // _di_fll_program_parameter_process_

#ifndef _di_fll_program_parameter_process_quietly_
  f_return_status fll_program_parameter_process_quietly(const f_console_arguments arguments, f_console_parameters parameters, const f_console_parameter_ids choices, const bool right, f_string_lengths *remaining, fl_color_context *context) {
    f_status status = F_none;

    status = f_console_parameter_process(arguments, parameters, remaining);

    if (F_status_is_error(status)) return status;

    f_console_parameter_id decision = choices.id[2];

    if (right) {
      status = f_console_parameter_prioritize_right(parameters, choices, &decision);
    }
    else {
      status = f_console_parameter_prioritize_left(parameters, choices, &decision);
    }

    if (F_status_is_error(status)) return status;

    // load colors unless told not to.
    if (decision != choices.id[0]) {
      f_status allocation_status = F_none;

      fl_macro_color_context_new(allocation_status, (*context));

      if (F_status_is_error(allocation_status)) return allocation_status;

      status = fl_color_load_context(context, decision == choices.id[1]);
    }

    return status;
  }
#endif // _di_fll_program_parameter_process_quietly_

#ifndef _di_fll_program_parameter_additional_append_
  f_return_status fll_program_parameter_additional_append(const f_string *argv, const f_string_lengths additional, f_string_dynamics *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (argv == 0) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status status = F_none;

    f_string_length length = 0;
    f_string_length start = destination->used;

    for (f_string_length i = 0; i < additional.used; i++) {
      length = strnlen(argv[additional.array[i]], f_console_length_size);

      if (length > 0) {
        f_string_dynamic ripped = f_string_dynamic_initialize;

        status = fl_string_append(argv[additional.array[i]], length, &ripped);

        if (F_status_is_error(status)) return status;

        if (status == F_data_not) {
          status = F_none;
        }
        else {
          if (destination->used >= destination->size) {
            f_macro_string_dynamics_resize(status, (*destination), destination->size + f_console_default_allocation_step);

            if (F_status_is_error(status)) return status;
          }

          destination->array[destination->used] = ripped;
          destination->used++;
        }
      }
    } // for

    if (status == F_none && start == destination->used) {
      return F_data_not;
    }

    return status;
  }
#endif // _di_fll_program_parameter_additional_append_

#ifndef _di_fll_program_parameter_additional_mash_
  f_return_status fll_program_parameter_additional_mash(const f_string glue, const f_string_length glue_length, const f_string *argv, const f_string_lengths additional, f_string_dynamic *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (argv == 0) return F_status_set_error(F_parameter);
      if (glue_length < 1) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status status = F_none;

    f_string_length length = 0;
    f_string_length start = destination->used;

    for (f_string_length i = 0; i < additional.used; i++) {
      length = strnlen(argv[additional.array[i]], f_console_length_size);

      if (length > 0) {
        status = fl_string_mash(glue, glue_length, argv[additional.array[i]], length, destination);

        if (F_status_is_error(status)) return F_status_set_error(F_string_too_large);
      }
    } // for

    if (status == F_none && start == destination->used) {
      return F_data_not;
    }

    return status;
  }
#endif // _di_fll_program_parameter_additional_mash_

#ifndef _di_fll_program_parameter_additional_rip_
  f_return_status fll_program_parameter_additional_rip(const f_string *argv, const f_string_lengths additional, f_string_dynamics *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (argv == 0) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status status = F_none;
    f_string_length length = 0;
    f_string_length start = destination->used;

    for (f_string_length i = 0; i < additional.used; i++) {
      length = strnlen(argv[additional.array[i]], f_console_length_size);

      if (length > 0) {
        f_string_dynamic ripped = f_string_dynamic_initialize;

        status = fl_string_rip(argv[additional.array[i]], length, &ripped);

        if (F_status_is_error(status)) return status;

        if (status == F_data_not) {
          status = F_none;
        }
        else {
          if (destination->used >= destination->size) {
            f_macro_string_dynamics_resize(status, (*destination), destination->size + f_console_default_allocation_step);

            if (F_status_is_error(status)) return status;
          }

          destination->array[destination->used] = ripped;
          destination->used++;
        }
      }
    } // for

    if (status == F_none && start == destination->used) {
      return F_data_not;
    }

    return status;
  }
#endif // _di_fll_program_parameter_additional_rip_

#ifndef _di_fll_program_parameter_additional_rip_mash_
  f_return_status fll_program_parameter_additional_rip_mash(const f_string glue, const f_string_length glue_length, const f_string *argv, const f_string_lengths additional, f_string_dynamic *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (argv == 0) return F_status_set_error(F_parameter);
      if (glue_length < 1) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status status = F_none;

    f_string_length length = 0;
    f_string_length start = destination->used;
    f_string_dynamic ripped = f_string_dynamic_initialize;

    for (f_string_length i = 0; i < additional.used; i++) {
      length = strnlen(argv[additional.array[i]], f_console_length_size);

      if (length > 0) {
        status = fl_string_rip(argv[additional.array[i]], length, &ripped);

        if (F_status_is_error(status)) {
          f_macro_string_dynamic_delete_simple(ripped);
          return status;
        }

        if (ripped.used > 0) {
          status = fl_string_dynamic_mash(glue, glue_length, ripped, destination);

          if (F_status_is_error(status)) {
            f_macro_string_dynamic_delete_simple(ripped);
            return F_status_set_error(F_string_too_large);
          }
        }
      }
    } // for

    if (ripped.size) {
      f_macro_string_dynamic_delete(status, ripped);
    }

    if (status == F_none && start == destination->used) {
      return F_data_not;
    }

    return status;
  }
#endif // _di_fll_program_parameter_additional_rip_mash_

#ifdef __cplusplus
} // extern "C"
#endif
