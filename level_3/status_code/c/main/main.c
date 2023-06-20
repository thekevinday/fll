#include "status_code.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  status_code_main_t data = status_code_main_t_initialize;

  data.program.debug.flag |= status_code_print_flag_debug_e | status_code_print_flag_out_e;
  data.program.error.flag |= status_code_print_flag_error_e | status_code_print_flag_out_e;
  data.program.output.flag |= status_code_print_flag_out_e;
  data.program.message.flag |= status_code_print_flag_message_e | status_code_print_flag_out_e;
  data.program.warning.flag |= status_code_print_flag_warning_e | status_code_print_flag_out_e;
  data.program.error.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;

  data.setting.program_name = &status_code_program_name_s;
  data.setting.program_name_long = &status_code_program_name_long_s;
  data.setting.status_string_from = &fl_status_string_from;
  data.setting.status_string_to = &f_status_string_to;
  data.setting.status_string_help_detail = &status_code_print_message_help_detail;

  f_console_parameter_t parameters[] = status_code_console_parameter_t_initialize;

  data.program.parameters.array = parameters;
  data.program.parameters.used = status_code_parameter_total_d;
  data.program.environment = envp;

  if (f_pipe_input_exists()) {
    data.program.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data.program);

  f_file_umask_get(&data.program.umask);

  #ifdef _di_thread_support_
    {
      const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

      status_code_setting_load(arguments, &data);
    }

    status_code_main(&data);
  #else
    {
      f_thread_id_t id_signal;

      memset(&id_signal, 0, sizeof(f_thread_id_t));

      data.setting.state.status = f_thread_create(0, &id_signal, &status_code_thread_signal, (void *) &data);

      if (F_status_is_error(data.setting.state.status)) {
        status_code_print_error(&data.program.error, macro_status_code_f(f_thread_create));
      }
      else {
        {
          const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

          status_code_setting_load(arguments, &data);
        }

        if (!status_code_signal_check(&data)) {
          status_code_main(&data);
        }

        f_thread_cancel(id_signal);
        f_thread_join(id_signal, 0);
      }
    }
  #endif // _di_thread_support_

  status_code_main_delete(&data);

  fll_program_standard_set_down(&data.program);

  return (F_status_is_error(data.setting.state.status) || data.setting.state.status == F_false) ? 1 : 0;
}
