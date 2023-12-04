#include "../iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_print_data_
  void iki_read_print_data(fl_print_t * const print, const f_number_unsigned_t index) {

    if (!print || !print->custom) return;

    iki_read_main_t * const main = (iki_read_main_t *) print->custom;

    f_number_unsigned_t at = main->setting.reassign.used;

    if (main->setting.reassign.used && (main->setting.flag & (iki_read_main_flag_content_e | iki_read_main_flag_literal_e))) {
      at = iki_read_identify_substitution(main, main->setting.data.vocabulary.array[index], main->setting.data.content.array[index], &main->setting.reassign);
    }

    if (at < main->setting.reassign.used) {
      if (main->setting.flag & iki_read_main_flag_content_e) {
        f_print_dynamic(main->setting.reassign.array[at].c, main->program.output.to);
      }
      else {
        f_range_t range = macro_f_range_t_initialize_1(main->setting.data.variable.array[index].start, main->setting.data.content.array[index].start - 1);

        f_print_dynamic_partial(main->setting.buffer, range, main->program.output.to);

        f_print_dynamic(main->setting.reassign.array[at].c, main->program.output.to);

        range.start = main->setting.data.content.array[index].stop + 1;
        range.stop = main->setting.data.variable.array[index].stop;

        f_print_dynamic_partial(main->setting.buffer, range, main->program.output.to);
      }

      return;
    }

    at = main->setting.substitute.used;

    if (main->setting.substitute.used && (main->setting.flag & (iki_read_main_flag_content_e | iki_read_main_flag_literal_e))) {
      at = iki_read_identify_substitution(main, main->setting.data.vocabulary.array[index], main->setting.data.content.array[index], &main->setting.substitute);
    }

    if (at < main->setting.substitute.used) {
      if (main->setting.flag & iki_read_main_flag_content_e) {
        iki_read_print_data_wrap_prepend(&main->program.output, index);

        f_print_dynamic(main->setting.substitute.array[at].c, main->program.output.to);

        iki_read_print_data_wrap_append(&main->program.output, index);
      }
      else {
        f_range_t range = macro_f_range_t_initialize_1(main->setting.data.variable.array[index].start, main->setting.data.content.array[index].start - 1);

        f_print_dynamic_partial(main->setting.buffer, range, main->program.output.to);

        iki_read_print_data_wrap_prepend(&main->program.output, index);

        f_print_dynamic(main->setting.substitute.array[at].c, main->program.output.to);

        iki_read_print_data_wrap_append(&main->program.output, index);

        range.start = main->setting.data.content.array[index].stop + 1;
        range.stop = main->setting.data.variable.array[index].stop;

        f_print_dynamic_partial(main->setting.buffer, range, main->program.output.to);
      }
    }
    else if (main->setting.replace.used && main->setting.map_replaces[index] < main->setting.replace.used) {
      if (main->setting.flag & iki_read_main_flag_content_e) {
        iki_read_print_data_wrap_prepend(&main->program.output, index);

        f_print_dynamic(main->setting.replace.array[main->setting.map_replaces[index]].value, main->program.output.to);

        iki_read_print_data_wrap_append(&main->program.output, index);
      }
      else if (main->setting.flag & iki_read_main_flag_object_e) {
        f_print_dynamic(main->setting.replace.array[main->setting.map_replaces[index]].name, main->program.output.to);
      }
      else {
        f_range_t range = macro_f_range_t_initialize_1(main->setting.data.variable.array[index].start, main->setting.data.content.array[index].start - 1);

        f_print_dynamic_partial(main->setting.buffer, range, main->program.output.to);

        iki_read_print_data_wrap_prepend(&main->program.output, index);

        f_print_dynamic(main->setting.replace.array[main->setting.map_replaces[index]].value, main->program.output.to);

        iki_read_print_data_wrap_append(&main->program.output, index);

        range.start = main->setting.data.content.array[index].stop + 1;
        range.stop = main->setting.data.variable.array[index].stop;

        f_print_dynamic_partial(main->setting.buffer, range, main->program.output.to);
      }
    }
    else if (main->setting.flag & iki_read_main_flag_content_e) {
      iki_read_print_data_wrap_prepend(&main->program.output, index);

      f_print_dynamic_partial(main->setting.buffer, main->setting.data.content.array[index], main->program.output.to);

      iki_read_print_data_wrap_append(&main->program.output, index);
    }
    else if (main->setting.flag & iki_read_main_flag_object_e) {
      f_print_dynamic_partial(main->setting.buffer, main->setting.data.vocabulary.array[index], main->program.output.to);
    }
    else {
      f_range_t range = macro_f_range_t_initialize_1(main->setting.data.variable.array[index].start, main->setting.data.content.array[index].start - 1);

      f_print_dynamic_partial(main->setting.buffer, range, main->program.output.to);

      iki_read_print_data_wrap_prepend(&main->program.output, index);

      f_print_dynamic_partial(main->setting.buffer, main->setting.data.content.array[index], main->program.output.to);

      iki_read_print_data_wrap_append(&main->program.output, index);

      range.start = main->setting.data.content.array[index].stop + 1;
      range.stop = main->setting.data.variable.array[index].stop;

      f_print_dynamic_partial(main->setting.buffer, range, main->program.output.to);
    }
  }
#endif // _di_iki_read_print_data_

#ifndef _di_iki_read_print_data_wrap_append_
  void iki_read_print_data_wrap_append(fl_print_t * const print, const f_number_unsigned_t index) {

    if (!print || !print->custom) return;

    iki_read_main_t * const main = (iki_read_main_t *) print->custom;

    if (index < main->setting.data.vocabulary.used && main->setting.map_wraps[index] < main->setting.wrap.used) {
      if (!main->setting.wrap.array[main->setting.map_wraps[index]].c.used) return;
    }
    else {
      return;
    }

    f_print_dynamic(main->setting.wrap.array[main->setting.map_wraps[index]].c, main->program.output.to);
  }
#endif // _di_iki_read_print_data_wrap_append_

#ifndef _di_iki_read_print_data_wrap_prepend_
  void iki_read_print_data_wrap_prepend(fl_print_t * const print, const f_number_unsigned_t index) {

    if (!print || !print->custom) return;

    iki_read_main_t * const main = (iki_read_main_t *) print->custom;

    if (index < main->setting.data.vocabulary.used && main->setting.map_wraps[index] < main->setting.wrap.used) {
      if (!main->setting.wrap.array[main->setting.map_wraps[index]].b.used) return;
    }
    else {
      return;
    }

    f_print_dynamic(main->setting.wrap.array[main->setting.map_wraps[index]].b, main->program.output.to);
  }
#endif // _di_iki_read_print_data_wrap_prepend_

#ifdef __cplusplus
} // extern "C"
#endif
