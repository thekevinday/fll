#include "fss_read.h"
#include "../main/fss_read.h"

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

  data.setting.flag |= fss_read_main_flag_line_single_e;
  data.setting.flag |= fss_read_main_flag_quote_content_e | fss_read_main_flag_quote_object_e;

  data.setting.state.custom = (void *) &data;
  data.setting.standard = fss_read_basic_standard_s;

  data.callback.process_help = &fss_read_basic_process_help;
  data.callback.process_last_line = &fss_read_process_last_line;
  data.callback.process_normal = &fss_read_process_normal;

  data.callback.process_at = &fss_read_process_normal_at;
  data.callback.process_at_line = &fss_read_process_normal_at_line;
  data.callback.process_columns = &fss_read_process_normal_columns;
  data.callback.process_load = &fss_read_basic_process_load;
  data.callback.process_name = &fss_read_process_normal_name;
  data.callback.process_total = &fss_read_process_normal_total;

  data.callback.print_at = &fss_read_print_at;
  data.callback.print_content = &fss_read_print_content;
  data.callback.print_content_ignore = 0;
  data.callback.print_content_next = 0;
  data.callback.print_object = &fss_read_print_object;
  data.callback.print_object_end = &fss_read_basic_print_object_end;
  data.callback.print_set_end = &fss_read_print_set_end;

  f_console_parameter_t parameters[] = fss_read_console_parameter_t_initialize;
  data.program.parameters.array = parameters;
  data.program.parameters.array[fss_read_parameter_as_e].flag |= f_console_flag_disable_e;
  data.program.parameters.used = fss_read_parameter_total_d;
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

          fss_read_setting_load(arguments, &data, 0);
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