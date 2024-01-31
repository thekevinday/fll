#include "../fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_print_at_
  f_status_t fss_read_print_at(fl_print_t * const print, const f_number_unsigned_t at, const f_number_unsigneds_t delimits_object, const f_number_unsigneds_t delimits_content) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_read_main_t * const main = (fss_read_main_t *) print->custom;

    if (at >= main->setting.contents.used) return F_output_not;

    bool print_set_end = F_false;

    if ((main->setting.flag & fss_read_main_flag_object_e) || (main->setting.flag & fss_read_main_flag_content_e) && (main->setting.contents.array[at].used || (main->setting.flag & fss_read_main_flag_empty_e))) {
      if (main->setting.flag & fss_read_main_flag_object_e) {
        if (main->callback.print_object) {
          main->callback.print_object(&main->program.output, at, delimits_object);
        }

        if (main->callback.print_object_end) {
          main->callback.print_object_end(&main->program.output);
        }

        print_set_end = F_true;
      }

      if (main->setting.flag & fss_read_main_flag_content_e) {
        if (main->setting.flag & fss_read_main_flag_select_e) {
          if (main->setting.contents.array[at].used) {
            if (main->setting.select < main->setting.contents.array[at].used) {
              if (main->setting.contents.array[at].array[main->setting.select].start <= main->setting.contents.array[at].array[main->setting.select].stop) {
                print_set_end = F_true;

                if (main->callback.print_content) {
                  main->callback.print_content(&main->program.output, main->setting.contents.array[at].array[main->setting.select], main->setting.quotes_content.array[at].used ? main->setting.quotes_content.array[at].array[main->setting.select] : 0, delimits_content);
                }
              }
              else {
                print_set_end = F_true;
              }
            }
          }
          else if (main->callback.print_content_empty_set && !main->setting.select) {
            main->callback.print_content_empty_set(&main->program.output);
          }
        }
        else if (main->setting.contents.array[at].used) {
          print_set_end = F_true;

          if (main->callback.print_content) {
            for (f_number_unsigned_t i = 0; i < main->setting.contents.array[at].used; ++i) {

              main->callback.print_content(&main->program.output, main->setting.contents.array[at].array[i], main->setting.quotes_content.array[at].used ? main->setting.quotes_content.array[at].array[i] : 0, delimits_content);

              if (main->callback.print_content_next && i + 1 < main->setting.contents.array[at].used) {
                main->callback.print_content_next(&main->program.output);
              }
            } // for
          }
        }
        else if (main->callback.print_content_empty_set) {
          main->callback.print_content_empty_set(&main->program.output);
        }
      }

      if (print_set_end && main->callback.print_set_end) {
        main->callback.print_set_end(&main->program.output);
      }
    }

    return F_okay;
  }
#endif // _di_fss_read_print_at_

#ifndef _di_fss_read_print_content_
  f_status_t fss_read_print_content(fl_print_t * const print, const f_range_t range, const uint8_t quote, const f_number_unsigneds_t delimits) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_read_main_t * const main = (fss_read_main_t *) print->custom;

    if (main->callback.print_content_ignore) {
      main->callback.print_content_ignore(&main->program.output);
    }

    if (main->setting.flag & fss_read_main_flag_original_e) {
      if (main->setting.flag & fss_read_main_flag_quote_content_e) {
        fss_read_print_quote(&main->program.output, quote);
      }
    }

    fll_print_except_in_dynamic_partial(main->setting.buffer, range, delimits, main->setting.comments, print->to);

    if (main->setting.flag & fss_read_main_flag_original_e) {
      if (main->setting.flag & fss_read_main_flag_quote_content_e) {
        fss_read_print_quote(&main->program.output, quote);
      }
    }

    if (main->callback.print_content_ignore) {
      main->callback.print_content_ignore(&main->program.output);
    }

    return F_okay;
  }
#endif // _di_fss_read_print_content_

#ifndef _di_fss_read_print_content_empty_set_end_
  f_status_t fss_read_print_content_empty_set_end(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_read_main_t * const main = (fss_read_main_t *) print->custom;

    if (main->callback.print_set_end && (main->setting.flag & fss_read_main_flag_empty_e)) {
      main->callback.print_set_end(print);
    }

    return F_okay;
  }
#endif // _di_fss_read_print_content_empty_set_end_

#ifndef _di_fss_read_print_content_ignore_
  f_status_t fss_read_print_content_ignore(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_read_main_t * const main = (fss_read_main_t *) print->custom;

    if (main->setting.flag & fss_read_main_flag_pipe_format_e) {
      fll_print_dynamic_raw(fss_read_pipe_content_ignore_s, print->to);
    }

    return F_okay;
  }
#endif // _di_fss_read_print_content_ignore_

#ifndef _di_fss_read_print_number_
  f_status_t fss_read_print_number(fl_print_t * const print, const f_number_unsigned_t number) {

    if (!print) return F_status_set_error(F_output_not);

    fll_print_format("%ul%r", print->to, number, f_string_eol_s);

    return F_okay;
  }
#endif // _di_fss_read_print_number_

#ifndef _di_fss_read_print_object_
  f_status_t fss_read_print_object(fl_print_t * const print, const f_number_unsigned_t at, const f_number_unsigneds_t delimits) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_read_main_t * const main = (fss_read_main_t *) print->custom;

    if (at >= main->setting.objects.used) return F_output_not;

    if (main->setting.flag & (fss_read_main_flag_trim_e | fss_read_main_flag_trim_object_e)) {
      if (main->setting.flag & fss_read_main_flag_original_e) {
        if (main->setting.quotes_object.array[at]) {
          fss_read_print_quote(&main->program.output, main->setting.quotes_object.array[at]);
        }

        fll_print_trim_dynamic_partial(main->setting.buffer, main->setting.objects.array[at], main->program.output.to);

        if (main->setting.quotes_object.array[at]) {
          fss_read_print_quote(&main->program.output, main->setting.quotes_object.array[at]);
        }
      }
      else {
        fll_print_trim_except_dynamic_partial(main->setting.buffer, main->setting.objects.array[at], delimits, main->program.output.to);
      }
    }
    else {
      if (main->setting.flag & fss_read_main_flag_original_e) {
        if (main->setting.quotes_object.array[at]) {
          fss_read_print_quote(&main->program.output, main->setting.quotes_object.array[at]);
        }

        fll_print_dynamic_partial(main->setting.buffer, main->setting.objects.array[at], main->program.output.to);

        if (main->setting.quotes_object.array[at]) {
          fss_read_print_quote(&main->program.output, main->setting.quotes_object.array[at]);
        }
      }
      else {
        fll_print_except_dynamic_partial(main->setting.buffer, main->setting.objects.array[at], delimits, main->program.output.to);
      }
    }

    return F_okay;
  }
#endif // _di_fss_read_print_object_

#ifndef _di_fss_read_print_quote_
  f_status_t fss_read_print_quote(fl_print_t * const print, const uint8_t type) {

    if (!print) return F_status_set_error(F_output_not);

    if (type) {
      fll_print_dynamic_raw(
        type == f_fss_quote_type_single_e
          ? f_fss_quote_single_s
          : type == f_fss_quote_type_grave_e
            ? f_fss_quote_grave_s
            : f_fss_quote_double_s,
        print->to
      );
    }

    return F_okay;
  }
#endif // _di_fss_read_print_quote_

#ifndef _di_fss_read_print_set_end_
  f_status_t fss_read_print_set_end(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_read_main_t * const main = (fss_read_main_t *) print->custom;

    fll_print_dynamic_raw((main->setting.flag & fss_read_main_flag_pipe_format_e) ? fss_read_pipe_content_end_s : f_string_eol_s, print->to);

    return F_okay;
  }
#endif // _di_fss_read_print_set_end_

#ifndef _di_fss_read_print_set_end_no_eol_
  f_status_t fss_read_print_set_end_no_eol(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_read_main_t * const main = (fss_read_main_t *) print->custom;

    if (main->setting.flag & fss_read_main_flag_pipe_format_e) {
      fll_print_dynamic_raw(fss_read_pipe_content_end_s, print->to);
    }

    return F_okay;
  }
#endif // _di_fss_read_print_set_end_no_eol_

#ifdef __cplusplus
} // extern "C"
#endif
