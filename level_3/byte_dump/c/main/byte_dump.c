#include "byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_main_
  void byte_dump_main(byte_dump_main_t * const main) {

    if (!main) return;

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & byte_dump_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if ((main->setting.flag & byte_dump_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    main->setting.state.status = F_none;

    if (main->setting.flag & (byte_dump_main_flag_help_e | byte_dump_main_flag_version_e | byte_dump_main_flag_copyright_e)) {
      if (main->setting.flag & byte_dump_main_flag_help_e) {
        byte_dump_print_message_help(&main->program.message);
      }
      else if (main->setting.flag & byte_dump_main_flag_version_e) {
        fll_program_print_version(&main->program.message, byte_dump_program_version_s);
      }
      else if (main->setting.flag & byte_dump_main_flag_copyright_e) {
        fll_program_print_copyright(&main->program.message);
      }

      if ((main->setting.flag & byte_dump_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if (main->setting.files.used || (main->program.pipe & fll_program_data_pipe_input_e)) {
      f_file_t file = f_file_t_initialize;

      if (main->program.pipe & fll_program_data_pipe_input_e) {
        file.id = F_type_descriptor_input_d;
        file.stream = F_type_input_d;

        byte_dump_print_file_header(&main->program.output, f_string_empty_s);

        byte_dump_process_file(main, f_string_empty_s, file);
      }

      if (main->setting.files.used && F_status_is_error_not(main->setting.state.status)) {
        file.id = -1;
        file.stream = 0;

        for (f_number_unsigned_t i = 0; i < main->setting.files.used; ++i) {

          if (byte_dump_signal_check(main)) break;
          if (!main->setting.files.array[i].used) continue;

          main->setting.state.status = f_file_stream_open(main->setting.files.array[i], f_string_empty_s, &file);

          if (F_status_is_error(main->setting.state.status)) {
            byte_dump_print_error_file(&main->program.error, macro_byte_dump_f(f_file_stream_open), main->setting.files.array[i], f_file_operation_open_s, fll_error_file_type_file_e);

            break;
          }

          byte_dump_print_file_header(&main->program.output, main->setting.files.array[i]);

          byte_dump_process_file(main, main->setting.files.array[i], file);

          f_file_stream_flush(file);
          f_file_stream_close(&file);

          if (F_status_is_error(main->setting.state.status)) break;
        } // for
      }
      else {
        main->setting.state.status = F_false;
      }
    }
    else {
      main->setting.state.status = F_status_set_error(F_parameter);

      byte_dump_print_error_file_none(&main->program.error);
    }

    if ((main->setting.flag & byte_dump_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }
  }
#endif // _di_byte_dump_main_

#ifdef __cplusplus
} // extern "C"
#endif
