#include "fss_read.h"
#include "../main/fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_payload_process_help_
  void fss_read_payload_process_help(void * const void_main) {

    if (!void_main) return;

    fss_read_payload_print_help(&((fss_read_main_t *) void_main)->program.message);
  }
#endif // _di_fss_read_payload_process_help_

#ifndef _di_fss_read_payload_process_load_
  void fss_read_payload_process_load(void * const void_main) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    if (main->setting.buffer.used) {
      main->setting.range.start = 0;
      main->setting.range.stop = main->setting.buffer.used;
    }
    else {
      main->setting.range.start = 1;
      main->setting.range.stop = 0;
    }

    main->setting.objects.used = 0;
    main->setting.contents.used = 0;
    main->setting.comments.used = 0;
    main->setting.delimits_object.used = 0;
    main->setting.delimits_content.used = 0;
    main->setting.nest.used = 0;
    main->setting.quotes_object.used = 0;
    main->setting.quotes_content.used = 0;

    fll_fss_payload_read(main->setting.buffer, &main->setting.range, &main->setting.objects, &main->setting.contents, &main->setting.delimits_object, &main->setting.delimits_content, &main->setting.comments, &main->setting.state);

    if (F_status_is_error(main->setting.state.status)) {
      if (F_status_set_fine(main->setting.state.status) == F_interrupt) return;

      fll_error_file_print(
        &main->program.error,
        F_status_set_fine(main->setting.state.status),
        macro_fss_read_f(fll_fss_payload_read),
        fll_error_file_flag_fallback_e,
        fss_read_file_identify(main->setting.range.start, main->setting.files),
        f_file_operation_process_s,
        fll_error_file_type_file_e
      );

      return;
    }

    if (main->setting.state.status == F_data_not_stop || main->setting.state.status == F_data_not_eos) {
      if (!(main->setting.flag & fss_read_main_flag_total_e)) {
        main->setting.state.status = F_status_set_warning(main->setting.state.status);

        return;
      }
    }

    fss_read_ensure_quotes_length(main);

    if (F_status_is_error(main->setting.state.status)) {
      fss_read_print_error(&main->program.error, macro_fss_read_f(fss_read_ensure_quotes_length));

      return;
    }

    main->setting.state.status = F_none;
  }
#endif // _di_fss_read_payload_process_load_

#ifndef _di_fss_read_payload_process_set_
  void fss_read_payload_process_set(void * const void_main) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    main->setting.state.status = F_none;
  }
#endif // _di_fss_read_payload_process_set_

#ifndef _di_fss_read_payload_setting_load_
  void fss_read_payload_setting_load(const f_console_arguments_t arguments, fss_read_main_t * const main) {

    if (!main) return;

    f_number_unsigneds_t * const values = &main->program.parameters.array[fss_read_parameter_object_e].values;
    f_string_static_t * const argv = main->program.parameters.arguments.array;

    if ((main->program.parameters.array[fss_read_parameter_object_e].result & f_console_result_value_e) && values->used) {
      for (f_number_unsigned_t i = 0; i < values->used; ++i) {

        if (fss_read_signal_check(main)) return;

        if (f_compare_dynamic(argv[values->array[i]], fss_read_payload_s) == F_equal_to && i + 1 < values->used) {
          main->setting.state.status = F_status_set_error(F_parameter);

          fss_read_payload_print_error_payload_not_last(&main->program.error);

          return;
        }
      } // for
    }
  }
#endif // _di_fss_read_payload_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
