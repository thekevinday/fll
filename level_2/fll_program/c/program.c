#include "program.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_program_print_help_header_
  f_status_t fll_program_print_help_header(const f_file_t file, const f_color_context_t context, const f_string_t name, const f_string_t version) {

    fprintf(file.stream, "%c", f_string_eol_s[0]);
    fl_color_print(file.stream, context.set.title, " %s", name);

    fprintf(file.stream, "%c", f_string_eol_s[0]);
    fl_color_print(file.stream, context.set.notable, "  Version %s", version);

    fprintf(file.stream, "%c%c", f_string_eol_s[0], f_string_eol_s[0]);
    fl_color_print(file.stream, context.set.important, " Available Options: ");

    return F_none;
  }
#endif // _di_fll_program_print_help_header_

#ifndef _di_fll_program_print_help_option_
  f_status_t fll_program_print_help_option(const f_file_t file, const f_color_context_t context, const f_string_t option_short, const f_string_t option_long, const f_string_t symbol_short, const f_string_t symbol_long, const f_string_t description) {

    fprintf(file.stream, "%c  %s", f_string_eol_s[0], symbol_short);
    fl_color_print(file.stream, context.set.standout, option_short);

    fprintf(file.stream, ", %s", symbol_long);
    fl_color_print(file.stream, context.set.standout, option_long);

    fprintf(file.stream, "  %s", description);

    return F_none;
  }
#endif // _di_fll_program_print_help_option_

#ifndef _di_fll_program_print_help_option_long_
  f_status_t fll_program_print_help_option_long(const f_file_t file, const f_color_context_t context, const f_string_t option_long, const f_string_t symbol_long, const f_string_t description) {

    fprintf(file.stream, "%c      %s", f_string_eol_s[0], symbol_long);
    fl_color_print(file.stream, context.set.standout, option_long);

    fprintf(file.stream, "  %s", description);

    return F_none;
  }
#endif // _di_fll_program_print_help_option_long_

#ifndef _di_fll_program_print_help_option_other_
  f_status_t fll_program_print_help_option_other(const f_file_t file, const f_color_context_t context, const f_string_t option_other, const f_string_t description) {

    fprintf(file.stream, "%c  ", f_string_eol_s[0]);
    fl_color_print(file.stream, context.set.standout, option_other);

    fprintf(file.stream, "  %s", description);

    return F_none;
  }
#endif // _di_fll_program_print_help_option_other_

#ifndef _di_fll_program_print_help_usage_
  f_status_t fll_program_print_help_usage(const f_file_t file, const f_color_context_t context, const f_string_t name, const f_string_t parameters) {

    fprintf(file.stream, "%c%c", f_string_eol_s[0], f_string_eol_s[0]);
    fl_color_print(file.stream, context.set.important, " Usage:");

    fprintf(file.stream, "%c  ", f_string_eol_s[0]);
    fl_color_print(file.stream, context.set.standout, name);

    fprintf(file.stream, f_string_space_s);
    fl_color_print(file.stream, context.set.notable, "[");

    fprintf(file.stream, " options ");
    fl_color_print(file.stream, context.set.notable, "]");

    if (parameters[0] != '\0') {
      fprintf(file.stream, f_string_space_s);
      fl_color_print(file.stream, context.set.notable, "[");

      fprintf(file.stream, " %s ", parameters);
      fl_color_print(file.stream, context.set.notable, "]");
    }

    fprintf(file.stream, "%c%c", f_string_eol_s[0], f_string_eol_s[0]);

    return F_none;
  }
#endif // _di_fll_program_print_help_usage_

#ifndef _di_fll_program_print_version_
  f_status_t fll_program_print_version(const f_file_t file, const f_string_t version) {

    fprintf(file.stream, "%s%c", version, f_string_eol_s[0]);

    return F_none;
  }
#endif // _di_fll_program_print_version_

#ifndef _di_fll_program_parameter_process_
  f_status_t fll_program_parameter_process(const f_console_arguments_t arguments, f_console_parameters_t parameters, const f_console_parameter_ids_t choices, const bool right, f_string_lengths_t *remaining, f_color_context_t *context) {
    f_status_t status = F_none;

    status = f_console_parameter_process(arguments, parameters, remaining);
    if (F_status_is_error(status)) return status;

    f_console_parameter_id_t decision = choices.id[2];

    if (right) {
      status = f_console_parameter_prioritize_right(parameters, choices, &decision);
    }
    else {
      status = f_console_parameter_prioritize_left(parameters, choices, &decision);
    }

    if (F_status_is_error(status)) return status;

    // load colors unless told not to.
    if (decision != choices.id[0]) {
      f_status_t allocation_status = F_none;

      f_macro_color_context_t_new(allocation_status, (*context));
      if (F_status_is_error(status)) return status;

      status = fl_color_load_context(context, decision == choices.id[1]);
    }
    else {
      context->mode = f_color_mode_no_color;
    }

    return status;
  }
#endif // _di_fll_program_parameter_process_

#ifndef _di_fll_program_parameter_additional_append_
  f_status_t fll_program_parameter_additional_append(const f_string_t *argv, const f_array_lengths_t values, f_string_dynamics_t *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!argv) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    f_string_length_t length = 0;
    const f_string_length_t start = destination->used;

    for (f_string_length_t i = 0; i < values.used; i++) {

      length = strnlen(argv[values.array[i]], f_console_length_size);

      if (length > 0) {
        f_string_dynamic_t ripped = f_string_dynamic_t_initialize;

        status = fl_string_append(argv[values.array[i]], length, &ripped);
        if (F_status_is_error(status)) return status;

        if (status == F_data_not) {
          status = F_none;
        }
        else {
          f_macro_memory_structure_macro_increment(status, (*destination), 1, f_memory_default_allocation_step, f_macro_string_dynamics_t_resize, F_array_too_large);
          if (F_status_is_error(status)) break;

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
  f_status_t fll_program_parameter_additional_mash(const f_string_t glue, const f_string_length_t glue_length, const f_string_t *argv, const f_array_lengths_t values, f_string_dynamic_t *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!argv) return F_status_set_error(F_parameter);
      if (glue_length < 1) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    f_string_length_t length = 0;
    const f_string_length_t start = destination->used;

    for (f_string_length_t i = 0; i < values.used; i++) {

      length = strnlen(argv[values.array[i]], f_console_length_size);

      if (length > 0) {
        status = fl_string_mash(glue, glue_length, argv[values.array[i]], length, destination);
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
  f_status_t fll_program_parameter_additional_rip(const f_string_t *argv, const f_array_lengths_t values, f_string_dynamics_t *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!argv) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    f_string_length_t length = 0;
    const f_string_length_t start = destination->used;

    for (f_string_length_t i = 0; i < values.used; i++) {

      length = strnlen(argv[values.array[i]], f_console_length_size);

      if (length > 0) {
        f_string_dynamic_t ripped = f_string_dynamic_t_initialize;

        status = fl_string_rip(argv[values.array[i]], length, &ripped);
        if (F_status_is_error(status)) return status;

        if (status == F_data_not) {
          status = F_none;
        }
        else {
          if (destination->used == destination->size) {
            f_macro_string_dynamics_t_resize(status, (*destination), destination->size + f_memory_default_allocation_step);
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
  f_status_t fll_program_parameter_additional_rip_mash(const f_string_t glue, const f_string_length_t glue_length, const f_string_t *argv, const f_array_lengths_t values, f_string_dynamic_t *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!argv) return F_status_set_error(F_parameter);
      if (glue_length < 1) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    f_string_length_t length = 0;
    const f_string_length_t start = destination->used;
    f_string_dynamic_t ripped = f_string_dynamic_t_initialize;

    for (f_string_length_t i = 0; i < values.used; i++) {

      length = strnlen(argv[values.array[i]], f_console_length_size);

      if (length > 0) {
        status = fl_string_rip(argv[values.array[i]], length, &ripped);

        if (F_status_is_error(status)) {
          fl_string_dynamic_delete(&ripped);
          return status;
        }

        if (ripped.used > 0) {
          status = fl_string_dynamic_mash(glue, glue_length, ripped, destination);

          if (F_status_is_error(status)) {
            fl_string_dynamic_delete(&ripped);
            return F_status_set_error(F_string_too_large);
          }
        }
      }
    } // for

    if (ripped.size) {
      status = fl_string_dynamic_delete(&ripped);
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
