#include "fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_delimit_content_is_
  f_status_t fss_read_delimit_content_is(fss_read_main_t * const main, const f_array_length_t depth) {

    if (!main) return F_false;

    if (main->setting.delimit_mode == fss_read_delimit_mode_none_e) return F_false;
    if (main->setting.delimit_mode == fss_read_delimit_mode_all_e) return F_true;
    if (depth < main->setting.delimit_depth) return main->setting.delimit_mode == fss_read_delimit_mode_content_lesser_e;
    if (depth == main->setting.delimit_depth) return F_true;

    return main->setting.delimit_mode == fss_read_delimit_mode_content_greater_e;
  }
#endif // _di_fss_read_delimit_content_is_

#ifndef _di_fss_read_delimit_object_is_
  f_status_t fss_read_delimit_object_is(fss_read_main_t * const main, const f_array_length_t depth) {

    if (!main) return F_false;

    switch (main->setting.delimit_mode) {
      case fss_read_delimit_mode_none_e:
      case fss_read_delimit_mode_content_e:
      case fss_read_delimit_mode_content_greater_e:
      case fss_read_delimit_mode_content_lesser_e:
        return F_false;

      case fss_read_delimit_mode_all_e:
      case fss_read_delimit_mode_content_object_e:
      case fss_read_delimit_mode_content_greater_object_e:
      case fss_read_delimit_mode_content_lesser_object_e:
      case fss_read_delimit_mode_object_e:
        return F_true;

      default:
        break;
    }

    return depth == main->setting.delimit_depth || main->setting.delimit_mode == fss_read_delimit_mode_content_lesser_e;
  }
#endif // _di_fss_read_delimit_object_is_

#ifndef _di_fss_read_main_
  void fss_read_main(void * const void_main) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & fss_read_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    main->setting.state.status = F_none;

    if (main->setting.flag & (fss_read_main_flag_help_e | fss_read_main_flag_version_e | fss_read_main_flag_copyright_e)) {
      if (main->setting.flag & fss_read_main_flag_help_e) {
        if (main->callback.process_help) {
          main->callback.process_help(void_main);
        }
        else {
          fss_read_print_message_help(&main->program.message);
        }
      }
      else if (main->setting.flag & fss_read_main_flag_version_e) {
        fll_program_print_version(&main->program.message, fss_read_program_version_s);
      }
      else if (main->setting.flag & fss_read_main_flag_copyright_e) {
        fll_program_print_copyright(&main->program.message);
      }

      if ((main->setting.flag & fss_read_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if (main->setting.flag & (fss_read_main_flag_object_e | fss_read_main_flag_content_e)) {
      if (main->callback.process_normal) {
        main->callback.process_normal(void_main);
      }
    }

    if ((main->setting.flag & fss_read_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }
  }
#endif // _di_fss_read_main_

#ifndef _di_fss_read_process_at_line_
  void fss_read_process_at_line(fss_read_main_t * const main, const f_array_length_t at, const f_array_lengths_t delimits_object, const f_array_lengths_t delimits_content, f_array_length_t * const line) {

    if (!main || !line) return;

    if (main->setting.flag & fss_read_main_flag_object_e) {
      if (*line == main->setting.line) {

        if (main->setting.flag & fss_read_main_flag_total_e) {
          fss_read_print_number(&main->program.output, 1);
        }
        else {
          if (main->callback.print_object) {
            main->callback.print_object(&main->program.output, at, delimits_object);
          }

          if (main->setting.flag & fss_read_main_flag_content_e) {
            if (main->callback.print_object_end) {
              main->callback.print_object_end(&main->program.output);
            }
          }
        }

        main->setting.state.status = F_success;

        return;
      }

      ++(*line);
    }

    // There is only a single Content column for this standard.
    if (main->setting.flag & fss_read_main_flag_content_e) {
      if (!main->setting.contents.array[at].used) {
        main->setting.state.status = F_none;

        return;
      }

      f_string_range_t range = main->setting.contents.array[at].array[0];

      // This content has no data, do not even check "include empty" because it cannot be counted as a line.
      if (range.start > range.stop) {
        main->setting.state.status = F_none;

        return;
      }

      for (f_array_length_t i = range.start; i <= range.stop; ++i) {

        if (fss_read_signal_check(main)) return;

        if (main->setting.buffer.string[i] == f_string_eol_s.string[0]) {
          if (*line == main->setting.line) {
            range.stop = i;

            if (main->setting.flag & fss_read_main_flag_total_e) {
              fss_read_print_number(&main->program.output, 1);
            }
            else {
              fss_read_print_content(&main->program.output, range, main->setting.quotes_content.array[at].array[0], delimits_content);
            }

            main->setting.state.status = F_success;

            return;
          }

          range.start = i + 1;

          if (i <= range.stop) {
            ++(*line);
          }
        }
      } // for

      // If Content does not end with a newline, it still must be treated as the last line.
      if (main->setting.buffer.string[range.stop] != f_string_eol_s.string[0]) {
        ++(*line);

        if (*line == main->setting.line) {
          if (main->setting.flag & fss_read_main_flag_total_e) {
            fss_read_print_number(&main->program.output, 1);
          }
          else {
            range.stop = main->setting.contents.array[at].array[0].stop;

            fss_read_print_content(&main->program.output, range, main->setting.quotes_content.array[at].array[0], delimits_content);
            f_print_dynamic_raw(f_string_eol_s, main->program.output.to);
          }

          main->setting.state.status = F_success;

          return;
        }
      }
    }

    main->setting.state.status = F_none;
  }
#endif // _di_fss_read_process_at_line_

#ifndef _di_fss_read_file_identify_
  f_string_static_t fss_read_file_identify(const f_array_length_t at, const fss_read_files_t files) {

    for (f_array_length_t i = 0; i < files.used; ++i) {
      if (at >= files.array[i].range.start && at <= files.array[i].range.stop) return files.array[i].name;
    } // for

    // When stopped after the end of the buffer, the last file in the list is the correct file.
    if (at > files.array[files.used - 1].range.stop) return files.array[files.used - 1].name;

    return f_string_empty_s;
  }
#endif // _di_fss_read_file_identify_

#ifndef _di_fss_read_process_last_line_
  void fss_read_process_last_line(void * const void_main) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    main->setting.state.status = f_string_dynamic_append_assure(f_string_eol_s, &main->setting.buffer);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_error_file_print(&main->program.error, F_status_set_fine(main->setting.state.status), macro_fss_read_f(f_string_dynamic_append_assure), fll_error_file_flag_fallback_e, f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_pipe_e);
    }
  }
#endif // _di_fss_read_process_last_line_

#ifdef __cplusplus
} // extern "C"
#endif
