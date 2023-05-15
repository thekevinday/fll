#include "fss_read.h"
#include "../main/fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_basic_process_help_
  void fss_read_basic_process_help(void * const void_main) {

    if (!void_main) return;

    fss_read_basic_print_help(&((fss_read_main_t *) void_main)->program.message);
  }
#endif // _di_fss_read_basic_process_help_

#ifndef _di_fss_read_basic_process_load_
  void fss_read_basic_process_load(fss_read_main_t * const main) {

    if (!main) return;

    f_string_range_t input = macro_f_string_range_t_initialize_2(main->setting.buffer.used);

    main->setting.delimits.used = 0;
    main->setting.quotes.used = 0;

    fll_fss_basic_read(main->setting.buffer, &input, &main->setting.objects, &main->setting.contents, &main->setting.quotes_object, &main->setting.delimits, 0, &main->setting.state);

    if (F_status_is_error(data.setting.state.status)) {
      if (F_status_set_fine(data.setting.state.status) == F_interrupt) return;

      fll_error_file_print(
        &main->error,
        F_status_set_fine(data.setting.state.status),
        macro_fss_read_f(fll_fss_basic_read),
        fll_error_file_flag_fallback_e,
        fss_read_file_identify(input.start, main->setting.files),
        f_file_operation_process_s,
        fll_error_file_type_file_e
      );

      return;
    }

    if (data.setting.state.status == F_data_not_stop || data.setting.state.status == F_data_not_eos) {
      if (!(main->setting.flag & fss_read_main_flag_total_e)) {
        data.setting.state.status = F_status_set_warning(status);

        return;
      }
    }

    data.setting.state.status = F_none;
  }
#endif // _di_fss_read_basic_process_load_

#ifdef __cplusplus
} // extern "C"
#endif
