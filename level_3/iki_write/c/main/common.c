#include "iki_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_setting_load_
  void iki_write_setting_load(const f_console_arguments_t arguments, iki_write_main_t * const main) {

    if (!main) return;

    main->setting.state.step_small = iki_write_allocation_console_d;

    f_console_parameter_process(arguments, &main->program.parameters, &main->setting.state, 0);

    main->setting.state.step_small = iki_write_allocation_small_d;

    // Identify and pocess first/last parameters.
    if (main->program.parameters.array[iki_write_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & iki_write_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= iki_write_main_flag_print_first_e;
    }

    if (main->program.parameters.array[iki_write_parameter_line_last_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & iki_write_main_flag_print_last_e;
    }
    else {
      main->setting.flag |= iki_write_main_flag_print_last_e;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & iki_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      iki_write_print_error(&main->program.error, macro_iki_write_f(f_console_parameter_process));

      return;
    }

    {
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { iki_write_parameter_no_color_e, iki_write_parameter_light_e, iki_write_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        static const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        main->setting.state.status = fll_program_parameter_process_context(choices, modes, F_true, &main->program);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & iki_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          iki_write_print_error(&main->program.error, macro_iki_write_f(fll_program_parameter_process_context));

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { iki_write_parameter_verbosity_quiet_e, iki_write_parameter_verbosity_error_e, iki_write_parameter_verbosity_verbose_e, iki_write_parameter_verbosity_debug_e, iki_write_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        static const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        main->setting.state.status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, &main->program);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & iki_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          iki_write_print_error(&main->program.error, macro_iki_write_f(fll_program_parameter_process_verbosity));

          return;
        }
      }
    }

    main->program.output.to.id = F_type_descriptor_output_d;
    main->program.output.to.stream = F_type_output_d;
    main->program.output.to.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    if (main->program.parameters.array[iki_write_parameter_help_e].result & f_console_result_found_e) {
      main->setting.flag |= iki_write_main_flag_help_e;

      return;
    }

    if (main->program.parameters.array[iki_write_parameter_version_e].result & f_console_result_found_e) {
      main->setting.flag |= iki_write_main_flag_version_e;

      return;
    }

    if (main->program.parameters.array[iki_write_parameter_copyright_e].result & f_console_result_found_e) {
      main->setting.flag |= iki_write_main_flag_copyright_e;

      return;
    }

    if (main->program.parameters.array[iki_write_parameter_file_e].result & f_console_result_value_e && main->program.parameters.array[iki_write_parameter_file_e].values.used) {
      if (main->program.parameters.array[iki_write_parameter_file_e].values.used > 1) {
        main->setting.state.status = F_status_set_error(F_parameter);

        if ((main->setting.flag & iki_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fll_program_print_error_parameter_must_specify_once(&main->program.error, f_console_symbol_long_normal_s, iki_write_long_file_s);

        return;
      }

      const f_array_length_t index = main->program.parameters.array[iki_write_parameter_file_e].values.array[0];

      main->program.output.to.id = -1;
      main->program.output.to.stream = 0;

      main->setting.state.status = f_file_stream_open(main->program.parameters.arguments.array[index], f_string_empty_s, &main->program.output.to);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & iki_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fll_error_file_print(&main->program.error, F_status_set_fine(main->setting.state.status), macro_iki_write_f(f_file_stream_open), fll_error_file_flag_fallback_e, main->program.parameters.arguments.array[index], f_file_operation_open_s, fll_error_file_type_file_e);

        return;
      }

      main->setting.flag |= iki_write_main_flag_file_to_e;
    }
    else if (main->program.parameters.array[iki_write_parameter_file_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & iki_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, iki_write_long_file_s);

      return;
    }

    if (main->program.parameters.array[iki_write_parameter_object_e].result & f_console_result_value_e) {
      f_array_lengths_t * const values = &main->program.parameters.array[iki_write_parameter_object_e].values;

      main->setting.objects.used = 0;

      main->setting.state.status = f_string_dynamics_resize(values->used, &main->setting.objects);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & iki_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        iki_write_print_error(&main->program.error, macro_iki_write_f(f_string_dynamics_resize));

        return;
      }

      // Construct the array without allocating any more memory by setting this as a static string (used > 0, size = 0).
      for (f_array_length_t index = 0; main->setting.objects.used < values->used; ) {

        index = values->array[main->setting.objects.used];

        main->setting.objects.array[main->setting.objects.used].string = main->program.parameters.arguments.array[index].string;
        main->setting.objects.array[main->setting.objects.used].used = main->program.parameters.arguments.array[index].used;
        main->setting.objects.array[main->setting.objects.used++].size = 0;
      } // for

      main->setting.flag |= iki_write_main_flag_object_e;
    }
    else if (main->program.parameters.array[iki_write_parameter_object_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & iki_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, iki_write_long_object_s);

      return;
    }

    if (main->program.parameters.array[iki_write_parameter_content_e].result & f_console_result_value_e) {
      f_array_lengths_t * const values = &main->program.parameters.array[iki_write_parameter_content_e].values;

      main->setting.contents.used = 0;

      main->setting.state.status = f_string_dynamics_resize(values->used, &main->setting.contents);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & iki_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        iki_write_print_error(&main->program.error, macro_iki_write_f(f_string_dynamics_resize));

        return;
      }

      // Construct the array without allocating any more memory by setting this as a static string (used > 0, size = 0).
      for (f_array_length_t index = 0; main->setting.contents.used < values->used; ) {

        index = values->array[main->setting.contents.used];

        main->setting.contents.array[main->setting.contents.used].string = main->program.parameters.arguments.array[index].string;
        main->setting.contents.array[main->setting.contents.used].used = main->program.parameters.arguments.array[index].used;
        main->setting.contents.array[main->setting.contents.used++].size = 0;
      } // for

      main->setting.flag |= iki_write_main_flag_content_e;
    }
    else if (main->program.parameters.array[iki_write_parameter_content_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & iki_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, iki_write_long_content_s);

      return;
    }

    if (!(main->program.pipe & fll_program_data_pipe_input_e) && !(main->setting.flag & (iki_write_main_flag_content_e | iki_write_parameter_object_e))) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & iki_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      iki_write_print_error_main_missing(&main->program.error);

      return;
    }

    if (main->program.parameters.array[iki_write_parameter_wrap_e].result & f_console_result_found_e) {
      main->setting.flag |= iki_write_main_flag_wrap_e;
    }

    main->setting.quote = f_iki_syntax_quote_double_s;

    if (main->program.parameters.array[iki_write_parameter_double_e].result & f_console_result_found_e) {
      if (main->program.parameters.array[iki_write_parameter_single_e].result & f_console_result_found_e) {
        if (main->program.parameters.array[iki_write_parameter_double_e].location < main->program.parameters.array[iki_write_parameter_single_e].location) {
          main->setting.quote = f_iki_syntax_quote_single_s;

          if (main->program.parameters.array[iki_write_parameter_backtick_e].result & f_console_result_found_e) {
            if (main->program.parameters.array[iki_write_parameter_single_e].location < main->program.parameters.array[iki_write_parameter_backtick_e].location) {
              main->setting.quote = f_iki_syntax_quote_backtick_s;
            }
          }
        }
        else if (main->program.parameters.array[iki_write_parameter_backtick_e].result & f_console_result_found_e) {
          if (main->program.parameters.array[iki_write_parameter_double_e].location < main->program.parameters.array[iki_write_parameter_backtick_e].location) {
            main->setting.quote = f_iki_syntax_quote_backtick_s;
          }
        }
      }
      else if (main->program.parameters.array[iki_write_parameter_backtick_e].result & f_console_result_found_e) {
        if (main->program.parameters.array[iki_write_parameter_double_e].location < main->program.parameters.array[iki_write_parameter_backtick_e].location) {
          main->setting.quote = f_iki_syntax_quote_backtick_s;
        }
      }
    }
    else if (main->program.parameters.array[iki_write_parameter_single_e].result & f_console_result_found_e) {
      main->setting.quote = f_iki_syntax_quote_single_s;

      if (main->program.parameters.array[iki_write_parameter_backtick_e].result & f_console_result_found_e) {
        if (main->program.parameters.array[iki_write_parameter_single_e].location < main->program.parameters.array[iki_write_parameter_backtick_e].location) {
          main->setting.quote = f_iki_syntax_quote_backtick_s;
        }
      }
    }
    else if (main->program.parameters.array[iki_write_parameter_backtick_e].result & f_console_result_found_e) {
      main->setting.quote = f_iki_syntax_quote_backtick_s;
    }
  }
#endif // _di_iki_write_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
