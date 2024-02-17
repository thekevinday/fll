#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_delete_chains_
  void firewall_operate_delete_chains(firewall_main_t * const main) {

    if (!main || F_status_is_error_not(main->setting.state.status) && main->setting.state.status == F_child) return;

    const f_string_static_t tools[2] = { firewall_tool_iptables_s, firewall_tool_ip6tables_s };
    const f_string_static_t command[2] = { firewall_chain_flush_operation_s, firewall_chain_delete_operation_s };

    f_string_statics_t arguments = f_string_statics_t_initialize;
    arguments.used = 1;

    f_string_static_t argument_array[arguments.used];
    arguments.array = argument_array;
    argument_array[0] = firewall_chain_flush_operation_s;

    int return_code = 0;
    uint8_t i = 0;
    uint8_t j = 0;

    for (i = 0; i < 2; ++i) {

      argument_array[0] = command[i];

      for (j = 0; j < 2; ++j) {

        if (firewall_signal_check(main)) return;

        return_code = 0;

        firewall_print_debug_tool(&main->program.warning, tools[j], arguments);

        main->setting.state.status = fll_execute_program(tools[j], arguments, 0, 0, (void *) &return_code);

        if (main->setting.state.status == F_child) {
          main->program.child = return_code;

          return;
        }

        if (F_status_is_error(main->setting.state.status)) {
          if (F_status_set_fine(main->setting.state.status) == F_failure) {
            firewall_print_error_operation(&main->program.error, tools[j], arguments);
          }
          else {
            firewall_print_error(&main->program.error, macro_firewall_f(fll_execute_program));
          }

          return;
        }
        else if (return_code) {
          firewall_print_error_operation_return_code(&main->program.error, tools[j], main->cache.arguments, return_code);
        }
      } // for
    } // for

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_operate_delete_chains_

#ifdef __cplusplus
} // extern "C"
#endif
