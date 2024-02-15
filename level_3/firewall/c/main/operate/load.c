#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_load_chains_
  void firewall_operate_load_chains(firewall_main_t * const main) {

    if (!main || F_status_is_error_not(main->setting.state.status) && main->setting.state.status == F_child) return;

    for (i = 0; i < local.chain_contents.used; ++i) {

      main->data.range = local.chain_contents.array[i].array[0];

      if ((main->data.has & firewall_data_has_main_e) && i == main->data.main) {
        main->data.is |= firewall_data_is_main_e;
      }
      else {
        main->data.is &= ~firewall_data_is_main_e;
      }

      main->data.chain = i;

      firewall_operate_load_rules(main);
      if (F_status_is_error(main->setting.state.status) || (main->setting.flag & firewall_main_flag_operation_stop_e) || main->setting.state.status == F_child) return;
    } // for

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_operate_load_chains_

#ifndef _di_firewall_operate_load_rules_
  void firewall_operate_load_rules(firewall_main_t * const main) {

    if (!main || F_status_is_error_not(main->setting.state.status) && main->setting.state.status == F_child) return;

    main->data.buffer.used = 0;
    main->data.delimits.used = 0;
    main->data.rule_objects.used = 0;
    main->data.rule_contents.used = 0;

// @fixme the data.rule_objects and rule_contents may be in use by a caller function (specifically in operate.c via firewall_operate_buffer_rules()).
    main->setting.state.status = fll_fss_extended_read(main->data.buffer, main->setting.state, main->data.range, &main->data.rule_objects, &main->data.rule_contents, 0, 0, &main->data.delimits, 0);

    if (F_status_is_error(main->setting.state.status)) {
      firewall_print_error(&main->program.error, macro_firewall_f(fll_fss_extended_read));

      return;
    }

    main->setting.state.status = f_fss_apply_delimit(main->setting.state, main->data.delimits, &main->data.buffer);

    if (F_status_is_error(main->setting.state.status)) {
      firewall_print_error(&main->program.error, macro_firewall_f(f_fss_apply_delimit));

      return;
    }

    firewall_operate_process_rules(main);

    if (F_status_is_error(main->setting.state.status)) {
      if (F_status_set_fine(main->setting.state.status) != F_failure) {
        firewall_print_error_unhandled(&main->error, macro_firewall_f(firewall_operate_process_rules));
      }

      return;
    }

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_operate_load_rules_

#ifdef __cplusplus
} // extern "C"
#endif
