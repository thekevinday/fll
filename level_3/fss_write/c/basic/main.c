#include "fss_write.h"
#include "../main/fss_write.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  fss_write_main_t data = fss_write_main_t_initialize;

  data.program.debug.flag |= fss_write_print_flag_debug_e | fss_write_print_flag_out_e;
  data.program.error.flag |= fss_write_print_flag_error_e | fss_write_print_flag_out_e;
  data.program.output.flag |= fss_write_print_flag_out_e;
  data.program.message.flag |= fss_write_print_flag_message_e | fss_write_print_flag_out_e;
  data.program.warning.flag |= fss_write_print_flag_warning_e | fss_write_print_flag_out_e;
  data.program.error.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;

  data.setting.state.custom = (void *) &data;
  data.setting.standard = fss_write_basic_standard_s;

  data.callback.process_content = &fss_write_basic_process_content;
  data.callback.process_help = &fss_write_basic_process_help;
  data.callback.process_normal = &fss_write_process_normal;
  data.callback.process_object = &fss_write_basic_process_object;
  data.callback.process_pipe = &fss_write_process_pipe;
  data.callback.process_set = &fss_write_process_set;

  f_console_parameter_t parameters[] = fss_write_console_parameter_t_initialize;
  data.program.parameters.array = parameters;
  data.program.parameters.array[fss_write_parameter_as_e].flag |= f_console_flag_disable_e;
  data.program.parameters.used = fss_write_parameter_total_d;
  data.program.environment = envp;

  if (f_pipe_input_exists()) {
    data.program.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data.program);

  f_file_umask_get(&data.program.umask);

  #ifdef _di_thread_support_
    {
      const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

      fss_write_setting_load(arguments, &data, 0);
    }

    fss_write_main(&data);
  #else
    {
      f_thread_id_t id_signal;

      memset(&id_signal, 0, sizeof(f_thread_id_t));

      data.setting.state.status = f_thread_create(0, &id_signal, &fss_write_thread_signal, (void *) &data);

      if (F_status_is_error(data.setting.state.status)) {
        fss_write_print_error(&data.program.error, macro_fss_write_f(f_thread_create));
      }
      else {
        {
          const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

          fss_write_setting_load(arguments, &data, 0);
        }

        if (!fss_write_signal_check(&data)) {
          fss_write_main(&data);
        }

        f_thread_cancel(id_signal);
        f_thread_join(id_signal, 0);
      }
    }
  #endif // _di_thread_support_

  fss_write_main_delete(&data);

  fll_program_standard_set_down(&data.program);

  return F_status_is_error(data.setting.state.status) ? 1 : 0;
}
