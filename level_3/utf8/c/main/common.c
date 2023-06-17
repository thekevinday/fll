#include "utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_setting_load_
  void utf8_setting_load(const f_console_arguments_t arguments, utf8_main_t * const main) {

    if (!main) return;

    main->setting.state.step_small = utf8_allocation_console_d;

    f_console_parameter_process(arguments, &main->program.parameters, &main->setting.state, 0);

    main->setting.state.step_small = utf8_allocation_small_d;

    // Identify and pocess first/last parameters.
    if (main->program.parameters.array[utf8_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & utf8_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= utf8_main_flag_print_first_e;
    }

    if (main->program.parameters.array[utf8_parameter_line_last_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & utf8_main_flag_print_last_e;
    }
    else {
      main->setting.flag |= utf8_main_flag_print_last_e;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      utf8_print_error(&main->program.error, macro_utf8_f(f_console_parameter_process));

      return;
    }

    {
      f_number_unsigned_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { utf8_parameter_no_color_e, utf8_parameter_light_e, utf8_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        static const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        main->setting.state.status = fll_program_parameter_process_context(choices, modes, F_true, &main->program);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          utf8_print_error(&main->program.error, macro_utf8_f(fll_program_parameter_process_context));

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { utf8_parameter_verbosity_quiet_e, utf8_parameter_verbosity_error_e, utf8_parameter_verbosity_verbose_e, utf8_parameter_verbosity_debug_e, utf8_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        static const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        main->setting.state.status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, &main->program);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          utf8_print_error(&main->program.error, macro_utf8_f(fll_program_parameter_process_verbosity));

          return;
        }
      }

      // Identify and prioritize "from" mode parameters.
      {
        uint16_t choices_array[2] = { utf8_parameter_from_bytesequence_e, utf8_parameter_from_codepoint_e };
        choices.array = choices_array;
        choices.used = 2;

        main->setting.state.status = f_console_parameter_prioritize_right(main->program.parameters, choices, &choice);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          utf8_print_error(&main->program.error, macro_utf8_f(f_console_parameter_prioritize_right));

          return;
        }

        if (choices.array[choice] == utf8_parameter_from_bytesequence_e) {
          main->setting.mode -= main->setting.mode & utf8_mode_from_codepoint_e;
          main->setting.mode |= utf8_mode_from_bytesequence_e;
        }
        else if (choices.array[choice] == utf8_parameter_from_codepoint_e) {
          main->setting.mode -= main->setting.mode & utf8_mode_from_bytesequence_e;
          main->setting.mode |= utf8_mode_from_codepoint_e;
        }
      }

      // Identify and prioritize "to" mode parameters.
      {
        uint16_t choices_array[4] = { utf8_parameter_to_bytesequence_e, utf8_parameter_to_codepoint_e, utf8_parameter_to_combining_e, utf8_parameter_to_width_e };
        choices.array = choices_array;
        choices.used = 4;
        choice = 1;

        main->setting.state.status = f_console_parameter_prioritize_right(main->program.parameters, choices, &choice);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          utf8_print_error(&main->program.error, macro_utf8_f(f_console_parameter_prioritize_right));

          return;
        }

        if (choices.array[choice] == utf8_parameter_to_bytesequence_e) {
          main->setting.mode -= main->setting.mode & utf8_mode_to_codepoint_e;
          main->setting.mode -= main->setting.mode & utf8_mode_to_combining_e;
          main->setting.mode -= main->setting.mode & utf8_mode_to_width_e;

          main->setting.mode |= utf8_mode_to_bytesequence_e;
        }
        else if (choices.array[choice] == utf8_parameter_to_codepoint_e) {
          main->setting.mode -= main->setting.mode & utf8_mode_to_bytesequence_e;
          main->setting.mode -= main->setting.mode & utf8_mode_to_combining_e;
          main->setting.mode -= main->setting.mode & utf8_mode_to_width_e;

          main->setting.mode |= utf8_mode_to_codepoint_e;
        }
        else if (choices.array[choice] == utf8_parameter_to_combining_e) {
          main->setting.mode -= main->setting.mode & utf8_mode_to_bytesequence_e;
          main->setting.mode -= main->setting.mode & utf8_mode_to_codepoint_e;

          // --to_width may be specified with --to_combining.
          if (main->program.parameters.array[utf8_parameter_to_width_e].result & f_console_result_found_e) {
            main->setting.mode |= utf8_mode_to_width_e;
          }

          main->setting.mode |= utf8_mode_to_combining_e;
        }
        else if (choices.array[choice] == utf8_parameter_to_width_e) {
          main->setting.mode -= main->setting.mode & utf8_mode_to_bytesequence_e;
          main->setting.mode -= main->setting.mode & utf8_mode_to_codepoint_e;

          // --to_width may be specified with --to_combining.
          if (main->program.parameters.array[utf8_parameter_to_combining_e].result & f_console_result_found_e) {
            main->setting.mode |= utf8_mode_to_combining_e;
          }

          main->setting.mode |= utf8_mode_to_width_e;
        }
      }
    }

    if (main->program.parameters.array[utf8_parameter_help_e].result & f_console_result_found_e) {
      main->setting.flag |= utf8_main_flag_help_e;

      return;
    }

    if (main->program.parameters.array[utf8_parameter_version_e].result & f_console_result_found_e) {
      main->setting.flag |= utf8_main_flag_version_e;

      return;
    }

    if (main->program.parameters.array[utf8_parameter_copyright_e].result & f_console_result_found_e) {
      main->setting.flag |= utf8_main_flag_copyright_e;

      return;
    }

    if (main->program.parameters.array[utf8_parameter_to_file_e].result & f_console_result_value_e) {
      if (main->program.parameters.array[utf8_parameter_to_file_e].values.used > 1) {
        main->setting.state.status = F_status_set_error(F_parameter);

        if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        utf8_print_error_parameter_file_to_too_many(&main->program.error);

        return;
      }

      if (main->program.parameters.arguments.array[main->program.parameters.array[utf8_parameter_to_file_e].values.array[0]].used) {
        main->setting.path_files_to.used = 0;

        main->setting.state.status = f_string_dynamics_increase_by(1, &main->setting.path_files_to);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          utf8_print_error(&main->program.error, macro_utf8_f(f_string_dynamics_increase_by));

          return;
        }

        main->setting.path_files_to.array[main->setting.path_files_to.used].used = 0;

        main->setting.state.status = f_string_dynamic_append_nulless(main->program.parameters.arguments.array[main->program.parameters.array[utf8_parameter_to_file_e].values.array[0]], &main->setting.path_files_to.array[0]);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          utf8_print_error(&main->program.error, macro_utf8_f(f_string_dynamic_append_nulless));

          return;
        }

        ++main->setting.path_files_to.used;

        main->setting.state.status = f_file_stream_open(main->program.parameters.arguments.array[main->program.parameters.array[utf8_parameter_to_file_e].values.array[0]], f_file_open_mode_append_s, &main->program.output.to);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          utf8_print_error_file(&main->program.error, macro_utf8_f(f_file_stream_open), main->program.parameters.arguments.array[main->program.parameters.array[utf8_parameter_to_file_e].values.array[0]], f_file_operation_open_s, fll_error_file_type_file_e);

          return;
        }

        main->setting.flag |= utf8_main_flag_file_to_e;
      }
      else {
        if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        utf8_print_error_parameter_file_name_empty(&main->program.error, main->program.parameters.array[utf8_parameter_to_file_e].values.array[0]);

        main->setting.state.status = F_status_set_error(F_parameter);

        return;
      }
    }
    else if (main->program.parameters.array[utf8_parameter_to_file_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

        if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, utf8_long_to_file_s);

      return;
    }
    else {
      main->program.output.to = main->program.message.to;
      main->setting.flag -= main->setting.flag & utf8_main_flag_file_to_e;
    }

    if (main->program.parameters.array[utf8_parameter_from_file_e].result & f_console_result_value_e) {
      main->setting.path_files_from.used = 0;

      main->setting.state.status = f_string_dynamics_increase_by(main->program.parameters.array[utf8_parameter_from_file_e].values.used, &main->setting.path_files_from);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        utf8_print_error(&main->program.error, macro_utf8_f(f_string_dynamics_increase_by));

        return;
      }

      main->setting.path_files_from.used = main->program.parameters.array[utf8_parameter_from_file_e].values.used;

      f_number_unsigned_t i = 0;
      f_number_unsigned_t index = 0;

      for (; i < main->setting.path_files_from.used; ++i) {

        index = main->program.parameters.array[utf8_parameter_from_file_e].values.array[i];
        main->setting.path_files_from.array[i].used = 0;

        main->setting.state.status = f_string_dynamic_append_nulless(main->program.parameters.arguments.array[index], &main->setting.path_files_from.array[i]);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_error_print(&main->program.error, F_status_set_fine(main->setting.state.status), macro_utf8_f(f_string_dynamic_append_nulless), fll_error_file_flag_fallback_e);

          break;
        }

        if (main->program.parameters.arguments.array[index].used) {
          if (f_file_exists(main->program.parameters.arguments.array[index], F_true) != F_true) {
            utf8_print_error_parameter_file_not_found(&main->program.error, F_true, main->program.parameters.arguments.array[index]);

            if (F_status_is_error_not(main->setting.state.status)) {
              main->setting.state.status = F_status_set_error(F_file_found_not);
            }
          }
        }
        else {
          if (F_status_is_error_not(main->setting.state.status)) {
            if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }
          }

          utf8_print_error_parameter_file_name_empty(&main->program.error, index);

          if (F_status_is_error_not(main->setting.state.status)) {
            main->setting.state.status = F_status_set_error(F_parameter);
          }
        }
      } // for

      if (F_status_is_error(main->setting.state.status)) return;

      main->setting.flag |= utf8_main_flag_file_from_e;
    }
    else if (main->program.parameters.array[utf8_parameter_from_file_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, utf8_long_from_file_s);

      return;
    }
    else {
      main->setting.flag -= main->setting.flag & utf8_main_flag_file_from_e;
    }

    if (main->program.parameters.remaining.used) {
      main->setting.remaining.used = 0;

      main->setting.state.status = f_string_dynamics_increase_by(main->program.parameters.remaining.used, &main->setting.remaining);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        utf8_print_error(&main->program.error, macro_utf8_f(f_string_dynamics_increase_by));

        return;
      }

      // Construct the array without allocating any more memory by setting this as a static string (used > 0, size = 0).
      for (f_number_unsigned_t index = 0; main->setting.remaining.used < main->program.parameters.remaining.used; ) {

        index = main->program.parameters.remaining.array[main->setting.remaining.used];

        main->setting.remaining.array[main->setting.remaining.used].string = main->program.parameters.arguments.array[index].string;
        main->setting.remaining.array[main->setting.remaining.used].used = main->program.parameters.arguments.array[index].used;
        main->setting.remaining.array[main->setting.remaining.used++].size = 0;
      } // for
    }

    if (!(main->program.parameters.array[utf8_parameter_from_file_e].result & f_console_result_found_e) && !((main->program.pipe & fll_program_data_pipe_input_e) || main->program.parameters.remaining.used)) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      utf8_print_error_no_from(&main->program.error);

      return;
    }

    if (!(main->setting.mode & utf8_mode_to_bytesequence_e)) {
      if ((main->program.parameters.array[utf8_parameter_separate_e].result & f_console_result_found_e) || (main->program.parameters.array[utf8_parameter_headers_e].result & f_console_result_found_e)) {
        main->setting.prepend = utf8_string_prepend_padding_s;
        main->setting.append = f_string_eol_s;
      }
      else {
        main->setting.prepend = f_string_space_s;
      }
    }

    if (main->program.parameters.array[utf8_parameter_headers_e].result & f_console_result_found_e) {
      if (main->program.parameters.array[utf8_parameter_separate_e].result & f_console_result_found_e) {
        if (main->program.parameters.array[utf8_parameter_headers_e].location < main->program.parameters.array[utf8_parameter_separate_e].location) {
          main->setting.flag |= utf8_main_flag_separate_e;
        }
        else if (main->program.parameters.array[utf8_parameter_headers_e].location == main->program.parameters.array[utf8_parameter_separate_e].location) {
          if (main->program.parameters.array[utf8_parameter_headers_e].location_sub < main->program.parameters.array[utf8_parameter_separate_e].location_sub) {
            main->setting.flag |= utf8_main_flag_separate_e;
          }
          else {
            main->setting.flag |= utf8_main_flag_header_e;
          }
        }
        else {
          main->setting.flag |= utf8_main_flag_header_e;
        }
      }
      else {
        main->setting.flag |= utf8_main_flag_header_e;
      }
    }
    else if (main->program.parameters.array[utf8_parameter_separate_e].result & f_console_result_found_e) {
      main->setting.flag |= utf8_main_flag_separate_e;
    }

    if (main->program.parameters.array[utf8_parameter_strip_invalid_e].result & f_console_result_found_e) {
      main->setting.flag |= utf8_main_flag_strip_invalid_e;
    }

    main->setting.valid_not = main->program.message.set->error;

    if (main->program.pipe & fll_program_data_pipe_input_e) {
      main->setting.flag |= utf8_main_flag_pipe_e;
    }
  }
#endif // _di_utf8_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
