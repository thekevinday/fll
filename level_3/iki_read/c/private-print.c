#include "iki_read.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_substitutions_print_
  void iki_read_substitutions_print(iki_read_data_t * const data, const f_iki_data_t iki_data, const f_string_ranges_t ranges, const iki_read_substitutions_t substitutions, const f_array_length_t index, const bool content_only) {

    f_status_t status = F_none;
    f_array_length_t i = 0;

    for (; i < substitutions.used; ++i) {

      status = fl_string_dynamic_partial_compare_string(substitutions.array[i].replace.string, data->buffer, substitutions.array[i].replace.used, iki_data.content.array[index]);
      if (status == F_equal_to) break;
    } // for

    if (status == F_equal_to) {
      if (content_only) {
        f_print_dynamic(substitutions.array[i].with, data->main->output.to.stream);
      }
      else {
        f_string_range_t range = macro_f_string_range_t_initialize(iki_data.variable.array[index].start, iki_data.content.array[index].start - 1);

        f_print_dynamic_partial(data->buffer, range, data->main->output.to.stream);

        f_print_dynamic(substitutions.array[i].with, data->main->output.to.stream);

        range.start = iki_data.content.array[index].stop + 1;
        range.stop = iki_data.variable.array[index].stop;

        f_print_dynamic_partial(data->buffer, range, data->main->output.to.stream);
      }
    }
    else {
      f_print_dynamic_partial(data->buffer, ranges.array[index], data->main->output.to.stream);
    }
  }
#endif // _di_iki_read_substitutions_print_

#ifdef __cplusplus
} // extern "C"
#endif
