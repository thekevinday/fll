#include "fss_read.h"
#include "../main/fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_extended_process_content_
  void fss_read_extended_process_content(void * const void_main, const bool last) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    if (main->setting.content) {
      fl_fss_extended_content_write(
        *main->setting.content,
        main->setting.quote.used
          ? main->setting.quote.string[0]
          : f_fss_quote_double_s.string[0],
        (main->setting.flag & fss_read_main_flag_partial_e)
          ? f_fss_complete_partial_e
          : last
            ? f_fss_complete_end_e
            : f_fss_complete_next_e,
        &main->setting.range,
        &main->setting.buffer,
        &main->setting.state
      );

      if (F_status_set_fine(main->setting.state.status) == F_none_eol) {
        main->setting.state.status = F_status_set_error(F_support_not);

        fss_read_print_error_unsupported_eol(&main->program.error);

        return;
      }

      if (F_status_is_error(main->setting.state.status)) {
        fss_read_print_error(&main->program.error, macro_fss_read_f(fl_fss_extended_content_write));

        return;
      }
    }

    if ((main->setting.flag & fss_read_main_flag_partial_e) && !(main->setting.flag & fss_read_main_flag_object_e) || !(main->setting.flag & (fss_read_main_flag_object_e | fss_read_main_flag_content_e))) {
      if (main->setting.flag & fss_read_main_flag_content_end_e) {
        main->setting.state.status = f_string_dynamic_append(f_fss_extended_close_s, &main->setting.buffer);

        if (F_status_is_error(main->setting.state.status)) {
          fss_read_print_error(&main->program.error, macro_fss_read_f(f_string_dynamic_append));
        }
      }
      else if (main->setting.flag & fss_read_main_flag_content_next_e) {
        main->setting.state.status = f_string_dynamic_append(f_fss_extended_next_s, &main->setting.buffer);

        if (F_status_is_error(main->setting.state.status)) {
          fss_read_print_error(&main->program.error, macro_fss_read_f(f_string_dynamic_append));
        }
      }
    }
  }
#endif // _di_fss_read_extended_process_content_

#ifndef _di_fss_read_extended_process_help_
  void fss_read_extended_process_help(void * const void_main) {

    if (!void_main) return;

    fss_read_extended_print_help(&((fss_read_main_t *) void_main)->program.message);
  }
#endif // _di_fss_read_extended_process_help_

#ifndef _di_fss_read_extended_process_object_
  void fss_read_extended_process_object(void * const void_main) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    if (main->setting.object) {
      fl_fss_extended_object_write(
        *main->setting.object,
        main->setting.quote.used
          ? main->setting.quote.string[0]
          : f_fss_quote_double_s.string[0],
        (main->setting.flag & fss_read_main_flag_partial_e)
          ? (main->setting.flag & fss_read_main_flag_trim_e)
            ? f_fss_complete_trim_e
            : f_fss_complete_none_e
          : (main->setting.flag & fss_read_main_flag_trim_e)
            ? f_fss_complete_full_trim_e
            : f_fss_complete_full_e,
        &main->setting.range,
        &main->setting.buffer,
        &main->setting.state
      );

      if (F_status_set_fine(main->setting.state.status) == F_none_eol) {
        main->setting.state.status = F_status_set_error(F_support_not);

        fss_read_print_error_unsupported_eol(&main->program.error);

        return;
      }

      if (F_status_is_error(main->setting.state.status)) {
        fss_read_print_error(&main->program.error, macro_fss_read_f(fl_fss_extended_object_write));

        return;
      }
    }

    if ((main->setting.flag & fss_read_main_flag_partial_e) && !(main->setting.flag & fss_read_main_flag_content_e) || !(main->setting.flag & (fss_read_main_flag_object_e | fss_read_main_flag_content_e))) {
      if (main->setting.flag & fss_read_main_flag_object_open_e) {
        main->setting.state.status = f_string_dynamic_append(f_fss_extended_open_s, &main->setting.buffer);
        if (F_status_is_error(main->setting.state.status)) {
          fss_read_print_error(&main->program.error, macro_fss_read_f(f_string_dynamic_append));
        }
      }
    }
  }
#endif // _di_fss_read_extended_process_object_

#ifdef __cplusplus
} // extern "C"
#endif
