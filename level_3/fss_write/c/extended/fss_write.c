#include "fss_write.h"
#include "private-common.h"
#include "private-write.h"
#include "../main/fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_extended_process_content_
  void fss_write_extended_process_content(fll_program_data_t * const main, void * const setting, const f_string_static_t * const content) {

    if (macro_fss_write_setting(setting)->flag & fss_write_flag_partial_e) {
      macro_fss_write_setting(setting)->status = fl_fss_extended_content_write(
        *content,
        (macro_fss_write_setting(setting)->flag & fss_write_flag_single_e) ? f_fss_quote_type_single_e : f_fss_quote_type_double_e,
        f_fss_complete_none_e,
        macro_fss_write_setting(setting)->state,
        &macro_fss_write_setting(setting)->range,
        &macro_fss_write_setting(setting)->buffer
      );
    }
    else {
      macro_fss_write_setting(setting)->status = fl_fss_extended_content_write(
        *content,
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
      fss_write_print_error_unsupported_eol(macro_fss_write_setting(setting), main->error, fss_write_extended_standard_s);
      fss_write_print_line_last_locked(macro_fss_write_setting(setting), main->error);

      return;
    }

    if (F_status_is_error(macro_fss_write_setting(setting)->status)) {
      fss_write_print_error(macro_fss_write_setting(setting), main->error, "fl_fss_extended_content_write");

      return;
    }
  }
#endif // _di_fss_write_extended_process_content_

#ifndef _di_fss_write_extended_process_help_
  void fss_write_extended_process_help(fll_program_data_t * const main, void * const setting) {

    fss_write_extended_print_help(macro_fss_write_setting(setting), main->message);
  }
#endif // _di_fss_write_extended_process_help_

#ifndef _di_fss_write_extended_process_normal_
  void fss_write_extended_process_normal(fll_program_data_t * const main, void * const setting) {

    // @todo
  }
#endif // _di_fss_write_extended_process_normal_

#ifndef _di_fss_write_extended_process_object_
  void fss_write_extended_process_object(fll_program_data_t * const main, void * const setting, const f_string_static_t * const object) {

    if (macro_fss_write_setting(setting)->flag & fss_write_flag_partial_e) {
      macro_fss_write_setting(setting)->status = fl_fss_extended_object_write(
        *object,
        (macro_fss_write_setting(setting)->flag & fss_write_flag_single_e) ? f_fss_quote_type_single_e : f_fss_quote_type_double_e,
        f_fss_complete_none_e,
        macro_fss_write_setting(setting)->state,
        &macro_fss_write_setting(setting)->range,
        &macro_fss_write_setting(setting)->buffer
      );
    }
    else {
      macro_fss_write_setting(setting)->status = fl_fss_extended_object_write(
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
      fss_write_print_error_unsupported_eol(macro_fss_write_setting(setting), main->error, fss_write_extended_standard_s);
      fss_write_print_line_last_locked(macro_fss_write_setting(setting), main->error);

      return;
    }

    if (F_status_is_error(macro_fss_write_setting(setting)->status)) {
      fss_write_print_error(macro_fss_write_setting(setting), main->error, "fl_fss_extended_object_write");
    }
  }
#endif // _di_fss_write_extended_process_object_

#ifndef _di_fss_write_extended_process_pipe_
  void fss_write_extended_process_pipe(fll_program_data_t * const main, void * const setting) {

    // @todo
  }
#endif // _di_fss_write_extended_process_pipe_

#ifdef __cplusplus
} // extern "C"
#endif
