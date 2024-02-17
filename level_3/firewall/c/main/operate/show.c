#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_show_
  void firewall_operate_show(firewall_main_t * const main) {

    if (!main) return;

    int return_code = 0;

    f_string_statics_t parameters = f_string_statics_t_initialize;
    parameters.used = 6;

    f_string_static_t show_nats[] = {
      firewall_show_parameter_exact_s,
      firewall_show_parameter_verbose_s,
      firewall_show_parameter_table_s,
      firewall_show_nat_s,
      firewall_show_parameter_numeric_s,
      firewall_show_parameter_list_s,
    };

    f_string_static_t show_mangles[] = {
      firewall_show_parameter_exact_s,
      firewall_show_parameter_verbose_s,
      firewall_show_parameter_table_s,
      firewall_show_mangle_s,
      firewall_show_parameter_numeric_s,
      firewall_show_parameter_list_s,
    };

    f_string_static_t show_filters[] = {
      firewall_show_parameter_exact_s,
      firewall_show_parameter_verbose_s,
      firewall_show_parameter_numeric_s,
      firewall_show_parameter_list_s,
    };

    f_string_static_t * const show_arrays[] = {
      show_nats,
      show_mangles,
      show_filters,
    };

    const f_number_unsigned_t show_lengths[] = {
      6,
      6,
      4,
    };

    const f_string_static_t show_lefts[] = {
      firewall_print_show_bars_27_s,
      firewall_print_show_bars_26_s,
      firewall_print_show_bars_26_s,
    };

    const f_string_static_t show_headers[] = {
      firewall_print_show_nat_s,
      firewall_print_show_mangle_s,
      firewall_print_show_filter_s,
    };

    const f_string_static_t show_rights[] = {
      firewall_print_show_bars_28_s,
      firewall_print_show_bars_26_s,
      firewall_print_show_bars_26_s,
    };

    const uint16_t show_flags[] = {
      firewall_main_flag_operation_show_nat_e,
      firewall_main_flag_operation_show_mangle_e,
      firewall_main_flag_operation_show_filter_e,
    };

    for (uint8_t i = 0; i < 3; ++i) {

      if (!show_flags[i]) continue;

      parameters.array = show_arrays[i];
      parameters.used = show_lengths[i];
      return_code = 0;

      // A newline should be printed before each inner message header, but not the first.
      if (i) {
        f_print_dynamic_raw(f_string_eol_s, main->program.output.to);
      }

      firewall_print_message_show_header(&main->program.output, show_lefts[i], show_headers[i], show_rights[i]);

      main->setting.state.status = fll_execute_program(firewall_tool_iptables_s, parameters, 0, 0, (void *) &return_code);

      if (main->setting.state.status == F_child) {
        main->program.child = return_code;

        return;
      }

      if (F_status_is_error(main->setting.state.status)) {
        firewall_print_error_operation(&main->program.error, firewall_tool_iptables_s, parameters);

        return;
      }
      else if (return_code) {
        firewall_print_error_operation_return_code(&main->program.error, firewall_tool_iptables_s, main->cache.arguments, return_code);
      }
    } // for

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_operate_show_

#ifdef __cplusplus
} // extern "C"
#endif
