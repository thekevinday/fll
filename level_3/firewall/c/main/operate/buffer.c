#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_buffer_rules_
  f_status_t firewall_operate_buffer_rules(firewall_main_t * const main, const f_string_static_t filename, const bool optional) {

    if (!main) return F_status_set_error(F_parameter);

    f_file_t file = f_file_t_initialize;

    f_status_t status = f_file_open(filename, 0, &file);

    if (F_status_is_error(status)) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        if (optional) {
          if (F_status_set_fine(status) == F_parameter) {
            firewall_print_error_on_invalid_parameter(data->main->error, "f_file_open");
          }
          else if (F_status_set_fine(status) != F_file_found_not && F_status_set_fine(status) != F_file_open && F_status_set_fine(status) != F_file_descriptor) {
            firewall_print_error_on_unhandled(data->main->error, "f_file_open", F_status_set_fine(status));
          }
        } else {
          if (F_status_set_fine(status) == F_parameter) {
            firewall_print_error_on_invalid_parameter(data->main->error, "f_file_open");
          }
          else if (F_status_set_fine(status) == F_file_found_not) {
            fll_print_format("%r%[%QUnable to find the file '%Q'.%]%r", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, filename, data->main->error.context, f_string_eol_s);
          }
          else if (F_status_set_fine(status) == F_file_open) {
            fll_print_format("%r%[%QUnable to open the file '%Q'.%]%r", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, filename, data->main->error.context, f_string_eol_s);
          }
          else if (F_status_set_fine(status) == F_file_descriptor) {
            fll_print_format("%r%[%QFile descriptor error while trying to open the file '%Q'.%]%r", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, filename, data->main->error.context, f_string_eol_s);
          }
          else {
            firewall_print_error_on_unhandled(data->main->error, "f_file_open", F_status_set_fine(status));
          }
        }
      }

      return status;
    }

    status = f_file_read(file, &local->buffer);

    f_file_stream_flush(file);
    f_file_stream_close(&file);

    if (F_status_is_error(status)) {
      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        if (F_status_set_fine(status) == F_parameter) {
          firewall_print_error_on_invalid_parameter(data->main->error, "f_file_read");
        }
        else if (F_status_set_fine(status) == F_number_overflow) {
          fll_print_format("%r%[%QInteger overflow while trying to buffer the file '%Q'.%]%r", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, filename, data->main->error.context, f_string_eol_s);
        }
        else if (F_status_set_fine(status) == F_file_closed) {
          fll_print_format("%r%[%QThe file '%Q' is no longer open.%]%r", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, filename, data->main->error.context, f_string_eol_s);
        }
        else if (F_status_set_fine(status) == F_file_seek) {
          fll_print_format("%r%[%QA seek error occurred while accessing the file '%Q'.%]%r", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, filename, data->main->error.context, f_string_eol_s);
        }
        else if (F_status_set_fine(status) == F_file_read) {
          fll_print_format("%r%[%QA read error occurred while accessing the file '%Q'.%]%r", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, filename, data->main->error.context, f_string_eol_s);
        }
        else if (F_status_set_fine(status) == F_memory_not) {
          firewall_print_error_on_allocation_failure(data->main->error);
        }
        else {
          firewall_print_error_on_unhandled(data->main->error, "f_file_read", F_status_set_fine(status));
        }
      }

      return status;
    }

    f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;
    f_range_t comments = f_range_t_initialize;
    f_state_t state = f_state_t_initialize;

    {
      f_range_t input = macro_f_range_t_initialize_2(local->buffer.used);

      status = fll_fss_basic_list_read(local->buffer, state, &input, &local->chain_objects, &local->chain_contents, &delimits, 0, &comments);
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
        if (status == F_parameter) {
          firewall_print_error_on_invalid_parameter_for_file(data->main->error, "fll_fss_basic_list_read", filename);
        }
        else if (status == F_data_not_eos || status == F_data_not || status == F_data_not_stop) {
          fll_print_format("%r%[%QNo relevant main was found within the file '%Q'.%]%r", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, filename, data->main->error.context, f_string_eol_s);
        }
        else if (status == F_memory_not) {
          firewall_print_error_on_allocation_failure(data->main->error);
        }
        else {
          firewall_print_error_on_unhandled_for_file(data->main->error, "fll_fss_basic_read", status, filename);
        }
      }
    }
    else {
      status = f_fss_apply_delimit(state, delimits, &local->buffer);

      if (F_status_is_error(status)) {
        fll_error_print(data->main->error, F_status_set_fine(status), "f_fss_apply_delimit", fll_error_file_flag_fallback_e);
      }
    }

    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &delimits.array, &delimits.used, &delimits.size);
    macro_f_range_t_delete_simple(comments);

    return status;
  }
#endif // _di_firewall_operate_buffer_rules_

#ifdef __cplusplus
} // extern "C"
#endif
