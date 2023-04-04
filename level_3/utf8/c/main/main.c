#include "utf8.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  utf8_main_t data = utf8_main_t_initialize;

  data.program.debug.flag |= utf8_print_flag_debug_e | utf8_print_flag_out_e;
  data.program.error.flag |= utf8_print_flag_error_e | utf8_print_flag_out_e;
  data.program.output.flag |= utf8_print_flag_out_e;
  data.program.message.flag |= utf8_print_flag_message_e | utf8_print_flag_out_e;
  data.program.warning.flag |= utf8_print_flag_warning_e | utf8_print_flag_out_e;
  data.program.error.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;

  f_console_parameter_t parameters[] = utf8_console_parameter_t_initialize;

  data.program.parameters.array = parameters;
  data.program.parameters.used = utf8_total_parameters_d;
  data.program.environment = envp;

  if (f_pipe_input_exists()) {
    data.program.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data.program);

  f_file_umask_get(&data.program.umask);

  #ifdef _di_thread_support_
    {
      const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

      utf8_setting_load(arguments, &data);
    }

    utf8_main(&data);
  #else
    {
      f_thread_id_t id_signal;

      memset(&id_signal, 0, sizeof(f_thread_id_t));

      data.setting.state.status = f_thread_create(0, &id_signal, &utf8_thread_signal, (void *) &data);

      if (F_status_is_error(data.setting.state.status)) {
        utf8_print_error(&data.program.error, macro_utf8_f(f_thread_create));
      }
      else {
        {
          const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

          utf8_setting_load(arguments, &data);
        }

        if (!utf8_signal_check(&data)) {
          utf8_main(&data);
        }

        f_thread_cancel(id_signal);
        f_thread_join(id_signal, 0);
      }
    }
  #endif // _di_thread_support_

  utf8_main_delete(&data);

  fll_program_standard_set_down(&data.program);

  return (F_status_is_error(data.setting.state.status) || data.setting.state.status == F_false) ? 1 : 0;
}
