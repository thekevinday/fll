#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_rules_
  void firewall_operate_rules(firewall_main_t * const main) {

    if (!main || F_status_is_error_not(main->setting.state.status) && main->setting.state.status == F_child) return;

    firewall_operate_process_rules(main);

    if (F_status_is_error(main->setting.state.status)) {
      if (F_status_set_fine(main->setting.state.status) != F_failure && F_status_set_fine(main->setting.state.status) != F_interrupt) {
        firewall_print_error_unhandled(&main->program.error, macro_firewall_f(firewall_operate_process_rules), f_string_empty_s);
      }

      return;
    }

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_operate_rules_

#ifdef __cplusplus
} // extern "C"
#endif
