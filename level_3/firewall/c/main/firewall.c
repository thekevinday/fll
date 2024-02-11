#include "firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_main_
  void firewall_main(firewall_main_t * const main) {

    if (!main) return;

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & firewall_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if ((main->setting.flag & firewall_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    main->setting.state.status = F_okay;

    if (main->setting.flag & firewall_main_flag_version_copyright_help_e) {
      if (main->setting.flag & firewall_main_flag_help_e) {
        firewall_print_message_help(&main->program.message);
      }
      else if (main->setting.flag & firewall_main_flag_version_e) {
        fll_program_print_version(&main->program.message, firewall_program_version_s);
      }
      else if (main->setting.flag & firewall_main_flag_copyright_e) {
        fll_program_print_copyright(&main->program.message);
      }

      if ((main->setting.flag & firewall_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if (main->setting.flag & firewall_main_flag_operation_e) {
      firewall_operate(main);
    }
    else {
      main->setting.state.status = F_status_set_error(F_parameter);

      firewall_print_error_operation_specified_not(&main->program.error);
    }

    if ((main->setting.flag & firewall_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    if (F_status_is_error(main->setting.state.status) || main->setting.state.status == F_interrupt) return;

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_main_

#ifdef __cplusplus
} // extern "C"
#endif
