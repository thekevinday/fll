#include "firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_setting_load_
  void firewall_setting_load(const f_console_arguments_t arguments, firewall_main_t * const main) {

    if (!main) return;

    main->setting.state.step_small = firewall_allocation_console_d;

    f_console_parameter_process(arguments, &main->program.parameters, &main->setting.state, 0);

    main->setting.state.step_small = firewall_allocation_small_d;

    // Identify and process first/last parameters.
    if (main->program.parameters.array[f_console_standard_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag &= ~firewall_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= firewall_main_flag_print_first_e;
    }

    if (main->program.parameters.array[f_console_standard_parameter_line_last_no_e].result & f_console_result_found_e) {
      main->setting.flag &= ~firewall_main_flag_print_last_e;
    }
    else {
      main->setting.flag |= firewall_main_flag_print_last_e;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & firewall_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      firewall_print_error(&main->program.error, macro_firewall_f(f_console_parameter_process));

      return;
    }

    main->setting.state.status = fll_program_parameter_process_context_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & firewall_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      firewall_print_error(&main->program.error, macro_firewall_f(fll_program_parameter_process_context_standard));

      return;
    }

    main->setting.state.status = fll_program_parameter_process_verbosity_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & firewall_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      firewall_print_error(&main->program.error, macro_firewall_f(fll_program_parameter_process_verbosity_standard));

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_help_e].result & f_console_result_found_e) {
      main->setting.flag |= firewall_main_flag_help_e;

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_version_e].result & f_console_result_found_e) {
      main->setting.flag |= firewall_main_flag_version_e;

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_copyright_e].result & f_console_result_found_e) {
      main->setting.flag |= firewall_main_flag_copyright_e;

      return;
    }

    f_number_unsigned_t index = 0;

    if (main->program.parameters.array[firewall_parameter_operation_start_e].result & f_console_result_found_e) {
      main->setting.flag &= ~firewall_main_flag_operation_e;
      main->setting.flag |= firewall_main_flag_operation_start_e;

      index = main->program.parameters.array[firewall_parameter_operation_start_e].location;
    }

    if (main->program.parameters.array[firewall_parameter_operation_stop_e].result & f_console_result_found_e) {
      if (!(main->setting.flag & firewall_main_flag_operation_e) || main->program.parameters.array[firewall_parameter_operation_stop_e].location > index) {
        main->setting.flag &= ~firewall_main_flag_operation_e;
        main->setting.flag |= firewall_main_flag_operation_stop_e;

        index = main->program.parameters.array[firewall_parameter_operation_stop_e].location;
      }
    }

    if (main->program.parameters.array[firewall_parameter_operation_restart_e].result & f_console_result_found_e) {
      if (!(main->setting.flag & firewall_main_flag_operation_e) || main->program.parameters.array[firewall_parameter_operation_restart_e].location > index) {
        main->setting.flag &= ~firewall_main_flag_operation_e;
        main->setting.flag |= firewall_main_flag_operation_restart_e;

        index = main->program.parameters.array[firewall_parameter_operation_restart_e].location;
      }
    }

    if (main->program.parameters.array[firewall_parameter_operation_lock_e].result & f_console_result_found_e) {
      if (!(main->setting.flag & firewall_main_flag_operation_e) || main->program.parameters.array[firewall_parameter_operation_lock_e].location > index) {
        main->setting.flag &= ~firewall_main_flag_operation_e;
        main->setting.flag |= firewall_main_flag_operation_lock_e;

        index = main->program.parameters.array[firewall_parameter_operation_lock_e].location;
      }
    }

    if (main->program.parameters.array[firewall_parameter_operation_show_e].result & f_console_result_found_e) {
      if (!(main->setting.flag & firewall_main_flag_operation_e) || main->program.parameters.array[firewall_parameter_operation_show_e].location > index) {
        main->setting.flag &= ~firewall_main_flag_operation_e;
        main->setting.flag |= firewall_main_flag_operation_show_e;
      }
    }

    if (main->program.pipe & fll_program_data_pipe_input_e) {
      main->setting.flag |= firewall_main_flag_pipe_e;
    }
    else {
      main->setting.flag &= ~firewall_main_flag_pipe_e;
    }

    if (main->setting.flag & firewall_main_flag_operation_show_e) {
      if (main->program.parameters.remaining.used) {
        main->setting.flag &= ~firewall_main_flag_operation_show_filter_nat_mangle_e;

        for (f_number_unsigned_t i = 0; i < main->program.parameters.remaining.used; ++i) {

          if (firewall_signal_check(main)) return;

          index = main->program.parameters.remaining.array[i];

          if (f_compare_dynamic(firewall_show_nat_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
            main->setting.flag |= firewall_main_flag_operation_show_nat_e;
          }
          else if (f_compare_dynamic(firewall_show_mangle_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
            main->setting.flag |= firewall_main_flag_operation_show_mangle_e;
          }
          else if (f_compare_dynamic(firewall_show_filter_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
            main->setting.flag |= firewall_main_flag_operation_show_filter_e;
          }
          else {
            firewall_print_warning_show_option_unknown(&main->program.warning, main->program.parameters.arguments.array[index]);
          }
        } // for
      }
      else {
        main->setting.flag |= firewall_main_flag_operation_show_filter_nat_mangle_e;
      }
    }
  }
#endif // _di_firewall_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
