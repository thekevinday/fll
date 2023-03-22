#include "fss_write.h"
#include "main.h"
#include "main-print.h"
#include "../basic/fss_write.h"
#include "../basic_list/fss_write.h"
#include "../extended/fss_write.h"
#include "../extended_list/fss_write.h"
#include "../embedded_list/fss_write.h"
#include "../payload/fss_write.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  fss_write_main_t data = fss_write_main_t_initialize;

  setting.state.custom = (void *) &data;

  data.program.debug.flag |= fss_write_print_flag_debug_e;
  data.program.error.flag |= fss_write_print_flag_error_e;
  data.program.message.flag |= fss_write_print_flag_message_e;
  data.program.warning.flag |= fss_write_print_flag_warning_e;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.error.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;

  f_console_parameter_t parameters[] = fss_write_console_parameter_t_initialize;
  data.parameters.array = parameters;
  data.parameters.used = fss_write_total_parameters_d;
  data.environment = envp;

  if (f_pipe_input_exists()) {
    data.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data);

  {
    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

    fss_write_setting_load(arguments, &data, &setting, &fss_write_main_setting_load_as);
  }

  fss_write_main(&data, &setting);

  fss_write_setting_unload(&data, &setting);

  fll_program_data_delete(&data);

  fll_program_standard_set_down(&data);

  return F_status_is_error(setting.state.status) ? 1 : 0;
}

#ifndef _di_fss_write_main_process_help_
  void fss_write_main_process_help(fll_program_data_t * const main, void * const void_setting) {

    if (!main || !void_setting) return;

    fss_write_main_print_help(macro_fss_write_setting(void_setting), main->message);
  }
#endif // _di_fss_write_main_process_help_

#ifndef _di_fss_write_main_setting_load_as_
  void fss_write_main_setting_load_as(const f_console_arguments_t arguments, fll_program_data_t * const main, fss_write_setting_t * const setting) {

    if (!main || !setting || F_status_is_error(setting->state.status) || (setting->flag & fss_write_main_flag_version_e)) return;

    setting->standard = fss_write_basic_standard_s;
    setting->process_content = &fss_write_basic_process_content;
    setting->process_help = &fss_write_main_process_help;
    setting->process_normal = &fss_write_process_normal;
    setting->process_object = &fss_write_basic_process_object;
    setting->process_pipe = &fss_write_process_pipe;
    setting->process_set = &fss_write_process_set;

    if (main->parameters.array[fss_write_parameter_as_e].result & f_console_result_value_e && main->parameters.array[fss_write_parameter_as_e].values.used) {

      f_array_length_t index = 0;
      f_string_static_t *argv = main->parameters.arguments.array;

      for (f_array_length_t i = 0; i < main->parameters.array[fss_write_parameter_as_e].values.used; ++i) {

        index = main->parameters.array[fss_write_parameter_as_e].values.array[i];

        if (fl_string_dynamic_compare(argv[index], fss_write_format_code_short_0000_s) == F_equal_to ||
            fl_string_dynamic_compare(argv[index], fss_write_format_code_long_0000_s) == F_equal_to ||
            fl_string_dynamic_compare(argv[index], fss_write_format_code_human_0000_s) == F_equal_to) {

          setting->standard = fss_write_basic_standard_s;
          setting->process_content = &fss_write_basic_process_content;
          setting->process_help = &fss_write_basic_process_help;
          setting->process_object = &fss_write_basic_process_object;
          setting->process_pipe = &fss_write_process_pipe;
          setting->process_normal = &fss_write_process_normal;
          setting->process_set = &fss_write_process_set;
          setting->flag -= setting->flag & fss_write_main_flag_ignore_e; // Not supported by basic.
          setting->flag -= setting->flag & fss_write_main_flag_content_multiple_e; // Not supported by basic.
        }
        else if (fl_string_dynamic_compare(argv[index], fss_write_format_code_short_0001_s) == F_equal_to ||
                 fl_string_dynamic_compare(argv[index], fss_write_format_code_long_0001_s) == F_equal_to ||
                 fl_string_dynamic_compare(argv[index], fss_write_format_code_human_0001_s) == F_equal_to) {

          setting->standard = fss_write_extended_standard_s;
          setting->process_content = &fss_write_extended_process_content;
          setting->process_help = &fss_write_extended_process_help;
          setting->process_object = &fss_write_extended_process_object;
          setting->process_pipe = &fss_write_process_pipe;
          setting->process_normal = &fss_write_process_normal;
          setting->process_set = &fss_write_process_set;
          setting->flag -= setting->flag & fss_write_main_flag_ignore_e; // Not supported by extended.
          setting->flag |= fss_write_main_flag_content_multiple_e;
        }
        else if (fl_string_dynamic_compare(argv[index], fss_write_format_code_short_0002_s) == F_equal_to ||
                 fl_string_dynamic_compare(argv[index], fss_write_format_code_long_0002_s) == F_equal_to ||
                 fl_string_dynamic_compare(argv[index], fss_write_format_code_human_0002_s) == F_equal_to) {

          setting->standard = fss_write_basic_list_standard_s;
          setting->process_content = &fss_write_basic_list_process_content;
          setting->process_help = &fss_write_basic_list_process_help;
          setting->process_object = &fss_write_basic_list_process_object;
          setting->process_pipe = &fss_write_process_pipe;
          setting->process_normal = &fss_write_process_normal;
          setting->process_set = &fss_write_process_set;
          setting->flag -= setting->flag & fss_write_main_flag_ignore_e; // Not supported by basic list.
          setting->flag -= setting->flag & fss_write_main_flag_content_multiple_e; // Not supported by basic list.
        }
        else if (fl_string_dynamic_compare(argv[index], fss_write_format_code_short_0003_s) == F_equal_to ||
                 fl_string_dynamic_compare(argv[index], fss_write_format_code_long_0003_s) == F_equal_to ||
                 fl_string_dynamic_compare(argv[index], fss_write_format_code_human_0003_s) == F_equal_to) {

          setting->standard = fss_write_extended_list_standard_s;
          setting->process_content = &fss_write_extended_list_process_content;
          setting->process_help = &fss_write_extended_list_process_help;
          setting->process_object = &fss_write_extended_list_process_object;
          setting->process_pipe = &fss_write_process_pipe;
          setting->process_normal = &fss_write_process_normal;
          setting->process_set = &fss_write_process_set;
          setting->flag |= fss_write_main_flag_ignore_e;
          setting->flag -= setting->flag & fss_write_main_flag_content_multiple_e; // Not supported by extended list.
        }
        else if (fl_string_dynamic_compare(argv[index], fss_write_format_code_short_0008_s) == F_equal_to ||
                 fl_string_dynamic_compare(argv[index], fss_write_format_code_long_0008_s) == F_equal_to ||
                 fl_string_dynamic_compare(argv[index], fss_write_format_code_human_0008_s) == F_equal_to) {

          setting->standard = fss_write_embedded_list_standard_s;
          setting->process_content = &fss_write_embedded_list_process_content;
          setting->process_help = &fss_write_embedded_list_process_help;
          setting->process_object = &fss_write_embedded_list_process_object;
          setting->process_pipe = &fss_write_process_pipe;
          setting->process_normal = &fss_write_process_normal;
          setting->process_set = &fss_write_process_set;
          setting->flag |= fss_write_main_flag_ignore_e;
          setting->flag |= fss_write_main_flag_content_multiple_e;
        }
        else if (fl_string_dynamic_compare(argv[index], fss_write_format_code_short_000e_s) == F_equal_to ||
                 fl_string_dynamic_compare(argv[index], fss_write_format_code_long_000e_s) == F_equal_to ||
                 fl_string_dynamic_compare(argv[index], fss_write_format_code_human_000e_s) == F_equal_to) {

          setting->standard = fss_write_payload_standard_s;
          setting->process_content = 0; // Not used by payload.
          setting->process_help = &fss_write_payload_process_help;
          setting->process_normal = &fss_write_process_normal;
          setting->process_object = 0; // Not used by payload.
          setting->process_pipe = &fss_write_payload_process_pipe;
          setting->process_set = &fss_write_payload_process_set;
          setting->flag -= setting->flag & fss_write_main_flag_ignore_e; // Not supported by payload.
          setting->flag -= setting->flag & fss_write_main_flag_content_multiple_e; // Not supported by payload.
        }
        else {
          if (setting->flag & fss_write_main_flag_help_e) {
            setting->state.status = F_status_set_error(F_parameter);

            break;
          }

          setting->state.status = F_status_set_error(F_parameter);

          fss_write_main_print_error_format_unknown(main->error, argv[index]);
        }
      } // for

      if (F_status_is_error(setting->state.status)) {
        if (setting->flag & fss_write_main_flag_help_e) {
          fss_write_main_process_help(main, setting);
        }

        return;
      }
    }
    else if (main->parameters.array[fss_write_parameter_as_e].result & f_console_result_found_e) {
      setting->state.status = F_status_set_error(F_parameter);

      if (setting->flag & fss_write_main_flag_help_e) {
        fss_write_main_process_help(main, setting);

        return;
      }

      if (main->error.verbosity > f_console_verbosity_quiet_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->error.to);
      }

      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, fss_write_long_as_s);

      return;
    }
  }
#endif // _di_fss_write_main_setting_load_as_
