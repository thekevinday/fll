#include "iki_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_process_
  void iki_write_process(iki_write_main_t * const main, const f_string_static_t object, const f_string_static_t content) {

    if (!object.used) {
      main->setting.state.status = F_status_set_error(F_failure);

      fll_program_print_error_missing_variable_not_zero(&main->program.error, iki_write_object_s);

      return;
    }

    main->setting.state.status = f_iki_object_is(object);

    if (main->setting.state.status == F_false) {
      main->setting.state.status = F_status_set_error(F_failure);

      iki_write_print_error_object_not_valid(&main->program.error, object);

      return;
    }

    if (F_status_is_error(main->setting.state.status)) {
      iki_write_print_error(&main->program.error, macro_iki_write_f(f_iki_object_is));

      return;
    }

    main->setting.escaped.used = 0;

    main->setting.state.status = fll_iki_content_escape(content, main->setting.quote, &main->setting.escaped);

    if (F_status_is_error(main->setting.state.status)) {
      iki_write_print_error(&main->program.error, macro_iki_write_f(fll_iki_content_escape));

      return;
    }

    if (main->setting.flag & iki_write_main_flag_wrap_e) {
      fl_print_format("%r%Q%r%r%r%Q%r", main->program.output.to, f_iki_syntax_wrap_open_s, object, f_iki_syntax_wrap_close_s, f_iki_syntax_separator_s, main->setting.quote, main->setting.escaped, main->setting.quote);
    }
    else {
      fl_print_format("%Q%r%r%Q%r", main->program.output.to, object, f_iki_syntax_separator_s, main->setting.quote, main->setting.escaped, main->setting.quote);
    }
  }
#endif // _di_iki_write_process_

#ifdef __cplusplus
} // extern "C"
#endif
