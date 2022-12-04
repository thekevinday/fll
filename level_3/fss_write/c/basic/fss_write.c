#include "fss_write.h"
#include "private-common.h"
#include "private-write.h"
#include "../main/fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_basic_process_content_
  void fss_write_basic_process_content(fll_program_data_t * const main, void * const setting, const f_string_static_t * const content) {

    if (macro_fss_write_setting(setting)->flag & fss_write_flag_partial_e) {
      macro_fss_write_setting(setting)->status = fl_fss_basic_content_write(
        *content,
        f_fss_complete_none_e,
        macro_fss_write_setting(setting)->state,
        &macro_fss_write_setting(setting)->range,
        &macro_fss_write_setting(setting)->buffer
      );
    }
    else {
      macro_fss_write_setting(setting)->status = fl_fss_basic_content_write(
        *content,
        (macro_fss_write_setting(setting)->flag & fss_write_flag_trim_e) ? f_fss_complete_full_trim_e : f_fss_complete_full_e,
        macro_fss_write_setting(setting)->state,
        &macro_fss_write_setting(setting)->range,
        &macro_fss_write_setting(setting)->buffer
      );
    }

    if (F_status_set_fine(macro_fss_write_setting(setting)->status) == F_none_eol) {
      macro_fss_write_setting(setting)->status = F_status_set_error(F_supported_not);

      fss_write_print_line_first_locked(macro_fss_write_setting(setting), main->error);
      fss_write_print_error_unsupported_eol(macro_fss_write_setting(setting), main->error, fss_write_basic_standard_s);
      fss_write_print_line_last_locked(macro_fss_write_setting(setting), main->error);

      return;
    }

    if (F_status_is_error(macro_fss_write_setting(setting)->status)) {
      fss_write_print_error(macro_fss_write_setting(setting), main->error, "fl_fss_basic_content_write");

      return;
    }
  }
#endif // _di_fss_write_basic_process_content_

#ifndef _di_fss_write_basic_process_help_
  void fss_write_basic_process_help(fll_program_data_t * const main, void * const setting) {

    fss_write_basic_print_help(macro_fss_write_setting(setting), main->message);
  }
#endif // _di_fss_write_basic_process_help_

#ifndef _di_fss_write_basic_process_object_
  void fss_write_basic_process_object(fll_program_data_t * const main, void * const setting, const f_string_static_t * const object) {

    if (macro_fss_write_setting(setting)->flag & fss_write_flag_partial_e) {
      macro_fss_write_setting(setting)->status = fl_fss_basic_object_write(
        *object,
        (macro_fss_write_setting(setting)->flag & fss_write_flag_single_e) ? f_fss_quote_type_single_e : f_fss_quote_type_double_e,
        f_fss_complete_none_e,
        macro_fss_write_setting(setting)->state,
        &macro_fss_write_setting(setting)->range,
        &macro_fss_write_setting(setting)->buffer
      );
    }
    else {
      macro_fss_write_setting(setting)->status = fl_fss_basic_object_write(
        *object,
        (macro_fss_write_setting(setting)->flag & fss_write_flag_single_e) ? f_fss_quote_type_single_e : f_fss_quote_type_double_e,
        (macro_fss_write_setting(setting)->flag & fss_write_flag_trim_e) ? f_fss_complete_full_trim_e : f_fss_complete_full_e,
        macro_fss_write_setting(setting)->state,
        &macro_fss_write_setting(setting)->range,
        &macro_fss_write_setting(setting)->buffer
      );
    }

    if (F_status_set_fine(macro_fss_write_setting(setting)->status) == F_none_eol) {
      macro_fss_write_setting(setting)->status = F_status_set_error(F_supported_not);

      fss_write_print_line_first_locked(macro_fss_write_setting(setting), main->error);
      fss_write_print_error_unsupported_eol(macro_fss_write_setting(setting), main->error, fss_write_basic_standard_s);
      fss_write_print_line_last_locked(macro_fss_write_setting(setting), main->error);

      return;
    }

    if (F_status_is_error(macro_fss_write_setting(setting)->status)) {
      fss_write_print_error(macro_fss_write_setting(setting), main->error, "fl_fss_basic_object_write");
    }
  }
#endif // _di_fss_write_basic_process_object_

#ifndef _di_fss_write_basic_process_normal_
  void fss_write_basic_process_normal(fll_program_data_t * const main, void * const setting) {

    f_string_statics_t * const data = (macro_fss_write_setting(setting)->flag & fss_write_flag_object_e) ? &macro_fss_write_setting(setting)->objects : &macro_fss_write_setting(setting)->contents;

    for (f_array_length_t i = 0; i < data->used; ++i) {

      // @todo replace all signal checks with forked main process that independently checks and assigns main->signal_received.
      if (!((++main->signal_check) % fss_write_signal_check_d)) {
        if (fll_program_standard_signal_received(main)) {
          macro_fss_write_setting(setting)->status = F_status_set_error(F_interrupt);

          return;
        }

        main->signal_check = 0;
      }

      fss_write_process_set(
        main,
        macro_fss_write_setting(setting),
        (macro_fss_write_setting(setting)->flag & fss_write_flag_object_e) ? &macro_fss_write_setting(setting)->objects.array[i] : 0,
        (macro_fss_write_setting(setting)->flag & fss_write_flag_content_e) ? &macro_fss_write_setting(setting)->contents.array[i] : 0
      );

      if (F_status_is_error(macro_fss_write_setting(setting)->status)) break;
    } // for
  }
#endif // _di_fss_write_basic_process_normal_

#ifndef _di_fss_write_basic_process_pipe_
  void fss_write_basic_process_pipe(fll_program_data_t * const main, void * const setting) {

    // @todo
  }
#endif // _di_fss_write_basic_process_pipe_

#ifdef __cplusplus
} // extern "C"
#endif
