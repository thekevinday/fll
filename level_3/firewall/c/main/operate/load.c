#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_load_rules_
  void firewall_operate_load_rules(firewall_main_t * const main) {

    if (!main) return;

    main->data.buffer.used = 0;
    main->data.delimits.used = 0;
    main->data.rule_objects.used = 0;
    main->data.rule_contents.used = 0;

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

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_operate_load_rules_

#ifdef __cplusplus
} // extern "C"
#endif
