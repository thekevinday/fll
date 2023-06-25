#include "fss_identify.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_process_
  void fss_identify_process(fss_identify_main_t * const main, const f_string_static_t name) {

    if (!main) return;

    main->setting.ids.used = 0;

    main->setting.state.status = fll_fss_identify(main->setting.buffer, &main->setting.range, &main->setting.ids);

    if (F_status_is_error(main->setting.state.status)) {
      fss_identify_print_error_file(&main->program.error, macro_fss_identify_f(fll_fss_identify), name.used ? name : f_string_ascii_minus_s, f_file_operation_read_s, name.used ? fll_error_file_type_file_e : fll_error_file_type_pipe_e);

      return;
    }

    // 0 = is name, 1 = is type, 2 = is full.
    uint8_t modes[main->setting.names.used];
    f_number_unsigned_t i = 0;

    if (main->setting.names.used) {
      for (f_number_unsigned_t j = 0; i < main->setting.names.used; ++i) {

        modes[i] = 1;

        for (j = 0; j < main->setting.names.array[i].used; ++j) {

          if (main->setting.names.array[i].string[j] == f_string_ascii_minus_s.string[0]) {
            modes[i] = 2;

            break;
          }

          if (f_utf_is_digit(main->setting.names.array[i].string + j, main->setting.names.array[i].used - j, 0) != F_true) {
            modes[i] = 0;
          }
        } // for
      } // for
    }

    if (main->setting.flag & fss_identify_main_flag_line_e) {
      for (i = 0; i < main->setting.ids.used; ++i, ++main->setting.current) {

        if (main->setting.current == main->setting.line) {
          if (main->setting.names.used) {
            if (fss_identify_process_name_compare(main, main->setting.ids.array[i], modes) != F_equal_to) continue;
          }

          if (main->setting.flag & fss_identify_main_flag_total_e) {
            ++main->setting.total;
          }
          else {
            fss_identify_print_data_id(&main->program.output, main->setting.ids.array[i]);
          }

          ++main->setting.current;

          break;
        }
      } // for
    }
    else if (main->setting.flag & fss_identify_main_flag_total_e) {
      if (main->setting.names.used) {
        for (i = 0; i < main->setting.ids.used; ++i, ++main->setting.current) {

          if (fss_identify_process_name_compare(main, main->setting.ids.array[i], modes) == F_equal_to) {
            ++main->setting.total;
          }
        } // for
      }
      else {
        main->setting.total += main->setting.ids.used;
      }
    }
    else if (main->setting.state.status == F_found || main->setting.state.status == F_maybe) {
      for (i = 0; i < main->setting.ids.used; ++i) {

        if (main->setting.names.used) {
          if (fss_identify_process_name_compare(main, main->setting.ids.array[i], modes) != F_equal_to) continue;
        }

        fss_identify_print_data_id(&main->program.output, main->setting.ids.array[i]);
      } // for
    }

    main->setting.state.status = F_none;
  }
#endif // _di_fss_identify_process_

#ifndef _di_fss_identify_process_name_compare_
  f_status_t fss_identify_process_name_compare(fss_identify_main_t * const main, const f_fll_id_t id, const uint8_t modes[]) {

    if (!main) return F_equal_to_not;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;
    f_number_unsigned_t number = 0;
    f_string_range_t range = f_string_range_t_initialize;

    for (main->setting.state.status = F_equal_to_not; i < main->setting.names.used && main->setting.state.status == F_equal_to_not; ++i) {

      if (modes[i]) {
        if (main->setting.names.array[i].used) {
          range.start = 0;
          range.stop = main->setting.names.array[i].used - 1;
        }
        else {
          range.start = 1;
          range.stop = 0;
        }

        for (j = 0; j < main->setting.names.array[i].used; ++j) {

          if (main->setting.names.array[i].string[j] == f_string_ascii_minus_s.string[0] && j + 1 < main->setting.names.array[i].used) {
            range.start = j + 1;

            break;
          }
        } // for

        {
          main->setting.state.status = fl_conversion_dynamic_partial_to_unsigned(fl_conversion_data_base_16_c, main->setting.names.array[i], range, &number);
          if (F_status_is_error(main->setting.state.status)) return F_equal_to_not;
        }

        if (id.type != number) {
          main->setting.state.status = F_equal_to_not;

          continue;
        }

        if (modes[i] == 1) return F_equal_to;

        if (range.start) {
          range.stop = range.start - 2;
          range.start = 0;
        }

        main->setting.state.status = f_compare_dynamic_partial_string((const f_string_t) id.name, main->setting.names.array[i], id.used, range);
      }
      else {
        main->setting.state.status = f_compare_dynamic_string((const f_string_t) id.name, main->setting.names.array[i], id.used);
      }
    } // for

    return main->setting.state.status == F_equal_to ? F_equal_to : F_equal_to_not;
  }
#endif // _di_fss_identify_process_name_compare_

#ifdef __cplusplus
} // extern "C"
#endif
