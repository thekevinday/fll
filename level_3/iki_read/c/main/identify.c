#include "iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_identify_alteration_
  void iki_read_identify_alteration(iki_read_main_t * const main) {

    if (!main || !(main->setting.replace.used || main->setting.wrap.used)) return;

    f_number_unsigned_t i = 0;

    if (main->setting.flag & (iki_read_main_flag_content_e | iki_read_main_flag_literal_e)) {
      f_number_unsigned_t j = 0;

      for (i = 0; i < main->setting.data.vocabulary.used; ++i) {

        if (main->setting.replace.used) {
          main->setting.map_replaces[i] = main->setting.replace.used;

          j = main->setting.replace.used - 1;

          do {
            if (f_compare_dynamic_partial_string(main->setting.replace.array[j].name.string, main->setting.buffer, main->setting.replace.array[j].name.used, main->setting.data.vocabulary.array[i]) == F_equal_to) {
              main->setting.map_replaces[i] = j;

              break;
            }

          } while (j--);
        }

        if (main->setting.wrap.used) {
          main->setting.map_wraps[i] = main->setting.wrap.used;

          j = main->setting.wrap.used - 1;

          do {
            if (f_compare_dynamic_partial_string(main->setting.wrap.array[j].a.string, main->setting.buffer, main->setting.wrap.array[j].a.used, main->setting.data.vocabulary.array[i]) == F_equal_to) {
              main->setting.map_wraps[i] = j;

              break;
            }

          } while (j--);
        }
      } // for
    }
    else {
      for (i = 0; i < main->setting.data.vocabulary.used; ++i) {

        if (main->setting.replace.used) {
          main->setting.map_replaces[i] = main->setting.replace.used;
        }

        if (main->setting.wrap.used) {
          main->setting.map_wraps[i] = main->setting.wrap.used;
        }
      } // for
    }
  }
#endif // _di_iki_read_identify_alteration_

#ifndef _di_iki_read_identify_substitution_
  f_number_unsigned_t iki_read_identify_substitution(iki_read_main_t * const main, const f_range_t name, const f_range_t value, f_string_triples_t *triple) {

    f_number_unsigned_t i = triple->used - 1;

    do {
      if (f_compare_dynamic_partial_string(triple->array[i].a.string, main->setting.buffer, triple->array[i].a.used, name) == F_equal_to) {
        if (f_compare_dynamic_partial_string(triple->array[i].b.string, main->setting.buffer, triple->array[i].b.used, value) == F_equal_to) {
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
