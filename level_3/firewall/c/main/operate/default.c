#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_default_lock_
  void firewall_operate_default_lock(firewall_main_t * const main) {

    if (!main || F_status_is_error_not(main->setting.state.status) && main->setting.state.status == F_child) return;

    const f_string_static_t chains[3] = { firewall_chain_input_s, firewall_chain_output_s, firewall_chain_forward_s };
    const f_string_static_t tools[2] = { firewall_tool_iptables_s, firewall_tool_ip6tables_s };

    f_string_statics_t arguments = f_string_statics_t_initialize;
    arguments.used = 3;

    f_string_static_t argument_array[arguments.used];
    arguments.array = argument_array;
    arguments.array[0] = firewall_action_policy_operation_s;
    arguments.array[2] = firewall_chain_drop_s;

    int return_code = 0;
    uint8_t i = 0;
    uint8_t j = 0;

    for (; i < 3; ++i) {

      arguments.array[1] = chains[i];

      for (j = 0; j < 2; ++j) {

        firewall_print_debug_tool(&main->program.warning, tools[j], arguments);

        return_code = 0;

        main->setting.state.status = fll_execute_program(tools[j], arguments, 0, 0, (void *) &return_code);

        if (main->setting.state.status == F_child) {
          main->program.child = return_code;

          return;
        }

        if (firewall_signal_check(main)) return;

        if (F_status_is_error(main->setting.state.status)) {
          if (F_status_set_fine(main->setting.state.status) == F_failure) {
            firewall_print_error_operation(&main->program.error, tools[j], arguments);
          }
          else {
            firewall_print_error(&main->program.error, macro_firewall_f(fll_execute_program));
          }

          return;
        }
      } // for
    } // for

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_operate_default_lock_

#ifdef __cplusplus
} // extern "C"
#endif
