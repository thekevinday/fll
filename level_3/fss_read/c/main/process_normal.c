#include "fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_process_normal_
  void fss_read_process_normal(void * const void_main) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    // @todo note that embedded list will probably need to implement its own version of this function (aka: fss_read_process_embedded).
    // @todo note that payload will probably need to implement its own version of this function (aka: fss_read_process_payload).

    // For depth, most standards do not support nesting, so any depth greater than 0 can be predicted without processing the buffer.
    // For select, most standards do not support multiple select, so any select greater than 0 can be predicted without processing the buffer.
    if (!(main->setting.flag & fss_read_main_flag_depth_multiple_e) && main->setting.depths.array[0].depth || !(main->setting.flag & fss_read_main_flag_content_multiple_e) && ((main->setting.flag & fss_read_main_flag_select_e) && data->select)) {
      if (main->setting.flag & fss_read_main_flag_total_e) {
        f_file_stream_lock(main->program.output.to);

        fss_read_print_number(&main->program.output, 0);

        f_file_stream_unlock(main->program.output.to);
      }

      main->setting.state.status = F_none;

      return;
    }

    // The process_load() callback is required to be non-NULL.
    if (!main->setting.process_load) return;

    main->setting.process_load(main);
    if (F_status_is_error(main->setting.state.status)) return;

    f_array_lengths_t except_none = f_array_lengths_t_initialize;
    f_array_lengths_t *delimits_object = fss_read_delimit_object_is(main, 0) ? &main->setting.delimits_object : &except_none;
    f_array_lengths_t *delimits_content = fss_read_delimit_content_is(main, 0) ? &main->setting.delimits_content : &except_none;

    if (main->setting.flag & fss_read_main_flag_original_e) {
      delimits_object = &except_none;
      delimits_content = &except_none;
    }

    bool names[main->setting.objects.used];

    if (main->setting.process_name) {
      main->setting.process_name(main, names);
      if (F_status_is_error(main->setting.state.status)) return;
    }
    else if (main->setting.objects.used) {
      memset(names, 0, sizeof(bool) * main->setting.objects.used);
    }

    if (main->setting.process_at) {
      main->setting.process_at(main, names, *delimits_object, *delimits_content);

      return;
    }

    if ((main->setting.flag & fss_read_main_flag_columns_e) && main->setting.process_columns) {
      main->setting.process_columns(main, names);

      return;
    }

    if ((main->setting.flag & fss_read_main_flag_total_e) && main->setting.process_total) {
      main->setting.process_total(main, names);

      return;
    }

    if ((main->setting.flag & fss_read_main_flag_line_e) && main->setting.process_line) {
      main->setting.process_line(main, names);

      return;
    }

    if (main->setting.process_print_at) {
      for (f_array_length_t i = 0; i < main->setting.contents.used; ++i) {

        if (!names[i]) continue;
        if (fss_read_signal_check(main)) return;

        main->setting.process_print_at(main, i, *delimits_object, *delimits_content);
      } // for
    }

    main->setting.state.status = F_none;
  }
#endif // _di_fss_read_process_normal_

#ifndef _di_fss_read_process_normal_at_
  void fss_read_process_normal_at(void * const main, const bool names[], const f_array_lengths_t delimits_object, f_array_lengths_t delimits_content) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    if (main->setting.depths.array[0].value_at >= main->setting.objects.used) {
      if (main->setting.flag & (fss_read_main_flag_columns_e | fss_read_main_flag_total_e)) {
        f_file_stream_lock(main->program.output.to);

        fss_read_print_number(&main->program.output, 0);

        f_file_stream_unlock(main->program.output.to);
      }

      main->setting.state.status = F_none;

      return;
    }

    // If the standard only has one line per Content, then any line value greater than 0 equates to no line to print.
    if (main->setting.flag & (fss_read_main_flag_line_e | fss_read_main_flag_line_single_e) == (fss_read_main_flag_line_e | fss_read_main_flag_line_single_e)) {
      if (main->setting.line) {
        if (main->setting.flag & fss_read_main_flag_total_e) {
          f_file_stream_lock(main->program.output.to);

          fss_read_print_zero(main);

          f_file_stream_unlock(main->program.output.to);
        }

        main->setting.state.status = F_none;

        return;
      }
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;
    f_array_length_t at = 0;
    f_array_length_t line = 0;
    f_array_length_t total = 0;

    // @todo this is originally from basic list, compare this against extended and determine what else needs to be done when it comes to quotes (consider checking if flags exist and performing appropriate modifications,  or perhaps custom callback). There probably should be a standard flag for designating that quotes should be printed around Objects and the same for Contents.
    // Example:
    /*
              f_print_dynamic_raw(
                data->quotes_object.array[at] == f_fss_quote_type_single_e
                  ? f_fss_quote_single_s
                  : data->quotes_object.array[at] == f_fss_quote_type_backtick_e
                    ? f_fss_quote_backtick_s
                    : f_fss_quote_double_s,
                main->program.output.to
              );
    */

    for (; i < main->setting.objects.used; ++i) {

      if (!names[i]) continue;
      if (fss_read_signal_check(main)) return;

      if (at == main->setting.depths.array[0].value_at) {
        if (main->setting.flag & fss_read_main_flag_line_e) {

          // For standards that only support one line per Object so when using "--at", then the only valid line is line 0.
          if (main->setting.flag & fss_read_main_flag_line_single_e) break;

          line = 0;

          if (data->option & fss_basic_list_read_data_option_total_d) {

            // Total is always 1 in this case because "line" parameter forces a single line.
            fss_read_print_number(&main->program.output, 1);
          }
          else {
            fss_read_process_at_line(main, data, i, delimits_object, delimits_content, &line);
          }

          if (main->setting.state.status == F_success) {
            main->setting.state.status = F_none;

            return;
          }
        }
        else if (main->setting.flag & fss_read_main_flag_columns_e) {
          fss_read_print_number(&main->program.output, main->setting.contents.array[i].used);
        }
        else if (main->setting.flag & fss_read_main_flag_total_e) {
          total = 0;
          k = 0;

          // @todo this is originally from basic list, compare this against extended list and determine what else needs to be done.

          // Count each new line.
          for (j = 0; j < main->setting.contents.array[i].used; ++j) {

            if (main->setting.contents.array[i].array[j].start > main->setting.contents.array[i].array[j].stop) continue;
            if (main->setting.contents.array[i].array[j].start > main->setting.buffer.used) continue;

            for (k = main->setting.contents.array[i].array[j].start; k <= main->setting.contents.array[i].array[j].stop && k < main->setting.buffer.used; ++k) {
              if (main->setting.buffer.string[k] == f_string_eol_s.string[0]) ++total;
            } // for
          } // for

          // If there are no newline characters but there is data, then this represents a single line.
          if (main->setting.contents.array[i].used && !total) {
            total = 1;
          }

          fss_read_print_number(&main->program.output, total);
        }
        else if (main->setting.process_print_at) {
          main->setting.process_print_at(main, i, delimits_object, delimits_content);
        }

        main->setting.state.status = F_none;

        return;
      }

      ++at;
    } // for

    if (main->setting.flag & fss_read_main_flag_total_e) {
      f_file_stream_lock(main->program.output.to);

      fss_read_print_number(&main->program.output, 0);

      f_file_stream_unlock(main->program.output.to);
    }

    main->setting.state.status = F_none;
  }
#endif // _di_fss_read_process_normal_at_

#ifndef _di_fss_read_process_normal_columns_
  void fss_read_process_normal_columns(void * const main, const bool names[]) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    main->setting.state.status = F_none;
  }
#endif // _di_fss_read_process_normal_columns_

#ifndef _di_fss_read_process_normal_line_
  void fss_read_process_normal_line(void * const main, const bool names[]) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    main->setting.state.status = F_none;
  }
#endif // _di_fss_read_process_normal_line_

#ifndef _di_fss_read_process_normal_load_
  void fss_read_process_normal_load(void * const main) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    main->setting.state.status = F_none;
  }
#endif // _di_fss_read_process_normal_load_

#ifndef _di_fss_read_process_normal_name_
  void fss_read_process_normal_name(void * const main, const bool names[]) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    main->setting.state.status = F_none;
  }
#endif // _di_fss_read_process_normal_name_

#ifndef _di_fss_read_process_normal_print_at_
  void fss_read_process_normal_print_at(void * const main, const f_array_length_t at, const f_fss_delimits_t delimits_object, const f_fss_delimits_t delimits_content) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    main->setting.state.status = F_none;
  }
#endif // _di_fss_read_process_normal_print_at_

#ifndef _di_fss_read_process_normal_read_
  void fss_read_process_normal_read(void * const main, const bool names[]) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    main->setting.state.status = F_none;
  }
#endif // _di_fss_read_process_normal_read_

#ifndef _di_fss_read_process_normal_total_
  void fss_read_process_normal_total(void * const main, const bool names[]) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    main->setting.state.status = F_none;
  }
#endif // _di_fss_read_process_normal_total_

#ifdef __cplusplus
} // extern "C"
#endif
