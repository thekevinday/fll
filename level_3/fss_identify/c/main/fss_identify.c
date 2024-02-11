#include "fss_identify.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_main_
  void fss_identify_main(fss_identify_main_t * const main) {

    if (!main) return;

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & fss_identify_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if ((main->setting.flag & fss_identify_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    main->setting.state.status = F_okay;

    if (main->setting.flag & fss_identify_main_flag_version_copyright_help_e) {
      if (main->setting.flag & fss_identify_main_flag_help_e) {
        fss_identify_print_message_help(&main->program.message);
      }
      else if (main->setting.flag & fss_identify_main_flag_version_e) {
        fll_program_print_version(&main->program.message, fss_identify_program_version_s);
      }
      else if (main->setting.flag & fss_identify_main_flag_copyright_e) {
        fll_program_print_copyright(&main->program.message);
      }

      if ((main->setting.flag & fss_identify_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if (F_status_is_error_not(main->setting.state.status) && (main->setting.flag & fss_identify_main_flag_pipe_e)) {
      main->setting.file.id = F_type_descriptor_input_d;
      main->setting.file.stream = F_type_input_d;
      main->setting.file.size_read = 512;

      fss_identify_load_line(main, f_string_empty_s);

      if (F_status_is_error_not(main->setting.state.status)) {
        fss_identify_process(main, f_string_empty_s);
      }
    }

    for (f_number_unsigned_t i = 0; F_status_is_error_not(main->setting.state.status) && i < main->setting.files.used; ++i) {

      if (fss_identify_signal_check(main)) break;
      if ((main->setting.flag & fss_identify_main_flag_line_e) && main->setting.current > main->setting.line) break;

      macro_f_file_t_reset(main->setting.file);

      main->setting.file.size_read = 512;

      main->setting.state.status = f_file_stream_open(main->setting.files.array[i], f_string_empty_s, &main->setting.file);

      if (F_status_is_error(main->setting.state.status)) {
        fss_identify_print_error_file(&main->program.error, macro_fss_identify_f(f_file_stream_open), main->setting.files.array[i], f_file_operation_open_s, fll_error_file_type_file_e);
      }
      else {
        fss_identify_load_line(main, main->setting.files.array[i]);

        if (F_status_is_error_not(main->setting.state.status)) {
          fss_identify_process(main, main->setting.files.array[i]);
        }
      }

      f_file_stream_flush(main->setting.file);
      f_file_stream_close(&main->setting.file);
    } // for

    if (F_status_is_error_not(main->setting.state.status)) {
      if (main->setting.flag & fss_identify_main_flag_total_e) {
        fss_identify_print_data_total(&main->program.message);
      }
    }

    if ((main->setting.flag & fss_identify_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    if (F_status_is_error(main->setting.state.status) || main->setting.state.status == F_interrupt) return;

    main->setting.state.status = F_okay;
  }
#endif // _di_fss_identify_main_

#ifdef __cplusplus
} // extern "C"
#endif
