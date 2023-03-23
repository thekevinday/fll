#include "fss_write.h"
#include "../main/fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_embedded_list_process_content_
  void fss_write_embedded_list_process_content(void * const void_main, const bool last) {

    if (!void_main) return;

    fss_write_main_t * const main = (fss_write_main_t *) void_main;

    if (main->setting.content) {
      fl_fss_embedded_list_content_write(
        *main->setting.content,
        (main->setting.flag & fss_write_main_flag_partial_e)
          ? f_fss_complete_partial_e
          : last
            ? f_fss_complete_end_e
            : f_fss_complete_next_e,
        &main->setting.prepend,
        main->setting.ignores,
        &main->setting.range,
        &main->setting.buffer,
        &main->setting.state
      );

      if (F_status_set_fine(main->setting.state.status) == F_none_eol) {
        main->setting.state.status = F_status_set_error(F_support_not);

        fss_write_print_error_unsupported_eol(&main->program.error);

        return;
      }

      if (F_status_is_error(main->setting.state.status)) {
        fss_write_print_error(&main->program.error, macro_fss_write_f(fl_fss_embedded_list_content_write));

        return;
      }
    }

    if ((main->setting.flag & fss_write_main_flag_partial_e) && !(main->setting.flag & fss_write_main_flag_object_e) || !(main->setting.flag & (fss_write_main_flag_object_e | fss_write_main_flag_content_e))) {
      if (main->setting.flag & fss_write_main_flag_content_end_e) {
        main->setting.state.status = f_string_dynamic_append(f_fss_embedded_list_close_s, &main->setting.buffer);

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append(f_fss_embedded_list_close_end_s, &main->setting.buffer);
        }

        if (F_status_is_error(main->setting.state.status)) {
          fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamic_append));
        }
      }
    }
  }
#endif // _di_fss_write_embedded_list_process_content_

#ifndef _di_fss_write_embedded_list_process_help_
  void fss_write_embedded_list_process_help(void * const void_main) {

    if (!void_main) return;

    fss_write_embedded_list_print_help(&((fss_write_main_t *) void_main)->program.message);
  }
#endif // _di_fss_write_embedded_list_process_help_

#ifndef _di_fss_write_embedded_list_process_object_
  void fss_write_embedded_list_process_object(void * const void_main) {

    if (!void_main) return;

    fss_write_main_t * const main = (fss_write_main_t *) void_main;

    if (main->setting.object) {
      fl_fss_embedded_list_object_write(
        *main->setting.object,
        (main->setting.flag & fss_write_main_flag_partial_e)
          ? (main->setting.flag & fss_write_main_flag_trim_e)
            ? f_fss_complete_trim_e
            : f_fss_complete_none_e
          : (main->setting.flag & fss_write_main_flag_trim_e)
            ? f_fss_complete_full_trim_e
            : f_fss_complete_full_e,
        &main->setting.range,
        &main->setting.buffer,
        &main->setting.state
      );

      if (F_status_set_fine(main->setting.state.status) == F_none_eol) {
        main->setting.state.status = F_status_set_error(F_support_not);

        fss_write_print_error_unsupported_eol(&main->program.error);

        return;
      }

      if (F_status_is_error(main->setting.state.status)) {
        fss_write_print_error(&main->program.error, macro_fss_write_f(fl_fss_embedded_list_object_write));

        return;
      }
    }

    if ((main->setting.flag & fss_write_main_flag_partial_e) && !(main->setting.flag & fss_write_main_flag_content_e) || !(main->setting.flag & (fss_write_main_flag_object_e | fss_write_main_flag_content_e))) {
      if (main->setting.flag & fss_write_main_flag_object_open_e) {
        main->setting.state.status = f_string_dynamic_append(f_fss_embedded_list_open_s, &main->setting.buffer);

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append(f_fss_embedded_list_open_end_s, &main->setting.buffer);
        }

        if (F_status_is_error(main->setting.state.status)) {
          fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamic_append));
        }
      }
    }
  }
#endif // _di_fss_write_embedded_list_process_object_

#ifdef __cplusplus
} // extern "C"
#endif
