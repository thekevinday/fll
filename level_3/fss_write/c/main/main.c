#include "fss_write.h"
#include "main.h"
#include "../basic/fss_write.h"
#include "../basic_list/fss_write.h"
#include "../extended/fss_write.h"
#include "../extended_list/fss_write.h"
#include "../embedded_list/fss_write.h"
#include "../payload/fss_write.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  fll_program_data_t data = fll_program_data_t_initialize;
  fss_write_setting_t setting = fss_write_setting_t_initialize;
  setting.state.data = (void *) &data;
  setting.program_name = &fss_write_program_name_s;
  setting.program_name_long = &fss_write_program_name_long_s;

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

  return F_status_is_error(setting.status) ? 1 : 0;
}

#ifndef _di_fss_write_main_process_help_
  void fss_write_main_process_help(fll_program_data_t * const main, void * const void_setting) {

    fss_write_setting_t * const setting = (fss_write_setting_t *) void_setting;

    f_file_stream_lock(main->message.to);

    f_print_dynamic_raw(setting->line_first, main->message.to);

    fll_program_print_help_header(main->message, fss_write_program_name_long_s, fss_write_program_version_s);

    fss_write_print_help(setting, main->message);

    fll_program_print_help_option(main->message, fss_write_short_as_s, fss_write_long_as_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Designate the supported format to write as.");

    f_print_dynamic_raw(f_string_eol_s, main->message.to);
    f_print_dynamic_raw(f_string_eol_s, main->message.to);

    fll_program_print_help_usage(main->message, fss_write_program_name_s, f_string_empty_s);

    fss_write_print_help_pipe(setting, main->message);

    f_print_dynamic_raw(f_string_eol_s, main->message.to);

    fl_print_format("  The '%[%r%r%]' parameter supports the following standards with the specified possible case-sensitive values:%r", main->message.to, main->message.set->notable, f_console_symbol_long_normal_s, fss_write_long_as_s, main->message.set->notable, f_string_eol_s);

    // FSS-0000 (Basic)
    fl_print_format("    - As %[%r%]         format: ", main->message.to, main->message.set->notable, fss_write_basic_standard_s, main->message.set->notable);
    fl_print_format("'%[%r%]', ", main->message.to, main->message.set->notable, fss_write_format_code_short_0000_s, main->message.set->notable);
    fl_print_format("'%[%r%]', or ", main->message.to, main->message.set->notable, fss_write_format_code_long_0000_s, main->message.set->notable);
    fl_print_format("'%[%r%]'.%r", main->message.to, main->message.set->notable, fss_write_format_code_human_0000_s, main->message.set->notable, f_string_eol_s);

    // FSS-0001 (Extended)
    fl_print_format("    - As %[%r%]      format: ", main->message.to, main->message.set->notable, fss_write_extended_standard_s, main->message.set->notable);
    fl_print_format("'%[%r%]', ", main->message.to, main->message.set->notable, fss_write_format_code_short_0001_s, main->message.set->notable);
    fl_print_format("'%[%r%]', or ", main->message.to, main->message.set->notable, fss_write_format_code_long_0001_s, main->message.set->notable);
    fl_print_format("'%[%r%]'.%r", main->message.to, main->message.set->notable, fss_write_format_code_human_0001_s, main->message.set->notable, f_string_eol_s);

    // FSS-0002 (Basic List)
    fl_print_format("    - As %[%r%]    format: ", main->message.to, main->message.set->notable, fss_write_basic_list_standard_s, main->message.set->notable);
    fl_print_format("'%[%r%]', ", main->message.to, main->message.set->notable, fss_write_format_code_short_0002_s, main->message.set->notable);
    fl_print_format("'%[%r%]', or ", main->message.to, main->message.set->notable, fss_write_format_code_long_0002_s, main->message.set->notable);
    fl_print_format("'%[%r%]'.%r", main->message.to, main->message.set->notable, fss_write_format_code_human_0002_s, main->message.set->notable, f_string_eol_s);

    // FSS-0003 (Extended List)
    fl_print_format("    - As %[%r%] format: ", main->message.to, main->message.set->notable, fss_write_extended_list_standard_s, main->message.set->notable);
    fl_print_format("'%[%r%]', ", main->message.to, main->message.set->notable, fss_write_format_code_short_0003_s, main->message.set->notable);
    fl_print_format("'%[%r%]', or ", main->message.to, main->message.set->notable, fss_write_format_code_long_0003_s, main->message.set->notable);
    fl_print_format("'%[%r%]'.%r", main->message.to, main->message.set->notable, fss_write_format_code_human_0003_s, main->message.set->notable, f_string_eol_s);

    // FSS-0008 (Embedded List)
    fl_print_format("    - As %[%r%] format: ", main->message.to, main->message.set->notable, fss_write_embedded_list_standard_s, main->message.set->notable);
    fl_print_format("'%[%r%]', ", main->message.to, main->message.set->notable, fss_write_format_code_short_0008_s, main->message.set->notable);
    fl_print_format("'%[%r%]', or ", main->message.to, main->message.set->notable, fss_write_format_code_long_0008_s, main->message.set->notable);
    fl_print_format("'%[%r%]'.%r", main->message.to, main->message.set->notable, fss_write_format_code_human_0008_s, main->message.set->notable, f_string_eol_s);

    // FSS-000E (Payload)
    fl_print_format("    - As %[%r%]       format: ", main->message.to, main->message.set->notable, fss_write_payload_standard_s, main->message.set->notable);
    fl_print_format("'%[%r%]', ", main->message.to, main->message.set->notable, fss_write_format_code_short_000e_s, main->message.set->notable);
    fl_print_format("'%[%r%]', or ", main->message.to, main->message.set->notable, fss_write_format_code_long_000e_s, main->message.set->notable);
    fl_print_format("'%[%r%]'.%r", main->message.to, main->message.set->notable, fss_write_format_code_human_000e_s, main->message.set->notable, f_string_eol_s);

    f_print_dynamic_raw(f_string_eol_s, main->message.to);

    fl_print_format("  The %[%r%] format is the default when no ", main->message.to, main->message.set->notable, fss_write_basic_standard_s, main->message.set->notable);
    fl_print_format("'%[%r%r%]' is specified.%r", main->message.to, main->message.set->notable, f_console_symbol_long_normal_s, fss_write_long_as_s, main->message.set->notable, f_string_eol_s);

    f_print_dynamic_raw(setting->line_last, main->message.to);

    f_file_stream_flush(main->message.to);
    f_file_stream_unlock(main->message.to);
  }
#endif // _di_fss_write_main_process_help_

#ifndef _di_fss_write_main_setting_load_as_
  void fss_write_main_setting_load_as(const f_console_arguments_t arguments, fll_program_data_t * const main, fss_write_setting_t * const setting) {

    if (!main || !setting || F_status_is_error(setting->status) || (setting->flag & fss_write_main_flag_version_e)) return;

    setting->program_name = &fss_write_program_name_s;
    setting->program_name_long = &fss_write_program_name_long_s;
    setting->process_help = &fss_write_main_process_help;
    setting->process_pipe = &fss_write_basic_process_pipe;
    setting->process_normal = &fss_write_basic_process_normal;

    if (main->parameters.array[fss_write_parameter_as_e].result & f_console_result_value_e && main->parameters.array[fss_write_parameter_as_e].values.used) {

      f_array_length_t index = 0;
      f_string_static_t *argv = main->parameters.arguments.array;

      for (f_array_length_t i = 0; i < main->parameters.array[fss_write_parameter_as_e].values.used; ++i) {

        index = main->parameters.array[fss_write_parameter_as_e].values.array[i];

        if (fl_string_dynamic_compare(argv[index], fss_write_format_code_short_0000_s) == F_equal_to ||
            fl_string_dynamic_compare(argv[index], fss_write_format_code_long_0000_s) == F_equal_to ||
            fl_string_dynamic_compare(argv[index], fss_write_format_code_human_0000_s) == F_equal_to) {

          setting->program_name = &fss_write_basic_program_name_s;
          setting->program_name_long = &fss_write_basic_program_name_long_s;
          setting->process_help = &fss_write_basic_process_help;
          setting->process_pipe = &fss_write_basic_process_pipe;
          setting->process_normal = &fss_write_basic_process_normal;
        }
        else if (fl_string_dynamic_compare(argv[index], fss_write_format_code_short_0001_s) == F_equal_to ||
            fl_string_dynamic_compare(argv[index], fss_write_format_code_long_0001_s) == F_equal_to ||
            fl_string_dynamic_compare(argv[index], fss_write_format_code_human_0001_s) == F_equal_to) {

          setting->program_name = &fss_write_extended_program_name_s;
          setting->program_name_long = &fss_write_extended_program_name_long_s;
          setting->process_help = &fss_write_extended_process_help;
          setting->process_pipe = &fss_write_extended_process_pipe;
          setting->process_normal = &fss_write_extended_process_normal;
        }
        else if (fl_string_dynamic_compare(argv[index], fss_write_format_code_short_0002_s) == F_equal_to ||
            fl_string_dynamic_compare(argv[index], fss_write_format_code_long_0002_s) == F_equal_to ||
            fl_string_dynamic_compare(argv[index], fss_write_format_code_human_0002_s) == F_equal_to) {

          setting->program_name = &fss_write_basic_list_program_name_s;
          setting->program_name_long = &fss_write_basic_list_program_name_long_s;
          setting->process_help = &fss_write_basic_list_process_help;
          setting->process_pipe = &fss_write_basic_list_process_pipe;
          setting->process_normal = &fss_write_basic_list_process_normal;
        }
        else if (fl_string_dynamic_compare(argv[index], fss_write_format_code_short_0003_s) == F_equal_to ||
            fl_string_dynamic_compare(argv[index], fss_write_format_code_long_0003_s) == F_equal_to ||
            fl_string_dynamic_compare(argv[index], fss_write_format_code_human_0003_s) == F_equal_to) {

          setting->program_name = &fss_write_extended_list_program_name_s;
          setting->program_name_long = &fss_write_extended_list_program_name_long_s;
          setting->process_help = &fss_write_extended_list_process_help;
          setting->process_pipe = &fss_write_extended_list_process_pipe;
          setting->process_normal = &fss_write_extended_list_process_normal;
        }
        else if (fl_string_dynamic_compare(argv[index], fss_write_format_code_short_0008_s) == F_equal_to ||
            fl_string_dynamic_compare(argv[index], fss_write_format_code_long_0008_s) == F_equal_to ||
            fl_string_dynamic_compare(argv[index], fss_write_format_code_human_0008_s) == F_equal_to) {

          setting->program_name = &fss_write_embedded_list_program_name_s;
          setting->program_name_long = &fss_write_embedded_list_program_name_long_s;
          setting->process_help = &fss_write_embedded_list_process_help;
          setting->process_pipe = &fss_write_embedded_list_process_pipe;
          setting->process_normal = &fss_write_embedded_list_process_normal;
        }
        else if (fl_string_dynamic_compare(argv[index], fss_write_format_code_short_000e_s) == F_equal_to ||
            fl_string_dynamic_compare(argv[index], fss_write_format_code_long_000e_s) == F_equal_to ||
            fl_string_dynamic_compare(argv[index], fss_write_format_code_human_000e_s) == F_equal_to) {

          setting->program_name = &fss_write_payload_program_name_s;
          setting->program_name_long = &fss_write_payload_program_name_long_s;
          setting->process_help = &fss_write_payload_process_help;
          setting->process_pipe = &fss_write_payload_process_pipe;
          setting->process_normal = &fss_write_payload_process_normal;

        }
        else {
          // @todo print error

          setting->status = F_status_set_error(F_parameter);
        }
      } // for

      if (F_status_is_error(setting->status)) {
        if (setting->flag & fss_write_main_flag_help_e) {
          fss_write_main_process_help(main, setting);
        }

        return;
      }
    }
    else if (main->parameters.array[fss_write_parameter_as_e].result & f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      if (setting->flag & fss_write_main_flag_help_e) {
        fss_write_main_process_help(main, setting);

        return;
      }

      fss_write_print_line_first_locked(setting, main->error);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, fss_write_long_as_s);
      fss_write_print_line_last_locked(setting, main->error);

      return;
    }
  }
#endif // _di_fss_write_main_setting_load_as_
