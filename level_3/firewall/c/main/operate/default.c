#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_default_lock_
  f_status_t firewall_operate_default_lock(firewall_data_t * const data) {

    if (!data) return F_status_set_error(F_parameter);

    const f_string_static_t chains[3] = { firewall_chain_input_s, firewall_chain_output_s, firewall_chain_forward_s };
    const f_string_static_t tools[2] = { firewall_tool_iptables_s, firewall_tool_ip6tables_s };

    f_status_t status = F_okay;

    int return_code = 0;

    f_string_statics_t arguments = f_string_statics_t_initialize;
    arguments.used = 3;

    f_string_static_t argument_array[arguments.used];
    arguments.array = argument_array;
    arguments.array[0] = firewall_action_policy_command_s;
    arguments.array[2] = firewall_chain_drop_s;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;

    for (; i < 3; ++i) {

      arguments.array[1] = chains[i];

      for (j = 0; j < 2; ++j) {

        firewall_print_debug_tool(data->main->warning, tools[j], arguments);

        return_code = 0;

        status = fll_execute_program(tools[j], arguments, 0, 0, (void *) &return_code);

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
            firewall_print_error_operation(data->main->error, tools[j], arguments);
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
    } // for

    return status;
  }
#endif // _di_firewall_operate_default_lock_

#ifdef __cplusplus
} // extern "C"
#endif
