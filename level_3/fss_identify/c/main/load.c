#include "fss_identify.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_load_line_
  void fss_identify_load_line(fss_identify_main_t * const main, const f_string_static_t name) {

    if (!main) return;

    main->setting.state.status = F_okay;
    main->setting.buffer.used = 0;
    main->setting.range.start = 0;
    main->setting.range.stop = 0;

    do {
      if (fss_identify_signal_check(main)) return;

      main->setting.state.status = f_string_dynamic_increase_by(main->setting.file.size_read, &main->setting.buffer);

      if (F_status_is_error(main->setting.state.status)) {
        fss_identify_print_error_file(&main->program.error, macro_fss_identify_f(f_string_dynamic_increase_by), name.used ? name : f_string_ascii_minus_s, f_file_operation_read_s, name.used ? fll_error_file_type_file_e : fll_error_file_type_pipe_e);

        return;
      }

      main->setting.state.status = f_file_stream_read_block(main->setting.file, &main->setting.buffer);

      if (F_status_is_error(main->setting.state.status)) {
        fss_identify_print_error_file(&main->program.error, macro_fss_identify_f(f_file_stream_read_block), name.used ? name : f_string_ascii_minus_s, f_file_operation_read_s, name.used ? fll_error_file_type_file_e : fll_error_file_type_pipe_e);

        return;
      }

      for (; main->setting.range.start < main->setting.buffer.used; ++main->setting.range.start) {
        if (main->setting.buffer.string[main->setting.range.start] == f_string_eol_s.string[0]) break;
      } // for

      main->setting.range.stop = main->setting.range.start;

    } while (main->setting.state.status != F_okay_eof && main->setting.buffer.string[main->setting.range.start] != f_string_eol_s.string[0]);

    // Reset the start point to prepare the buffer for processing.
    main->setting.range.start = 0;

    main->setting.state.status = F_okay;
  }
#endif // _di_fss_identify_load_line_

#ifdef __cplusplus
} // extern "C"
#endif
