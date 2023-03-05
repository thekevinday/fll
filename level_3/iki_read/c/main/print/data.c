#include "../iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_print_data_
  void iki_read_print_data(fll_program_data_t * const main, iki_read_setting_t * const setting, const f_array_length_t index) {

    if (!setting) return;

    if (!main) {
      setting->state.status = F_status_set_error(F_parameter);
    }

    f_array_length_t at = setting->reassign.used;

    if (setting->reassign.used && (setting->flag & (iki_read_main_flag_content_e | iki_read_main_flag_literal_e))) {
      at = iki_read_identify_substitution(setting, setting->data.vocabulary.array[index], setting->data.content.array[index], &setting->reassign);
    }

    if (at < setting->reassign.used) {
      if (setting->flag & iki_read_main_flag_content_e) {
        f_print_dynamic(setting->reassign.array[at].c, main->output.to);
      }
      else {
        f_string_range_t range = macro_f_string_range_t_initialize(setting->data.variable.array[index].start, setting->data.content.array[index].start - 1);

        f_print_dynamic_partial(setting->buffer, range, main->output.to);

        f_print_dynamic(setting->reassign.array[at].c, main->output.to);

        range.start = setting->data.content.array[index].stop + 1;
        range.stop = setting->data.variable.array[index].stop;

        f_print_dynamic_partial(setting->buffer, range, main->output.to);
      }

      return;
    }

    at = setting->substitute.used;

    if (setting->substitute.used && (setting->flag & (iki_read_main_flag_content_e | iki_read_main_flag_literal_e))) {
      at = iki_read_identify_substitution(setting, setting->data.vocabulary.array[index], setting->data.content.array[index], &setting->substitute);
    }

    if (at < setting->substitute.used) {
      if (setting->flag & iki_read_main_flag_content_e) {
        iki_read_print_data_wrap_prepend(main, setting, index);

        f_print_dynamic(setting->substitute.array[at].c, main->output.to);

        iki_read_print_data_wrap_append(main, setting, index);
      }
      else {
        f_string_range_t range = macro_f_string_range_t_initialize(setting->data.variable.array[index].start, setting->data.content.array[index].start - 1);

        f_print_dynamic_partial(setting->buffer, range, main->output.to);

        iki_read_print_data_wrap_prepend(main, setting, index);

        f_print_dynamic(setting->substitute.array[at].c, main->output.to);

        iki_read_print_data_wrap_append(main, setting, index);

        range.start = setting->data.content.array[index].stop + 1;
        range.stop = setting->data.variable.array[index].stop;

        f_print_dynamic_partial(setting->buffer, range, main->output.to);
      }
    }
    else if (setting->replace.used && setting->map_replaces[index] < setting->replace.used) {
      if (setting->flag & iki_read_main_flag_content_e) {
        iki_read_print_data_wrap_prepend(main, setting, index);

        f_print_dynamic(setting->replace.array[setting->map_replaces[index]].value, main->output.to);

        iki_read_print_data_wrap_append(main, setting, index);
      }
      else if (setting->flag & iki_read_main_flag_object_e) {
        f_print_dynamic(setting->replace.array[setting->map_replaces[index]].name, main->output.to);
      }
      else {
        f_string_range_t range = macro_f_string_range_t_initialize(setting->data.variable.array[index].start, setting->data.content.array[index].start - 1);

        f_print_dynamic_partial(setting->buffer, range, main->output.to);

        iki_read_print_data_wrap_prepend(main, setting, index);

        f_print_dynamic(setting->replace.array[setting->map_replaces[index]].value, main->output.to);

        iki_read_print_data_wrap_append(main, setting, index);

        range.start = setting->data.content.array[index].stop + 1;
        range.stop = setting->data.variable.array[index].stop;

        f_print_dynamic_partial(setting->buffer, range, main->output.to);
      }
    }
    else if (setting->flag & iki_read_main_flag_content_e) {
      iki_read_print_data_wrap_prepend(main, setting, index);

      f_print_dynamic_partial(setting->buffer, setting->data.content.array[index], main->output.to);

      iki_read_print_data_wrap_append(main, setting, index);
    }
    else if (setting->flag & iki_read_main_flag_object_e) {
      f_print_dynamic_partial(setting->buffer, setting->data.vocabulary.array[index], main->output.to);
    }
    else {
      f_string_range_t range = macro_f_string_range_t_initialize(setting->data.variable.array[index].start, setting->data.content.array[index].start - 1);

      f_print_dynamic_partial(setting->buffer, range, main->output.to);

      iki_read_print_data_wrap_prepend(main, setting, index);

      f_print_dynamic_partial(setting->buffer, setting->data.content.array[index], main->output.to);

      iki_read_print_data_wrap_append(main, setting, index);

      range.start = setting->data.content.array[index].stop + 1;
      range.stop = setting->data.variable.array[index].stop;

      f_print_dynamic_partial(setting->buffer, range, main->output.to);
    }
  }
#endif // _di_iki_read_print_data_

#ifndef _di_iki_read_print_data_wrap_append_
  void iki_read_print_data_wrap_append(fll_program_data_t * const main, iki_read_setting_t * const setting, const f_array_length_t index) {

    if (!setting) return;

    if (!main) {
      setting->state.status = F_status_set_error(F_parameter);
    }

    if (index < setting->data.vocabulary.used && setting->map_wraps[index] < setting->wrap.used) {
      if (!setting->wrap.array[setting->map_wraps[index]].c.used) return;
    }
    else {
      return;
    }

    f_print_dynamic(setting->wrap.array[setting->map_wraps[index]].c, main->output.to);
  }
#endif // _di_iki_read_print_data_wrap_append_

#ifndef _di_iki_read_print_data_wrap_prepend_
  void iki_read_print_data_wrap_prepend(fll_program_data_t * const main, iki_read_setting_t * const setting, const f_array_length_t index) {

    if (!setting) return;

    if (!main) {
      setting->state.status = F_status_set_error(F_parameter);
    }

    if (index < setting->data.vocabulary.used && setting->map_wraps[index] < setting->wrap.used) {
      if (!setting->wrap.array[setting->map_wraps[index]].b.used) return;
    }
    else {
      return;
    }

    f_print_dynamic(setting->wrap.array[setting->map_wraps[index]].b, main->output.to);
  }
#endif // _di_iki_read_print_data_wrap_prepend_

#ifdef __cplusplus
} // extern "C"
#endif
