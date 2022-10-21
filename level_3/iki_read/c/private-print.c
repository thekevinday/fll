#include "iki_read.h"
#include "private-common.h"
#include "private-print.h"
#include "private-read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_print_
  void iki_read_print(fll_program_data_t * const main, iki_read_setting_t * const setting, const f_array_length_t index, const bool content_only) {

    f_array_length_t at = setting->substitute.used;

    if (setting->substitute.used && (setting->flag & (iki_read_main_flag_content_e | iki_read_main_flag_literal_e))) {
      at = iki_read_identify_substitution(setting, setting->data.vocabulary.array[index], setting->data.content.array[index]);
    }

    if (at < setting->substitute.used) {
      if (content_only) {
        iki_read_print_wrap_prepend(main, setting, index);

        f_print_dynamic(setting->substitute.array[at].c, main->output.to.stream);

        iki_read_print_wrap_append(main, setting, index);
      }
      else {
        f_string_range_t range = macro_f_string_range_t_initialize(setting->data.variable.array[index].start, setting->data.content.array[index].start - 1);

        f_print_dynamic_partial(setting->buffer, range, main->output.to.stream);

        iki_read_print_wrap_prepend(main, setting, index);

        f_print_dynamic(setting->substitute.array[at].a, main->output.to.stream);

        iki_read_print_wrap_append(main, setting, index);

        f_print_dynamic(setting->substitute.array[at].c, main->output.to.stream);
      }
    }
    else if (setting->replace.used && setting->map_replaces[index] < setting->replace.used) {
      if (content_only) {
        iki_read_print_wrap_prepend(main, setting, index);

        f_print_dynamic(setting->replace.array[index].value, main->output.to.stream);

        iki_read_print_wrap_append(main, setting, index);
      }
      else if (setting->flag & iki_read_main_flag_object_e) {
        f_print_dynamic(setting->replace.array[index].name, main->output.to.stream);
      }
      else {
        f_string_range_t range = macro_f_string_range_t_initialize(setting->data.variable.array[index].start, setting->data.content.array[index].start - 1);

        f_print_dynamic_partial(setting->buffer, setting->data.vocabulary.array[index], main->output.to.stream);
        f_print_dynamic_partial(setting->buffer, range, main->output.to.stream);

        iki_read_print_wrap_prepend(main, setting, index);

        f_print_dynamic_partial(setting->buffer, setting->data.content.array[index], main->output.to.stream);

        iki_read_print_wrap_append(main, setting, index);

        f_print_dynamic(setting->replace.array[index].value, main->output.to.stream);

        range.start = setting->data.content.array[index].stop + 1;
        range.stop = setting->data.variable.array[index].stop;

        f_print_dynamic_partial(setting->buffer, range, main->output.to.stream);
      }
    }
    else if (content_only) {
      iki_read_print_wrap_prepend(main, setting, index);

      f_print_dynamic_partial(setting->buffer, setting->data.content.array[index], main->output.to.stream);

      iki_read_print_wrap_append(main, setting, index);
    }
    else if (setting->flag & iki_read_main_flag_object_e) {
      f_print_dynamic_partial(setting->buffer, setting->data.vocabulary.array[index], main->output.to.stream);
    }
    else {
      f_string_range_t range = macro_f_string_range_t_initialize(setting->data.variable.array[index].start, setting->data.content.array[index].start - 1);

      f_print_dynamic_partial(setting->buffer, setting->data.vocabulary.array[index], main->output.to.stream);
      f_print_dynamic_partial(setting->buffer, range, main->output.to.stream);

      iki_read_print_wrap_prepend(main, setting, index);

      f_print_dynamic_partial(setting->buffer, setting->data.content.array[index], main->output.to.stream);

      iki_read_print_wrap_append(main, setting, index);

      range.start = setting->data.content.array[index].stop + 1;
      range.stop = setting->data.variable.array[index].stop;

      f_print_dynamic_partial(setting->buffer, range, main->output.to.stream);
    }
  }
#endif // _di_iki_read_print_

#ifndef _di_iki_read_print_wrap_append_
  void iki_read_print_wrap_append(fll_program_data_t * const main, iki_read_setting_t * const setting, const f_array_length_t index) {

    if (!(index < setting->wrap.used && setting->wrap.array[setting->map_wraps[index]].c.used)) return;

    f_print_dynamic(setting->wrap.array[setting->map_wraps[index]].c, main->output.to.stream);
  }
#endif // _di_iki_read_print_wrap_append_

#ifndef _di_iki_read_print_wrap_prepend_
  void iki_read_print_wrap_prepend(fll_program_data_t * const main, iki_read_setting_t * const setting, const f_array_length_t index) {

    if (!(index < setting->wrap.used && setting->wrap.array[setting->map_wraps[index]].b.used)) return;

    f_print_dynamic(setting->wrap.array[setting->map_wraps[index]].b, main->output.to.stream);
  }
#endif // _di_iki_read_print_wrap_prepend_

#ifdef __cplusplus
} // extern "C"
#endif
