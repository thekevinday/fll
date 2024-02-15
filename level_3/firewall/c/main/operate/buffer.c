#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_buffer_rules_
  void firewall_operate_buffer_rules(firewall_main_t * const main, const f_string_static_t file, const bool optional) {

    if (!main || F_status_is_error_not(main->setting.state.status) && main->setting.state.status == F_child) return;

    main->data.buffer.used = 0;

    main->setting.state.status = f_file_open(file, 0, &main->cache.file);

    if (F_status_is_error(main->setting.state.status)) {
      if (!optional || optional && F_status_set_fine(main->setting.state.status) != F_file_found_not && F_status_set_fine(main->setting.state.status) != F_file_open && F_status_set_fine(main->setting.state.status) != F_file_descriptor) {
        firewall_print_error_file(&main->program.error, macro_firewall_f(f_file_open), f_file_operation_open_s, fll_error_file_type_file_e);

        return;
      }
    }

    main->setting.state.status = f_file_read(main->cache.file, &main->data.buffer);

    f_file_stream_flush(main->cache.file);
    f_file_stream_close(&main->cache.file);

    if (F_status_is_error(main->setting.state.status)) {
      firewall_print_error_file(&main->program.error, macro_firewall_f(f_file_read), f_file_operation_read_s, fll_error_file_type_file_e);

      return;
    }

    if (main->data.buffer.used) {
      main->data.range.start = 0;
      main->data.range.stop = main->data.buffer.used - 1;

// @fixme bufferchain_objects, etc..
      main->setting.state.status = fll_fss_basic_list_read(main->data.buffer, main->setting.state, &main->data.range, &main->data.bufferchain_objects, &main->data.bufferchain_contents, &main->data.delimits, 0, &main->data.comments);

      if (F_status_is_error(main->setting.state.status)) {
        if (F_status_set_fine(main->setting.state.status) == F_data_not_eos || F_status_set_fine(main->setting.state.status) == F_data_not || F_status_set_fine(main->setting.state.status) == F_data_not_stop) {
          firewall_print_error_file_empty(&main->program.error, file);
        }
        else {
          firewall_print_error_file(&main->program.error, macro_firewall_f(fll_fss_basic_list_read), f_file_operation_process_s, fll_error_file_type_file_e);
        }

        return;
      }
      else {
        main->setting.state.status = f_fss_apply_delimit(state, main->data.delimits, &main->data.buffer);

        if (F_status_is_error(main->setting.state.status)) {
          firewall_print_error(&main->program.error, macro_firewall_f(f_fss_apply_delimit));

          return;
        }
      }
    }

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_operate_buffer_rules_

#ifdef __cplusplus
} // extern "C"
#endif
