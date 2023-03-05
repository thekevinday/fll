#include "iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_identify_alteration_
  void iki_read_identify_alteration(iki_read_setting_t * const setting) {

    if (!(setting->replace.used || setting->wrap.used)) return;

    f_array_length_t i = 0;

    if (setting->flag & (iki_read_main_flag_content_e | iki_read_main_flag_literal_e)) {
      f_array_length_t j = 0;

      for (i = 0; i < setting->data.vocabulary.used; ++i) {

        if (setting->replace.used) {
          setting->map_replaces[i] = setting->replace.used;

          j = setting->replace.used - 1;

          do {
            if (fl_string_dynamic_partial_compare_string(setting->replace.array[j].name.string, setting->buffer, setting->replace.array[j].name.used, setting->data.vocabulary.array[i]) == F_equal_to) {
              setting->map_replaces[i] = j;

              break;
            }

          } while (j--);
        }

        if (setting->wrap.used) {
          setting->map_wraps[i] = setting->wrap.used;

          j = setting->wrap.used - 1;

          do {
            if (fl_string_dynamic_partial_compare_string(setting->wrap.array[j].a.string, setting->buffer, setting->wrap.array[j].a.used, setting->data.vocabulary.array[i]) == F_equal_to) {
              setting->map_wraps[i] = j;

              break;
            }

          } while (j--);
        }
      } // for
    }
    else {
      for (i = 0; i < setting->data.vocabulary.used; ++i) {

        if (setting->replace.used) {
          setting->map_replaces[i] = setting->replace.used;
        }

        if (setting->wrap.used) {
          setting->map_wraps[i] = setting->wrap.used;
        }
      } // for
    }
  }
#endif // _di_iki_read_identify_alteration_

#ifndef _di_iki_read_identify_substitution_
  f_array_length_t iki_read_identify_substitution(iki_read_setting_t * const setting, const f_string_range_t name, const f_string_range_t value, f_string_triples_t *triple) {

    f_array_length_t i = triple->used - 1;

    do {
      if (fl_string_dynamic_partial_compare_string(triple->array[i].a.string, setting->buffer, triple->array[i].a.used, name) == F_equal_to) {
        if (fl_string_dynamic_partial_compare_string(triple->array[i].b.string, setting->buffer, triple->array[i].b.used, value) == F_equal_to) {
          return i;
        }
      }

    } while (i--);

    return triple->used;
  }
#endif // _di_iki_read_identify_substitution_

#ifdef __cplusplus
} // extern "C"
#endif
