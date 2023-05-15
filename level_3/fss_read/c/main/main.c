#include "fss_read.h"
#include "main.h"
#include "main/print.h"
#include "../basic/fss_read.h"
#include "../basic_list/fss_read.h"
#include "../extended/fss_read.h"
#include "../extended_list/fss_read.h"
#include "../embedded_list/fss_read.h"
#include "../payload/fss_read.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  fss_read_main_t data = fss_read_main_t_initialize;

  data.program.debug.flag |= fss_read_print_flag_debug_e | fss_read_print_flag_out_e;
  data.program.error.flag |= fss_read_print_flag_error_e | fss_read_print_flag_out_e;
  data.program.output.flag |= fss_read_print_flag_out_e;
  data.program.message.flag |= fss_read_print_flag_message_e | fss_read_print_flag_out_e;
  data.program.warning.flag |= fss_read_print_flag_warning_e | fss_read_print_flag_out_e;
  data.program.error.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;

  data.setting.state.custom = (void *) &data;

  f_console_parameter_t parameters[] = fss_read_console_parameter_t_initialize;
  data.program.parameters.array = parameters;
  data.program.parameters.used = fss_read_total_parameters_d;
  data.program.environment = envp;

  if (f_pipe_input_exists()) {
    data.program.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data.program);

  f_file_umask_get(&data.program.umask);

  #ifdef _di_thread_support_
    {
      const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

      fss_read_setting_load(arguments, &data, 0);
    }

    fss_read_main(&data);
  #else
    {
      f_thread_id_t id_signal;

      memset(&id_signal, 0, sizeof(f_thread_id_t));

      data.setting.state.status = f_thread_create(0, &id_signal, &fss_read_thread_signal, (void *) &data);

      if (F_status_is_error(data.setting.state.status)) {
        fss_read_print_error(&data.program.error, macro_fss_read_f(f_thread_create));
      }
      else {
        {
          const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

          fss_read_setting_load(arguments, &data, &fss_read_main_setting_load_as);
        }

        if (!fss_read_signal_check(&data)) {
          fss_read_main(&data);
        }

        f_thread_cancel(id_signal);
        f_thread_join(id_signal, 0);
      }
    }
  #endif // _di_thread_support_

  fss_read_main_delete(&data);

  fll_program_standard_set_down(&data.program);

  return F_status_is_error(data.setting.state.status) ? 1 : 0;
}

#ifndef _di_fss_read_main_process_help_
  void fss_read_main_process_help(void * const void_main) {

    if (!main) return;

    fss_read_main_print_help(&((fss_read_main_t *) void_main)->program.message);
  }
#endif // _di_fss_read_main_process_help_

#ifndef _di_fss_read_main_setting_load_as_
  void fss_read_main_setting_load_as(const f_console_arguments_t arguments, fss_read_main_t * const main) {

    if (!main || F_status_is_error(main->setting.state.status) || (main->setting.flag & fss_read_main_flag_version_e)) return;

    main->setting.standard = fss_read_basic_standard_s;

    main->callback.process_content = &fss_read_basic_process_content;
    main->callback.process_help = &fss_read_main_process_help;
    main->callback.process_load_depth = 0;
    main->callback.process_normal = &fss_read_process_normal;
    main->callback.process_object = &fss_read_basic_process_object;
    main->callback.process_set = &fss_read_process_set;

    if (main->program.parameters.array[fss_read_parameter_as_e].result & f_console_result_value_e && main->program.parameters.array[fss_read_parameter_as_e].values.used) {

      f_array_length_t index = 0;
      f_string_static_t *argv = main->program.parameters.arguments.array;

      for (f_array_length_t i = 0; i < main->program.parameters.array[fss_read_parameter_as_e].values.used; ++i) {

        index = main->program.parameters.array[fss_read_parameter_as_e].values.array[i];

        if (f_compare_dynamic(argv[index], fss_read_format_code_short_0000_s) == F_equal_to ||
            f_compare_dynamic(argv[index], fss_read_format_code_long_0000_s) == F_equal_to ||
            f_compare_dynamic(argv[index], fss_read_format_code_human_0000_s) == F_equal_to ||
            f_compare_dynamic(argv[index], fss_read_format_code_machine_0000_s) == F_equal_to) {

          main->setting.standard = fss_read_basic_standard_s;

          main->setting.flag -= main->setting.flag & fss_read_main_flag_ignore_e; // Not supported by basic.
          main->setting.flag -= main->setting.flag & fss_read_main_flag_content_multiple_e; // Not supported by basic.

          main->callback.process_content = &fss_read_basic_process_content;
          main->callback.process_help = &fss_read_basic_process_help;
          main->callback.process_load_depth = 0;
          main->callback.process_object = &fss_read_basic_process_object;
          main->callback.process_normal = &fss_read_process_normal;
          main->callback.process_set = &fss_read_process_set;
        }
        else if (f_compare_dynamic(argv[index], fss_read_format_code_short_0001_s) == F_equal_to ||
                 f_compare_dynamic(argv[index], fss_read_format_code_long_0001_s) == F_equal_to ||
                 f_compare_dynamic(argv[index], fss_read_format_code_human_0001_s) == F_equal_to ||
                 f_compare_dynamic(argv[index], fss_read_format_code_machine_0001_s) == F_equal_to) {

          main->setting.standard = fss_read_extended_standard_s;

          main->setting.flag -= main->setting.flag & fss_read_main_flag_ignore_e; // Not supported by extended.
          main->setting.flag |= fss_read_main_flag_content_multiple_e;

          main->callback.process_content = &fss_read_extended_process_content;
          main->callback.process_help = &fss_read_extended_process_help;
          main->callback.process_load_depth = 0;
          main->callback.process_object = &fss_read_extended_process_object;
          main->callback.process_normal = &fss_read_process_normal;
          main->callback.process_set = &fss_read_process_set;
        }
        else if (f_compare_dynamic(argv[index], fss_read_format_code_short_0002_s) == F_equal_to ||
                 f_compare_dynamic(argv[index], fss_read_format_code_long_0002_s) == F_equal_to ||
                 f_compare_dynamic(argv[index], fss_read_format_code_human_0002_s) == F_equal_to ||
                 f_compare_dynamic(argv[index], fss_read_format_code_machine_0002_s) == F_equal_to) {

          main->setting.standard = fss_read_basic_list_standard_s;

          main->setting.flag -= main->setting.flag & fss_read_main_flag_ignore_e; // Not supported by basic list.
          main->setting.flag -= main->setting.flag & fss_read_main_flag_content_multiple_e; // Not supported by basic list.

          main->callback.process_content = &fss_read_basic_list_process_content;
          main->callback.process_help = &fss_read_basic_list_process_help;
          main->callback.process_load_depth = 0;
          main->callback.process_object = &fss_read_basic_list_process_object;
          main->callback.process_normal = &fss_read_process_normal;
          main->callback.process_set = &fss_read_process_set;
        }
        else if (f_compare_dynamic(argv[index], fss_read_format_code_short_0003_s) == F_equal_to ||
                 f_compare_dynamic(argv[index], fss_read_format_code_long_0003_s) == F_equal_to ||
                 f_compare_dynamic(argv[index], fss_read_format_code_human_0003_s) == F_equal_to ||
                 f_compare_dynamic(argv[index], fss_read_format_code_machine_0003_s) == F_equal_to) {

          main->setting.standard = fss_read_extended_list_standard_s;

          main->setting.flag |= fss_read_main_flag_ignore_e;
          main->setting.flag -= main->setting.flag & fss_read_main_flag_content_multiple_e; // Not supported by extended list.

          main->callback.process_content = &fss_read_extended_list_process_content;
          main->callback.process_help = &fss_read_extended_list_process_help;
          main->callback.process_load_depth = 0;
          main->callback.process_object = &fss_read_extended_list_process_object;
          main->callback.process_normal = &fss_read_process_normal;
          main->callback.process_set = &fss_read_process_set;
        }
        else if (f_compare_dynamic(argv[index], fss_read_format_code_short_0008_s) == F_equal_to ||
                 f_compare_dynamic(argv[index], fss_read_format_code_long_0008_s) == F_equal_to ||
                 f_compare_dynamic(argv[index], fss_read_format_code_human_0008_s) == F_equal_to ||
                 f_compare_dynamic(argv[index], fss_read_format_code_machine_0008_s) == F_equal_to) {

          main->setting.standard = fss_read_embedded_list_standard_s;

          main->setting.flag |= fss_read_main_flag_ignore_e;
          main->setting.flag |= fss_read_main_flag_content_multiple_e;

          main->callback.process_content = &fss_read_embedded_list_process_content;
          main->callback.process_help = &fss_read_embedded_list_process_help;
          main->callback.process_load_depth = 0;
          main->callback.process_object = &fss_read_embedded_list_process_object;
          main->callback.process_normal = &fss_read_process_normal;
          main->callback.process_set = &fss_read_process_set;
        }
        else if (f_compare_dynamic(argv[index], fss_read_format_code_short_000e_s) == F_equal_to ||
                 f_compare_dynamic(argv[index], fss_read_format_code_long_000e_s) == F_equal_to ||
                 f_compare_dynamic(argv[index], fss_read_format_code_human_000e_s) == F_equal_to ||
                 f_compare_dynamic(argv[index], fss_read_format_code_machine_000e_s) == F_equal_to) {

          main->setting.standard = fss_read_payload_standard_s;

          main->setting.flag -= main->setting.flag & fss_read_main_flag_ignore_e; // Not supported by payload.
          main->setting.flag -= main->setting.flag & fss_read_main_flag_content_multiple_e; // Not supported by payload.

          main->callback.process_content = 0; // Not used by payload.
          main->callback.process_help = &fss_read_payload_process_help;
          main->callback.process_load_depth = 0;
          main->callback.process_normal = &fss_read_process_normal;
          main->callback.process_object = 0; // Not used by payload.
          main->callback.process_set = &fss_read_payload_process_set;
        }
        else {
          if (main->setting.flag & fss_read_main_flag_help_e) {
            main->setting.state.status = F_status_set_error(F_parameter);

            break;
          }

          main->setting.state.status = F_status_set_error(F_parameter);

          fss_read_main_print_error_format_unknown(&main->program.error, argv[index]);
        }
      } // for

      if (F_status_is_error(main->setting.state.status)) {
        if (main->setting.flag & fss_read_main_flag_help_e) {
          fss_read_main_process_help((void *) main);
        }

        return;
      }
    }
    else if (main->program.parameters.array[fss_read_parameter_as_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if (main->setting.flag & fss_read_main_flag_help_e) {
        fss_read_main_process_help((void *) main);

        return;
      }

      if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.error.to);
      }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, fss_read_long_as_s);

      return;
    }
  }
#endif // _di_fss_read_main_setting_load_as_
