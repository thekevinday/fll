#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_chains_
  void firewall_operate_chains(firewall_main_t * const main) {

    if (!main || F_status_is_error_not(main->setting.state.status) && main->setting.state.status == F_child) return;

    for (f_number_unsigned_t i = 0; i < main->data.chain_contents.used; ++i) {

      main->data.range = main->data.chain_contents.array[i].array[0];

      if ((main->data.has & firewall_data_has_main_e) && i == main->data.main) {
        main->data.is |= firewall_data_is_main_e;
      }
      else {
        main->data.is &= ~firewall_data_is_main_e;
      }

      main->data.chain = i;

      firewall_operate_buffer_rules(main);

      firewall_operate_rules(main);

      if (F_status_is_error(main->setting.state.status) || (main->setting.flag & firewall_main_flag_operation_stop_e) || main->setting.state.status == F_child) return;
    } // for

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_operate_chains_

#ifdef __cplusplus
} // extern "C"
#endif
