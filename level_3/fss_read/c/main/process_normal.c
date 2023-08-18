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
    if (!(main->setting.flag & fss_read_main_flag_depth_multiple_e) && main->setting.depths.array[0].depth || !(main->setting.flag & fss_read_main_flag_content_multiple_e) && ((main->setting.flag & fss_read_main_flag_select_e) && main->setting.select)) {
      if (main->setting.flag & fss_read_main_flag_total_e) {
        fss_read_print_number(&main->program.output, 0);
      }

      main->setting.state.status = F_okay;

      return;
    }

    // The process_load() callback is required to be non-NULL.
    if (!main->callback.process_load) return;

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

    main->callback.process_load(main);
    if (F_status_is_error(main->setting.state.status)) return;

    const f_number_unsigneds_t * const delimits_object = !(main->setting.flag & fss_read_main_flag_original_e) && fss_read_delimit_object_is(main, 0) ? &main->setting.delimits_object : &fss_read_except_none_c;
    const f_number_unsigneds_t * const delimits_content = !(main->setting.flag & fss_read_main_flag_original_e) && fss_read_delimit_content_is(main, 0) ? &main->setting.delimits_content : &fss_read_except_none_c;

    bool names[main->setting.objects.used];

    if (main->callback.process_name) {
      main->callback.process_name(main, names);
      if (F_status_is_error(main->setting.state.status)) return;
    }
    else if (main->setting.objects.used) {

      // If no processing is enabled, then default to F_true to enable all names.
      memset(names, F_true, sizeof(bool) * main->setting.objects.used);
    }

    if (main->setting.flag & fss_read_main_flag_total_e) {
      if (main->callback.process_total) {
        main->callback.process_total(main, names);
      }
    }
    else if (main->setting.flag & fss_read_main_flag_at_e) {
      if (main->callback.process_at) {
        main->callback.process_at(main, names, *delimits_object, *delimits_content);
      }
    }
    else if (main->setting.flag & fss_read_main_flag_columns_e) {
      if (main->callback.process_columns) {
        main->callback.process_columns(main, names);
      }
    }
    else {
      f_number_unsigned_t i = 0;

      if (main->setting.flag & fss_read_main_flag_line_e) {
        if (main->callback.process_at_line) {
          f_number_unsigned_t line = 0;

          for (; i < main->setting.contents.used && main->setting.state.status != F_success; ++i) {

            if (!names[i]) continue;
            if (fss_read_signal_check(main)) return;

            main->callback.process_at_line(void_main, i, *delimits_object, *delimits_content, &line);
            if (F_status_is_error(main->setting.state.status)) return;
          } // for
        }
      }
      else if (main->callback.print_at) {
        for (; i < main->setting.contents.used; ++i) {

          if (!names[i]) continue;
          if (fss_read_signal_check(main)) return;

          main->callback.print_at(&main->program.output, i, *delimits_object, *delimits_content);
        } // for
      }
    }

    if (F_status_is_error(main->setting.state.status)) return;

    main->setting.state.status = F_okay;
  }
#endif // _di_fss_read_process_normal_

#ifndef _di_fss_read_process_normal_at_
  void fss_read_process_normal_at(void * const void_main, const bool names[], const f_number_unsigneds_t delimits_object, f_number_unsigneds_t delimits_content) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    if (main->setting.depths.array[0].value_at >= main->setting.objects.used) {
      if (main->setting.flag & (fss_read_main_flag_columns_e | fss_read_main_flag_total_e)) {
        fss_read_print_number(&main->program.output, 0);
      }

      main->setting.state.status = F_okay;

      return;
    }

    // If the standard only has one line per Content, then any line value greater than 0 equates to no line to print.
    if ((main->setting.flag & fss_read_main_flag_line_e) && (main->setting.flag & fss_read_main_flag_line_single_e)) {
      if (main->setting.line) {
        main->setting.state.status = F_okay;

        return;
      }
    }

    f_number_unsigned_t i = 0;
    f_number_unsigned_t at = 0;

    for (; i < main->setting.objects.used; ++i) {

      if (!names[i]) continue;
      if (fss_read_signal_check(main)) return;

      if (at == main->setting.depths.array[0].value_at) {
        if (main->setting.flag & fss_read_main_flag_line_e) {

          // If using "--at" for standards that only support one line per Object, then the only valid line is line 0.
          if ((main->setting.flag & fss_read_main_flag_line_single_e) && !at) break;

          if (main->callback.process_at_line) {
            f_number_unsigned_t line = 0;

            main->callback.process_at_line(void_main, i, delimits_object, delimits_content, &line);
          }
        }
        else if (main->setting.flag & fss_read_main_flag_columns_e) {
          fss_read_print_number(&main->program.output, main->setting.contents.array[i].used);
        }
        else if (main->callback.print_at) {
          main->callback.print_at(&main->program.output, i, delimits_object, delimits_content);
        }

        if (F_status_is_error(main->setting.state.status)) return;

        main->setting.state.status = F_okay;

        return;
      }

      ++at;
    } // for

    if (F_status_is_error(main->setting.state.status)) return;

    if (main->setting.flag & fss_read_main_flag_total_e) {
      fss_read_print_number(&main->program.output, 0);
    }

    main->setting.state.status = F_okay;
  }
#endif // _di_fss_read_process_normal_at_

#ifndef _di_fss_read_process_normal_at_line_
  void fss_read_process_normal_at_line(void * const void_main, const f_number_unsigned_t at, const f_number_unsigneds_t delimits_object, const f_number_unsigneds_t delimits_content, f_number_unsigned_t * const line) {

    if (!void_main || !line) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    if (main->setting.flag & fss_read_main_flag_object_e) {
      if (*line == main->setting.line) {
        if (main->callback.print_object) {
          main->callback.print_object(&main->program.output, at, delimits_object);
        }

        if (main->callback.print_object_end) {
          main->callback.print_object_end(&main->program.output);
        }

        if (!(main->setting.flag & fss_read_main_flag_content_e)) {
          if (!(main->setting.flag & fss_read_main_flag_object_as_line_e)) {
            f_print_dynamic_raw(f_string_eol_s, main->program.output.to);
          }

          main->setting.state.status = F_success;

          return;
        }
      }

      if ((main->setting.flag & fss_read_main_flag_object_as_line_e) || !(main->setting.flag & fss_read_main_flag_content_e)) {
        ++(*line);
      }
    }

    if (main->setting.flag & fss_read_main_flag_content_e) {
      if (!main->setting.contents.array[at].used) {

        // Must process/count line when both Object and Content share the same line but Content is empty.
        if ((main->setting.flag & fss_read_main_flag_object_e) && !(main->setting.flag & fss_read_main_flag_object_as_line_e) && (main->setting.flag & fss_read_main_flag_line_single_e)) {
          if (*line == main->setting.line) {
            f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

            main->setting.state.status = F_success;

            return;
          }

          ++(*line);
        }

        main->setting.state.status = F_okay;

        return;
      }

      f_number_unsigned_t i = 0;

      if (main->setting.flag & fss_read_main_flag_line_single_e) {
        if (*line == main->setting.line) {
          while (main->setting.contents.array[at].used) {

            fss_read_print_content(&main->program.output, main->setting.contents.array[at].array[i], main->setting.quotes_content.array[at].array[i], delimits_content);

            if (++i >= main->setting.contents.array[at].used) break;

            if (main->callback.print_content_next) {
              main->callback.print_content_next(&main->program.output);
            }
          } // while

          f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

          main->setting.state.status = F_success;

          return;
        }

        ++(*line);
      }
      else {
        f_number_unsigned_t line_original = 0;
        f_number_unsigned_t j = 0;
        f_number_unsigned_t k = 0;

        for (; i < main->setting.contents.array[at].used; ++i) {

          if (fss_read_signal_check(main)) return;

          line_original = *line;
          main->setting.range = main->setting.contents.array[at].array[i];
          k = 0;

          for (j = main->setting.range.start; j <= main->setting.range.stop; ++j) {

            if (fss_read_signal_check(main)) return;

            if (k < main->setting.comments.used) {
              while (main->setting.comments.array[k].stop < j) ++k;

              if (j >= main->setting.comments.array[k].start && j <= main->setting.comments.array[k].stop) {
                j = main->setting.comments.array[k++].stop + 1;

                if (j > main->setting.range.stop) break;
              }
            }

            if (main->setting.buffer.string[j] == f_string_eol_s.string[0]) {
              if (*line == main->setting.line) {
                main->setting.range.stop = j;

                fss_read_print_content(&main->program.output, main->setting.range, main->setting.quotes_content.array[at].array[i], delimits_content);

                main->setting.state.status = F_success;

                return;
              }

              main->setting.range.start = j + 1;

              if (j <= main->setting.range.stop) {
                ++(*line);
              }
            }
          } // for

          // If Content does not end with a newline, it still must be treated as the last line.
          if ((main->setting.flag & fss_read_main_flag_line_single_e) && *line == line_original) {
            ++(*line);

            if (*line == main->setting.line) {
              main->setting.range.stop = main->setting.contents.array[at].array[i].stop;

              fss_read_print_content(&main->program.output, main->setting.range, main->setting.quotes_content.array[at].array[i], delimits_content);
              f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

              main->setting.state.status = F_success;

              return;
            }
          }
        } // for
      }

      // @fixme The fll_fss_*_read functions do not have a store of the set closing ranges but should.
      //        Simulate the ending by printing, but the original range should ideally be used (add new features to accomplish this).
      if ((main->setting.flag & fss_read_main_flag_object_e) && (main->setting.flag & fss_read_main_flag_content_has_close_e)) {
        if (*line == main->setting.line) {
          if (main->callback.print_set_end) {
            main->callback.print_set_end(&main->program.output);
          }

          main->setting.state.status = F_success;

          return;
        }

        ++(*line);
      }
    }

    main->setting.state.status = F_okay;
  }
#endif // _di_fss_read_process_normal_at_line_

#ifndef _di_fss_read_process_normal_columns_
  void fss_read_process_normal_columns(void * const void_main, const bool names[]) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    if (!(main->setting.flag & fss_read_main_flag_content_e)) {
      fss_read_print_number(&main->program.output, 0);

      main->setting.state.status = F_okay;

      return;
    }

    f_number_unsigned_t max = 0;

    if (main->setting.flag & fss_read_main_flag_content_multiple_e) {
      for (f_number_unsigned_t at = 0; at < main->setting.contents.used; ++at) {

        if (!names[at]) continue;
        if (fss_read_signal_check(main)) return;

        if (main->setting.contents.array[at].used > max) {
          max = main->setting.contents.array[at].used;
        }
      } // for
    }
    else {
      for (f_number_unsigned_t at = 0; at < main->setting.contents.used; ++at) {

        if (names[at]) {
          max = 1;

          break;
        }

        if (fss_read_signal_check(main)) return;
      } // for
    }

    fss_read_print_number(&main->program.output, max);

    main->setting.state.status = F_okay;
  }
#endif // _di_fss_read_process_normal_columns_

#ifndef _di_fss_read_process_normal_name_
  void fss_read_process_normal_name(void * const void_main, bool names[]) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    if (main->setting.depths.array[0].index_name) {
      f_number_unsigned_t i = 0;

      memset(names, F_false, sizeof(bool) * main->setting.objects.used);

      if (main->setting.flag & (fss_read_main_flag_trim_e | fss_read_main_flag_trim_object_e | fss_read_main_flag_object_trim_e)) {
        for (i = 0; i < main->setting.objects.used; ++i) {

          if (fss_read_signal_check(main)) return;

          if (f_compare_dynamic_partial_except_trim_dynamic(main->setting.depths.array[0].value_name, main->setting.buffer, main->setting.objects.array[i], fss_read_except_none_c, main->setting.delimits_object) == F_equal_to) {
            names[i] = F_true;
          }
        } // for
      }
      else {
        for (i = 0; i < main->setting.objects.used; ++i) {

          if (fss_read_signal_check(main)) return;

          if (f_compare_dynamic_partial_except_dynamic(main->setting.depths.array[0].value_name, main->setting.buffer, main->setting.objects.array[i], fss_read_except_none_c, main->setting.delimits_object) == F_equal_to) {
            names[i] = F_true;
          }
        } // for
      }
    }
    else {
      memset(names, F_true, sizeof(bool) * main->setting.objects.used);
    }

    main->setting.state.status = F_okay;
  }
#endif // _di_fss_read_process_normal_name_

#ifndef _di_fss_read_process_normal_total_
  void fss_read_process_normal_total(void * const void_main, const bool names[]) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    f_number_unsigned_t total = 0;
    f_number_unsigned_t i = 0;

    if (main->setting.flag & fss_read_main_flag_select_e) {
      for (; i < main->setting.contents.used; ++i) {

        if (!names[i]) continue;
        if (fss_read_signal_check(main)) return;

        if (main->setting.flag & fss_read_main_flag_at_e) {
          if (main->setting.depths.array[0].value_at != i) continue;
        }

        if (main->setting.select < main->setting.contents.array[i].used && main->setting.contents.array[i].array[main->setting.select].start <= main->setting.contents.array[i].array[main->setting.select].stop) {
          ++total;
        }
      } // for
    }
    else {
      for (; i < main->setting.objects.used; ++i) {

        if (!names[i]) continue;
        if (fss_read_signal_check(main)) return;

        if (main->setting.flag & fss_read_main_flag_at_e) {
          if (main->setting.depths.array[0].value_at != i) continue;
        }

        if (!(main->setting.flag & fss_read_main_flag_object_e) && (main->setting.flag & fss_read_main_flag_content_e)) {
          if (!(main->setting.contents.array[i].used || (main->setting.flag & fss_read_main_flag_empty_e))) continue;
        }

        ++total;
      } // for
    }

    fss_read_print_number(
      &main->program.output,
      main->setting.flag & fss_read_main_flag_line_e
        ? main->setting.line < total ? 1 : 0
        : total
    );

    main->setting.state.status = F_okay;
  }
#endif // _di_fss_read_process_normal_total_

#ifndef _di_fss_read_process_normal_total_multiple_
  void fss_read_process_normal_total_multiple(void * const void_main, const bool names[]) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    f_number_unsigned_t total = 0;
    f_string_range_t range = f_string_range_t_initialize;
    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;
    f_number_unsigned_t k = 0;

    for (f_number_unsigned_t at = 0; at < main->setting.contents.used; ++at) {

      if (!names[at]) continue;
      if (fss_read_signal_check(main)) return;

      if (main->setting.flag & fss_read_main_flag_at_e) {
        if (main->setting.depths.array[0].value_at != at) continue;
      }

      if (main->setting.flag & fss_read_main_flag_object_e) {
        ++total;
      }

      if (main->setting.flag & fss_read_main_flag_content_e) {

        if (!main->setting.contents.array[at].used) continue;

        for (i = 0; i < main->setting.contents.array[at].used; ++i) {

          range.start = main->setting.contents.array[at].array[i].start;
          range.stop = main->setting.contents.array[at].array[i].stop;

          // This content has no data, do not even check "include empty" because it cannot be counted as a line.
          if (range.start > range.stop) continue;

          for (j = range.start; j <= range.stop; ++j) {

            if (k < main->setting.comments.used) {
              while (main->setting.comments.array[k].stop < j) ++k;

              if (j >= main->setting.comments.array[k].start && j <= main->setting.comments.array[k].stop) {
                j = main->setting.comments.array[k++].stop;

                continue;
              }
            }

            if (main->setting.buffer.string[j] == f_string_eol_s.string[0]) ++total;
          } // for
        } // for

        // If Content does not end with a newline, it still must be treated as the last line.
        if ((main->setting.flag & fss_read_main_flag_line_single_e) && i) {
          j = main->setting.contents.array[at].array[i - 1].stop;

          if (main->setting.buffer.string[j] != f_string_eol_s.string[0]) ++total;
        }

        if ((main->setting.flag & fss_read_main_flag_object_e) && (main->setting.flag & fss_read_main_flag_content_has_close_e)) {
           ++total;
        }
      }
    } // for

    fss_read_print_number(
      &main->program.output,
      main->setting.flag & fss_read_main_flag_line_e
        ? main->setting.line < total ? 1 : 0
        : total
    );

    main->setting.state.status = F_okay;
  }
#endif // _di_fss_read_process_normal_total_multiple_

#ifdef __cplusplus
} // extern "C"
#endif
