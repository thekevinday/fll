#include "fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_extended_print_at_
  f_status_t fss_read_extended_print_at(fl_print_t * const print, const f_array_length_t at, const f_fss_delimits_t delimits_object, const f_fss_delimits_t delimits_content) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_read_main_t * const main = (fss_read_main_t *) print->custom;

    if (at >= main->setting.contents.used) return F_output_not;

    // @todo This is copied from fss_read_print_at() and needs to be updated to handle multiple content.

    if ((main->setting.flag & fss_read_main_flag_object_e) || (main->setting.flag & fss_read_main_flag_content_e) && (main->setting.contents.array[at].used || (main->setting.flag & fss_read_main_flag_empty_e))) {
      if (main->setting.flag & fss_read_main_flag_object_e) {
        if (main->callback.print_object) {
          main->callback.print_object(&main->program.output, at, delimits_object);
        }

        if (main->setting.flag & fss_read_main_flag_content_e) {
          if (main->callback.print_object_end) {
            main->callback.print_object_end(&main->program.output);
          }
        }
      }

      if ((main->setting.flag & fss_read_main_flag_content_e) && main->setting.contents.array[at].used) {
        if (main->callback.print_content) {
          main->callback.print_content(&main->program.output, main->setting.contents.array[at].array[0], main->setting.quotes_content.array[at].used ? main->setting.quotes_content.array[at].array[0] : 0, delimits_content);
        }
      }

      if (main->callback.print_set_end) {
        main->callback.print_set_end(&main->program.output);
      }
    }

    return F_none;
  }
#endif // _di_fss_read_extended_print_at_

#ifndef _di_fss_read_extended_print_help_
  f_status_t fss_read_extended_print_help(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, fss_read_extended_program_name_long_s, fss_read_program_version_s);

    fss_read_print_message_help(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, fss_read_extended_program_name_s, f_string_empty_s);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fss_read_print_message_help_note_header(print, fss_read_format_code_short_0001_s, fss_read_format_code_name_0001_s);

    fss_read_print_message_help_pipe(print);

    fss_read_print_message_help_note(print, F_false);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_fss_read_extended_print_help_

#ifdef __cplusplus
} // extern "C"
#endif
