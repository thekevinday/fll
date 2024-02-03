#include "fss_read.h"
#include "../main/fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_payload_process_help_
  void fss_read_payload_process_help(void * const void_main) {

    if (!void_main) return;

    fss_read_payload_print_message_help(&((fss_read_main_t *) void_main)->program.message);
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

      if (main->setting.state.status == F_status_set_error(F_okay_stop) || main->setting.state.status == F_status_set_error(F_okay_eos)) {
        if (main->setting.flag & fss_read_main_flag_payload_error_e) {
          fss_read_payload_print_problem_payload_missing(&main->program.error);

          return;
        }

        if (main->setting.flag & (fss_read_main_flag_payload_error_e | fss_read_main_flag_payload_warn_e)) {
          if (main->program.warning.verbosity > f_console_verbosity_normal_e) {
            fss_read_payload_print_problem_payload_missing(&main->program.warning);
          }

          main->setting.state.status = F_okay;
        }
        else if (main->setting.flag & fss_read_main_flag_payload_create_e) {
          main->setting.state.status = f_string_dynamic_append_assure(f_string_eol_s, &main->setting.buffer);

          if (F_status_is_error(main->setting.state.status)) {
            fss_read_print_error(&main->program.error, macro_fss_read_f(f_string_dynamic_append_assure));
          }
          else {
            main->setting.state.status = f_memory_array_increase(main->setting.state.step_small, sizeof(f_range_t), (void **) &main->setting.objects.array, &main->setting.objects.used, &main->setting.objects.size);

            if (F_status_is_error_not(main->setting.state.status)) {
              main->setting.state.status = f_memory_array_increase(main->setting.state.step_small, sizeof(f_ranges_t), (void **) &main->setting.contents.array, &main->setting.contents.used, &main->setting.contents.size);
            }

            if (F_status_is_error(main->setting.state.status)) {
              fss_read_print_error(&main->program.error, macro_fss_read_f(f_memory_array_increase));
            }
            else {
              main->setting.objects.array[main->setting.objects.used].start = main->setting.buffer.used;

              main->setting.state.status = f_string_dynamic_append(f_fss_payload_s, &main->setting.buffer);

              if (F_status_is_error_not(main->setting.state.status)) {
                main->setting.state.status = f_string_dynamic_append(f_fss_payload_list_open_s, &main->setting.buffer);
              }

              if (F_status_is_error_not(main->setting.state.status)) {
                main->setting.state.status = f_string_dynamic_append(f_fss_payload_list_open_end_s, &main->setting.buffer);
              }

              if (F_status_is_error(main->setting.state.status)) {
                fss_read_print_error(&main->program.error, macro_fss_read_f(f_string_dynamic_append));
              }
              else {
                main->setting.objects.array[main->setting.objects.used].stop = main->setting.objects.array[main->setting.objects.used].start + f_fss_payload_s.used - 1;
                main->setting.contents.array[main->setting.contents.used++].used = 0;
                ++main->setting.objects.used;

                main->setting.state.status = F_okay;
              }
            }
          }
        }
      }
      else {
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

    main->setting.state.status = F_okay;
  }
#endif // _di_fss_read_payload_process_load_

#ifndef _di_fss_read_payload_process_set_
  void fss_read_payload_process_set(void * const void_main) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    main->setting.state.status = F_okay;
  }
#endif // _di_fss_read_payload_process_set_

#ifndef _di_fss_read_payload_setting_load_
  void fss_read_payload_setting_load(const f_console_arguments_t arguments, fss_read_main_t * const main) {

    if (!main) return;

    f_number_unsigneds_t * const values = &main->program.parameters.array[fss_read_parameter_payload_e].values;

    if ((main->program.parameters.array[fss_read_parameter_payload_e].result & f_console_result_value_e) && values->used) {
      f_string_static_t * const argv = main->program.parameters.arguments.array;

      if (f_compare_dynamic(argv[values->array[values->used - 1]], fss_read_string_create_s) == F_equal_to) {
        main->setting.flag |= fss_read_main_flag_payload_create_e;
        main->setting.flag &= ~(fss_read_main_flag_payload_error_e | fss_read_main_flag_payload_warn_e);
      }
      else if (f_compare_dynamic(argv[values->array[values->used - 1]], fss_read_string_none_s) == F_equal_to) {
        main->setting.flag |= fss_read_main_flag_payload_error_e;
        main->setting.flag &= ~(fss_read_main_flag_payload_create_e | fss_read_main_flag_payload_error_e | fss_read_main_flag_payload_warn_e);
      }
      else if (f_compare_dynamic(argv[values->array[values->used - 1]], fss_read_string_error_s) == F_equal_to) {
        main->setting.flag |= fss_read_main_flag_payload_error_e;
        main->setting.flag &= ~(fss_read_main_flag_payload_create_e | fss_read_main_flag_payload_warn_e);
      }
      else if (f_compare_dynamic(argv[values->array[values->used - 1]], fss_read_string_warn_s) == F_equal_to) {
        main->setting.flag |= fss_read_main_flag_payload_warn_e;
        main->setting.flag &= ~(fss_read_main_flag_payload_create_e | fss_read_main_flag_payload_error_e);
      }
      else {
        main->setting.state.status = F_status_set_error(F_parameter);

        fss_read_payload_print_error_parameter_value_payload(&main->program.error, argv[values->array[values->used - 1]]);
      }
    }
  }
#endif // _di_fss_read_payload_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
