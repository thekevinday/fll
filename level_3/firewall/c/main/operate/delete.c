#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_delete_chains_
  f_status_t firewall_operate_delete_chains(firewall_main_t * const main) {

    if (!data) return F_status_set_error(F_parameter);

    const f_string_static_t tools[2] = { firewall_tool_iptables_s, firewall_tool_ip6tables_s };
    f_status_t status = F_okay;

    for (f_number_unsigned_t i = 0; i < 2; ++i) {

      if (firewall_signal_received(data)) {
        return F_status_set_error(F_interrupt);
      }

      f_string_statics_t arguments = f_string_statics_t_initialize;
      arguments.used = 1;

      f_string_static_t arguments_array[arguments.used];
      arguments_array[0] = firewall_chain_flush_command_s;
      arguments.array = arguments_array;

      int return_code = 0;

      firewall_print_debug_tool(data->main->warning, tools[i], arguments);

      status = fll_execute_program(tools[i], arguments, 0, 0, (void *) &return_code);

      if (status == F_child) {
        data->main->child = return_code;

        return status;
      }

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_failure) {
          firewall_print_error_operation(data->main->error, tools[i], arguments);
        }
        else if (F_status_set_fine(status) == F_parameter) {
          firewall_print_error_on_invalid_parameter(data->main->error, "fll_execute_program");
        }
        else {
          firewall_print_error_on_unhandled(data->main->error, "fll_execute_program", F_status_set_fine(status));
        }

        return status;
      }
    } // for

    int return_code = 0;

    f_string_statics_t arguments = f_string_statics_t_initialize;
    arguments.used = 1;

    f_string_static_t argument_array[arguments.used];
    arguments.array = argument_array;
    argument_array[0] = firewall_chain_delete_command_s;

    for (f_number_unsigned_t i = 0; i < 2; ++i) {

      firewall_print_debug_tool(data->main->warning, tools[i], arguments);

      return_code = 0;

      status = fll_execute_program(tools[i], arguments, 0, 0, (void *) &return_code);

      if (status == F_child) {
        data->main->child = return_code;

        break;
      }

      if (firewall_signal_received(data)) {
        status = F_status_set_error(F_interrupt);

        break;
      }

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_failure) {
          firewall_print_error_operation(data->main->error, tools[i], arguments);
        }
        else if (F_status_set_fine(status) == F_parameter) {
          firewall_print_error_on_invalid_parameter(data->main->error, "fll_execute_program");
        }
        else {
          firewall_print_error_on_unhandled(data->main->error, "fll_execute_program", F_status_set_fine(status));
        }

        break;
      }
    } // for

    return status;
  }
#endif // _di_firewall_operate_delete_chains_

#ifdef __cplusplus
} // extern "C"
#endif
